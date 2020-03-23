### 需要的资料
- 谷歌推出的framesequence
    -   https://android.googlesource.com/platform/frameworks/ex/+/refs/tags/android-9.0.0_r54/framesequence/
- 谷歌推出的giflib
    -   https://android.googlesource.com/platform/external/giflib/+/refs/tags/android-9.0.0_r54
-   谷歌推出的webp
     -   https://android.googlesource.com/platform/external/webp/+/refs/tags/android-9.0.0_r54

- 这个需要翻墙，如果不能翻墙可以直接从资料中获取。如果不会编译，可以从app的jniLibs中获取四个平台的so

### 一些解
#### app module
- 是为了生成so
- 本需求只为了完成gif的功能
 - 没有依赖webp
 - 删除了framesequence的webp的代码 FrameSequence_webp.h，FrameSequence.cpp
- 为了练习cmake，本次编译全部都是使用cmake编译的。代码中删除了.mk、.bp的文件。

#### giflib module
- 就是使用so
- 将app中的so拷贝到giflib的jniLibs中。
- 将framesequence的src/android/support/rastermill文件下的FrameSequence.java、FrameSequenceDrawable.java拷贝到项目中。android/support/rastermill的路径不可以变。
- 在配合glide就可以使用了。
- 项目中有一个14m的gif。可以很顺画的显示


#### 感觉得缺点
- 感觉so有点儿大。一个为了实现gif的功能so就得1m多。
- 这个1m的前提是删除了framesequence
中webp相关的代码，因为删除了webp的代码，也没有编译webp的库。这样还需要1m多，确实有点儿，大还是需要自己衡量apk的大小
- 如果还是嫌大可以自己写c的代码来调用giflib这个库。就不使用framesequence
的代码了。



