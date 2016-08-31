#include "QGetDVOStream.h"

QGetDVOStream::QGetDVOStream()
{

}
unsigned QGetDVOStream::get_stream_buf_next_seq(int stream_id)
{
  return g_stream_buf[stream_id].next_seq;
}
int QGetDVOStream::get_stream(char *buffer,stream_rtsp_info_t *stream_info)
{
  head:
    pro_next_seq = get_stream_buf_next_seq(fStreamID);
    if (SEQ_LEQ(pro_next_seq, send_seq, shift_bits))
    {
    	usleep(10000);
    	goto head;
    }
    frame_addr = get_enc_stream(fStreamID, send_seq, stream_info);
    //printf("stream id:%d,frame type:%d len:%d\n",fStreamID,stream_info->data_type,stream_info->stream_len);
  	if (DATA_TYPE_VIDEO == stream_info->data_type)
  	{
        //findNalu_amba(fNalus, &fNaluCount, (u_int8_t *)frame_addr, stream_info.stream_len);
      memcpy(buffer,frame_addr,stream_info->stream_len);
  	}
    send_seq = stream_info->next_seq;
    return stream_info->stream_len;
}
void QGetDVOStream::init_stream_buf(int stream_id)
{
  key_t shm_key = ftok(SHM_KEY_FILE, 1);
	int shm_id;
	char *shm_addr;
  fStreamID = stream_id;
  shift_bits = ((0 == fStreamID) ? 8 : 10);

  if((shm_id = shmget(shm_key, 0, 0)) < 0)
  {
    printf("rtsp get share memory failed! shm_id = %d, cause: %s\n", shm_id, strerror(errno));
    exit(-1);
  }
  shm_addr = (char *)shmat(shm_id, (char *)0, 0);
	if ((int)(*shm_addr) == -1)
	{
		printf("rtsp attach share memory failed!");
		exit(-1);
	}

    g_sys_param = (SystemParam *)shm_addr;

    g_stream_buf = (struct stream_buf_t *)(shm_addr + sizeof(SystemParam));
    g_stream_addr[0] = (char *)g_stream_buf + (MW_STREAM_MAX * sizeof(struct stream_buf_t));
    g_stream_addr[1] = g_stream_addr[0] + MAX_STREAM_BUF_SIZE;
    g_stream_addr[2] = g_stream_addr[1] + MID_STREAM_BUF_SIZE;
    send_seq = get_stream_buf_next_seq(fStreamID);

}
char *QGetDVOStream::get_enc_stream(int stream_id, unsigned start_seq, stream_rtsp_info_t *stream_info)
{
  char *start_addr = g_stream_addr[stream_id];
  unsigned cur_seq;
  unsigned buf_size = g_stream_buf[stream_id].size;
  char enc_hd[ENC_HD_LEN];
  struct tagMsgHead_t *msg_head;
	app_net_tcp_enc_stream_head_t *stream_head;

  if ((buf_size - start_seq) >= ENC_HD_LEN)
  {
    memcpy(enc_hd, start_addr + start_seq, ENC_HD_LEN);
    cur_seq = SEQ_INCR(start_seq, ENC_HD_LEN, buf_size);
  }
  else
  {
    memcpy(enc_hd, start_addr, ENC_HD_LEN);
    cur_seq = ENC_HD_LEN;
  }

  msg_head    = (struct tagMsgHead_t *)enc_hd;
  stream_info->data_type  = ntohs(msg_head->DataType);
  stream_info->stream_len = ntohl(msg_head->Pktlen) - ENC_HD_LEN;

	stream_head = (app_net_tcp_enc_stream_head_t *)&enc_hd[MSG_HEADER_LEN];
	stream_info->frame_num  = ntohl(stream_head->frame_num);
	stream_info->session_id = ntohl(stream_head->rev[0]);
	stream_info->pts        = ntohl(stream_head->rev[1]);
	stream_info->sec        = ntohl(stream_head->sec);
	stream_info->usec       = ntohl(stream_head->usec);
	stream_info->frame_type = ntohl(stream_head->frame_type );

	int stream_head_len = sizeof(app_net_tcp_enc_stream_head_t);
  if ((buf_size - cur_seq) >= stream_info->stream_len)
  {
    stream_info->next_seq = SEQ_INCR(cur_seq, (stream_info->stream_len), buf_size);
    return start_addr + cur_seq;
  }
  else
  {
    stream_info->next_seq = stream_info->stream_len;
    return start_addr;
  }
}
