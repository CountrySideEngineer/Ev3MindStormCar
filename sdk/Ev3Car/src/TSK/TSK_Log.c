/**
 *  TSK_Log.c
 *
 *  Task for logging.
 */
#include "ev3api.h"
#include "TSK_Log.h"

/*****************************************************************************/
/*                                  �ϐ���`                                 */
/*****************************************************************************/
bool_t log_task_running;
int log_task_count;

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
extern void init_logging(void);
extern void fin_logging(void);
extern void logging_data(void);

/*****************************************************************************/
/*                                  �֐�����                                 */
/*****************************************************************************/

/**
 *  @brief  Initialize logging setting.
 */
void init_log_task(void)
{
    init_logging();

    log_task_running = false;
    log_task_count = 0;
}

/**
 *  @brief  finalize logging.
 */
void fin_log(void)
{
    fin_logging();

    log_task_running = false;
}

/**
 *  @brief  Main funtion of log task.
 */
void log_task(intptr_t unused)
{
    while (log_task_running) {
        log_task_count++;

        logging_data();

        dly_tsk(TASK_LOG_INTERVAL);
    }
}

/**
 *  @brief  Start logging task.
 */
void start_log_task(void)
{
    ER ercd;

    if (false == log_task_running) {
        ercd = act_tsk(LOG_TASK);
        if (E_OK == ercd) {
            log_task_running = true;
        } else {
            log_task_running = false;
        }
    }
}

/**
 *  @brief  Stop logging task and clear the flag representing
 */
void stop_log_task(void)
{
    if (true == log_task_running) {
        log_task_running = false;
    }
}