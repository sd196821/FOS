#if 0
#ifndef N1SDK_H
#define N1SDK_H
#include "usart.h"
#include "DJI_Pro_Type.h"
#include "encodeType.h"
#include "littletask.h"



using namespace USART;

extern volatile uint32_t ms;
namespace FOS
{
class N1SDK
{
public:
    N1SDK(usart *SDK);
    void setApp(uint32_t appid, uint32_t level, uint32_t version, char* budleID, char* keyptr);
    void freePoll(void);
private:
    virtual void send(unsigned char *buf);
    virtual unsigned int getTimestamp(void){return ms;}
    virtual bool get(unsigned char &data);
    virtual void preconvert(sdk_std_msg_t &data);
private://stream recv functions
    void byteHandle(uint8_t in_data);
    void byteStream(SDKFilter* p_filter, uint8_t in_data);
    void storeData(SDKFilter* p_filter, uint8_t in_data);
    void checkStream(SDKFilter* p_filter);
    void verifyHead(SDKFilter* p_filter);
    void sdk_call_data_app(SDKFilter* p_filter);
    void Pro_Link_Recv_Hook(ProHeader *header);
    void sdk_stream_verify_data(SDKFilter* p_filter);
    void sdk_stream_update_reuse_part(SDKFilter* p_filter);
    void sdk_stream_shift_data(SDKFilter* p_filter);
    void Free_Send_Session(Session_Queue * session);
    void Free_Send_MMU(Memory_Manage_Unit *mmu);
    void Pro_Request_Interface(ProHeader *header);
    void App_Recv_Req_Data(ProHeader *header);
    uint8_t find_set_index(uint8_t cmd_set,set_handler_table_t* p_set_handler_tab);
    uint8_t find_cmd_index(uint8_t cmd_id,cmd_handler_table_t* p_cmd_handler_tab);
    Ack_Session_Queue * Search_Ack_Session(unsigned char session_id);
private://encode functions
    static void sdk_stream_codec(SDKFilter* p_filter, ProHeader *p_head, ptr_aes256_codec codec_func);
    void aes256_init(aes256_context *ctx, uint8_t *k);
    void aes_expandEncKey(uint8_t *k, uint8_t *rc);
    void aes256_done(aes256_context *ctx);
    void aes256_decrypt_ecb(aes256_context *ctx, uint8_t *buf);
    void sdk_stream_prepare(SDKFilter* p_filter, ProHeader *p_head);
    uint8_t rj_xtime(uint8_t x);
    void aes_subBytes(uint8_t *buf);
    void aes_subBytes_inv(uint8_t *buf);
    void aes_addRoundKey(uint8_t *buf, uint8_t *key);
    void aes_addRoundKey_cpy(uint8_t *buf, uint8_t *key, uint8_t *cpk);
    void aes_shiftRows(uint8_t *buf);
    void aes_shiftRows_inv(uint8_t *buf);
    void aes_mixColumns(uint8_t *buf);
    void aes_mixColumns_inv(uint8_t *buf);
    void aes_expandEncKey(uint8_t *k, uint8_t *rc);
    void aes_expandDecKey(uint8_t *k, uint8_t *rc);
private://stream send functions
    void Send_Poll(void);
    void spin_callback(void);
    void App_Send_Ack(req_id_t req_id, uint8_t *ack, int len);
    void App_Send_Data(unsigned char flag, uint8_t is_enc, unsigned char  cmd_set, unsigned char cmd_id,unsigned char *pdata,int len,ACK_Callback_Func ack_callback, int timeout ,int n);
    int Pro_Send_Interface(ProSendParameter *parameter);
    unsigned short sdk_encrypt_interface(uint8_t *pdest, const uint8_t *psrc,
                                         uint16_t w_len,uint8_t is_ack,uint8_t is_enc,uint8_t session_id,
                                         uint16_t seq_num);
    Session_Queue * Request_Send_Session(unsigned short size);
    Memory_Manage_Unit *Request_Send_MMU(unsigned short size);

    int Pro_Ack_Interface(ProAckParameter *parameter);
    Memory_Manage_Unit *Request_Ack_MMU(unsigned short size);
private:
    usart *sdk;
    SDKFilter serial_sdk;
    activation_data_t activation;
    Session_Queue Send_Session_Common_Tab;
    Session_Queue Send_Session_Tab[session];
    dji_sdk_data_msg_t recv_data;
    set_handler_table_t* app_set_tab_ptr;
    cmd_handler_table_t* app_cmd_tab_ptr;
    unsigned char DJIbuffer[bufferSize];
    unsigned char *key;

    sdk_std_msg_t recv_sdk_std_msgs;
    cmd_handler_table_t cmd_handler_tab[];
    set_handler_table_t set_handler_tab[];
    Ack_Session_Queue Ack_Session_Tab[SESSION_AND_MEM_COUNT + 1];
    Memory_Manage_Unit Send_MMU_Tab[SESSION_AND_MEM_COUNT];
    unsigned char Send_Global_Memory[SESSION_AND_MEM_COUNT * PKG_MAX_SIZE];
    Memory_Manage_Unit Ack_MMU_Tab[SESSION_AND_MEM_COUNT + 1];
    unsigned char Send_Global_Common_Memory[PKG_MAX_SIZE];
    unsigned char Ack_Global_Memory[(SESSION_AND_MEM_COUNT + 1) * PKG_MAX_SIZE];
    unsigned char Pro_Encode_Data[1024];
    req_id_t nav_force_close_req_id;
    int simple_task_num;
private:
    static const size_t session = 30;
    static const size_t bufferSize = 1024;


};
}

#endif // N1SDK_H
#endif
