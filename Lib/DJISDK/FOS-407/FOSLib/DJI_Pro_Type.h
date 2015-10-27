#ifndef DJI_PRO_TYPE_H
#define DJI_PRO_TYPE_H

#include <stdint.h>

#define DJI_SDK_PRO_VER					0
#define PRO_DATA_MAX_SIZE				512 //TODO: for user define
#define PKG_MAX_SIZE					(PRO_DATA_MAX_SIZE + 16) //data,CRC32,header size
#define PRO_ACK_MAX_SIZE				8	//TODO: for user define
#define ACK_MAX_SIZE					(PRO_DATA_MAX_SIZE + 16)

#define SESSION_AND_MEM_COUNT			30

#define ACK_SESSION_IDLE				0
#define ACK_SESSION_PROCESS				1
#define ACK_SESSION_USING				2

#define POLL_TICK						20  //unit is ms


#define _SDK_MAX_RECV_SIZE          (300)
#define _SDK_SOF                    ((uint8_t)(0xAA))
#define _SDK_CRC_HEAD_SIZE          (2)                 // CRC16
#define _SDK_CRC_DATA_SIZE          (4)                 // CRC32
#define _SDK_HEAD_DATA_LEN          (sizeof(SDKHeader) - 2)
#define _SDK_FULL_DATA_SIZE_MIN     (sizeof(SDKHeader) + _SDK_CRC_DATA_SIZE)

#define _SDK_U32_SET(_addr, _val)   (*((uint32_t*)(_addr)) = (_val))
#define _SDK_U16_SET(_addr, _val)   (*((uint16_t*)(_addr)) = (_val))

#define _SDK_CALC_CRC_HEAD(_msg, _len)   sdk_stream_crc16_calc((const uint8_t*)(_msg), _len)
#define _SDK_CALC_CRC_TAIL(_msg, _len)   sdk_stream_crc32_calc((const uint8_t*)(_msg), _len)

#define DATA_MAX_SIZE 	(1000u)
#define ERR_INDEX       (0xff)
#define EXC_DATA_SIZE	(16u)
#define SET_CMD_SIZE	(2u)
//!@todo Define this micros as a C++ like const variables

typedef struct ProAckParameter
{
    unsigned short session_id : 8;
    unsigned short need_encrypt : 8;
    unsigned short seq_num;
    unsigned int length;
    unsigned char *buf;
}ProAckParameter;

typedef struct ProSendParameter
{
    unsigned short pkg_type : 2;
    unsigned short need_encrypt : 1;
    unsigned short retry_time : 13;
    unsigned short ack_timeout;	//unit is ms
    unsigned int length;
    unsigned char *buf;
    ACK_Callback_Func ack_callback;
}ProSendParameter;

typedef float 	fp32;
typedef double	fp64;
#pragma pack(1)
typedef struct
{
    uint8_t ctrl_flag;
    fp32 	roll_or_x;
    fp32	pitch_or_y;
    fp32	thr_z;
    fp32	yaw;
}api_ctrl_without_sensor_data_t;

typedef struct
{
    fp32	q0;
    fp32	q1;
    fp32	q2;
    fp32	q3;
}sdk_4_16B_data_t;

typedef struct
{
    fp32	x;
    fp32	y;
    fp32	z;
}sdk_3_12B_data_t;

typedef struct
{
    fp64	lati;
    fp64	longti;
    fp32	alti;
    fp32	height;
    unsigned char health_flag;
}sdk_4_24B_data_t;

typedef struct
{
    int16_t	roll;
    int16_t	pitch;
    int16_t	yaw;
    int16_t	throttle;
    int16_t	mode;
    int16_t gear;
}sdk_5_10B_data_t;

typedef struct
{
    int16_t	x;
    int16_t	y;
    int16_t	z;
}sdk_3_6B_data_t;
typedef struct
{
    uint32_t		time_stamp;
    sdk_4_16B_data_t	q;
    sdk_3_12B_data_t	a;
    sdk_3_12B_data_t	v;
    sdk_3_12B_data_t	w;
    sdk_4_24B_data_t	pos;
    sdk_3_12B_data_t	mag;
    sdk_5_10B_data_t	rc;
    sdk_3_12B_data_t	gimbal;
    uint8_t			status;
    uint8_t			battery_remaining_capacity;
    uint8_t			ctrl_device;
}sdk_std_msg_t;
#pragma pack()
typedef int16_t (*func_cmd_handler)(uint8_t cmd_id,uint8_t* pbuf,uint16_t len, req_id_t req_id);
typedef struct _cmd_tab
{
    uint8_t             cmd_id;
    func_cmd_handler    pf_cmd_handler;
}cmd_handler_table_t;

typedef struct _set_tab
{
    uint8_t                cmd_set;
    cmd_handler_table_t*   p_cmd_handler_table;
}set_handler_table_t;

typedef struct
{
        uint8_t     len;
        uint8_t     cmd_set;
        uint8_t     cmd_id;
        uint8_t     data_buf[DATA_MAX_SIZE];
}dji_sdk_data_msg_t;

typedef struct
{
    uint16_t	sequence_number;
    uint8_t	session_id 	: 5;
    uint8_t	need_encrypt	: 1;
    uint8_t	reserve	   	: 2;
}req_id_t;

typedef struct Ack_Session_Queue
{
    unsigned int session_id : 5;
    unsigned int session_status:2;
    unsigned int res:25;
    Memory_Manage_Unit *mmu;
}Ack_Session_Queue;

typedef struct
{
    uint16_t reuse_index;
    uint16_t reuse_count;
    uint16_t recv_index;
    uint8_t comm_recv_buf[_SDK_MAX_RECV_SIZE];
    uint8_t         comm_key[32];
    uint8_t         enc_enabled;
} SDKFilter;

typedef struct
{
    uint32_t	app_id;
    uint32_t	app_api_level;
    uint32_t	app_ver;
    uint8_t		app_bundle_id[32];
}activation_data_t;

typedef void (*ACK_Callback_Func)(ProHeader *pHeader);

typedef struct Memory_Manage_Unit
{
    unsigned char mmu_index;
    unsigned char usage_flag;
    unsigned short res;
    unsigned long start_addr;
    unsigned long end_addr;
}Memory_Manage_Unit;

typedef struct Session_Queue
{
    unsigned int session_id : 5;
    unsigned int usage_flag : 1;
    unsigned int sent_time : 5;
    unsigned int retry_send_time : 5;
    unsigned int ack_timeout : 16;
    Memory_Manage_Unit *mmu;
    ACK_Callback_Func ack_callback;
    unsigned int pre_seq_num;
    unsigned int pre_timestamp;
}Session_Queue;

typedef struct ProHeader
{
    unsigned int sof : 8; 			// 1byte
    unsigned int length : 10;
    unsigned int version : 6; 		// 2byte
    unsigned int session_id : 5;
    unsigned int is_ack : 1;
    unsigned int reversed0 : 2; 	// always 0

    unsigned int padding : 5;
    unsigned int enc_type : 3;
    unsigned int reversed1 : 24;

    unsigned int sequence_number : 16;
    unsigned int head_crc : 16;
}ProHeader;

namespace FOS
{
typedef struct
{
    uint8_t     SOF;
    uint16_t    LEN     :10;
    uint16_t    VER     :6;
    uint8_t     SESSION :5;
    uint8_t     A       :1;
    uint8_t     RES0    :2;
    uint8_t     RADDING :5;
    uint8_t     ENC     :3;
    uint32_t    RES1    :24;
    uint16_t    SEQ;
    uint16_t    CRC16;
    uint8_t*    DATA;
    uint32_t    CRC32;
}N1Frame;

typedef struct
{
    uint8_t SET;
    uint8_t ID;
    uint8_t* DATA;
}FrameData;
typedef struct
{
    uint16_t RETURN;
    uint8_t* ACK;
}FrameACK;

namespace Command
{
typedef uint16_t ACK;
typedef uint8_t SET;
typedef uint8_t ID;
typedef uint16_t MOD;

/*! @code getAPIVersion static data*/
namespace APIVersion
{
const SET set = 0x00;
const ID  id  = 0x00;
const ACK success               = 0x0000;
const ACK unsupport             = 0xFF00;
const ACK noAccredit            = 0xFF01;
const ACK lackOfAccess          = 0xFF02;
}
/*! @code getAPIVersion static data*/
namespace Activation
{
const SET set = 0x00;
const ID  id  = 0x01;
const ACK success              = 0x0000;
const ACK illegalData          = 0x0001;
const ACK encryptData          = 0x0002;
const ACK newDevice            = 0x0003;
const ACK noResponseFromDJI    = 0x0004;
const ACK noInternet           = 0x0005;
const ACK reject               = 0x0006;
const ACK lowAPILevel          = 0x0007;
}
/*! @code obtain control*/
namespace ObtainOrRelease
{
const SET set = 0x01;
const ID  id  = 0x00;
const ACK releaseSuccess = 0x0001;
const ACK obtainSuccess  = 0x0002;
const ACK fail           = 0x0003;
}
/*! @code decode data*/
namespace FlightData
{
typedef struct
{
    float q0;
    float q1;
    float q2;
    float q3;
}Q;
typedef struct
{
    float x;
    float y;
    float z;
}Common;
typedef struct
{
    double latitude;
    double longitude;
    float altitude;
    float height;
    uint8_t health;
}GPS;
typedef struct
{
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t throttle;
    int16_t mode;
    int16_t gear;
}RadioControl;
typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
}Magnet;
typedef struct
{
    uint32_t time;
    Q q;
    Common a;
    Common v;
    Common w;
    GPS gps;
    Magnet mag;
    RadioControl rc;
    Common gimbal;
    uint8_t status;
    uint8_t battery;
    uint8_t device;
}Standard;
}
typedef struct
{

}DecodeFlag;
/*! @code control commands*/
typedef uint8_t Type;//control type
typedef struct
{
    Type H  :2;
    Type V  :2;
    Type Y  :1;
    Type HC :2;
    Type YC :1;
}ControlType;
namespace Control
{
namespace Vertical
{
const Type velocity     = 0x00;
const Type possition    = 0x01;
const Type thrust       = 0x02;
}//Vertical
namespace Horizontal
{
const Type angle        = 0x00;
const Type velocity     = 0x01;
const Type possition    = 0x02;
}//horizontal
namespace Yaw
{
const Type angle        = 0x00;
const Type rate         = 0x01;
}//Yaw
namespace Coordinate
{
const Type ground = 0x00;
const Type body   = 0x01;
}
}
}
}

#endif // DJI_PRO_TYPE_H
