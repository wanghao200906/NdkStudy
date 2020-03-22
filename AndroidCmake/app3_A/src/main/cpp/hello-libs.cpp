#include <jni.h>
#include <string>
#include <android/log.h>
#include <cstring>
#include <cinttypes>
#include <android/log.h>
#include <gmath.h>
#include <gperf.h>
#include <string>


#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "hello-libs::", __VA_ARGS__))

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   com/androidcmake/example/NdkUtils.java
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_androidcmake_example_NdkUtils_getStringJni(JNIEnv *env, jclass thiz) {
    // Just for simplicity, we do this right away; correct way would do it in
    // another thread...
    auto ticks = GetTicks();

    LOGI("ticks: %" PRIu64, ticks);
    for (auto exp = 0; exp < 32; ++exp) {
        volatile unsigned val = gpower(exp);
        (void) val;  // to silence compiler warning
    }
    ticks = GetTicks() - ticks;

    LOGI("calculation time: %" PRIu64, ticks);

    return env->NewStringUTF("Hello from JNI LIBS!");
}