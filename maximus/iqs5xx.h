/* Copyright 2020 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "report.h"

#define FINGER_MAX 3
#define TAP_TERM 100
#define FINGER_THREE_TAP_CNT 24
#define SWIPE_TERM 150
#define PINCH_TERM 200
#define GESTURE_TERM 200

#define IQS5xx_COM_END_REG 0xEEEE
#define IQS5xx_GESTURE_EVENT0 0x000D
#define IQS5xx_GESTURE_EVENT1 0x000E
#define IQS5xx_FINGER_NUM 0x0011
#define IQS5xx_RELATIVE_XY 0x0012
#define IQS5xx_TOUCH_STRENGTH_FINGER_THREE 0x0026
#define IQS5xx_ZOOM 0x06CB
#define IQS5xx_DEFAULT_READ 0x0675
#define IQS5xx_DEVICE_ADDR 0x74

typedef struct {
    union {
        uint8_t bytes[4];
    };
} iqs5xx_xy_t;

typedef enum {
    GESTURE_SWIPE_L = 0x10,    
    GESTURE_SWIPE_R,
    GESTURE_SWIPE_U,
    GESTURE_SWIPE_D,
    GESTURE_PINCH_OUT,
    GESTURE_PINCH_IN,
    TAP_FINGER_THREE
} iqs5xx_gesture_t;

typedef struct {
    uint8_t          finger_cnt;
    uint8_t          ges_evnet0;
    uint8_t          ges_evnet1;
    iqs5xx_xy_t      relative_xy;
    uint8_t          touch_strenght_finger_three;
    iqs5xx_gesture_t gesture;
} iqs5xx_data_t;

uint32_t tap_time;
uint32_t swipe_time;
uint32_t pinch_time;
uint32_t gesture_time;
uint32_t scroll_time;
uint32_t scroll_term;
uint32_t drag_time;
uint32_t drag_term;

bool clear_buttons;
bool tapped;
bool can_hf_for_layer;
int hf_waveform_number;
bool can_drag;
bool use_drag;

typedef struct {
    bool        is_pressed;
    uint16_t    keycode;
} ms_key_status_t;
ms_key_status_t ms_key_status;

bool can_trackpad_layer;
int trackpad_layer;
bool use_trackpad_layer;
int accel_speed;

void init_iqs5xx(void);
bool read_iqs5xx(iqs5xx_data_t* const data);
void process_iqs5xx(iqs5xx_data_t* const data, report_mouse_t* const rep_mouse);
