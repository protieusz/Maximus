#include "iqs5xx.h"
#include "maximus.h"

keypos_t get_d_3 = (keypos_t){.row = 4, .col = 0};
keypos_t get_u_3 = (keypos_t){.row = 4, .col = 1};
keypos_t get_r_2 = (keypos_t){.row = 4, .col = 2};
keypos_t get_r_3 = (keypos_t){.row = 4, .col = 3};
keypos_t get_l_2 = (keypos_t){.row = 4, .col = 4};
keypos_t get_l_3 = (keypos_t){.row = 4, .col = 5};
keypos_t get_i_2 = (keypos_t){.row = 4, .col = 6};
keypos_t get_o_2 = (keypos_t){.row = 4, .col = 7};
keypos_t get_t_3 = (keypos_t){.row = 4, .col = 8};

void gesture_press_key(keypos_t k) {
    keyevent_t k_event = { .key = k, .type = KEY_EVENT };
    k_event.pressed = true;
    k_event.time = (timer_read() | 1);
    action_exec(k_event);   
    k_event.pressed = false;
    k_event.time = (timer_read() | 1);
    action_exec(k_event);
}

void send_pointing_device_kb(report_mouse_t rep_mouse){
    if(rep_mouse.x || rep_mouse.y  || rep_mouse.v || rep_mouse.buttons || clear_buttons){
        pointing_device_set_report(rep_mouse);
        pointing_device_send();
        if(clear_buttons) {
            clear_buttons = false;
        }
    }
}

void keyboard_post_init_kb() {
    init_iqs5xx();
    tap_time = timer_read32();
    swipe_time = timer_read32();
    pinch_time = timer_read32();
    gesture_time = timer_read32();
    drag_term = 0;
    keyboard_post_init_user();
}

void matrix_scan_kb() {
    iqs5xx_data_t iqs5xx_data;
    iqs5xx_data.gesture = 0;
    report_mouse_t mouse_rep = {0};
    bool is_read_iqs5xx = false;

    is_read_iqs5xx = read_iqs5xx(&iqs5xx_data);
    if (is_read_iqs5xx) {
        process_iqs5xx(&iqs5xx_data, &mouse_rep);
        
        switch (iqs5xx_data.gesture) {
            case GESTURE_SWIPE_L:
                if(iqs5xx_data.finger_cnt == 2){
                    gesture_press_key(get_l_2);
                } else if(iqs5xx_data.finger_cnt == 3){
                    gesture_press_key(get_l_3);
                }
                break;
            case GESTURE_SWIPE_R:
                if(iqs5xx_data.finger_cnt == 2){
                    gesture_press_key(get_r_2);
                } else if(iqs5xx_data.finger_cnt == 3){
                    gesture_press_key(get_r_3);
                }
                break;
            case GESTURE_SWIPE_D:
                gesture_press_key(get_d_3);
                break;                
            case GESTURE_SWIPE_U:
                gesture_press_key(get_u_3);
                break;
            case GESTURE_PINCH_OUT:
                gesture_press_key(get_o_2);
                break;
            case GESTURE_PINCH_IN:
                gesture_press_key(get_i_2);
                break;
            case TAP_FINGER_THREE:
                gesture_press_key(get_t_3);
            default:
                break;
        }
        send_pointing_device_kb(mouse_rep);
    }
    matrix_scan_user();
}
