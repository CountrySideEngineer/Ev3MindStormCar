/**
 *  URT_Debug.c
 *
 *  Send message to UART port for debug
 */
#include "ev3api.h"
#include <stdarg.h>
#include <syssvc/serial.h>

#define DEBUG_DISPLAY_LCD
//#define DEBUG_DISPLAY_UART
#if defined(DEBUG_DISPLAY_LCD)
#if defined(DEBUG_DISPLAY_UART)
#error "Both DEBUG_DISPLAY_LCD and DEBUG_DISPLAY_UART are define."
#endif  //defined(DEBUG_DISPLAY_UART)
#endif  //defined(DEBUG_DISPLAY_LCD)
#if !defined(DEBUG_DISPLAY_LCD)
#if !defined(DEBUG_DISPLAY_UART)
#error "DEBUG_DISPLAY_LCD or DEBUG_DISPLAY_UART must be defined."
#endif  //!defined(DEBUG_DISPLAY_UART)
#endif  //!defined(DEBUG_DISPLAY_LCD)

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int cur_mode;
extern int bt_task_count;
extern int cmd_hdl_count;
extern int mode_task_count;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int debug_config = -1;
int debug_task_count = 0;
FILE *debug_file = NULL;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/
static int32_t font_size_width;
static int32_t font_size_height;
static int32_t char_num;
static int32_t line_num;
#define MSG_BUF_SIZE    (64)
static char msg_buf[MSG_BUF_SIZE];

/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
//関数宣言
void debug_write_msg(const char *msg, int line_index);

/**
 *  @brief  シリアルによるデバッグ設定の初期化を行う。
 */
void init_debug_uart(void) {
    ER ret;
    lcdfont_t font_size = EV3_FONT_SMALL;
    
    ev3_lcd_set_font(font_size);
    
    ret = ev3_font_get_size(font_size,
        &font_size_width,
        &font_size_height);
    if (E_OK == ret) {
        debug_config = 0;

        char_num = EV3_LCD_WIDTH / font_size_width;
        line_num = EV3_LCD_HEIGHT / font_size_height;
    } else if (E_ID == ret) {
        debug_config = 1;
    } else {
        debug_config = 2;
    }
}


/**
 *  @brief  バッファーの初期化関数。
 *          引数で指定されたバッファーを、'\0'で初期化する。
 *
 *  @param[in,out]  buf     初期化対象のバッファーへのポインタ
 *  @param          buf_len 初期化対象のバッファのサイズ
 */
static void reset_buf(char *buf, int buf_len) {
    int idx;
    
    for (idx = 0; idx < buf_len; idx++) {
        *buf = (char)0;
        buf++;
    }
}

/**
 *  @brief  デバッグのための関数。
 *          デバッグデータを、Ev3のLCDに表示する。
 */
void debug_device_info(void) {
    int32_t line_pos_x = 0;

    reset_buf((char *)&msg_buf[0], MSG_BUF_SIZE);

    sprintf((char *)&msg_buf[0], "APP_MOD = %d", cur_mode);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "BLT_TSK_CNT = %5d", bt_task_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "CMD_HDL_CNT = %5d", cmd_hdl_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;

    sprintf((char *)&msg_buf[0], "MOD_TSK_CNT = %5d", mode_task_count);
    debug_write_msg((char *)&msg_buf[0], line_pos_x);
    line_pos_x++;
}

/**
 *  @brief  デバッグ共通関数。
 *          デバッグ用のメッセージを、LCDに表示する。
 *
 *  @param[in,out]  msg 表示文字列へのポインタ
 *  @param          line_index  文字列を表示する行番号
 */
void debug_write_msg(const char *msg, int line_index) {
    int32_t line_pos_x = 0;

    //基本的に引数にNULLが指定されることはないが、念のために確認する。
    if (NULL != msg) {
        line_pos_x = font_size_height * ((int32_t)line_index);
        
        ev3_lcd_draw_string((char *)msg, 0, line_pos_x);
    }
}

/**
 *  @brief  デバッグの表示をクリアする。
 */
void debug_clear(void) {
    int line_index;
    int char_index;

    reset_buf((char *)&msg_buf[0], MSG_BUF_SIZE);

    for (char_index = 0; char_index < char_num; char_index++) {
        msg_buf[char_index] = ' ';
    }

    for (line_index = 0; line_index < line_num; line_index++) {
        debug_write_msg((char *)&msg_buf[0], line_index);
    }
}
