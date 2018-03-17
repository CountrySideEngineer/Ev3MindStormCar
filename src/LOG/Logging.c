/**
 *  Logging.c
 *
 *  Log current motor data.
 */
#include "ev3api.h"
#include "CLC_MotorOutput.h"

/*****************************************************************************/
/*                                  変数定義                                 */
/*****************************************************************************/
FILE *logging_file = NULL;

/*****************************************************************************/
/*                                  静的変数                                 */
/*****************************************************************************/
static const char *logging_file_name = "ev3_log.csv";
static const char *logging_header = "CNT,TRT,LP,LI,LD,RP,RI,RD,LFT,RGT,LCR,RCR,TRG,LTRG,RTRG,LHYS,RHYS,DST,AVE,CMD,DIR,MAX,LCNT,RCNT,LNG,RNG\n";
static const char *logging_format = "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n";

/*****************************************************************************/
/*                                  定数定義                                 */
/*****************************************************************************/
static int logging_count;

/*****************************************************************************/
/*                                外部変数宣言                               */
/*****************************************************************************/
extern int turn_ratio;
extern power_t left_power;
extern power_t right_power;
extern int left_motor_power;
extern int right_motor_power;
extern int left_motor_power_current;
extern int right_motor_power_current;
extern int target_motor_output;
extern int target_motor_output_left;
extern int target_motor_output_right;
extern int16_t distance_sensor_value;
extern int16_t distance_average_value;
extern uint8_t cmd_target_motor_output;
extern int cmd_drive_direction;
extern int8_t motor_output_max;
extern int8_t motor_failure_left;
extern int8_t motor_failure_right;
extern uint8_t motor_failure_left_count;
extern uint8_t motor_failure_right_count;
extern int left_motor_power_hys;
extern int right_motor_power_hys;


/*****************************************************************************/
/*                                外部定数定義                               */
/*****************************************************************************/


/*****************************************************************************/
/*                                  外部関数                                 */
/*****************************************************************************/


/*****************************************************************************/
/*                                  関数実装                                 */
/*****************************************************************************/

/**
 * @brief   Open logging file.
 */
void init_logging(void)
{
    logging_file = fopen(logging_file_name, "a");
    if (NULL != logging_file) {
        fprintf(logging_file, (const char *)logging_header);

        logging_count = 0;
    }
}

/**
 * @brief   Close logging file.
 */
void fin_logging(void) 
{
    if (NULL != logging_file) {
        fclose(logging_file);

        logging_count = 0;
        
    }
}

/**
 * @brief   Write log data to logging file in csv format.
 */
void logging_data(void)
{
    if (NULL != logging_file) {
        fprintf(logging_file, 
            logging_format,
            logging_count,
            turn_ratio,
            left_power.diff, left_power.integral, left_power.ddt,
            right_power.diff, right_power.integral, right_power.ddt,
            left_motor_power, right_motor_power,
            left_motor_power_current, right_motor_power_current,
            target_motor_output, target_motor_output_left, target_motor_output_right,
            left_motor_power_hys, right_motor_power_hys,
            distance_sensor_value, distance_average_value,
            (int)cmd_target_motor_output, cmd_drive_direction,
            (int)motor_output_max,
            (int)motor_failure_left_count,
            (int)motor_failure_right_count,
            (int)motor_failure_left,
            (int)motor_failure_right
            );

            logging_count++;
    }
}
