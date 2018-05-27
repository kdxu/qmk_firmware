/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial */

#define USE_I2C
#define USE_SERIAL
//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT

#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif

#define MATRIX_ROWS 8
#define MATRIX_COLS 7
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }

#define USE_SERIAL_PD2

#define PREVENT_STUCK_MODIFIERS
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#ifdef RGBLED_BACK
  #define RGBLED_NUM 25
#else
  #define RGBLED_NUM 6
#endif

#if RGBLED_NUM <= 6
  #define RGBLIGHT_LIMIT_VAL 255
#else
  #define RGBLIGHT_LIMIT_VAL 130
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGBLIGHT_ENABLE
  #define USB_MAX_POWER_CONSUMPTION 330
#endif
