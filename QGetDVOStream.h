#ifndef QGETDVOSTREAM_H
#define QGETDVOSTREAM_H
#include "dvo_protocol.h"

#define SEQ_LT(a, b, c)  ((int)(((a) - (b)) << c) < 0)
#define SEQ_LEQ(a, b, c) ((int)(((a) - (b)) << c) <= 0)
#define SEQ_GT(a, b, c)  ((int)(((a) - (b)) << c) > 0)
#define SEQ_GEQ(a, b, c) ((int)(((a) - (b)) << c) >= 0)
typedef struct
{
	unsigned short data_type;
	unsigned 	   stream_len;  //<add by Antony 2016-8-19>
	unsigned       frame_type;
	unsigned       next_seq;
	unsigned       frame_num;
	unsigned       session_id;
	unsigned       pts;
	unsigned       sec;
  unsigned       usec;
}stream_rtsp_info_t;
class QGetDVOStream
{
public:
  QGetDVOStream();
  void init_stream_buf(int stream_id);
  int get_stream(char *buffer,stream_rtsp_info_t *stream_info);
private:
  int fStreamID;
  struct stream_buf_t *g_stream_buf;
  char *g_stream_addr[MW_STREAM_MAX];
  SystemParam *g_sys_param;

  unsigned pro_next_seq;
  unsigned send_seq;
  unsigned shift_bits;

  unsigned fDataType;
  char *frame_addr;


private:
  unsigned get_stream_buf_next_seq(int stream_id);
  char *get_enc_stream(int stream_id, unsigned start_seq, stream_rtsp_info_t *stream_info);
};
#endif
