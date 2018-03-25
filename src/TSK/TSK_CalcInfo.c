/**
 *  TSK_CalcInfo.c
 *
 *  Task of informatino calculation.
 */
#include "ev3api.h"
#include "TSK_CalcInfo.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
int calc_info_task_count = 0;
bool_t calc_info_task_running;

/*****************************************************************************/
/*                                  �ÓI�ϐ�                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �萔��`                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���ϐ��錾                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                �O���萔��`                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  �O���֐�                                 */
/*****************************************************************************/
extern void init_travel_speed(void);
extern void calc_travel_speed(void);

/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/

/**
 * @brief   Task of calculation of information.
 */
void calc_info_task(intptr_t unused) {
    while (calc_info_task_running) {
        calc_info_task_count++;

        calc_travel_speed();

        dly_tsk(CALC_INFO_TASK_INTERVAL);
    }
}

/**
 * @brief   Initialize parameters of this task.
 */
void init_calc_info_task(void) {
    calc_info_task_count = 0;
    calc_info_task_running = false;

    init_travel_speed();
}

/**
 * @brief   Start calculation information task.
 */
void start_calc_info_task(void) {
    ER ercd;

    if (false == calc_info_task_running) {
        ercd = act_tsk(CALC_INFO_TASK);
        if (E_OK == ercd) {
            calc_info_task_running = true;
        } else {
            calc_info_task_running = false;
        }
    }
}

/**
 * @brief   Stop calculation information task.
 */
void stop_calc_info_task(void) {
    if (true == calc_info_task_running) {
        calc_info_task_running = false;
    }
}