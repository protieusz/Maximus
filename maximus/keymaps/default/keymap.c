/*
Copyright 2022 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "drivers/haptic/DRV2605L.h"
#include <stdio.h>
#include "iqs5xx.h"

typedef union {
  uint32_t raw;
  struct {
    bool init : 1;
    unsigned int hf_waveform_number : 7;
    bool can_hf_for_layer : 1;
    bool can_drag : 1;
    unsigned int  scroll_term : 7;
    unsigned int drag_term : 10;
    bool can_trackpad_layer : 1;
  };
} user_config_t;
user_config_t user_config;

#define DOUBLE_KEY_TAP_TERM 200

enum {
  U_DD_TOGG = QK_KB_0,
  U_HPL_TOGG,
  U_TPL_TOGG,
  U_SEND_SETTING,
  U_RESET_SETTING,
  SCLL_UP,
  SCLL_DOWN,
  DRG_UP,
  DRG_DOWN,
  HF_UP,
  HF_DOWN
};

enum combo_events {
  COMBO_DEL,
  COMBO_ESC,
 };
 
#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_del[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_A, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_DEL] = COMBO(combo_del,KC_DEL),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
} 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,         KC_W, KC_E,    KC_R,    KC_T,                                           KC_Y,          KC_U,          KC_I,     KC_O,   KC_P,
        KC_A,         KC_S, KC_D,    KC_F,    KC_G,                                           KC_H,          KC_J,          KC_K,     KC_L,   KC_SCLN,
        LSFT_T(KC_Z), KC_X, KC_C,    KC_V,    KC_B,                                           KC_N,          KC_M,          KC_COMMA, KC_DOT, RSFT_T(KC_SLSH),
                            KC_LCTL, KC_LGUI, LT(1,KC_BSPC),   KC_MS_BTN1,    KC_MS_BTN2,     LT(2,KC_SPC),   (KC_ENT),      KC_LALT
    ),
    [1] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,     KC_7,    KC_8,    KC_9,    KC_0,
        KC_TAB,  _______, _______, _______, _______,                         KC_MINS,  KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
        _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                         KC_TILD,  KC_GRV,  _______, _______, KC_BSLS,
                          _______, _______, _______,     _______, _______,   _______,  _______, _______
    ),
    [2] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        RGB_VAI,  RGB_SAI,    RGB_HUI,    RGB_SPI,   RGB_MOD,                RGB_TOG,  DT_PRNT,  DT_UP,   DT_DOWN, _______,
        RGB_VAD,  RGB_SAD,    RGB_HUD,    RGB_SPD,   RGB_RMOD,               KC_ACL0,  KC_ACL1, KC_ACL2, _______, _______,
                          _______, _______, _______,     _______, _______,   _______,  _______, _______
    ),
    [3] = LAYOUT(
        _______, KC_UP, _______, _______, _______,                         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PSCR,
        KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,                      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,
        _______, _______, _______, _______, _______,                       KC_F10,  KC_F11,  KC_F12,  _______, _______,
                          _______, _______, _______,     _______, _______,   _______, _______, _______
    )
};

uint32_t init_opts(user_config_t* user_config) {
  eeconfig_init_user();
  user_config->init = true;  
  user_config->can_hf_for_layer = true;
  user_config->hf_waveform_number = 47;   
  user_config->can_drag = true;  
  user_config->drag_term = 700;
  user_config->can_trackpad_layer = true;
  user_config->scroll_term = 0;
  eeconfig_update_user(user_config->raw); 
  DRV_pulse(53);
  return eeconfig_read_user();
}

void set_opts(user_config_t user_config) {
  hf_waveform_number = user_config.hf_waveform_number;
  can_hf_for_layer = user_config.can_hf_for_layer;
  can_drag = user_config.can_drag;  
  drag_term = user_config.drag_term;
  can_trackpad_layer = user_config.can_trackpad_layer;
  scroll_term = user_config.scroll_term;
  accel_speed = 1;
  trackpad_layer = 4;
  use_trackpad_layer = false;
  use_drag = false;
}

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  if(!user_config.init) {
    user_config.raw = init_opts(&user_config);
  }
  set_opts(user_config);

  //vial_tap_dance_entry_t td0 = { SCLL_UP, KC_NO, SCLL_DOWN, KC_NO,  DOUBLE_KEY_TAP_TERM };
  //vial_tap_dance_entry_t td1 = { DRG_UP, KC_NO, DRG_DOWN, KC_NO, DOUBLE_KEY_TAP_TERM };
  //vial_tap_dance_entry_t td2 = { HF_UP, KC_NO, HF_DOWN, KC_NO, DOUBLE_KEY_TAP_TERM };
  //dynamic_keymap_set_tap_dance(0, &td0);
  //dynamic_keymap_set_tap_dance(1, &td1);
  //dynamic_keymap_set_tap_dance(2, &td2);
}

char prefix_scroll_term[] = "Scroll Term: ";
char prefix_drag_term[] = "Drag&Drop Term: ";
char prefix_haptic_number[] = "HF Waveform Number: ";

char* can_hf_for_layer_to_char(void) {
  return user_config.can_hf_for_layer ? "HF for Layer: on\n" : "HF for Layer: off\n";
}

char* can_drag_char(void) {
  return user_config.can_drag ? "Drag&Drop: on\n" : "Drag&Drop: off\n";
}

char* can_trackpad_layer_char(void) {
  return user_config.can_trackpad_layer ? "Trackpad Layer: on\n" : "Trackpad Layer: off\n";
}

void send_setting_string(char* t, int i) {
  char cn[12];
  sprintf(cn, "%d", i);
  char end = '\n';

  size_t len1 = strlen(t);
  size_t len2 = 1;
  size_t len3 = 1;
  size_t buffer_size = len1 + len2 + len3 + 1;

  char* c = (char*)malloc(buffer_size);
  memset(c, 0, buffer_size);

  strcat(c, t);
  strcat(c, cn);
  strncat(c, &end, 1);

  send_string(c);

  free(c);

}

void hf_DRV_pulse(bool ee2_up) {
  if (ee2_up) {
    user_config.hf_waveform_number = hf_waveform_number;  
    eeconfig_update_user(user_config.raw); 
    hf_waveform_number = user_config.hf_waveform_number;
  }
  DRV_pulse(hf_waveform_number);
  send_setting_string(prefix_haptic_number, hf_waveform_number);
}

void send_pointing_device_user(ms_key_status_t ms_key_status) {
    report_mouse_t mouse_report = {0};
    if(ms_key_status.is_pressed) {
      mouse_report.buttons |= 1 << (ms_key_status.keycode - KC_BTN1);
    } else {
      mouse_report.buttons &= ~(1 << (ms_key_status.keycode - KC_BTN1));
    }
    pointing_device_set_report(mouse_report);
    pointing_device_send();
}

void update_drag_term(uint32_t dt){
  user_config.drag_term = dt;
  eeconfig_update_user(user_config.raw); 
  drag_term = user_config.drag_term;
  send_setting_string(prefix_drag_term, dt);
}
  
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {  
    case U_RESET_SETTING : 
      if (record->event.pressed) {
        user_config.raw = eeconfig_read_user();
        init_opts(&user_config);
        set_opts(user_config);
      }
      return false;
    case KC_BTN1 ... KC_BTN5:
      if (record->event.pressed) {
        if(!(keycode == KC_BTN1 && tapped)){
          ms_key_status.is_pressed = true;
          ms_key_status.keycode = keycode;
          send_pointing_device_user(ms_key_status);
        }
      } else {
        ms_key_status.is_pressed = false;
        ms_key_status.keycode = keycode;
        send_pointing_device_user(ms_key_status);
      }
      return false;    
    case KC_ACL0:
      if (record->event.pressed) {
        float as = accel_speed == 2 ? 1 : 2;
        accel_speed = as;
      }
      return false;  
    case KC_ACL1:
      if (record->event.pressed) {
        float as = accel_speed == 4 ? 1 : 4;
        accel_speed = as;
      }
      return false;  
    case SCLL_UP: 
      if (record->event.pressed) {
        scroll_term = scroll_term + 5;
        if(scroll_term > 100) {
          scroll_term = 100;
        }
        user_config.scroll_term = scroll_term;  
        eeconfig_update_user(user_config.raw); 
        send_setting_string(prefix_scroll_term, scroll_term);
      }
      return false;
    case SCLL_DOWN: 
      if (record->event.pressed) {
        if(scroll_term != 0) {
          scroll_term = scroll_term - 5;
          user_config.scroll_term = scroll_term;  
          eeconfig_update_user(user_config.raw); 
        }
        send_setting_string(prefix_scroll_term, scroll_term);      
      }
      return false;  
    case U_DD_TOGG: 
      if (record->event.pressed) {
        user_config.can_drag = !can_drag;  
        eeconfig_update_user(user_config.raw); 
        can_drag = user_config.can_drag;   
        char* dm = can_drag_char();
        send_string(dm);
      }
      return false;             
    case DRG_UP: 
      if (record->event.pressed) {
        drag_term = drag_term + 10;
        if(drag_term > 1000) {
          drag_term = 1000;
        }
        update_drag_term(drag_term);
      }
      return false;
    case DRG_DOWN: 
      if (record->event.pressed) {
        if(drag_term != 0) {
          drag_term = drag_term - 10;
        }
        update_drag_term(drag_term);
      }
      return false;
    case U_HPL_TOGG: 
      if (record->event.pressed) {
        user_config.can_hf_for_layer = !can_hf_for_layer;  
        eeconfig_update_user(user_config.raw); 
        can_hf_for_layer = user_config.can_hf_for_layer;  
        char* hl = can_hf_for_layer_to_char();  
        send_string(hl);
      }
      return false;         
    case HF_UP:
      if (record->event.pressed) {
        hf_waveform_number++;
        if(hf_waveform_number == 124) {
          hf_waveform_number = 0;
        }
        hf_DRV_pulse(true);
      }
      return false;
    case HF_DOWN:
      if (record->event.pressed) {
        hf_waveform_number--;
        if(hf_waveform_number == -1) {
          hf_waveform_number = 123;
        }
        hf_DRV_pulse(true);
      }
      return false;
    case U_TPL_TOGG: 
      if (record->event.pressed) {
        user_config.can_trackpad_layer = !can_trackpad_layer;  
        eeconfig_update_user(user_config.raw); 
        can_trackpad_layer = user_config.can_trackpad_layer;  
        char* atl = can_trackpad_layer_char();
        send_string(atl);
      }
      return false;    
    case U_SEND_SETTING: 
      if (record->event.pressed) {  
        char st[100];        
        strcpy(st, prefix_scroll_term); 
        sprintf(st + strlen(st), "%d\n", user_config.scroll_term);

        char* dm = can_drag_char();

        char dt[100];
        strcpy(dt, prefix_drag_term);     
        sprintf(dt + strlen(dt), "%d\n", user_config.drag_term);

        char* hl = can_hf_for_layer_to_char();

        char hm[100];
        strcpy(hm, prefix_haptic_number);     
        sprintf(hm + strlen(hm), "%d\n", user_config.hf_waveform_number);

        char* atl = can_trackpad_layer_char();
        
        char at[100];
        sprintf(at, "Accel Speed: %d\n", (int)accel_speed);

        size_t len1 = strlen(st);
        size_t len2 = strlen(dm);
        size_t len3 = strlen(dt);
        size_t len4 = strlen(hl);
        size_t len5 = strlen(hm);
        size_t len6 = strlen(atl);
        size_t len7 = strlen(at);

        size_t buffer_size = len1 + len2 + len3 + len4 + len5 + len6 + len7 + 1;
        char* c = (char*)malloc(buffer_size);
        memset(c, 0, buffer_size);

        strcat(c, st);
        strcat(c, dm);
        strcat(c, dt);      
        strcat(c, hl);       
        strcat(c, hm);
        strcat(c, atl);
        strcat(c, at);
       
        send_string(c);

        free(c);
      }
      return false; 
    default:
      return true;
  }
};

int layer = 0;

void matrix_scan_user(void) {
  int current_layer = get_highest_layer(layer_state|default_layer_state); 
  if(current_layer != trackpad_layer && can_hf_for_layer && layer != current_layer){
    DRV_pulse(hf_waveform_number);
    layer = current_layer;
  }
}

bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    return false;
}

//led_config_t g_led_config = { {
  // Key Matrix to LED Index
    //{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, }, 
    //{ 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, }, 
    //{ 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, }, 
    //{ NO_LED, NO_LED, NO_LED, 36, 37, 38, 39, 40, 41 }
//}, {
  // LED Index to Physical Position 
  //{0, 0},     {20, 0},     {40, 0},     {60, 0},     {80, 0},     {100, 0},    {120, 0},     {140, 0},     {160, 0},     {180, 0},     {200, 0},     {224, 0},  
  //{0, 21},    {20, 21},    {40, 21},    {60, 21},    {80, 21},    {100, 21},   {120, 21},    {140, 21},    {160, 21},    {180, 21},    {200, 21},    {224, 21},  
  //{0, 42},    {20, 42},    {40, 42},    {60, 42},    {80, 42},    {100, 42},   {120, 42},    {140, 42},    {160, 42},    {180, 42},    {200, 42},    {224, 42},  
                                        //{60, 64},    {80, 64},    {100, 64},   {120, 64},    {140, 64},    {160, 64}
  //}, {
  // LED Index to Flag
  //4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  //4, 4, 4, 4, 4, 4, 
  //2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  //2, 2, 2
  //} 
//};

//bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { 
  //int current_layer = get_highest_layer(layer_state|default_layer_state);  
  //HSV hsv = {0, 255, rgblight_get_val()};
  //if (current_layer == 1) {
    //hsv.h = 191; //PURPLE
  //} else if (current_layer == 2)  {
    //hsv.h = 85; //GREEN
  //} else if (current_layer == 3)  {
    //hsv.h = 43; //YELLOW
  //} else if (current_layer == 4)  {
    //hsv.h = 222; //ROSE
  //} else {
    //hsv.h = 128; //CYAN
  //}
  //RGB rgb = hsv_to_rgb(hsv);
  
  //for (uint8_t i = led_min; i <= led_max -1; i++) {
      //if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
        //rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      //}
  //}
  //return false;
//}  