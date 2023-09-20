#ifndef _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_BUILD_BUILD_CONFIG_H_
#define _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_BUILD_BUILD_CONFIG_H_

#include "wrappers/cpp_wrapper/build/plantform_build_config.h"
#if defined(H_AV_COMP_DLL)
#if defined(NE_HAV_OS_WIN)
#define H_AV_COMP_API_HIDDEN
#if defined(H_AV_COMP_EXPORTS)
#define H_AV_COMP_API __declspec(dllexport)
#else
#define H_AV_COMP_API __declspec(dllimport)
#endif  // defined(H_AV_COMP_EXPORTS)

#else  // defined(WIN32)
#if defined(H_AV_COMP_EXPORTS)
#define H_AV_COMP_API __attribute__((visibility("default")))
#define H_AV_COMP_API_HIDDEN __attribute__((visibility("hidden")))
#else
#define H_AV_COMP_API
#define H_AV_COMP_API_HIDDEN
#endif  // defined(H_AV_COMP_EXPORTS)
#endif

#else  // defined(H_AV_COMP_DLL)
#define H_AV_COMP_API
#define H_AV_COMP_API_HIDDEN
#endif

#define NE_HAVAILABLE_BEGIN_DECLS namespace ne_h_available {
#define NE_HAVAILABLE_END_DECLS }
#define USING_NE_HAVAILABLE using namespace ne_h_available;
#define NE_HAVAILABLE ne_h_available
#define _IN_
#define _IN_OUT_
#define _OUT_
#endif /* _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_BUILD_CONFIG_H_ */
