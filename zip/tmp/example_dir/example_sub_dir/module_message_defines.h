#ifndef MODULE_MESSAGE_DEFINES_HHH
#define MODULE_MESSAGE_DEFINES_HHH

typedef enum
{
    MSG_TYPE_LOG = 0x0,

    //用于文件监控
    MSG_TYPE_MONITOR,
    //用于进程监控
    MSG_TYPE_DISCOVERY,
	
    //用于 KV_LOGIN 
	MSG_TYPE_CENTER_AGENT,

	//用于 RPC_SERVER 测试
	MSG_TYPE_RPC_SERVER_TEST,
    
    // 与 reporter 相关
    MSG_TYPE_REPORTER,
    
    // 与扫描相关
    MSG_TYPE_VIRUSSCAN,
    
    // 用于Linux进程网络信息监控
    MSG_TYPE_EDR_SYSINFO,

    // file digest 相关
    MSG_TYPE_FILE_DIGEST,

	// usb
	MSG_TYPE_USB_STORAGE,

    // TODO: add message types here, and maximum is 255.
    MESSAGE_TYPE_TOTAL,    
}module_message_type_t;

typedef enum 
{
	BASE_CATEGORY = 0,
	CATEGORY_TOKEN,
	CATEGORY_TASK,
    CATEGORY_VIRUS
}message_category_t;

typedef enum
{
    LOG_MESSAGE = 0,
	
	MESSAGE_CATEGORY,
	
    /*******************************  用于文件监控模块的消息 *******************************/
    //用于描述当前发生的事件，详细定义如下
    MONITOR_MESSAGE_EVENT,
    //描述新建目录，删除目录，新建文件，删除文件，修改文件的目录
    MONITOR_MESSAGE_PATH,
    //复制文件或目录时的原目录
    MONITOR_MESSAGE_FROM,
    //复制文件或目录时的新目录
    MONITOR_MESSAGE_TO,
    /*******************************  用于文件监控模块的消息 *******************************/
    
    /*******************************  用于进程监控模块的消息 *******************************/
    //描述进程启动，接触
    DISCOVERY_MESSAGE_EVENT,
    //进程所在的路径
    DISCOVERY_MESSAGE_PATH,
    //进程启动时的参数
    DISCOVERY_MESSAGE_CMD,
    //进程ID
    DISCOVERY_MESSAGE_PID,
    /*******************************  用于进程监控模块的消息 *******************************/
    
	/*******************************  用于控制中心通信模块的消息 ***************************/
	CENTER_MESSAGE_TASK_CMD,
	CENTER_MESSAGE_TASK_PARAMS,
	CENTER_MESSAGE_NODE_STATUS,
	CENTER_MESSAGE_TASK_RESULT,
	CENTER_MESSAGE_TEST2,

	CENTER_MESSAGE_TOKEN,
	/*******************************  用于控制中心通信模块的消息 ***************************/
    
	/******************************* 用于 RPC_SERVER 消息 **********************************/
	RPC_MESSAGE_CONN_INDEX,

	// RPC_CMD CODE
	RPC_CMD,
	//RPC_SUBCMD CODE

	RPC_SUBCMD,
	

	//RPC_KEY_CODE
   	RPC_MESSAGE_RPCKEY_TOKEN,
	RPC_MESSAGE_RPCKEY_INT,
	RPC_MESSAGE_RPCKEY_CHAR,
	/******************************* 用于 RPC_SERVER 消息 **********************************/

    /*******************************  用于Linux进程网络监控模块 ***************************/
    //进程基础信息
    DISCOVERY_MESSAGE_PROC_BASE_INFO,
    //网络基础信息
    DISCOVERY_MESSAGE_NET_BASE_INFO,
    /*******************************  用于Linux进程网络监控模块 ***************************/

	/*******************************  用于上报模块 ***************************/
    REPORTER_MESSAGE_URL,
    REPORTER_MESSAGE_TYPE,
    REPORTER_MESSAGE_DATA,
	/*******************************  用于上报模块 ***************************/
    
    /*******************************  用于病毒扫描 ***************************/
    VIRUSSCAN_MESSAGE_DATA,
	/*******************************  用于病毒扫描 ***************************/
    
    /* 查询存储 file digest 相关 */
    FILE_DIGEST_DATA_SET,
    FILE_DIGEST_DATA_GET,
    /* 查询存储 file digest 相关 */

	/* usb */
	USBSTORAGE_EVENT,
	USBSTORAGE_DATA,
	USBSTORAGE_FLAG,
	/* usb */

    // TODO: Add new name indexes here
    TOTAL_PROPERTY_INDEX_COUNT,
}property_name_index_t;

static const char* g_p_property_names[] =
{
    "LOG_MESSAGE",
    
	"MESSAGE_CATEGORY",
    /*******************************  用于文件监控模块的消息 *******************************/
    //用于描述当前发生的事件，详细定义如下
    "MONITOR_MESSAGE_EVENT",
    //描述新建目录，删除目录，新建文件，删除文件，修改文件的目录
    "MONITOR_MESSAGE_PATH",
    //复制文件或目录时的原目录
    "MONITOR_MESSAGE_FROM",
    //复制文件或目录时的新目录
    "MONITOR_MESSAGE_TO",
    /*******************************  用于文件监控模块的消息 *******************************/
    
    /*******************************  用于进程监控模块的消息 *******************************/
    //描述进程启动，接触
    "DISCOVERY_MESSAGE_EVENT",
    //进程所在的路径
    "DISCOVERY_MESSAGE_PATH",
    //进程启动时的参数
    "DISCOVERY_MESSAGE_CMD",
    //进程ID
    "DISCOVERY_MESSAGE_PID",
    /*******************************  用于进程监控模块的消息 *******************************/
    
	/*******************************  用于控制中心通信模块的消息 ***************************/
	"CENTER_MESSAGE_TASK_CMD",
	"CENTER_MESSAGE_TASK_PARAMS",
	"CENTER_MESSAGE_NODE_STATUS",
	"CENTER_MESSAGE_TASK_RESULT",
	"CENTER_MESSAGE_TEST2",
	"CENTER_MESSAGE_TOKEN",
	/*******************************  用于控制中心通信模块的消息 ***************************/

	/******************************* 用于 RPC_SERVER 消息 **********************************/
	"RPC_MESSAGE_CONN_INDEX",
	"RPC_CMD",
	"RPC_SUBCMD",

	
	// RPC KER CODE 
	"RPC_MESSAGE_RPCKEY_TOKEN",
	"RPC_MESSAGE_RPCKEY_INT",
	"RPC_MESSAGE_RPCKEY_CHAR",

	/****************************** 用于 RPC_SERVER 消息 ***********************************/

    /*******************************  用于Linux进程网络监控模块 ***************************/
    //进程基础信息
    "DISCOVERY_MESSAGE_PROC_BASE_INFO",
    //网络基础信息
    "DISCOVERY_MESSAGE_NET_BASE_INFO",
    /*******************************  用于Linux进程网络监控模块 ***************************/


	/*******************************  用于上报模块 ***************************/
    "REPORTER_MESSAGE_URL",
    "REPORTER_MESSAGE_TYPE",
    "REPORTER_MESSAGE_DATA",
	/*******************************  用于上报模块 ***************************/

    /*******************************  用于病毒扫描 ***************************/
    "VIRUSSCAN_MESSAGE_DATA",
	/*******************************  用于病毒扫描 ***************************/

    /* 查询存储 file digest 相关 */
    "FILE_DIGEST_DATA_SET",
    "FILE_DIGEST_DATA_GET",
    /* 查询存储 file digest 相关 */

	/* usb */
	"USBSTORAGE_EVENT",
	"USBSTORAGE_DATA",
	"USBSTORAGE_FLAG",
	/* usb */

    // TODO: Add new names here
    0,
};

#endif

