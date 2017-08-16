/**
 *  led_output.c
 *
 *  Change led on ev3-intelligent-box following warning state parameter.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int led_config = -1;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
/**
 *  @brief  Reset led display.
 *          The initial value is "OFF".
 */
void init_led_color(void) {
    ER ret;

    ret = ev3_led_set_color(LED_OFF);
    if (E_OK == ret) {
        led_config = 0;
    } else if (E_ID == ret) {
        led_config = 1;
    } else if (E_PAR == ret) {
        led_config = 2;
    } else {
        led_config = 3;
    }
}

/*
 *  @brief  Set LED color off.
 */
void set_led_color_off(void) { ev3_led_set_color(LED_OFF); }

/**
 *  @brief  Set LED color red.
 */
void set_led_color_red(void) { ev3_led_set_color(LED_RED); }

/**
 *  @brief  Set LED color green.
 */
void set_led_color_green(void) { ev3_led_set_color(LED_GREEN); }

/**
 *  @brief  Set LED color orange.
 */
void set_led_color_orange(void) { ev3_led_set_color(LED_ORANGE); }
