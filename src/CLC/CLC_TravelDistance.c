/**
 *  CLC_TravelDistance.c
 *
 * Calculate travel distance from motor count.
 */
#include "ev3api.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
int32_t left_motor_trav_dist_hi_acc;    //Unit:mm LSB:0.01
int32_t right_motor_trav_dist_hi_acc;   //Unit:mm LSB:0.01
int32_t left_motor_trav_dist;           //Unit:mm LSB:1.0
int32_t right_motor_trav_dist;          //Unit:mm LSB:1.0
uint32_t left_motor_trav_dist_abs;      //Unit:mm LSB:1.0
uint32_t right_motor_trav_dista_abs;    //Unit:mm LSB:1.0
int32_t left_motor_count_prev;
int32_t right_motor_count_prev;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
static const int RADIUS = 28;   //Unit:mm LSB:1
static const int PI = 314;      //Unit:- LSB:0.01

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int32_t left_motor_count;
extern int32_t right_motor_count;

/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/
static int32_t calc_distance(int32_t count, int32_t count_prev);

/**
 * @brief   Calcultate travel distance.
 */
void calc_trav_distance(void) {
    int32_t distance = 0;

    //left_motor
    distance = calc_distance(left_motor_count, left_motor_count_prev);
    left_motor_trav_dist_hi_acc += distance;
    left_motor_trav_dist = left_motor_trav_dist_hi_acc / 100;    //Convert LSB from 0.01 to 1.
    if (distance < 0) {
        left_motor_trav_dist_abs -= (distance / 100);
    } else {
        left_motor_trav_dist_abs += (distance / 100);
    }

    //right_motor
    distance = calc_distance(right_motor_count, right_motor_count_prev);
    right_motor_trav_dist_hi_acc += distance;
    right_motor_trav_dist = right_motor_trav_dist_hi_acc / 100;   //Convert LSB from 0.01 to 1.
    if (distance < 0) {
        right_motor_trav_dista_abs -= (distance / 100);
    } else {
        right_motor_trav_dista_abs += (distance / 100);
    }

    left_motor_count_prev = left_motor_count;
    right_motor_count_prev = right_motor_count;
}

/**
 * @brief   Calc travel distance from count and that of previous cycle.
 *          The calculated value has high accuracy.
 */
static int32_t calc_distance(int32_t count, int32_t count_prev) {
    int32_t dcount = 0;
    int32_t distance = 0;

    dcount = count - count_prev;
    distance = PI * RADIUS * dcount / 180;

    return distance;
}

/**
 * @brief   Initialize variables used to calculate travel distance.
 */
void init_motor_distance(void) {
    left_motor_trav_dist_hi_acc = 0;
    right_motor_trav_dist_hi_acc = 0;
    left_motor_trav_dist = 0;
    right_motor_trav_dist = 0;
    left_motor_trav_dist_abs = 0;
    right_motor_trav_dista_abs = 0;
    left_motor_count_prev = 0;
    right_motor_count_prev = 0;
}
