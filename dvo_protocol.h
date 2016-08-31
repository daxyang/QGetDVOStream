#ifndef DVO_PROTOCOL_H
#define DVO_PROTOCOL_H
#include "sys/shm.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <arpa/inet.h>


#ifdef __cplusplus
extern "C" {
#endif

#define SHM_KEY_FILE "/dvo/exe/dvo_ipc_main"

#define MAX_STREAM_BUF_SIZE (16 * 1024 * 1024)
#define MID_STREAM_BUF_SIZE (4 * 1024 * 1024)
#define MIN_STREAM_BUF_SIZE (4 * 1024 * 1024)

typedef unsigned char  	    u8;	/**< UNSIGNED 8-bit data type */
typedef unsigned short 	    u16;/**< UNSIGNED 16-bit data type */
typedef unsigned int   	   	u32;/**< UNSIGNED 32-bit data type */
typedef unsigned long long 	u64;/**< UNSIGNED 64-bit data type */
typedef signed char         s8;	/**< SIGNED 8-bit data type */
typedef signed short       	s16;/**< SIGNED 16-bit data type */
typedef signed int         	s32;/**< SIGNED 32-bit data type */
typedef signed long long	  s64;/**< SIGNED 64-bit data type */

#define MW_STREAM_MAX 3

#define SEQ_INCR(a, b, c) (((a) + (b)) % (c))

#define CHN_MAX      4
#define	MAX_CHN		(4)


struct stream_buf_t
{
    unsigned next_seq;
    unsigned size;
    char     *addr;
};
typedef struct tagMsgHead_t
{
    char Magic1[4];
    u32  Pktlen;
    u16  Version;
    u16  Hwtype;
    u32  Sn;
    u16  CmdType;
    u16  CmdSubType;
    u16  DataType;
    u16  Rev1;
    u32  Rev2;
    u32  Rev3;
}tagMsgHead_t;

#define MSG_HEADER_LEN sizeof(tagMsgHead_t)

typedef struct
{
    int chn;
    int enable;
}app_net_tcp_sys_net_vout_t;

typedef struct app_net_tcp_sys_login_t
{
    char user_name[20];
    char user_pwd[20];
    u32	 rev[8];
}app_net_tcp_sys_login_t;

typedef struct
{
   int	state;
   char	dev_type[64];
   char	dev_name[64];
   char	dev_id[64];
   char	hw_version[32];
   char	sdk_sw_version[32];
   char	app_sw_version[32];
   char	rev1[32];
}app_net_tcp_sys_login_info_t;

enum
{
    DVO_LOGIN_IN_SUCCESS = 0,
    DVO_USER_PASSWORD_ERROR,
    DVO_USER_LOCKING,
    DVO_UNKOWN_ERROR,

};

typedef enum
{
    APP_NET_TCP_STATE_SUCCESS = 0,
    APP_NET_TCP_STATE_FAIL,
}APP_NET_TCP_STATE;

typedef struct
{
    char ipv4[30];
    char mac_addr[40];
    char net_mask[30];
    char gate_way[30];
    char dns[30];
}app_net_tcp_sys_ipv4_t;

typedef struct
{
    int	chn;
    int	exit;
    int	rev[6];
    app_net_tcp_sys_ipv4_t 	ipv4;
}app_net_tcp_sys_net_info_t;

typedef struct
{
    int	chn;
}app_net_tcp_com_chn_t;

typedef struct
{
    int tm_sec;         	/* seconds */
    int tm_min;         	/* minutes */
    int tm_hour;        	/* hours */
    int tm_mday;        	/* day of the month */
    int tm_mon;         	/* month */
    int tm_year;        	/* year */
    int tm_wday;        	/* day of the week */
    int tm_yday;        	/* day in the year */
    int tm_isdst;       		/* daylight saving time */
}app_net_tcp_sys_time_t;

typedef struct
{
    int ip_include; // 0:include ip, 1:not include ip.
    int	rev[3];
}app_net_tcp_sys_default_t;

typedef struct
{
    int ip_include; 	// 0:include ip, 1:not include ip.
    int	file_len;
    int	total_frame;
    int	cur_frame;
    u32	crc;
    int reserve[4];
}app_net_tcp_sys_update_head_t;

typedef struct
{
    u32	chn;
    int	bitrate;
    int	parity;
    int	len;
    int	stop;
    u32	rev[3];
}app_net_tcp_serial_cfg_t;

typedef enum
{
    APP_NET_TCP_SERIAL_TYPE_RS232	= 1,
    APP_NET_TCP_SERIAL_TYPE_RS422,
    APP_NET_TCP_SERIAL_TYPE_RS485,
}APP_NET_TCP_SERIAL_TYPE;

typedef struct
{
    int	vin_num;
    int	vout_num;
    int	ain_num;
    int	aout_num;
    int serial_num;
    int	ioin_num;
    int	ioout_num;
    int	netcard_num;
    int	disk_num;
    int	rev[10];
    int	vin_type[MAX_CHN];
    int	vout_type[MAX_CHN];
    int	ain_type[MAX_CHN];
    int	aout_type[MAX_CHN];
    int	serial_type[MAX_CHN];
    int	ioin_type[MAX_CHN];
    int	ioout_type[MAX_CHN];
    int	netcard_type[MAX_CHN];
    int	disk_type[MAX_CHN];
    int	revt[40];
}app_net_tcp_dev_cap_t;

typedef struct
{
    char dev_type[64];
    char dev_name[64];
    char dev_id[64];
    char hw_version[32];
    char sdk_sw_version[32];
    char app_sw_version[32];
    char rev1[32];
}app_net_tcp_sys_dev_info_t;

typedef struct
{
    char dev_name[64];
    char rev1[32];
}app_net_tcp_sys_dev_info_set_t;

typedef struct
{
    u32	part_num;
    u64	part_volume;
    u64	part_free;
    u32	part_state;
    u32	rev[9];
}app_net_tcp_sys_disk_part_t;

typedef struct
{
    u32	chn;
    u32	exit;
    u32	rev[6];
    app_net_tcp_sys_disk_part_t	part[4];
}app_net_tcp_sys_disk_t;

typedef struct
{
    int enable;
    int interval;
    int rev[2];
}app_net_tcp_sys_heart_t;

typedef struct
{
    int	 type;
    char ioin[CHN_MAX];
    char md[CHN_MAX];
    u32  dev_type;
    char _485_alarm[16];
    u32  _485_data[16];
    char rev[428];
}app_net_tcp_sys_event_trig_state_t;

typedef struct
{
    int	 port;
    int	 rev[7];
    char multi_cast_ip[30];
}app_net_tcp_sys_net_misc_t;

typedef enum
{
    APP_NET_TCP_COM_VIDEO_MODE_352_288	 = 0,
    APP_NET_TCP_COM_VIDEO_MODE_704_576,
    APP_NET_TCP_COM_VIDEO_MODE_1280_720,
    APP_NET_TCP_COM_VIDEO_MODE_1920_1080,
    APP_NET_TCP_COM_VIDEO_MODE_1280_960,
    APP_NET_TCP_COM_VIDEO_MODE_1024_768,

    APP_NET_TCP_COM_VIDEO_MODE_576_320,
    APP_NET_TCP_COM_VIDEO_MODE_1200_720,

    //#if CONFIG_PLATFORM_HISI
    /* BEGIN: Added by zhaojie, 2015/8/24 */
    APP_NET_TCP_COM_VIDEO_MODE_2304_1296,
    APP_NET_TCP_COM_VIDEO_MODE_2592_1944,
    /* END:   Added by zhaojie, 2015/8/24 */
   // #endif

    APP_NET_TCP_COM_VIDEO_MODE_176_144	 = 0xFF,
    APP_NET_TCP_COM_VIDEO_MODE_MAX,
}APP_NET_TCP_COM_VIDEO_MODE;

typedef struct
{
    u32	enc_mode;
    u32	enc_fps;
    u32	rev[6];
}app_net_tcp_enc_fmt_base_t;

typedef struct
{
    u8	idr_interval;
    u8	profile;
    u8	brc_mode;
    u8	rev1;
    u32	maxbps;
    u32	minbps;
    u32	rev2[6];
}app_net_tcp_enc_h264_base_t;

typedef struct
{
    u32	quality;
    u32	rev[7];
}app_net_tcp_enc_jpeg_base_t;

typedef struct
{
    u32	chn;
    u32	schn;
    u32	rev[2];
}app_net_tcp_com_schn_t;

typedef struct
{
    u32	chn;
    u32	stream;
    u32	enc_type;
    u32	rev[5];
    app_net_tcp_enc_fmt_base_t	fmt;
    app_net_tcp_enc_h264_base_t	h264;
    app_net_tcp_enc_jpeg_base_t	jpeg;
}app_net_tcp_enc_info_t;

typedef struct
{
    u32	chn;
    u32	stream;
    u32	enable;
    u32	nettype;
    u32	port;
    u32	rev[3];
}app_net_tcp_enc_ctl_t;

typedef struct
{
    u32	chn;
    u32	stream;
    u32	state;
    u32	rev;
}app_net_tcp_enc_ctl_ack_t;

typedef struct
{
    int log_type;
    int tm_year;
    int tm_mon;
    int tm_mday;
    int rev[5];
}app_net_tcp_sys_log_t;

typedef struct
{
    int available;
    int log_size;
    int rev[5];
}app_net_tcp_sys_log_info_t;

typedef struct
{
    int cur_frame;
    int frame_size;
    int rev[10];
}app_net_tcp_sys_log_download_head_t;

typedef u32 app_audio_stream_enc_type;
typedef u32 app_web_port_type;

typedef enum
{
    APP_NET_TCP_COM_DST_IDR_FRAME	= 1,
    APP_NET_TCP_COM_DST_I_FRAME,
    APP_NET_TCP_COM_DST_P_FRAME,
    APP_NET_TCP_COM_DST_B_FRAME,
    APP_NET_TCP_COM_DST_JPEG_FRAME,
    APP_NET_TCP_COM_DST_711_ALAW,
    APP_NET_TCP_COM_DST_711_ULAW,
    APP_NET_TCP_COM_DST_726,
    APP_NET_TCP_COM_DST_AAC,
    APP_NET_TCP_COM_DST_MAX,
} APP_NET_TCP_STREAM_TYPE;

typedef struct
{
    u32	chn;
    u32	stream;
    u32	frame_type;
    u32	frame_num;
    u32	sec;
    u32	usec;
    u32	rev[2];
}app_net_tcp_enc_stream_head_t;

#define ENC_HD_LEN (MSG_HEADER_LEN + sizeof(app_net_tcp_enc_stream_head_t))

typedef struct
{
    u8 b;
    u8 g;
    u8 r;
    u8 a;
}app_net_tcp_osd_color_t;

typedef struct
{
    u32	chn;
    u32	enable;
    u32	x_edge;
    u32	y_edge;
    app_net_tcp_osd_color_t color;
    u32	size;
    u32	type;
    u32	len;
    u32 outline;
    u32 align;
    u32	rev[6];
    char tag[32];
}app_net_tcp_osd_cfg_t;

typedef struct
{
    u32	chn;
    u32	type;
    u32	rev[2];
}app_net_tcp_enc_chn_t;

typedef struct
{
    u8 b;
    u8 g;
    u8 r;
    u8 a;
}pm_color_t;

typedef struct
{
    u32	chn;
    u32	enable;
    int	x;
    int	y;
    int	w;
    int	h;
    pm_color_t	color;
    int	rev;
}app_net_tcp_pm_cfg_t;

typedef struct
{
    int	chn;
    int	brightness;
    int	saturation;
    int	contrast;
    int	sharpness;
    int	hue;
    int	rev[2];
}app_net_tcp_img_color_t;

typedef enum
{
    APP_NET_TCP_ESHUTTER_1_SEC   = 0, /* 1 sec */
    APP_NET_TCP_ESHUTTER_10_SEC,      /* 1/10 sec */
    APP_NET_TCP_ESHUTTER_12_SEC,      /* 1/12 sec */
    APP_NET_TCP_ESHUTTER_15_SEC,
    APP_NET_TCP_ESHUTTER_20_SEC,
    APP_NET_TCP_ESHUTTER_25_SEC,
    APP_NET_TCP_ESHUTTER_30_SEC,
    APP_NET_TCP_ESHUTTER_50_SEC,
    APP_NET_TCP_ESHUTTER_60_SEC,
    APP_NET_TCP_ESHUTTER_100_SEC,
    APP_NET_TCP_ESHUTTER_120_SEC,
    APP_NET_TCP_ESHUTTER_240_SEC,
    APP_NET_TCP_ESHUTTER_480_SEC,
    APP_NET_TCP_ESHUTTER_960_SEC,
    APP_NET_TCP_ESHUTTER_1024_SEC,
    APP_NET_TCP_ESHUTTER_COUNT,
}APP_NET_TCP_ESHUTTER_E;

typedef enum
{
    APP_NET_TCP_IMG_EXP_AUTO	= 0,
    APP_NET_TCP_IMG_EXP_MANUAL	= 1,
    APP_NET_TCP_IMG_EXP_MODE_ALL,
}APP_NET_TCP_IMG_EXP_MODE;

typedef struct
{
    int	chn;
    int	mode;
    int	shutter;
    int	gain;
    int	rev[16];
}app_net_tcp_img_exp_t;

typedef struct
{
    int	chn;
    int	mode;
    int	rgain;
    int	ggain;
    int	bgain;
    int	rev[3];
}app_net_tcp_img_wb_t;

typedef enum
{
    APP_NET_TCP_IMG_WB_AUTO = 0,
    APP_NET_TCP_IMG_WB_CUSTOM,
    APP_NET_TCP_IMG_WB_MODE_ALL,
} APP_NET_TCP_IMG_WB_MODE;

typedef struct
{
    int chn;
    int	mode;
    int	rev[6];
}app_net_tcp_img_ircut_t;

typedef enum
{
    APP_NET_MIRROR_HORRIZONTALLY_VERTICALLY = 0,
    APP_NET_MIRROR_HORRIZONTALLY,
    APP_NET_MIRROR_VERTICALLY,
    APP_NET_MIRROR_NONE,
    APP_NET_MIRROR_ALL,
}APP_NET_MIRROR_MODE;

typedef struct
{
    int	chn;
    APP_NET_MIRROR_MODE	mirror_mode;
    u32	rev[6];
}app_net_tcp_img_mode_t;

typedef struct
{
    u32	type;
    u32	chn;
    u32	protocl;
    u32	cmd1;
    u32	cmd2;
    u32	ps;
    u32	ts;
    u32	rev[9];
}app_net_tcp_ptz_t;

typedef struct
{
    u32	 chn;
    u32	 len;
    u32	 rev[6];
    char data[256];
}app_net_tcp_ptz_tran_t;

typedef struct
{

u32 chn;
     u32 datalen;
     u32 rev[8];
}app_net_tcp_port_tran_head_t;

typedef struct
{
    u32 chn;
    u32 rev[8];
}app_net_tcp_port_tran_chn_t;

typedef struct
{
    int	chn;
    int	state;
    int	rev[6];
}app_net_tcp_event_act_ioout_t;

typedef struct
{
    int	chn;
    int	rows;
    int	cols;
    int	rev[5];
}app_net_tcp_event_trig_md_base_rc_t;

typedef struct
{
    int	 chn;
    int	 threshold;
    int	 sensitivity;
    int	 rev[5];
    char en[64*64/8];
}app_net_tcp_event_trig_md_t;

typedef struct
{
    u32	chn;
    u32	enable;
    u32	rev[6];
}app_net_tcp_audio_ctl_t;

typedef struct
{
    u32	chn;
    u32	state;
}app_net_tcp_audio_ctl_ack_t;

typedef struct
{
    int	chn;
    int	enc_type;
    int	samplerate;
    int	rev[5];
}app_net_tcp_audio_config_t;

typedef struct
{
    int  proto;
    char ssid[36];
    char passwd[68];
}app_net_wifi_t;

struct app_net_tcp_sn_mac_t
{
    char sn[32];
    char mac[40];
    char rev[88];
};

struct broadcast_dev_info_t
{
    unsigned temp_uuid;
	unsigned status;
    char mac_addr[40];
    char ipv4[30];
    char net_mask[30];
    char gate_way[30];
	char version[30];
	unsigned web_port;
    char rev[76];
};

#define MAX_CUSTOM_OSD_LINE_NUM 64

typedef struct
{
    u32 chn;
	u32 stream;
    u32 enable;
    u32 x_edge;
    u32 y_edge;
    u32 size;
    u32 rev[10];
}app_net_tcp_custom_osd_zone_cfg_t;

typedef struct
{
	u32 chn;
	u32 stream;
    u32 max_line_num;
    u32 max_text_len;
    u32 rev[4];
}app_net_tcp_custom_osd_zone_spec_t;

typedef struct
{
    u32 chn;
	u32 stream;
    u32 enable;
    u32 x_edge;
    u32 y_edge;
    u32 size;
    u32 max_line_num;
    u32 max_text_len;
    u32 rev[8];
}app_net_tcp_custom_osd_zone_para_t;

typedef struct
{
    u32 chn;
	u32 stream;
    u32 rev[2];
}app_net_tcp_custom_osd_zone_chn_t;

typedef struct
{
    u32 chn;
	u32 stream;
    u32 row_no;
    pm_color_t color;
    u32 outline;
    u32 keep_time;
    u32 rev[6];
}app_net_tcp_custom_osd_line_cfg_t;

typedef struct
{
    u32 chn;
	u32 stream;
    u32 row_no;
    u32 rev[5];
}app_net_tcp_custom_osd_line_chn_t;

typedef struct
{
    u32        chn;
	u32        stream;
    u32        row_no;
    u32        length;
    u8         text[256];
    u32        set_color;
    u32        outline;
    pm_color_t color;
    u32        rev[5];
}app_net_tcp_custom_osd_line_data_t;

typedef struct
{
    u32 chn;
    u32 stream;
    u32 rev[8];
}app_net_tcp_clear_osd_cfg_t;

typedef struct
{
    u32 chn;
    u32 stream;
    u32 result;
    u32 rev[8];
}app_net_tcp_clear_osd_ret_t;

typedef struct
{
    u32 OSDLines;
    u32 nRev[8];
    app_net_tcp_custom_osd_line_data_t OsdArray[MAX_CUSTOM_OSD_LINE_NUM];
}app_net_tcp_batch_set_osd_data_t;

typedef struct
{
    u32 chn;
    u32 data_type;
    u32 state;
    u32 rev[5];
}app_net_tcp_event_act_485_t;

typedef struct
{
    u32 chn;
    u32 data_type;
}app_net_tcp_event_act_485_data_type_t;

typedef struct
{
    u32 chn;
    u32 data_type;
    u32 value[256];
}app_net_tcp_485_input_alarm_para_t;

typedef struct
{
    u32 enable;
    u32 dev_type;
    u32 dev_id;
    u32 interval;
    char rev[512];
}app_net_tcp_485_dev_t;

typedef struct
{
    u32 data_type;
}app_net_tcp_485_data_type_t;

typedef struct
{
    u32  data_type;
    u32  row;
    u32  col;
    char prefix[32];
    char suffix[32];
    u32  dev_type;
    u32  osd;
    char rev[504];
}app_net_tcp_485_osd_para_t;

typedef struct
{
    u32 dev_type;
    u32 value[255];
    u32 status;
}app_net_tcp_485_input_data_t;

typedef struct
{
    u32  enable;
    char addr[128];
    u32  port;
    u32  interval;
    u32  set_time_zone;
    int  time_zone;
    char rev[248];
}app_net_tcp_sys_ntp_para_t;

typedef struct
{
    char func_list[1600];
    char rev[256];
}app_net_tcp_sys_func_list_t;

typedef struct
{
	unsigned io_alarm_num;
	unsigned rev[7];
}app_net_tcp_io_alarm_num_t;

typedef struct
{
	unsigned index;
	unsigned rev[7];
}app_net_tcp_io_alarm_index_t;

typedef struct
{
	unsigned index;
	unsigned active_level;
	unsigned set_in_out;
	unsigned in_out;
	unsigned rev[12];
}app_net_tcp_io_alarm_attr_t;

typedef struct
{
	unsigned index;
	unsigned active_level;
	unsigned in_out;
	unsigned rev[13];
}app_net_tcp_set_io_alarm_attr_t;

typedef struct
{
	unsigned state;
	unsigned rev[7];
}app_net_tcp_io_alarm_state_t;

typedef struct
{
    unsigned id;
    unsigned type;
    unsigned para_num;
    unsigned para[4];
    unsigned rev[245];
}app_net_tcp_sys_func_state_report_t;

typedef struct
{
    char name[128];
    char rev[128];
}app_net_tcp_func_model_t;

typedef enum
{
    DL_100 = 0,
    DL_302 = 1,
    M_7052 = 2,
    _485_INPUT_DEVICE_TYPE_BUTT,
}_485_input_device_type;
/*
enum
{
    _485_CELS_TEMP = 0,
    _485_FAHR_TEMP = 1,
    _485_HUMI      = 2,
    _485_CO2       = 3,

    _485_IO_0 = 0,
    _485_IO_1 = 1,
    _485_IO_2 = 2,
    _485_IO_3 = 3,
    _485_IO_4 = 4,
    _485_IO_5 = 5,
    _485_IO_6 = 6,
    _485_IO_7 = 7,

    _485_DATA_BUTT = 16,
}_485_INPUT_DATA_TYPE;
*/
enum
{
    APP_NET_RESET_CFG_INCLUDE_IP     = 0,
    APP_NET_RESET_CFG_NOT_INCLUDE_IP,
    APP_NET_RESET_CFG_END
};

enum
{
    ALARM_IO_INPUT  = 0,
    ALARM_IO_OUTPUT = 1
};
typedef struct
{
    unsigned crc;
    unsigned magic[4];
    unsigned ver_num;
    unsigned ver_date;
    unsigned img_len;
    unsigned mem_addr;
    unsigned flag;
    unsigned reserved[56];
}app_sys_param_head_t;
typedef struct
{
	unsigned close_video_stream_send;
	unsigned not_copy_video_stream;
    unsigned not_get_video_stream;
    unsigned not_get_audio_stream;
    unsigned save_enc_stream;

    unsigned send_wnd_stall_len;

    unsigned onvif_func_switch;
    unsigned rtsp_func_switch;
    unsigned search_func_switch;

    unsigned save_raw_enc_stream;
    unsigned save_raw_stream_id;

    unsigned custom_osd_switch;
    unsigned _485_input_switch;

  	int      ntp_time_zone;
    unsigned corridor_mode_switch;
    unsigned remote_io_switch;

    unsigned send_stall_not_break;

	#if CONFIG_PLATFORM_HISI
	    /* BEGIN: Added by zhaojie, 2015/8/24 */
    unsigned encode_switch;//0:1080p 1:3M 2:5M
    unsigned encode_type;//0:h264 1:h265
    unsigned encode_frameRate;//1~30
    unsigned encode_brcMode;//0:CBR 1:VBR 2:fixQP
    unsigned encode_maxbps;//kbps
    /* END:   Added by zhaojie, 2015/8/24 */
    #endif

    #if CONFIG_PLATFORM_HISI
    int      rev[2 * 1024 - 1 - 5];
    #else
    int      rev[2 * 1024 - 1];
    #endif
}app_soft_para_t;

typedef struct
{
    int index;
    int chn;
    int active_level;
    int set_in_out;
    int in_out;
}alarm_io_attr_t;

typedef struct
{
	unsigned        state;
    unsigned        alarm_io_num;
    alarm_io_attr_t alarm_io[CHN_MAX];
}app_alarm_io_para_t;
typedef struct SystemParam
{
    app_sys_param_head_t         head;
    app_net_tcp_sys_login_info_t sys_login;
    app_net_tcp_serial_cfg_t     serial_cfg;
    app_net_tcp_dev_cap_t        dev_cap;
    app_net_tcp_sys_dev_info_t   sys_dev_info;
    app_net_tcp_enc_info_t       enc_info[3];
    app_net_tcp_osd_cfg_t        osd_cfg[2];
    app_net_tcp_pm_cfg_t         pm_cfg[4];
    app_net_tcp_img_color_t      img_color;
    app_net_tcp_img_exp_t        img_exp;
    app_net_tcp_img_wb_t         img_wb;
    app_net_tcp_img_ircut_t      img_ircut;
    app_net_tcp_img_mode_t       img_mode;

    app_net_tcp_event_act_ioout_t  act_ioout;

    app_net_tcp_event_trig_md_base_rc_t  md_base;
    app_net_tcp_event_trig_md_t       md;

    app_net_tcp_audio_ctl_t           audio_input_ctl;
    app_net_tcp_sys_net_vout_t        sys_v_out;

    app_net_tcp_custom_osd_zone_cfg_t custom_osd_zone_cfg[MW_STREAM_MAX];
    app_net_tcp_custom_osd_zone_spec_t custom_osd_zone_spec[MW_STREAM_MAX];
    app_net_tcp_custom_osd_line_cfg_t custom_osd_line_cfg[MW_STREAM_MAX][MAX_CUSTOM_OSD_LINE_NUM];
    app_net_tcp_custom_osd_line_data_t custom_osd_line_data[MW_STREAM_MAX][MAX_CUSTOM_OSD_LINE_NUM];

	   app_net_tcp_sys_ntp_para_t ntp_para;
    app_net_tcp_event_act_485_t act_485[16];
    app_net_tcp_485_input_alarm_para_t _485_input_alarm_para[16];

    app_net_tcp_485_dev_t _485_dev;
    app_net_tcp_485_osd_para_t _485_osd_para[16];

    app_alarm_io_para_t alarm_io_para;

    app_net_tcp_func_model_t func_model;

	   app_soft_para_t soft_para;

    app_net_tcp_sys_net_info_t net_info;

    app_audio_stream_enc_type audio_enc;

    app_web_port_type web_port;



    char     rev1[824]; //1024 - sizeof(app_net_tcp_sys_net_info_t)
	char     rev2[22 * 1024];
	char     rev3[800];
}SystemParam;
#define DATA_TYPE_VIDEO 2




#ifdef __cplusplus
}
#endif

#endif
