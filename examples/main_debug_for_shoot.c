#include "zf_common_headfile.h"
#include "camera.h"
#include "control.h"
#include "servo.h"
#include "motor.h"
#include <stdio.h>
#include "encoder.h"
#include "pid.h"
#include "brushless.h"
#include "Target_Ring.h"
#include "Shoot.h"

#define UART_DEBUG_PRINT_ENABLE 1
#ifndef UART_DEBUG_PRINT_DIV
#define UART_DEBUG_PRINT_DIV 4
#endif

void main(void)
{
#if UART_DEBUG_PRINT_ENABLE
    static char debug_str[224];
    uint8 uart_dbg_div = 0;

    uint8 vofa_sstate = 0;
    uint8 vofa_tflag = 0;
    uint8 vofa_tstage = 0;
    uint8 vofa_far = 0;
    uint8 vofa_stop = 0;
    uint8 vofa_fire = 0;
    uint8 vofa_tx = 0;
    uint8 vofa_ty = 0;
    uint8 vofa_outer = 0;
    uint8 vofa_score = 0;
    uint8 vofa_votes = 0;
    uint8 vofa_rvotes = 0;
    uint8 vofa_near_votes = 0;
    uint8 vofa_stop_votes = 0;
    uint8 vofa_rstop_votes = 0;
    uint8 vofa_spread = 0;
    uint8 vofa_fire_window = 0;
    uint8 vofa_stable = 0;
    uint8 vofa_conf = 0;
    int16 vofa_err = 0;
    int16 vofa_aim_used = 0;
    int16 vofa_aim_pred = 0;
    uint8 vofa_slow = 0;
    uint8 vofa_stop_req = 0;
    uint8 vofa_rev_req = 0;
    uint8 vofa_fwd_req = 0;
    uint8 vofa_laser = 0;
    uint8 vofa_done = 0;
    int16 vofa_sangle = 0;
    int16 vofa_lt = 0;
    int16 vofa_rt = 0;
#endif

    clock_init(SYSTEM_CLOCK_96M);
    debug_init();

    motor_init();
    encoder_init();
    servo_init();
    shoot_init();
    shoot_enable = 1;
    control_init();
    //    fan_init();
    //    set_fan_speed(800, 800);
    imu660ra_init();

#if UART_DEBUG_PRINT_ENABLE
    wireless_uart_init();
#endif

    camara_init();

    pit_ms_init(TIM0_PIT, 5, control_loop);
    pit_ms_init(TIM1_PIT, 1, my_fps_timer_callback);

    EA = 1;

    while (1)
    {
        camara_task();

        if (print_flag)
        {
            print_flag = 0;

#if UART_DEBUG_PRINT_ENABLE
            uart_dbg_div++;
            if (uart_dbg_div >= UART_DEBUG_PRINT_DIV)
            {
                uart_dbg_div = 0;

                EA = 0;
                vofa_sstate = shoot_state;
                vofa_tflag = target_flag;
                vofa_tstage = target_stage;
                vofa_far = target_far_flag;
                vofa_stop = target_stop_ready;
                vofa_fire = target_fire_ready;
                vofa_tx = target_x;
                vofa_ty = target_y;
                vofa_outer = target_outer_w;
                vofa_score = target_score;
                vofa_votes = target_votes;
                vofa_rvotes = target_reliable_votes;
                vofa_near_votes = target_debug_near_votes;
                vofa_stop_votes = target_debug_stop_votes;
                vofa_rstop_votes = target_debug_reliable_stop_votes;
                vofa_spread = target_debug_spread;
                vofa_fire_window = target_debug_fire_window;
                vofa_stable = target_debug_stable_count;
                vofa_conf = target_confidence;
                vofa_err = target_servo2_input;
                vofa_aim_used = shoot_aim_error_used;
                vofa_aim_pred = shoot_aim_error_predict;
                vofa_slow = shoot_slow_request;
                vofa_stop_req = shoot_stop_request;
                vofa_rev_req = shoot_reverse_request;
                vofa_fwd_req = shoot_forward_request;
                vofa_laser = shoot_laser_on_flag;
                vofa_done = shoot_done_flag;
                vofa_sangle = shoot_servo2_angle_x10;
                vofa_lt = control_debug_left_target;
                vofa_rt = control_debug_right_target;
                EA = 1;

                sprintf(debug_str,
                        "%u,%u,%u,%u,%u,%u,%u,%u,",
                        vofa_sstate,
                        vofa_tflag,
                        vofa_tstage,
                        vofa_far,
                        vofa_stop,
                        vofa_fire,
                        vofa_tx,
                        vofa_ty);
                wireless_uart_send_string(debug_str);

                sprintf(debug_str,
                        "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,",
                        vofa_outer,
                        vofa_score,
                        vofa_votes,
                        vofa_rvotes,
                        vofa_near_votes,
                        vofa_stop_votes,
                        vofa_rstop_votes,
                        vofa_spread,
                        vofa_fire_window,
                        vofa_stable);
                wireless_uart_send_string(debug_str);

                sprintf(debug_str,
                        "%u,%d,%d,%d,%u,%u,%u,%u,%u,%u,%d,%d,%d\r\n",
                        vofa_conf,
                        vofa_err,
                        vofa_aim_used,
                        vofa_aim_pred,
                        vofa_slow,
                        vofa_stop_req,
                        vofa_rev_req,
                        vofa_fwd_req,
                        vofa_laser,
                        vofa_done,
                        vofa_sangle,
                        vofa_lt,
                        vofa_rt);

                wireless_uart_send_string(debug_str);
            }
#endif
        }
    }
}
