/** @file h_available_interface.h
 * @brief 高可用环境及高可用对象定义
 * @copyright (c) 2021-2022, NetEase Inc. All rights reserved
 * @date 2021/01/05
 */
#ifndef _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_INTERFACE_H_
#define _NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_INTERFACE_H_

#if defined(NE_HAV_OS_MACOSX) || defined(NE_HAV_OS_IOS)
#else
#include <functional>
#endif
#include <string>
#include <vector>
#include "wrappers/cpp_wrapper/build/build_config.h"
#include "wrappers/cpp_wrapper/interface/h_available_def.h"

NE_HAVAILABLE_BEGIN_DECLS

/** @class NEHAvailableEnvironmentSettings
 *  @brief 高可用组件环境初始化配置参数定义
 */
#define BUSINESS_TYPE_LENGTH (32)
#define BUSINESS_TOKEN_LENGTH (128)
#define BUSINESS_PUBLIC_VERSION_LENGTH (128)
#define DATA_PATH_LENGTH (1024)
#define LOG_PATH_LENGTH (1024)
#define SINGLE_REQUEST_DEF_TIMEOUT (7000)             // 单条http请求的超时时间 多链接http请求
#define SINGLE_REQUEST_MIN_TIMEOUT (1000)             // 单条http请求的最小超时时间 多链接http请求
#define SINGLE_REQUEST_MAX_TIMEOUT (30 * 1000)        // 单条http请求的最大超时时间 多链接http请求
#define SINGLE_REQUEST_PREFAIL_DEF_TIMEOUT (2000)     // 单条http请求预判失败的超时时间 多链接http请求
#define SINGLE_REQUEST_PREFAIL_MIN_TIMEOUT (200)      // 单条http请求预判失败的最小超时时间 多链接http请求
#define SINGLE_REQUEST_TIMEOUT_PREFAIL_MIN_DIFF (80)  // 单条http请求预判失败的超时时间与单条http请求的超时时间的差值

#if defined(NE_HAV_OS_MACOSX) || defined(NE_HAV_OS_IOS)
typedef void (*log_writer_t)(const char* const);
typedef log_writer_t LogWriter;
#else
using log_writer_t = std::function<void(const char* const)>;
using LogWriter = log_writer_t;
#endif

typedef struct _NEHAvailableEnvironmentSettings {
    EMBoolean enable_httpdns;  /**< 是否开启 httpdns功能 */
    bool only_https_supported; /**< 是否只支持https请求,开启后,只有https请求会被发送 ip类型的http请求目前不受限制*/
    char business_type[BUSINESS_TYPE_LENGTH];      /**< 业务版本标识 im_g1 (业务_版本) 业务：im、av等；版本：g1、g2等 */
    char bacbusiness_token[BUSINESS_TOKEN_LENGTH]; /**< 应用标识,一般是appkey*/
    char bacbusiness_public_version[BUSINESS_PUBLIC_VERSION_LENGTH]; /**< 外部版本号 */
    int32_t internal_version;                                        /**< 内部版本号 */
    int32_t protocol_version;                                        /**< 协议版本号 */
    int32_t client_type;                                             /**< 终端类型 */
    char appdata_path[DATA_PATH_LENGTH];                             /**< 数据缓存目录 */
    char log_path[LOG_PATH_LENGTH];                                  /**< 日志缓存目录 */
    LogWriter log_writer;
    EMBoolean try_http_req_netunav;
    int32_t sreq_timeout_ms;                   /**< 单条http请求的超时时间 多链接http请求*/
    int32_t sreq_pred_fail_time_ms;            /**< 单条http请求预判失败的超时时间 多链接http请求*/
    EMBoolean http_req_ip_preferred;           /**< http请求是否ip优先 kEMBUnknown/kEMBFalse:不开启 kEMBTrue:开启*/
    EMBoolean enable_exception_data_reporting; /**< 是否开启异常数据上报 kEMBUnknown/kEMBFalse:不开启 kEMBTrue:开启*/
} NEHAvailableEnvironmentSettings;

struct HAVExceptionDataItem {
    int32_t operation_type;
    std::string target;
    int32_t code;
    std::string description;
    std::string context;
};
using HAVExceptionDataItemList = std::vector<HAVExceptionDataItem>;
struct HAVExceptionData {
    std::string user_id;
    std::string trace_id;
    std::string process_id;
    int32_t action;
    int64_t duration;
    int64_t start_time;
    int32_t state;
    int32_t exception_service;
    HAVExceptionDataItemList extension_list;
};
#if defined(NE_HAV_OS_MACOSX) || defined(NE_HAV_OS_IOS)
typedef void (*hav_exception_data_reporter_t)(const HAVExceptionData&);
typedef hav_exception_data_reporter_t HAVExceptionDataReporter;
#else
using hav_exception_data_reporter_t = std::function<void(const HAVExceptionData&)>;
using HAVExceptionDataReporter = hav_exception_data_reporter_t;
#endif

class INEHAvailableLBSService;

/** @class INEHAvailableObject
 *  @brief  高可用环境对象定义
 */
class INEHAvailableObject {
public:
    /** @fn void SetNetworkChanged(enum EMAddressFamily addr_family)
     * 设置网络环境发生了变化
     * @param[in]  addr_family 网络变更过后的类型 ipv4/ipv6/auto 定义详情参考EMAddressFamily
     * @return void
     */
    virtual void SetNetworkChanged(enum EMAddressFamily addr_family) = 0;

    /** @fn INEHAvailableLBSService* GetLBSService() const
     * 获取LBS服务
     * @return LBS服务对象指针
     * @note 需判断返回结果是否为nullptr
     */
    virtual INEHAvailableLBSService* GetLBSService() = 0;

    /** @fn void ReleaseLBSService()
     * 释放LBS服务
     * @return void
     */
    virtual void ReleaseLBSService() = 0;

    /** @fn void UpdatebacBusinessToken(const char* business_token)
     * 更新环境业务标识
     * @param[in]  business_token
     * @return void
     */
    virtual void UpdatebacBusinessToken(const char* business_token) = 0;
};

/** @fn bool StartHAvailableEnvironment(const NEHAvailableEnvironmentSettings& settings)
 * 初始化高可用环境
 * @param[in]  settings 详细见NEHAvailableEnvironmentSettings定义
 * @return bool
 * @note 单独进程内只需初始化一次,会进行http dns 等模块的加载
 */
H_AV_COMP_API EnvironmentHandle StartHAvailableEnvironment(const NEHAvailableEnvironmentSettings& settings);

/** @fn void SetExceptionDataReporter(const HAVExceptionDataReporter& reporter)
 * 设置异常数据上报回调
 * @param[in]  reporter 详细见HAVExceptionDataReporter定义
 * @return void
 */
H_AV_COMP_API void SetExceptionDataReporter(const HAVExceptionDataReporter& reporter);

/** @fn std::string HAVExceptionDataToJsonString(const HAVExceptionData& data)
 * 异常数据转换为json字符串
 * @param[in]  data 详细见HAVExceptionData定义
 * @return std::string
 */
H_AV_COMP_API std::string HAVExceptionDataToJsonString(const HAVExceptionData& data);

/** @fn void GetHAvailableObject()
 * 获取高可用对象
 * @return 高可用对象指针
 */
H_AV_COMP_API INEHAvailableObject* GetHAvailableObject(EnvironmentHandle handle = 1);

/** @fn void ExitHAvailableEnvironment()
 * 退出/清理高可用环境
 * @return void
 */
H_AV_COMP_API void ExitHAvailableEnvironment(EnvironmentHandle handle = 1);

NE_HAVAILABLE_END_DECLS

#endif /*_NE_HAVAILABLE_CPP_WRAPPER_H_AVAILABLE_INTERFACE_H_*/
