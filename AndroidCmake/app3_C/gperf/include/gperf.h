//
// Created by 王浩 on 2020/3/21.
//

#ifndef __GPERF_HPP__
#define __GPERF_HPP__

#include <sys/types.h>

/*
 * return current system ticks
 */
#ifdef __cplusplus
extern "C" {
#endif

uint64_t GetTicks(void);

#ifdef __cplusplus
}
#endif

#endif //__GPERF_HPP__