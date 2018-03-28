#include <kernel.h>
#include "common/module_common.h"
#include "target_config.h"
#include "platform_interface_layer.h"
#include "csl.h"
#include "chip_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_serial.h"
#include "target_serial_dbsio.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "api.cfg.h"
#include "app.h"
#include "./TSK/TSK_Mode.h"
#include "./TSK/TSK_Bt.h"
#include "./TSK/TSK_cmd.h"
#include "./TSK/TSK_Safe.h"
#include "./TSK/TSK_Motor.h"
#include "./TSK/TSK_Log.h"
#include "./TSK/TSK_Sensor.h"
#include "./TSK/TSK_CalcInfo.h"

ID _module_id_APP_INIT_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_APP_INIT_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_MODE_1_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_MODE_1_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_MODE_2_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_MODE_2_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_MODE_3_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_MODE_3_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_MODE_4_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_MODE_4_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_BTTASK __attribute__((section (".module.text")));
static STK_T _module_ustack_BTTASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_SAFE_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_SAFE_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_MOTOR_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_MOTOR_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_LOG_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_LOG_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_SENSOR_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_SENSOR_TASK[COUNT_STK_T(STACK_SIZE)];

ID _module_id_CALC_INFO_TASK __attribute__((section (".module.text")));
static STK_T _module_ustack_CALC_INFO_TASK[COUNT_STK_T(STACK_SIZE)];

static const T_CTSK _module_ctsk_tab[11] = {
	{ TA_ACT, 0, _app_init_task, TPRI_APP_INIT_TASK, ROUND_STK_T(STACK_SIZE), _module_ustack_APP_INIT_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_ACT, 0, task_mode1, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_MODE_1_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, task_mode2, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_MODE_2_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, task_mode3, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_MODE_3_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, task_mode4, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_MODE_4_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, BtTask, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_BTTASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, safe_task, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_SAFE_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, motor_task, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_MOTOR_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, log_task, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_LOG_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, sensor_task, TMIN_APP_TPRI, ROUND_STK_T(STACK_SIZE), _module_ustack_SENSOR_TASK, DEFAULT_SSTKSZ, NULL },
	{ TA_NULL, 0, calc_info_task, TMIN_APP_TPRI + 1, ROUND_STK_T(STACK_SIZE), _module_ustack_CALC_INFO_TASK, DEFAULT_SSTKSZ, NULL },
};

const SIZE _module_cfg_entry_num = 11;

const MOD_CFG_ENTRY _module_cfg_tab[11] = {
	{ TSFN_CRE_TSK, &_module_ctsk_tab[0], &_module_id_APP_INIT_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[1], &_module_id_MODE_1_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[2], &_module_id_MODE_2_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[3], &_module_id_MODE_3_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[4], &_module_id_MODE_4_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[5], &_module_id_BTTASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[6], &_module_id_SAFE_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[7], &_module_id_MOTOR_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[8], &_module_id_LOG_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[9], &_module_id_SENSOR_TASK },
	{ TSFN_CRE_TSK, &_module_ctsk_tab[10], &_module_id_CALC_INFO_TASK },
};

const uint32_t _module_pil_version = PIL_VERSION;
