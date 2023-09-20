#ifndef _NE_HAVAILABLE_CPP_WRAPPER_BUILD_PLANTFORM_BUILD_CONFIG_H_
#define _NE_HAVAILABLE_CPP_WRAPPER_BUILD_PLANTFORM_BUILD_CONFIG_H_

// A set of macros to use for platform detection.
#if defined(__native_client__)
// __native_client__ must be first, so that other OS_ defines are not set.
#define NE_HAV_OS_NACL 1
// OS_NACL comes in two sandboxing technology flavors, SFI or Non-SFI.
// PNaCl toolchain defines __native_client_nonsfi__ macro in Non-SFI build
// mode, while it does not in SFI build mode.
#if defined(__native_client_nonsfi__)
#define NE_HAV_OS_NACL_NONSFI
#else
#define NE_HAV_OS_NACL_SFI
#endif
#elif defined(ANDROID)
#define NE_HAV_OS_ANDROID 1
#elif defined(__APPLE__)
// only include TargetConditions after testing ANDROID as some android builds
// on mac don't have this header available and it's not needed unless the target
// is really mac/ios.
#include <TargetConditionals.h>
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define NE_HAV_OS_IOS 1
#else
#define NE_HAV_OS_MACOSX 1
#endif  // defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#elif defined(__linux__)
#define NE_HAV_OS_LINUX 1
// include a system header to pull in features.h for glibc/uclibc macros.
#include <unistd.h>
#if defined(__GLIBC__) && !defined(__UCLIBC__)
// we really are using glibc, not uClibc pretending to be glibc
#define LIBC_GLIBC 1
#endif
#elif defined(_WIN32)
#define NE_HAV_OS_WIN 1
#elif defined(__Fuchsia__)
#define NE_HAV_OS_FUCHSIA 1
#elif defined(__FreeBSD__)
#define NE_HAV_OS_FREEBSD 1
#elif defined(__NetBSD__)
#define NE_HAV_OS_NETBSD 1
#elif defined(__OpenBSD__)
#define NE_HAV_OS_OPENBSD 1
#elif defined(__sun)
#define NE_HAV_OS_SOLARIS 1
#elif defined(__QNXNTO__)
#define NE_HAV_OS_QNX 1
#elif defined(_AIX)
#define NE_HAV_OS_AIX 1
#elif defined(__asmjs__)
#define NE_HAV_OS_ASMJS
#else
#error Please add support for your platform in build/build_config.h
#endif

#if defined(NE_HAV_OS_FREEBSD) || defined(NE_HAV_OS_NETBSD) || defined(NE_HAV_OS_OPENBSD)
#define NE_HAV_OS_BSD 1
#endif

#if defined(NE_HAV_OS_AIX) || defined(NE_HAV_OS_ANDROID) || defined(NE_HAV_OS_ASMJS) ||    \
    defined(NE_HAV_OS_FREEBSD) || defined(NE_HAV_OS_LINUX) || defined(NE_HAV_OS_MACOSX) || \
    defined(NE_HAV_OS_NACL) || defined(NE_HAV_OS_NETBSD) || defined(NE_HAV_OS_OPENBSD) ||  \
    defined(NE_HAV_OS_QNX) || defined(NE_HAV_OS_SOLARIS)
#define OS_HAV_POSIX 1
#endif

#endif  /* _NE_HAVAILABLE_CPP_WRAPPER_BUILD_PLANTFORM_BUILD_CONFIG_H_ */

