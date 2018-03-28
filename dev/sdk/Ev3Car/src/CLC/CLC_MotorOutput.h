#pragma once

extern void calc_motor_power(void);

//PIDêßå‰ÇÃÇΩÇﬂÇÃç\ë¢ëÃ
typedef struct _power_t {
    int target;
    int target_prev;
    int current;
    int diff;       //P Term
    int integral;   //I Term
    int ddt;        //D Term
    int reset_count;
} power_t;

