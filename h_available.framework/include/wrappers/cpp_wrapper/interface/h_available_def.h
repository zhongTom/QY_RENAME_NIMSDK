/** @file h_available_def.h
 * @brief 高可用环境及公共数据定义
 * @copyright (c) 2021-2022, NetEase Inc. All rights reserved
 * @date 2021/01/05
 */
#ifndef _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_DEF_H_
#define _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_DEF_H_

#include "wrappers/cpp_wrapper/build/build_config.h"
#include <sys/types.h>

#ifndef _MSC_VER
// stdint.h is part of C99 but MSVC doesn't have it.
#include <stdint.h>  // For intptr_t.
#endif

/* define int types */
#if defined(__GNUC__)

#ifndef _STDINT_H

/* FreeBSD has these C99 int types defined in /sys/inttypes.h already */
#ifndef _SYS_TYPES_H
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#else
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
#endif  // _SYS_TYPES_H

#endif  // _STDINT_H

#elif defined(_MSC_VER) && (_MSC_VER != 1900)  // not vs2015
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed __int64 int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

// below vs2015 only
#if _MSC_VER < 1900

/* the following definitions are from VS2010's stdint.h */
#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED
#ifdef _WIN64
typedef __int64 intptr_t;
#else  /* _WIN64 */
typedef _W64 int intptr_t;
#endif /* _WIN64 */
#endif /* _INTPTR_T_DEFINED */

#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64 uintptr_t;
#else  /* _WIN64 */
typedef _W64 unsigned int uintptr_t;
#endif /* _WIN64 */
#endif /* _UINTPTR_T_DEFINED */

#endif  //_MSC_VER < 1900

#endif  // COMPILER_GCC/COMPILER_MSVC
NE_HAVAILABLE_BEGIN_DECLS
enum EMBoolean { kEMBFalse = -1, kEMBUnknown = 0, kEMBTrue = 1 };

/** @enum EMAddressFamily 地址族定义 */
enum EMAddressFamily {
    kUnKnown, /**< 未知，不能判断或者给的address是域名 */
    kIPV4,    /**< ipv4 */
    kIPV6     /**< ipv6 */
};

typedef int EnvironmentHandle;
#define InvalidEnvironmentHandle (0)

NE_HAVAILABLE_END_DECLS

#endif /*_NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_DEF_H_*/
