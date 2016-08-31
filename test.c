#include "QGetDVOStream.h"
#include "stdlib.h"
#include "stdio.h"

int main(void)
{
  QGetDVOStream *dvo_stream = new QGetDVOStream();
  dvo_stream->init_stream_buf(0);
  char *buffer = (char *)malloc(sizeof(char) * 1024 * 1024);
  stream_rtsp_info_t rtsp_info;
  while(1)
  {
    int len = dvo_stream->get_stream(buffer,&rtsp_info);
    printf("len:%d\n",len);
  }
}
