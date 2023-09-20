/** @file h_available_lbs_interface.h
 * @brief LBS服务对象定义
 * @copyright (c) 2021-2022, NetEase Inc. All rights reserved
 * @date 2021/01/05
 */

#ifndef _NE_HAVAILABLE_BUSINESS_H_AVAILABLE_LBS_INTERFACE_H_
#define _NE_HAVAILABLE_BUSINESS_H_AVAILABLE_LBS_INTERFACE_H_

#include "wrappers/cpp_wrapper/build/build_config.h"
#include "wrappers/cpp_wrapper/interface/h_available_def.h"

NE_HAVAILABLE_BEGIN_DECLS

#define LBS_HOST_LENGTH (1024)
#define LBS_RESPONSE_LENGTH (1024 * 4)
#define LBS_ADDR_LENGTH (512)
#define LBS_BACKUP_ADDR_COUNT (5)
#define LINK_ADDR_LENGTH (128)
#define LINK_ADDR_COUNT (10)
#define LBS_MSG_DELAY_STATICS_HOST_LENGTH (512)
#define LBS_MSG_DELAY_STATICS_API_LENGTH (512)
#define LBS_MSG_DELAY_STATICS_ENVIRONMENT_LENGTH (128)
#define LBS_ACCID_LENGTH (256)

/** @class NEHAvailableLBSSettings
 *  @brief LBSService 私有化配置参数定义
 */
typedef struct _NEHAvailableLBSSettings {
    /// 是否启用了私有化环境
    bool using_private;
    /// 主lbs请求地址
    char lbs_main_addr[LBS_ADDR_LENGTH];
    /// 备用lbs地址列表
    char lbs_backup_addrs[LBS_BACKUP_ADDR_COUNT][LBS_ADDR_LENGTH];
    /// 缺省连接地址
    char default_link[LINK_ADDR_LENGTH];
    /// 缺省 ipv6 连接地址
    char default_link_ipv6[LINK_ADDR_LENGTH];
    /// 连接地址列表,如果可以拿到传下来
    char link_list[LINK_ADDR_COUNT][LINK_ADDR_LENGTH];
    /// 当前网络连接类型
    enum EMAddressFamily addr_family;
    /// 单条http请求的超时时间 多链接http请求
    int32_t sreq_timeout_ms;
    /// 单条http请求预判失败的超时时间 多链接http请求
    int32_t sreq_pred_fail_time_ms;
    /// lbs host
    char def_lbs_host[LBS_HOST_LENGTH];
} NEHAvailableLBSSettings;

/** @class NEHAvailableLBSMSGDelayStaticsInfo
 *  @brief LBSService 消息时延上报参数定义
 */
typedef struct _NEHAvailableLBSMSGDelayStaticsInfo {
    /// 是否开启了上报功能
    bool enable;
    /// 是否开启了上报域名 形如 statistic.live.126.net
    char host[LBS_MSG_DELAY_STATICS_HOST_LENGTH];
    /// 是否开启了上报 API 形如 /statics/report/im/sdk/msgreceived
    char api[LBS_MSG_DELAY_STATICS_API_LENGTH];
    /// 当前环境描述，上报数据时会用到
    char desc[LBS_MSG_DELAY_STATICS_ENVIRONMENT_LENGTH];
} NEHAvailableLBSMSGDelayStaticsInfo;

/** @class NEHAvailableLBSRequestErrorInfo
 *  @brief LBSService lbs请求错误信息定义
 */
typedef struct _NEHAvailableLBSRequestErrorInfo {
    /// 错误码
    int error_code;
    /// 请求的 URL
    char* url;
    /// 应答的 head 信息,如果存在
    char* head;
    /// 应答的 body 信息,如果存在
    char* body;
} NEHAvailableLBSRequestErrorInfo;

/** @class INEHAvailableLBSService
 *  @brief LBS服务对象定义
 */
class INEHAvailableLBSService {
public:
    typedef void (*FunTLBSUpdateCallback)(int /*code*/, const char* const /*response*/, void* custom_data);
    typedef void (*FunTLBSAccIDGetter)(void* custom_data, char* accid);
    typedef void (*FunTLBSRequestErrorCollector)(void* custom_data, const NEHAvailableLBSRequestErrorInfo* error_info);

public:
    /** @fn bool Init()
     * LBS初始化接口
     * @param[in]  settings sdk私有化配置读取对象
     * @return bool
     * @note 初始化操作会进行lbs的更新等操作
     */
    virtual bool Init(const NEHAvailableLBSSettings& settings) = 0;
    /** @fn void Update(enum EMAddressFamily addr_family)
     * LBS更新接口
     * @param[in]  addr_family 网络ip类型 httpdns会用到
     * @return void
     * @note
     */
    virtual void Update(enum EMAddressFamily addr_family, bool force = false) = 0;

    /** @fn void RegUpdateResponse(FunTLBSUpdateCallback cb)
     * 注册LBS更新回调
     * @param[in]  cb 回调
     * @param[in] custom_data 用户自定义数据，sdk只负责透传
     * @return void
     * @note
     */
    virtual void RegUpdateResponse(FunTLBSUpdateCallback cb, void* custom_data) = 0;

    /** @fn void SetAccIDGetter(FunTLBSAccIDGetter cb, void* custom_data)
     *  获取accid 的接口
     * @param[in]  cb 回调
     * @param[in] custom_data 用户自定义数据，sdk只负责透传
     * @return void
     * @note
     */
    virtual void SetAccIDGetter(FunTLBSAccIDGetter cb, void* custom_data) = 0;

    /** @fn void SetRequestErrorCollector(FunTLBSRequestErrorCollector cb, void*
     * custom_data) 设置LBS请求错误信息的收集器
     * @param[in]  cb 回调
     * @param[in] custom_data 用户自定义数据，sdk只负责透传
     * @return void
     * @note
     */
    virtual void SetRequestErrorCollector(FunTLBSRequestErrorCollector cb, void* custom_data) = 0;

    /** @fn const char* GetLBSResponse()
     * 获取lbs的应答内容
     * @param[in] from_cache 是否从缓存读取
     * @res[out] res 内容 上层应该分配足够的空间
     * @return void
     * @note 同步接口
     */
    virtual void GetLBSResponse(bool from_cache, char* res) = 0;

    /** @fn bool GetLinkAddress(char* ip, int* port, enum EMAddressFamily
     * *addr_family) 获取连接地址
     * @param[out]  ip ip地址或域名
     * @param[out]  port 连接的端口
     * @param[in/out]  addr_family
     * 要获取的地址类型,如果是ip会返回ip的类型定义参考EMAddressFamily定义
     * @return bool
     * @note 调用此接口会进行连接地址的切换
     */
    virtual bool GetLinkAddress(char* ip, int* port, enum EMAddressFamily* addr_family) = 0;

    virtual void GetNOSDL(char* nos_dl) = 0;

    virtual void GetNOSDLList(char* nos_dl_list) = 0;

    virtual void GetNOSList(char* nos_list) = 0;

    virtual void GetName(char* name) = 0;

    virtual void GetDesc(char* desc) = 0;

    virtual int GetLinkCount() = 0;

    /** @fn bool GetCurrentLinkAddress(char* ip, int* port, enum
     * EMAddressFamily *addr_family) 获取当前连接地址
     * @param[out]  ip ip地址或域名
     * @param[out]  port 连接的端口
     * @param[out]  addr_family
     * 如果是ip会返回ip的类型定义参考EMAddressFamily定义
     * @return bool
     * @note
     */
    virtual bool GetCurrentLinkAddress(char* ip, int* port, enum EMAddressFamily* addr_family) = 0;

    /** @fn void OnCurrentLinkConnectSucceed(char* ip, int port)
     * sdk告诉LBS服务当前连接成功
     * @return void
     * @note
     * 调用此接口后LBS服务会记录当前连接地址，下次重连时会优先使用此连接地址
     */
    virtual void OnCurrentLinkConnectSucceed(const char* ip, int port) = 0;

    /** @fn void GetMessageDelayStaticsInfo(NEHAvailableLBSMSGDelayStaticsInfo*
     * info) 获取消息时延上报信息
     * @param[out]  info 上报信息
     * @return void
     * @note
     * 调用此接口后LBS服务会记录当前连接地址，下次重连时会优先使用此连接地址
     */
    virtual void GetMessageDelayStaticsInfo(NEHAvailableLBSMSGDelayStaticsInfo* info) = 0;
};

NE_HAVAILABLE_END_DECLS

#endif /*_NE_HAVAILABLE_BUSINESS_H_AVAILABLE_LBS_INTERFACE_H_ */
