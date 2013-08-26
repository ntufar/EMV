
//----------------------------------------------------------------------------
//	DIPLAY Functions....
//----------------------------------------------------------------------------

#define  OK			0
#define  ERROR			-1

#define  SUCCESS		0
#define  FAILURE		-1  

#define  DISP_OK		0
#define  DISP_ERROR		-1
#define  DISP_NO_MSG		-1
#define  DISP_TIMEOUT		0
#define  DISP_KEYPRESSED	1

#define  CLR_LINE		1
#define  CLR_EOL		2
#define  CLR_CLEAR		3

#define  DISP_NO_SCR		0
#define  DISP_H_SCR		1
#define  DISP_V_SCR		2

#define  DISP_ENTER_REQ		0
#define  ENTER_REQ		DISP_ENTER_REQ
#define  DISP_NO_ENTER		1
#define  NO_ENTER		DISP_NO_ENTER

#define  FORWARD		0
#define  BACKWARD		1
#define  REVERSE		BACKWARD

#define  DISP_NULL		-1
#define  DISP_OFFSET_OVER	-2

#define  DISP_NORMAL_MODE	0
#define  DISP_REVERSE_MODE	1

int DISP_initialize(void);
int DISP_close(void);
char DISP_display_series(char *message[], unsigned int num_message,
unsigned int delay, char *error_prompt, long int valid_keys);
void DISP_clr_eol(void);
void DISP_clr_scr(void);
void DISP_clr_line(void);
void DISP_del_line(void);
int  DISP_display(char *string);
int  DISP_display_repos(int column, int line, char *string, int clear);
int  DISP_display_new(char *string);
int  DISP_get_pix_type(void);
int  DISP_gotoxy(int x, int y);
int  DISP_get_scroll_status(void);
void DISP_insert_line(void);
int  DISP_prompt(char *string, unsigned int wait_time, int option);
int  DISP_prompt_at(int column, int line, char *message, unsigned int wait_time, int option);
int  DISP_reset_display(char *font, int grid_id);
int  DISP_scroll_buffer(char *buffer, int incrment, unsigned long valid_keys,
unsigned int scroll_offset, char scroll_left, char scroll_right, 
char exit_key, char *key_buf);
int DISP_scroll_long_buf(char *message, unsigned int scroll_offset, 
char scoll_left, char scroll_right, unsigned long valid_keys, 
char exit_key, char key_max, char *key_buffer, char enter_reqired, 
unsigned int increment);
void DISP_set_contrast(int level);
void DISP_set_display_scroll_mode(int mode); 
void DISP_set_scroll_mode(int mode);
int  DISP_str_to_dsp_len(char *source, unsigned int offset, char display_width, 
char dir);
int  DISP_view_buffer(char *buffer, int increment, unsigned long key_map);
void DISP_where_cursor(int *x, int *y);
void DISP_where_window(int *x1, int *y1, int *x2, int *y2);
void DISP_where_window_cursor( int *x, int *y);
void DISP_window(int x1, int y1, int x2, int y2);
void DISP_set_reverse_mode(void);
void DISP_set_normal_mode(void);
int  DISP_get_info(int type);
int DISP_display_bmp(unsigned int x, unsigned int y, char *filename, int mode);
int  DISP_display_char(char character);

#define OR_PUT			0
#define COPY_PUT		1

#define  DISP_CPR		0
#define  DISP_CPC		1
#define  DISP_PPR		2
#define  DISP_PPC		3
#define  DISP_PTC		4
#define  DISP_NOF		5
#define  DISP_TYPE		6
#define  DISP_CONTRAST		7

// grid
// 0	:  8 * 16  ( 4096bytes)   16column
// 1	: 16 * 16  ( 8192bytes)    8column
struct font_info{
	char name[9];		// 8byte + NULL
	unsigned char x;	// 8 or 16
	unsigned char y;	// 16 
	unsigned char ffu[5];	// 
};

int DISP_get_font_info(struct font_info *pinfo);
int DISP_get_font_width(void);
unsigned char DISP_get_font_status(void);
//  0x00 : normal
//  0x01 : X-double
//  0x02 : Y-double
//  0x03 : X-double & Y-double
int DISP_register_font(char *fontname);
int DISP_unregister_font(char *fontname);
int DISP_active_font(char *fontiname);
int DISP_get_font_list(char *fontlist);
int DISP_get_font_name(char *fontname);
int DISP_set_normal(void);
int DISP_set_bold(void);
int DISP_reset_bold(void);
int DISP_set_x_double(void);
int DISP_set_x_normal(void);
int DISP_set_y_double(void);
int DISP_set_y_normal(void);
int DISP_set_xy_double(void);
void changenumber(char *dispbuffer,char *kbuffer,int fraction, int punctuate);
//----------------------------------------------------------------------------
#if 0
int  FONT_get_font_def(char *font);
int  FONT_get_font_info(int index, char *buffer);
int  FONT_getgrid(void);
int  FONT_set_font_def(char *font);
#endif

void GRAPH_put_pixel_column(char *buffer, int length);

//int  CRC_calculation(char type, int size, char *buffer);
unsigned short  CRC_calculation(char type, int size, char *buffer);

int  BARCODE_get_info(int type);



//----------------------------------------------------------------------------
//	MODEM Functions....
//----------------------------------------------------------------------------
#define  SUCCESS		0
#define  FAILURE		-1  
#define  ERROR_FORMAT_CMD	-2
#define  ERROR_WRITE_CMD	-3
#define  ERROR_WRITE		-3
#define  ERROR_HR_TIMEOUT	-4
//#define  TIMEOUT		-4
#define  ERROR_READ_CMD		-5
#define  ERROR_READ		-5
#define  ERROR_ONLY_CR		-6
#define  ERROR_OPEN		-7
#define  ERROR_CLOSE		-8
#define  ERROR_STATUS		-9
#define  ERROR_OUTPUT_PENDING   -10
#define  OUTPUT_PENDING		-10
#define  ERROR_INPUT_PENDING	-11
#define  INPUT_PENDING		-11
#define  ERROR_OUTPUT_FAILED	-12
#define  OUTPUT_FAILED		-12
#define  ERROR_REJECT_Q		-13
#define  ERROR_FLUSH		-14
#define  ERROR_PRO_SET		-15
#define  ERROR_NO_LINE		-16
#define  NO_LINE		-16
//#define  ERROR_HAYES		-17
//#define  HAYES_ERROR		-17
#define  ERROR_INVALID_RESP	-18
#define  ERROR_READ_PROTOCOL	-19
#define  ERROR_INVALID_PARM	-20
#define  ERROR_NO_CARRIER	-21
#define  ERROR_PARTIAL		-22
#define  ERROR_READ_FLUSH	-23
#define  ERROR_NOT_OPENED	-24
#define  ERROR_INVALID_HANDLE	-25
#define  ERROR_ALREADY_OPEN	-26
#define  ERROR_ALREADY_CONN	-27

#define  ERROR_LATCH		-30
#define  ERROR_PARITY		-31
#define  ERROR_OVERRUN		-32
#define  ERROR_PARITY_OVERRUN	-33
#define  ERROR_FRAMING		-34
#define  ERROR_PARITY_FRAME	-35
#define  ERROR_FRAME_OVERRUN	-36
#define  ERROR_PARITY_FRAME_OVERRUN	-37

#define  PENDING		1

#define  E_PARITY		0x00
#define  E_PARITY_OVERRUN	0x01
#define  E_PARITY_FRAME		0x02
#define  E_OVERRUN		0x04
#define  E_FRAME_OVERRUN	0x08
#define  E_FRAMING		0x10
#define  MDM_BREAK		0x20
#define  MDM_CTS		0x40
#define  MDM_DCD		0x80

#define  HAYES_OK		0
#define  HANGUP_OK		0
#define  CONN_2400		1
#define  CONNECTION_2400	1
#define  RING_DETECT		2
#define  NO_CARRIER		3
#define  HAYES_ERROR		4
#define  CONN_1200		5
#define  CONNECTION_1200	5
#define  NO_DIALTONE		6
#define  BUSY			7
#define  NO_ANSWER		8
#define  CONNECT		9
#define  ERROR_HAYES		HAYES_ERROR
#define  TIMEOUT		-4

#define  HAYES_OK_MSG		"OK"
#define  CONN_2400_MSG		"CONNECT 2400"
#define  RING_DETECT_MSG	"RING"
#define  NO_CARRIER_MSG		"NO CARRIER"
#define  HAYES_ERROR_MSG	"ERROR"
#define  CONN_1200_MSG		"CONNECT 1200"
#define  NO_DIALTONE_MSG	"NO DIALTONE"
#define  BUSY_MSG		"BUSY"
#define  NO_ANSWER_MSG		"NO ANSWER"

#define  MDM_S_BREAKABORT	0x80
#define  MDM_S_ZERO		0x40
#define  MDM_S_CTS		0x20
#define  MDM_S_RI		0x10
#define  MDM_S_DCD		0x08
#define  MDM_S_FRAME		0x04
#define  MDM_S_OVERRUN		0x02
#define  MDM_S_PARITY		0x01

#define  CHAR_PROTOCOL		1
#define  PACKET_PROTOCOL	2
#define  VISA1_PROTOCOL		3
#define  SDLC_PROTOCOL		4
#define  CUSTOM_PROTOCOL	5

int MODEM_open(int *modem_handle, int max_wait_time);
int MODEM_clear(int modem_handle, int max_wait_time);
int MODEM_close(int modem_handle, int output_pending, int input_pending, int ring_detect,
int output_failed, char *buffer, int buffer_size);
int MODEM_initialization(int modem_handle, int max_wait_time);
int MODEM_line_check(int modem_handle);
int MODEM_get_stat(int modem_handle, unsigned char stat_map);
int MODEM_check_line_dial(int modem_handle, char *dialno, int *iwrite_return, int max_wait_time);
int MODEM_get_dial_stat(int modem_handle, int max_wait_time);
int MODEM_disconnect(int modem_handle, int max_wait_time);
int MODEM_dial_check(int modem_handle, int max_wait_time);
int MODEM_clear_receive(int modem_handle);
int MODEM_read_param(int modem_handle);
int MODEM_data_receive(int modem_handle, char *buffer, int min_size, int max_size, int max_wait_time);
int MODEM_err_reset(int modem_handle);
int MODEM_data_send(int modem_handle, char *buffer, int buff_length, int max_time_out);

int MODEM_hayes_ctrl(int modem_handle, char command, char *buffer, int max_wait_time);
int MODEM_hayes_disp(int hayes_code, char *buffer);
int MODEM_hayes_clear(int modem_handle);
int MODEM_hayes_resp(int modem_handle, int max_wait_time);
int MODEM_hayes_send(int modem_handle, char *command_buff);
int MODEM_hayes_stat(int modem_handle, int max_wait_time, char command);
int MODEM_pending_input_mess(int modem_handle);

// added	2002.Apl.18
int MODEM_pending_output_mess(int modem_handle);
int MODEM_stat(int modem_handle);
extern int Modem_Status;
#define ZMD_DTR		0x002		// Data Terminal Ready 
#define ZMD_RTS		0x004		// Request To Send
#define ZMD_CTS		0x020		// Clear To Send
#define ZMD_DCD		0x040		// Data Carrier Detect
#define ZMD_RNG		0x080		// RING
#define ZMD_DSR		0x100		// Data Set Ready

extern int errno;

// added	2002.May,17
#define  DATA_8BITS	8
#define  DATA_7BITS	7
#define  DATA_6BITS	6
#define  NONE_PARITY	0
#define  ODD_PARITY	1
#define  EVEN_PARITY	2
#define  STOP_1BITS	1
#define	 STOP_2BITS	2
int MODEM_set_comm( int data, int parity, int stop );
void MODEM_get_comm( int *data, int *parity, int *stop );
int MODEM_dial(int modem_handle, char *dialno, int max_wait_time);
#define	MDM_ASYNC_MODE	0
#define	MDM_SDLC_MODE	1
int MODEM_set_mode(int mode, unsigned char address);
int MODEM_get_mode(void);

//Temporary Functions...
int MODEM_sdlc_direct_message(int length, unsigned char *message);
int MODEM_send_ATcommand(unsigned char *command);
//----------------------------------------------------------------------------
//	ISO_8583 MAP Functions....
//----------------------------------------------------------------------------
typedef struct {
	int pid;
	int mid;
	int field_size;
	int convert_index;
	void *variable;
	int size_var;
} variant_struct;

typedef struct {
	int field_number;
	int field_size;
	int convert_index;
	void *variable;
	int size_var;
} field_struct;

typedef int (*(converters[2])) (int cnt);

#define  ISO_ASSEMBLE		0
#define  ISO_DISASSEMBLE	1

#define  FIELD_NOT_DEFINED	-1
#define  LIMIT_OVER_BUFFER      -2
#define  EXCEED_VALID_DATA	-3
#define  LIMIT_OVER_INCOME	-4
#define  NO_MATCHING_VARIANT	-5
#define  INVALID_TYPE		-6
#define  INVALID_CVT_IDX	-7
#define  INVALID_MAP_SIZE	-8

#define  END_FILED	256
#define  FIELD_END	256

#define  ASC_ASC	0
#define  AV3_AV3	1
#define  BIT_BIT	2
#define  BCD_BCD	3
#define  BCD_ASC	4
#define  ASC_BCD	4
#define  ASC_STR	5
#define  STR_ASC	5
#define  BCD_STR	6
#define  STR_BCD	6
#define  BCD_SNZ	7
#define  SNZ_BCD	7
#define  AV2_STR	8
#define  STR_AV2	8
#define  BV2_STR	9
#define  STR_BV2	9
#define  AV3_STR	10
#define  STR_AV3	10
#define  XBC_STR	11
#define  STR_XBC	11
#define  BIN_HST	12
#define  HST_BIN	12
#define  BI2_HST	13
#define  HST_BI2	13
#define  BI3_HST	14
#define  HST_BI3	14
#define  COMPUTE	-1
#define  VARIANT	-2


//    Must be in application codes... (library will call that functions...)
//	unsigned int return_variant1();
//	unsigned int return_variant2();
//
//    these variables are in library....   to use 
//      unsigned char *src_8583, *dst_8583;
//      	to use in application => extern unsigned char *src_8583, *dst_8583;


void ISO_clear_map(unsigned char *iso_map, int max_fields_number);
int ISO_test_field_no(unsigned char *iso_map, int field_no);
void ISO_set_field_no(unsigned char *map, int field_no);
void ISO_reset_field_no(unsigned char *map, int field_no);
void ISO_construct_map(unsigned char *map, ...);
//int ISO_perform_packet(int type, field_struct *field_table, unsigned char *map,	unsigned char *buffer, int max_size);
int ISO_perform_packet(int type, field_struct *field_table, unsigned char *map,	int mapsize, unsigned char *buffer, int max_size);

//----------------------------------------------------------------------------
//	KEYBOARD Functions....
//----------------------------------------------------------------------------
// because the keyboard of our terminal is not 'stdin', 
// must call to 'openkey()' at the beginning of program...
int KEY_open(void);
	// return  0 : OK
	//        -1 : ERROR
void KEY_close(void);
char KEY_get_key(void);
int KEY_is_key(void);
int KEY_get_ch(void);
void KEY_flush(void);

#define  LKEY_F1	'a'
#define  LKEY_F2	'b'
#define  LKEY_F3	'c'
#define  LKEY_F4	'd'
#define  LKEY_1		'1'
#define  LKEY_2		'2'
#define  LKEY_3		'3'
#define  LKEY_4		'4'
#define  LKEY_5		'5'
#define  LKEY_6		'6'
#define  LKEY_7		'7'
#define  LKEY_8		'8'
#define  LKEY_9		'9'
#define  LKEY_0		'0'
#define  LKEY_AS	'*'
#define  LKEY_SH	'-'
#define  LKEY_BS	0x08
#define  LKEY_ESC	0x1b
#define  LKEY_ENTER	0x0d
#define  LKEY_ALPHA	0x40

int  KEY_get_info(int type);
int  KEY_get_numeric(char *buffer, int max, int min, int fraction, int punctuate);
int  KEY_get_text(char *buffer, int max, int min, int type);

//----------------------------------------------------------------------------
//	KEYBOARD Functions....
//----------------------------------------------------------------------------
int PRN_open(void);
void PRN_close(void);
void PRN_initialize(void);
unsigned char PRN_get_status(void);
#define PRINT_ING       1
#define PRINT_END	2
#define PAPER_OUT	3
#define LINE_OFF	4
void PRN_print_line(char *buffer, int length);
// after print a string by length, new line...
void PRN_print_char(char character);
// printing a character...
void PRN_print_buffer(char *buffer);
// printing a string..., no new line
void PRN_line_feed(void);
void PRN_line_back(void);

// grid
// 0	:  8 * 16  ( 4096bytes)   48column
// 1	: 12 * 24  (12288bytes)   32column
int PRN_get_font_info(struct font_info *pinfo);
int PRN_get_font_width(void);
unsigned char PRN_get_font_status(void);
//  0x00 : normal
//  0x01 : X-double
//  0x02 : Y-double
//  0x03 : X-double & Y-double
int PRN_register_font(char *fontname);
int PRN_unregister_font(char *fontname);
int PRN_active_font(char *fontname);
int PRN_get_font_list(char *fontlist);
int PRN_get_font_name(char *fontname);

// initialize		: ESC + '@' 	       
// Setting X-double... 	: ESC + 'W' + '1'
// Setting X-normal... 	: ESC + 'W' + '0'
// Setting Y-double... 	: ESC + 'w' + '1'
// Setting Y-normal... 	: ESC + 'w' + '0'
// Setting Bold... 	: ESC + 'B'
// Setting No-Bold...   : ESC + 'b' 
// Setting Underline... : ESC + 'U'
// Setting No-Underline : ESC + 'u' 
//----------------------------------------------------------------------------
//	MSCR Functions....
//----------------------------------------------------------------------------
struct TRACK 
{
	char acct[23];
	char exp[5];
	char name[27];
	char type[4];
	char PVN[6];
	char disc[17];
	char track[108];	
};	

#define  MCR_DUALTRACK		0x01
#define  MCR_TRACK1		0x02
#define  MCR_TRACK2		0x04
#define  MCR_TRACK3		0x08
#define  MCR_TRIPLETRACK	0x10

int MCR_get_info(void);
int MCR_get_data( char *tracks );
int MCR_parse(char *track, struct TRACK *parsed, char *order);

//----------------------------------------------------------------------------
//	PINPAD Functions....
//----------------------------------------------------------------------------
int PINPAD_send_master_key(unsigned int index, char *master_key);
int PINPAD_request_pin(unsigned int x, unsigned int y, unsigned int index, char func, char *working_key, char *account, char *result);
int PINPAD_cancel_request(void);


//----------------------------------------------------------------------------
//	SCR Functions....
//----------------------------------------------------------------------------
void SCR_flush(void);
int SCR_open(void);
int SCR_close(void);
int SCR_send_data(unsigned int len, char *buffer);
int SCR_read_data(char *buffer);
int SCR_read_byte(char *buf);
int SCR_set_speed(int speed);


//----------------------------------------------------------------------------
//	SERIAL Functions....
//----------------------------------------------------------------------------
void SERIAL_flush(void);
int SERIAL_open(void);
int SERAIL_close(void);
int SERIAL_send_data(int len, char *buffer);
int SERIAL_read_data(char *buffer, int length);
int SERIAL_read_byte(char *buffer);
int SERIAL_set_comm(int data, int parity, int stop);
int SERIAL_set_speed(int speed);

#define  S_SPEED_300 	1
#define  S_SPEED_600 	2
#define  S_SPEED_1200 	3
#define  S_SPEED_2400 	4
#define  S_SPEED_4800 	5
#define  S_SPEED_9600 	6
#define  S_SPEED_19200	7
#define  S_SPEED_38400	8
#define  S_SPEED_57600	9
#define  S_SPEED_115200	10
/*
#define  DATA_8BITS	8
#define  DATA_7BITS	7
#define  DATA_6BITS	6
#define  NONE_PARITY	0
#define  ODD_PARITY	1
#define  EVEN_PARITY	2
#define  STOP_1BITS	1
#define	 STOP_2BITS	2
*/
//----------------------------------------------------------------------------
//	SVC Functions....
//----------------------------------------------------------------------------
#define  TICKS_PER_SEC	1000

int SVC_TICKS(int action, long *tm);
long getusectime(void);
//------------------------------- end of file ----------------------------------



