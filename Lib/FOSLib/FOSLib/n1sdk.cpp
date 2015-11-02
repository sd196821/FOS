#if 0
#include "n1sdk.h"
#include "DJI_Pro_Type.h"
#include "encodeType.h"
#include <stdio.h>
#include <string.h>
extern usart debug;
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
int fputc(int ch,FILE *f)
{
    debug.print(ch);
    return ch;
}
int GetKey(void)
{
    uint8_t data;
    int ans;
    while(!debug.getRx()->read(data));
    ans = data;
    return ans;
}
#ifdef __cplusplus
}
#endif //__cplusplus

namespace FOS
{
cmd_handler_table_t N1SDK::cmd_handler_tab[] =
{
    {0x00,sdk_std_msgs_handler				},
    {0x01,nav_force_close_handler			},
    {ERR_INDEX,NULL							}
};

/* cmd set table */
set_handler_table_t N1SDK::set_handler_tab[] =
{
    {0x02,cmd_handler_tab					},
    {ERR_INDEX,NULL							}
};

N1SDK::N1SDK(usart *SDK)
{
    sdk = SDK;
    unsigned char i;

    for(i = 0; i < SESSION_AND_MEM_COUNT; i ++)
    {
        Send_Session_Tab[i].session_id = i + 2;
        Send_Session_Tab[i].usage_flag = 0;
        Send_Session_Tab[i].pre_seq_num = 0x10000;

        Send_MMU_Tab[i].mmu_index = i;
        Send_MMU_Tab[i].usage_flag = 0;
        Send_MMU_Tab[i].start_addr = (unsigned long)&Send_Global_Memory[i * PKG_MAX_SIZE];
    }

    Send_Session_Common_Tab.usage_flag = 0;
    Send_Session_Common_Tab.session_id = 1;
    Send_Session_Common_Tab.ack_callback = 0;

    for(i = 0; i < (SESSION_AND_MEM_COUNT + 1); i ++)
    {
        Ack_Session_Tab[i].session_id = i + 1;
        Ack_Session_Tab[i].session_status = ACK_SESSION_IDLE;
        Ack_MMU_Tab[i].mmu_index = i;
        Ack_MMU_Tab[i].usage_flag = 0;
        Ack_MMU_Tab[i].start_addr =  (unsigned long)&Ack_Global_Memory[i * PKG_MAX_SIZE];
    }
    LittleTask sendPoll(Send_Poll,5,10,0);
    LittleTask recv(CmdRecvThread,10,10,5);
    LittleTask callback(spin_callback,5,50,15);
    sendPoll.start();
    recv.start();
    callback.start();
}

void N1SDK::setApp(uint32_t appid, uint32_t level, uint32_t version, char *budleID, char *keyptr)
{
    activation.app_id = appid;//0xF7B36;
    activation.app_api_level = level;//2;
    activation.app_ver = version;//1;
    memcpy(activation.app_bundle_id,budleID/*"1234567890123456789012"*/, 32);
    key = keyptr;//"821c8c3abeb6e340637b01f908ddeefb6c76d18d5f289e5cdb3cd5756a17bef5";
}

void N1SDK::freePoll()
{
    uint8_t data;
    while(get(data))
    {
        byteHandle(data);
    }
}

void N1SDK::send(unsigned char *buf)
{
    ProHeader *pHeader = (ProHeader *)buf;
    size_t len = pHeader->length;
    for(int i = 0; i < len; ++i)
    {
        sdk->print(buf[i]);
    }
}

bool N1SDK::get(unsigned char &data)
{
    return sdk->getRx()->read(data);
}

void N1SDK::byteHandle(uint8_t in_data)
{
    serial_sdk.reuse_count = 0;
    serial_sdk.reuse_index = _SDK_MAX_RECV_SIZE;

    byteStream(&serial_sdk, in_data);

    /* Just think a command as below
        *
        * [123456HHD1234567===HHHH------------------] --- is buf un-used part
        *
        * if after recv full of above, but crc failed, we throw all data?
        * NO!
        * Just throw ONE BYTE, we move like below
        *
        * [123456HH------------------D1234567===HHHH]
        *
        * Use the buffer high part to re-loop, try to find a new command
        *
        * if new cmd also fail, and buf like below
        *
        * [56HHD1234567----------------------===HHHH]
        *
        * throw one byte, buf looks like
        *
        * [6HHD123-----------------------4567===HHHH]
        *
        * the command tail part move to buffer right
        **/
    if (serial_sdk.reuse_count != 0)
    {
        while (serial_sdk.reuse_index < _SDK_MAX_RECV_SIZE)
        {
            in_data = serial_sdk.comm_recv_buf[serial_sdk.reuse_index];
            // because reuse_index maybe re-located, so reuse_index must be
            // always point to un-used index
            serial_sdk.reuse_index++;
            // re-loop the buffered data
            byteStream(&serial_sdk, in_data);
        }
        serial_sdk.reuse_count = 0;
    }
}

void N1SDK::byteStream(SDKFilter *p_filter, uint8_t in_data)
{
    storeData(p_filter, in_data);
    checkStream(p_filter);
}

void N1SDK::storeData(SDKFilter *p_filter, uint8_t in_data)
{
    if (p_filter->recv_index < _SDK_MAX_RECV_SIZE)
    {
        p_filter->comm_recv_buf[p_filter->recv_index] = in_data;
        p_filter->recv_index++;
    }
    else
    {
        // Error, buffer overflow! Just clear and continue.
        printf("Error buffer overflow!/r/n");
        memset(p_filter->comm_recv_buf, 0, p_filter->recv_index);
        p_filter->recv_index = 0;
    }
}

void N1SDK::checkStream(SDKFilter *p_filter)
{
    ProHeader* p_head = (ProHeader*)(p_filter->comm_recv_buf);
    if (p_filter->recv_index < sizeof(ProHeader))
    {
        // Continue receive data, nothing to do

    }
    else if (p_filter->recv_index == sizeof(ProHeader))
    {
        // recv a full-head
        verifyHead(p_filter);
    }
    else if (p_filter->recv_index == p_head->length)
    {
        sdk_stream_verify_data(p_filter);
    }
}

void N1SDK::verifyHead(SDKFilter *p_filter)
{
    ProHeader* p_head = (ProHeader*)(p_filter->comm_recv_buf);

    if ((p_head->sof == _SDK_SOF) &&
            (p_head->version == 0) &&
            (p_head->length <= _SDK_MAX_RECV_SIZE) &&
            (p_head->reversed0 == 0) &&
            (p_head->reversed1 == 0) &&
            (_SDK_CALC_CRC_HEAD(p_head, sizeof(ProHeader)) == 0)
            )
    {
        // check if this head is a ack or simple package
        if (p_head->length == sizeof(ProHeader))
        {
            sdk_call_data_app(p_filter);
        }
    }
    else
    {
        sdk_stream_shift_data(p_filter);
    }
}

void N1SDK::sdk_call_data_app(SDKFilter *p_filter)
{
    // pass current data to handler
    ProHeader* p_head = (ProHeader*)p_filter->comm_recv_buf;
    sdk_stream_codec(p_filter, p_head, N1SDK::aes256_decrypt_ecb);
    Pro_Link_Recv_Hook((ProHeader*)p_filter->comm_recv_buf);
    sdk_stream_prepare(p_filter, p_head);
}

void N1SDK::Pro_Link_Recv_Hook(ProHeader *header)
{
    unsigned char i;
    ProHeader *p2header;
    Ack_Session_Queue *p2acksession;

    //TODO: parse the protocol data stream here
    if(header->is_ack == 1)
    {
        if(header->session_id == 1)
        {
            printf("%s:Recv Session 1 ACK\n",__func__);
            if(Send_Session_Common_Tab.usage_flag == 1 &&
                    Send_Session_Common_Tab.ack_callback)
            {
                Send_Session_Common_Tab.ack_callback(header);
            }
        }
        else if(header->session_id > 1 && header->session_id < 32)
        {
            for(i = 0 ; i < session ; i ++)
            {
                if(Send_Session_Tab[i].usage_flag == 1)
                {
                    p2header = (ProHeader*)Send_Session_Tab[i].mmu->start_addr;
                    if(p2header->session_id == header->session_id &&
                            p2header->sequence_number == header->sequence_number)
                    {
                        printf("%s:Recv Session %d ACK\n",__func__,p2header->session_id);
                        Send_Session_Tab[i].ack_callback(header);
                        Free_Send_Session(&Send_Session_Tab[i]);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        //TODO,is a request package
        switch(header->session_id)
        {
        case 0:
            Pro_Request_Interface(header);
            break;
        case 1:
        default:
            p2acksession = Search_Ack_Session(header->session_id);
            if(p2acksession)
            {
                if(p2acksession->session_status == ACK_SESSION_PROCESS)
                {
                    printf("%s,This session is waiting for App ack:"
                           "session id=%d,seq_num=%d\n",__func__,
                           header->session_id,header->sequence_number);
                }
                else if(p2acksession->session_status == ACK_SESSION_IDLE)
                {
                    if(header->session_id > 1)
                    {
                        p2acksession->session_status = ACK_SESSION_PROCESS;
                    }
                    Pro_Request_Interface(header);
                }
                else if(p2acksession->session_status == ACK_SESSION_USING)
                {
                    p2header = (ProHeader *)p2acksession->mmu->start_addr;
                    if(p2header->sequence_number == header->sequence_number)
                    {
                        printf("%s:repeat ACK to remote,session id=%d,seq_num=%d\n",
                               __func__,header->session_id,header->sequence_number);
                        send((unsigned char*)p2acksession->mmu->start_addr);
                    }
                    else
                    {
                        printf("%s:same session,but new seq_num pkg,session id=%d,"
                               "pre seq_num=%d,""cur seq_num=%d\n",__func__,
                               header->session_id,p2header->sequence_number,
                               header->sequence_number);
                        p2acksession->session_status = ACK_SESSION_PROCESS;
                        Pro_Request_Interface(header);
                    }
                }
            }
            break;
        }
    }

}

void N1SDK::sdk_stream_verify_data(SDKFilter *p_filter)
{
    ProHeader* p_head = (ProHeader*)(p_filter->comm_recv_buf);
    if (_SDK_CALC_CRC_TAIL(p_head, p_head->length) == 0)
        sdk_call_data_app(p_filter);
    else
        // data crc fail, re-use the data part
        sdk_stream_update_reuse_part(p_filter);
}

void N1SDK::sdk_stream_update_reuse_part(SDKFilter *p_filter)
{
    uint8_t* p_buf = p_filter->comm_recv_buf;
    uint16_t bytes_to_move = p_filter->recv_index - sizeof(ProHeader);
    uint8_t* p_src = p_buf + sizeof(ProHeader);

    uint16_t n_dest_index = p_filter->reuse_index - bytes_to_move;
    uint8_t* p_dest = p_buf + n_dest_index;

    memmove(p_dest, p_src, bytes_to_move);

    p_filter->recv_index = sizeof(ProHeader);
    sdk_stream_shift_data(p_filter);

    p_filter->reuse_index = n_dest_index;
    p_filter->reuse_count++;

}

void N1SDK::sdk_stream_shift_data(SDKFilter *p_filter)
{
    if (p_filter->recv_index)
    {
        p_filter->recv_index--;
        if (p_filter->recv_index)
            memmove(p_filter->comm_recv_buf, p_filter->comm_recv_buf + 1, p_filter->recv_index);
    }
}

void N1SDK::Free_Send_Session(Session_Queue *session)
{
    if(session->usage_flag == 1)
    {
        Free_Send_MMU(session->mmu);
        session->usage_flag = 0;
    }
}

void N1SDK::Free_Send_MMU(Memory_Manage_Unit *mmu)
{
    if(mmu->usage_flag == 1)
        mmu->usage_flag = 0;
}

void N1SDK::Pro_Request_Interface(ProHeader *header)
{
    App_Recv_Req_Data(header);
}

void N1SDK::App_Recv_Req_Data(ProHeader *header)
{
    req_id_t recv_req_id;
    recv_req_id.sequence_number = header->sequence_number;
    recv_req_id.session_id 	    = header->session_id;
    recv_req_id.need_encrypt    = header->enc_type & 0xff;
    recv_data.len 		    = header->length - EXC_DATA_SIZE;

    uint8_t *pos =(uint8_t *)header;
    uint8_t testdata = *pos;
    memcpy((uint8_t *)&recv_data.cmd_set,(((uint8_t *)header)+12), recv_data.len);

    uint8_t set_index = 0;
    uint8_t cmd_index = 0;

    set_index = find_set_index(recv_data.cmd_set,app_set_tab_ptr);
    cmd_index = find_cmd_index(recv_data.cmd_id,app_set_tab_ptr[set_index].p_cmd_handler_table);

    if(set_index == ERR_INDEX || cmd_index == ERR_INDEX)
    {
        printf("ERROR, NO SUCH CMD_SET(%d) OR CMD_ID(%d) !\n", set_index, cmd_index);
        return;
    }
    app_set_tab_ptr[set_index].p_cmd_handler_table[cmd_index].pf_cmd_handler(recv_data.cmd_id,
                                                                             recv_data.data_buf,
                                                                             (recv_data.len - SET_CMD_SIZE),
                                                                             recv_req_id);
}

uint8_t N1SDK::find_set_index(uint8_t cmd_set, set_handler_table_t *p_set_handler_tab)
{
    uint8_t item_data=0;
    uint8_t item_index=0;
    if(cmd_set == ERR_INDEX)return ERR_INDEX;
    if(p_set_handler_tab==NULL)return ERR_INDEX;

    while(item_data!=ERR_INDEX)
    {
        item_data = p_set_handler_tab[item_index].cmd_set;
        if(item_data == cmd_set)
        {
            return item_index;
        }
        item_index++;
    }
    return ERR_INDEX;
}

uint8_t N1SDK::find_cmd_index(uint8_t cmd_id, cmd_handler_table_t *p_cmd_handler_tab)
{
    uint16_t item_data=0;
    uint16_t item_index=0;
    if(cmd_id == ERR_INDEX) return ERR_INDEX;
    if(p_cmd_handler_tab==NULL) return ERR_INDEX;
    while(item_data!=ERR_INDEX)
    {
        item_data = p_cmd_handler_tab[item_index].cmd_id;
        if(item_data == cmd_id)
        {
            return item_index;
        }
        item_index++;
    }
    return ERR_INDEX;
}

Ack_Session_Queue *N1SDK::Search_Ack_Session(unsigned char session_id)
{
    unsigned char i;
    for(i = 0 ; i < (SESSION_AND_MEM_COUNT + 1) ; i ++)
    {
        if(Ack_Session_Tab[i].session_id == session_id)
        {
            return &Ack_Session_Tab[i];
        }
    }

    return (Ack_Session_Queue *)NULL;
}

void N1SDK::sdk_stream_codec(SDKFilter *p_filter, ProHeader *p_head, ptr_aes256_codec codec_func)
{
    aes256_context ctx;
    uint32_t buf_i;
    uint32_t loop_blk;
    uint32_t data_len;
    uint32_t data_idx;
    uint8_t* data_ptr;

    if (p_head->enc_type == 0)
        return;
    if (p_head->length == sizeof(ProHeader))
        return;
    if (p_head->length <= sizeof(ProHeader) + _SDK_CRC_DATA_SIZE)
        return;

    data_ptr = (uint8_t*)p_head + sizeof(ProHeader);
    data_len = p_head->length - _SDK_CRC_DATA_SIZE - sizeof(ProHeader);
    loop_blk = data_len / 16;
    data_idx = 0;

    aes256_init(&ctx, p_filter->comm_key);
    for (buf_i = 0; buf_i < loop_blk; buf_i++)
    {
        codec_func(&ctx, data_ptr + data_idx);
        data_idx += 16;
    }
    aes256_done(&ctx);

    if(codec_func == N1SDK::aes256_decrypt_ecb)
        p_head->length = p_head->length - p_head->padding; //minus padding length;
}

void N1SDK::aes256_init(aes256_context *ctx, uint8_t *k)
{
    uint8_t rcon = 1;
    register uint8_t i;
    for (i = 0; i < sizeof(ctx->key); i++) ctx->enckey[i] = ctx->deckey[i] = k[i];
    for (i = 8; --i;) aes_expandEncKey(ctx->deckey, &rcon);
}

void N1SDK::aes_expandEncKey(uint8_t *k, uint8_t *rc)
{
    register uint8_t i;

    k[0] ^= rj_sbox(k[29]) ^ (*rc);
    k[1] ^= rj_sbox(k[30]);
    k[2] ^= rj_sbox(k[31]);
    k[3] ^= rj_sbox(k[28]);
    *rc = F(*rc);

    for (i = 4; i < 16; i += 4)  k[i] ^= k[i - 4], k[i + 1] ^= k[i - 3],
            k[i + 2] ^= k[i - 2], k[i + 3] ^= k[i - 1];
    k[16] ^= rj_sbox(k[12]);
    k[17] ^= rj_sbox(k[13]);
    k[18] ^= rj_sbox(k[14]);
    k[19] ^= rj_sbox(k[15]);

    for (i = 20; i < 32; i += 4) k[i] ^= k[i - 4], k[i + 1] ^= k[i - 3],
            k[i + 2] ^= k[i - 2], k[i + 3] ^= k[i - 1];

}

void N1SDK::aes256_done(aes256_context *ctx)
{
    register uint8_t i;

    for (i = 0; i < sizeof(ctx->key); i++)
        ctx->key[i] = ctx->enckey[i] = ctx->deckey[i] = 0;
}

void N1SDK::aes256_decrypt_ecb(aes256_context *ctx, uint8_t *buf)
{
    uint8_t i, rcon;

    aes_addRoundKey_cpy(buf, ctx->deckey, ctx->key);
    aes_shiftRows_inv(buf);
    aes_subBytes_inv(buf);

    for (i = 14, rcon = 0x80; --i;)
    {
        if ((i & 1))
        {
            aes_expandDecKey(ctx->key, &rcon);
            aes_addRoundKey(buf, &ctx->key[16]);
        }
        else aes_addRoundKey(buf, ctx->key);
        aes_mixColumns_inv(buf);
        aes_shiftRows_inv(buf);
        aes_subBytes_inv(buf);
    }
    aes_addRoundKey(buf, ctx->key);
}

void N1SDK::sdk_stream_prepare(SDKFilter *p_filter, ProHeader *p_head)
{
    uint32_t bytes_to_move = sizeof(ProHeader) - 1;
    uint32_t index_of_move = p_filter->recv_index - bytes_to_move;

    p_head=p_head;//For eliminating the warning messages.
    memmove(p_filter->comm_recv_buf, p_filter->comm_recv_buf + index_of_move, bytes_to_move);
    memset(p_filter->comm_recv_buf + bytes_to_move, 0, index_of_move);
    p_filter->recv_index = bytes_to_move;
}

uint8_t N1SDK::rj_xtime(uint8_t x)
{
    return (x & 0x80) ? ((x << 1) ^ 0x1b) : (x << 1);
}

void N1SDK::aes_subBytes(uint8_t *buf)
{
    register uint8_t i = 16;

    while (i--) buf[i] = rj_sbox(buf[i]);
}

void N1SDK::aes_subBytes_inv(uint8_t *buf)
{
    register uint8_t i = 16;

    while (i--) buf[i] = rj_sbox_inv(buf[i]);
}

void N1SDK::aes_addRoundKey(uint8_t *buf, uint8_t *key)
{
    register uint8_t i = 16;

    while (i--) buf[i] ^= key[i];
}

void N1SDK::aes_addRoundKey_cpy(uint8_t *buf, uint8_t *key, uint8_t *cpk)
{
    register uint8_t i = 16;
    while (i--)  buf[i] ^= (cpk[i] = key[i]), cpk[16 + i] = key[16 + i];
}

void N1SDK::aes_shiftRows(uint8_t *buf)
{
    register uint8_t i, j; /* to make it potentially parallelable :) */

    i = buf[1]; buf[1] = buf[5]; buf[5] = buf[9]; buf[9] = buf[13]; buf[13] = i;
    i = buf[10]; buf[10] = buf[2]; buf[2] = i;
    j = buf[3]; buf[3] = buf[15]; buf[15] = buf[11]; buf[11] = buf[7]; buf[7] = j;
    j = buf[14]; buf[14] = buf[6]; buf[6] = j;

}

void N1SDK::aes_shiftRows_inv(uint8_t *buf)
{
    register uint8_t i, j; /* same as above :) */

    i = buf[1]; buf[1] = buf[13]; buf[13] = buf[9]; buf[9] = buf[5]; buf[5] = i;
    i = buf[2]; buf[2] = buf[10]; buf[10] = i;
    j = buf[3]; buf[3] = buf[7]; buf[7] = buf[11]; buf[11] = buf[15]; buf[15] = j;
    j = buf[6]; buf[6] = buf[14]; buf[14] = j;

}

void N1SDK::aes_mixColumns(uint8_t *buf)
{
    register uint8_t i, a, b, c, d, e;

    for (i = 0; i < 16; i += 4)
    {
        a = buf[i]; b = buf[i + 1]; c = buf[i + 2]; d = buf[i + 3];
        e = a ^ b ^ c ^ d;
        buf[i] ^= e ^ rj_xtime(a^b);   buf[i + 1] ^= e ^ rj_xtime(b^c);
        buf[i + 2] ^= e ^ rj_xtime(c^d); buf[i + 3] ^= e ^ rj_xtime(d^a);
    }
}

void N1SDK::aes_mixColumns_inv(uint8_t *buf)
{
    register uint8_t i, a, b, c, d, e, x, y, z;

    for (i = 0; i < 16; i += 4)
    {
        a = buf[i]; b = buf[i + 1]; c = buf[i + 2]; d = buf[i + 3];
        e = a ^ b ^ c ^ d;
        z = rj_xtime(e);
        x = e ^ rj_xtime(rj_xtime(z^a^c));  y = e ^ rj_xtime(rj_xtime(z^b^d));
        buf[i] ^= x ^ rj_xtime(a^b);   buf[i + 1] ^= y ^ rj_xtime(b^c);
        buf[i + 2] ^= x ^ rj_xtime(c^d); buf[i + 3] ^= y ^ rj_xtime(d^a);
    }
}

void N1SDK::aes_expandEncKey(uint8_t *k, uint8_t *rc)
{
    register uint8_t i;

    k[0] ^= rj_sbox(k[29]) ^ (*rc);
    k[1] ^= rj_sbox(k[30]);
    k[2] ^= rj_sbox(k[31]);
    k[3] ^= rj_sbox(k[28]);
    *rc = F(*rc);

    for (i = 4; i < 16; i += 4)  k[i] ^= k[i - 4], k[i + 1] ^= k[i - 3],
            k[i + 2] ^= k[i - 2], k[i + 3] ^= k[i - 1];
    k[16] ^= rj_sbox(k[12]);
    k[17] ^= rj_sbox(k[13]);
    k[18] ^= rj_sbox(k[14]);
    k[19] ^= rj_sbox(k[15]);

    for (i = 20; i < 32; i += 4) k[i] ^= k[i - 4], k[i + 1] ^= k[i - 3],
            k[i + 2] ^= k[i - 2], k[i + 3] ^= k[i - 1];

}

void N1SDK::aes_expandDecKey(uint8_t *k, uint8_t *rc)
{
    uint8_t i;

    for (i = 28; i > 16; i -= 4) k[i + 0] ^= k[i - 4], k[i + 1] ^= k[i - 3],
            k[i + 2] ^= k[i - 2], k[i + 3] ^= k[i - 1];

    k[16] ^= rj_sbox(k[12]);
    k[17] ^= rj_sbox(k[13]);
    k[18] ^= rj_sbox(k[14]);
    k[19] ^= rj_sbox(k[15]);

    for (i = 12; i > 0; i -= 4)  k[i + 0] ^= k[i - 4], k[i + 1] ^= k[i - 3],
            k[i + 2] ^= k[i - 2], k[i + 3] ^= k[i - 1];

    *rc = FD(*rc);
    k[0] ^= rj_sbox(k[29]) ^ (*rc);
    k[1] ^= rj_sbox(k[30]);
    k[2] ^= rj_sbox(k[31]);
    k[3] ^= rj_sbox(k[28]);
}

void N1SDK::Send_Poll()
{
    unsigned char i;
    unsigned int cur_timestamp;
    //printf("Poll \n");
    ////pthread_mutex_lock(&send_lock);
    for(i = 0 ; i < SESSION_AND_MEM_COUNT ; i ++)
    {
        if(Send_Session_Tab[i].usage_flag == 1)
        {
            cur_timestamp = getTimestamp();
            if((cur_timestamp - Send_Session_Tab[i].pre_timestamp)
                    > Send_Session_Tab[i].ack_timeout)
            {
                if(Send_Session_Tab[i].retry_send_time > 0 )
                {
                    if(Send_Session_Tab[i].sent_time >= Send_Session_Tab[i].retry_send_time )
                    {
                        Free_Send_Session(&Send_Session_Tab[i]);
                    }
                    else
                    {
                        send((unsigned char*)Send_Session_Tab[i].mmu->start_addr);
                        Send_Session_Tab[i].pre_timestamp = cur_timestamp;
                        Send_Session_Tab[i].sent_time ++;
                    }
                }
                else
                {
                    send((unsigned char*)Send_Session_Tab[i].mmu->start_addr);
                    Send_Session_Tab[i].pre_timestamp = cur_timestamp;
                }
            }
        }
    }
}

void N1SDK::spin_callback()
{
    //printf("call_back\n");
    static unsigned int count = 0;

    count++;
    if(count % 50 == 0)
    {
        /*
            DJI_INFO("STD_MSGS:");
            printf("[STD_MSGS] time_stamp %d \n",recv_sdk_std_msgs.time_stamp);
            printf("[STD_MSGS] q %f %f %f %f \n",recv_sdk_std_msgs.q.q0,recv_sdk_std_msgs.q.q1,recv_sdk_std_msgs.q.q2,recv_sdk_std_msgs.q.q3);
            printf("[STD_MSGS] a %f %f %f\n",recv_sdk_std_msgs.a.x,recv_sdk_std_msgs.a.y,recv_sdk_std_msgs.a.z);
            printf("[STD_MSGS] v %f %f %f\n",recv_sdk_std_msgs.v.x,recv_sdk_std_msgs.v.y,recv_sdk_std_msgs.v.z);
            printf("[STD_MSGS] w %f %f %f\n",recv_sdk_std_msgs.w.x,recv_sdk_std_msgs.w.y,recv_sdk_std_msgs.w.z);
            printf("[STD_MSGS] pos %f %f %f %f \n",recv_sdk_std_msgs.pos.lati, recv_sdk_std_msgs.pos.longti, recv_sdk_std_msgs.pos.alti, recv_sdk_std_msgs.pos.height);
            printf("[STD_MSGS] mag %d %d %d \n",recv_sdk_std_msgs.mag.x,recv_sdk_std_msgs.mag.y,recv_sdk_std_msgs.mag.z);
            printf("[STD_MSGS] rc %d %d %d %d %d\n",recv_sdk_std_msgs.rc.roll, recv_sdk_std_msgs.rc.pitch, recv_sdk_std_msgs.rc.yaw, recv_sdk_std_msgs.rc.throttle,recv_sdk_std_msgs.rc.mode);
            printf("[STD_MSGS] gimbal %f %f %f\n",recv_sdk_std_msgs.gimbal.x, recv_sdk_std_msgs.gimbal.y,recv_sdk_std_msgs.gimbal.z);
            printf("[STD_MSGS] status %d\n",recv_sdk_std_msgs.status);
            printf("[STD_MSGS] battery %d\n",recv_sdk_std_msgs.battery_remaining_capacity);
            printf("[STD_MSGS] ctrl_device %d\n",recv_sdk_std_msgs.ctrl_device);
    */
    }

    /* test session ack for force close */
    if(nav_force_close_req_id.reserve == 1)
    {
        nav_force_close_req_id.reserve = 0;
        uint16_t ack = 0x0001;
        printf("Ack close send %d !!!!!!!!!!! \n", ack);
        App_Send_Ack(nav_force_close_req_id, (uint8_t *)&ack, sizeof(ack));
    }
}

void N1SDK::App_Send_Ack(req_id_t req_id, uint8_t *ack, int len)
{
    ProAckParameter param;

    memcpy(Pro_Encode_ACK,ack,len);

    param.session_id = req_id.session_id;
    param.seq_num = req_id.sequence_number;
    param.need_encrypt = req_id.need_encrypt;
    param.buf = Pro_Encode_ACK;
    param.length = len;
    Pro_Ack_Interface(&param);
}



void N1SDK::App_Send_Data(unsigned char flag, uint8_t is_enc, unsigned char cmd_set, unsigned char cmd_id, unsigned char *pdata, int len, ACK_Callback_Func ack_callback, int timeout, int n)
{
    ProSendParameter param;
    unsigned char *ptemp = (unsigned char *)Pro_Encode_Data;
    *ptemp++ = cmd_set;
    *ptemp++ = cmd_id;


    memcpy(Pro_Encode_Data + SET_CMD_SIZE,pdata,len);

    param.ack_callback = ack_callback;
    param.pkg_type = flag;
    param.length = len + SET_CMD_SIZE;
    param.buf = Pro_Encode_Data;
    param.retry_time = n;

    param.ack_timeout = timeout;
    param.need_encrypt = is_enc;

    Pro_Send_Interface(&param);
}

int N1SDK::Pro_Send_Interface(ProSendParameter *parameter)
{
    unsigned short ret = 0;
    Session_Queue *p2session = NULL;
    static unsigned short global_seq_num = 0;

    if(parameter->length > PRO_DATA_MAX_SIZE)
    {
        return -1;
    }
    switch(parameter->pkg_type)
    {
    case 0:
        ret = sdk_encrypt_interface(Send_Global_Common_Memory,parameter->buf,parameter->length,
                                    0,parameter->need_encrypt,0,global_seq_num ++);
        if(ret == 0)
        {
            printf("%s:%d:ERROR\n",__func__,__LINE__);
            return -1;
        }
        send(Send_Global_Common_Memory);
        break;
    case 1:
        if(global_seq_num == Send_Session_Common_Tab.pre_seq_num)
        {
            global_seq_num ++;
        }
        Send_Session_Common_Tab.pre_seq_num = global_seq_num;

        ret = sdk_encrypt_interface(Send_Global_Common_Memory,parameter->buf,parameter->length,
                                    0,parameter->need_encrypt,1,global_seq_num ++);

        if(ret == 0)
        {
            printf("%s:%d:ERROR\n",__func__,__LINE__);
            return -1;
        }

        Send_Session_Common_Tab.ack_callback = parameter->ack_callback;
        Send_Session_Common_Tab.ack_timeout = (parameter->ack_timeout > POLL_TICK) ?
                    parameter->ack_timeout : POLL_TICK;
        Send_Session_Common_Tab.pre_timestamp = getTimestamp();
        Send_Session_Common_Tab.usage_flag = 1;

        send(Send_Global_Common_Memory);
        break;
    case 2:
        p2session = Request_Send_Session(parameter->length + sizeof(ProHeader) + 4);
        if(p2session)
        {
            if(global_seq_num == p2session->pre_seq_num)
            {
                global_seq_num ++;
            }
            p2session->pre_seq_num = global_seq_num;

            ret = sdk_encrypt_interface((unsigned char*)p2session->mmu->start_addr,
                                        parameter->buf,parameter->length,0,parameter->need_encrypt,
                                        p2session->session_id,global_seq_num ++);
            if(ret == 0)
            {
                printf("%s:%d:ERROR\n",__func__,__LINE__);
                Free_Send_Session(p2session);
                return -1;
            }

            p2session->ack_callback = parameter->ack_callback;
            p2session->ack_timeout = (parameter->ack_timeout > POLL_TICK) ?
                        parameter->ack_timeout : POLL_TICK;
            p2session->pre_timestamp = getTimestamp();

            send((unsigned char*)p2session->mmu->start_addr);
            p2session->sent_time = 1;
            p2session->retry_send_time = parameter->retry_time;
            ret = 0;
        }
        break;
    }

    ////pthread_mutex_unlock(&send_lock);

    return 0;
}

unsigned short N1SDK::sdk_encrypt_interface(uint8_t *pdest, const uint8_t *psrc, uint16_t w_len, uint8_t is_ack, uint8_t is_enc, uint8_t session_id, uint16_t seq_num)
{
    uint16_t data_len;

    ProHeader* p_head = (ProHeader*)pdest;

    if (w_len > 1024)
        return 0;

    if (serial_sdk.enc_enabled == 0 && is_enc)
        return 0;

    if (w_len == 0 || psrc == 0)
        data_len = (uint16_t)sizeof(ProHeader);
    else
        data_len = (uint16_t)sizeof(ProHeader) + _SDK_CRC_DATA_SIZE + w_len;

    if(is_enc)
        data_len = data_len + (16 - w_len % 16);

    p_head->sof = _SDK_SOF;
    p_head->length = data_len;
    p_head->version = 0;
    p_head->session_id = session_id;
    p_head->is_ack = is_ack ? 1 : 0;
    p_head->reversed0 = 0;

    p_head->padding = is_enc ? (16 - w_len % 16) : 0;
    p_head->enc_type = is_enc ? 1 : 0;
    p_head->reversed1 = 0;

    p_head->sequence_number = seq_num;
    p_head->head_crc = 0;

    if (psrc && w_len)
        memcpy(pdest + sizeof(ProHeader), psrc, w_len);
    sdk_stream_codec(&serial_sdk, p_head, aes256_encrypt_ecb);

    sdk_stream_recalc_crc(pdest);

    return data_len;
}

Session_Queue *N1SDK::Request_Send_Session(unsigned short size)
{
    int i;
    Session_Queue *p2session = NULL;
    Memory_Manage_Unit *p2mmu = NULL;

    for(i = 0 ; i < SESSION_AND_MEM_COUNT ; i ++)
    {
        if(Send_Session_Tab[i].usage_flag == 0)
        {
            Send_Session_Tab[i].usage_flag = 1;
            p2session = &Send_Session_Tab[i];
            break;
        }
    }

    p2mmu = Request_Send_MMU(size);
    if(p2mmu == NULL)
    {
        p2session = NULL;
    }
    else
    {
        p2session->mmu = p2mmu;
    }

    return p2session;
}

Memory_Manage_Unit *N1SDK::Request_Send_MMU(unsigned short size)
{
    unsigned char i;
    Memory_Manage_Unit *p2mmu = NULL;

    for(i = 0 ; i < SESSION_AND_MEM_COUNT; i ++)
    {
        if(Send_MMU_Tab[i].usage_flag == 0)
        {
            p2mmu = &Send_MMU_Tab[i];
            p2mmu->usage_flag = 1;
            p2mmu->end_addr = p2mmu->start_addr + size;
            break;
        }
    }

    return p2mmu;
}

int N1SDK::Pro_Ack_Interface(ProAckParameter *parameter)
{
    unsigned short ret = 0;
    Ack_Session_Queue *p2acksession;
    Memory_Manage_Unit *p2mmu;

    if(parameter->session_id == 0)
    {
        ;
    }
    else if(parameter->session_id > 0 && parameter->session_id < 32)
    {
        p2acksession = Search_Ack_Session(parameter->session_id);
        if(p2acksession)
        {
            if(parameter->length > PRO_ACK_MAX_SIZE)
            {
                printf("%s:ERROR,ACK buffer is not enough\n",__func__);
                p2acksession->session_status = ACK_SESSION_IDLE;
                return -1;
            }
            p2mmu = Request_Ack_MMU(parameter->length + sizeof(ProHeader) + 4);
            if(p2mmu)
            {
                p2acksession->mmu = p2mmu;

                ret = sdk_encrypt_interface((unsigned char*)p2mmu->start_addr,parameter->buf,
                                            parameter->length,1,parameter->need_encrypt,
                                            parameter->session_id,parameter->seq_num);

                if(ret == 0)
                {
                    printf("%s:%d:ERROR\n",__func__,__LINE__);
                    return -1;
                }

                send((unsigned char *)p2mmu->start_addr);

                p2acksession->session_status = ACK_SESSION_USING;
            }
        }
    }

    return 0;
}

Memory_Manage_Unit *N1SDK::Request_Ack_MMU(unsigned short size)
{
    unsigned char i;
    Memory_Manage_Unit *p2mmu = NULL;

    for(i = 0 ; i < (SESSION_AND_MEM_COUNT + 1); i ++)
        if(Ack_MMU_Tab[i].usage_flag == 0)
        {
            p2mmu = &Ack_MMU_Tab[i];
            p2mmu->usage_flag = 1;
            p2mmu->end_addr = p2mmu->start_addr + size;
            break;
        }
    return p2mmu;
}
}
#endif
