#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.

#ifdef COMBO_ENABLE
#    define COMBO_COUNT 6
#    define COMBO_TERM 200
#endif

#define I2C1_SDA_PIN        GP10
#define I2C1_SCL_PIN        GP11

#define WS2812_DI_PIN GP6

/* Haptic feedback */
#define FB_ERM_LRA 0
#define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3
/* Motor settings */
#define RATED_VOLTAGE 3
#define V_PEAK 5
#define HAPTIC_FEEDBACK_DEFAULT 0
#define DRV_MODE_DEFAULT 0
#define DRV_GREETING       alert_750ms