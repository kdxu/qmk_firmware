#include "lets_split.h"
#include "pro_micro.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#define _QGMLWY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QGMLWY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

#define _____ KC_TRNS
#define XXXXX KC_NO

qk_tap_dance_action_t tap_dance_actions[] = {
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* QGMLWY
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  Q   |  G   |  M   |  L   |  W   |      | |      |  Y   |  F   |  U   |  B   | DEL  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  D   |  S   |  T   |  N   |  R   |      | |      |  I   |  A   |  E   |  O   |  H   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  Z   |  X   |  C   |  V   |  J   |      | |      |  K   |  P   |  ,   |  .   |  /   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */
[_QGMLWY] = LAYOUT( \
		KC_Q,    KC_G,    KC_M,    KC_L,  KC_W,  XXXXX, XXXXX, KC_Y,  KC_F,  KC_U,  KC_B,  KC_DEL,    \
		KC_D,     KC_S,    KC_T,    KC_N,  KC_R,  XXXXX, XXXXX, KC_I,  KC_A,  KC_E,  KC_O,  KC_M,    \
		KC_Z ,    KC_X,   KC_C,    KC_V,  KC_J,    XXXXX, XXXXX, KC_K, KC_P,  KC_COMM,  KC_DOT,  XXXXX,    \
		XXXXX,   XXXXX,   XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX   \
  ),
    /* LOWER (Symbol)
   * ,-----------------------------------------, ,-----------------------------------------,
   * |  !   |   "  |   #  |   $  |   %  |      | |      |   &  |  '   |  `   |   |  | yen  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | ESC  |   [  |  (   |   {  |  \   |      | |      |   ~  |  =   |  :   |   /  |  *   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  ^   |   ]  |  )   |   }  |  SPC |      | |      |      |  -   |  ;   |   .  |  +   |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

[_LOWER] = LAYOUT( \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, DF(QGMLWY) \
		),

  /* RAISE
   * ,-----------------------------------------, ,-----------------------------------------.
   * |  1   |  2   |   3  |  4   |  5   |      | |      |   6  |   7  |   8  |   9  |   0  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * | TAB  |  F1  |  F2  |  F3  |  F4  |      | |      |  F5  |  SPC |  F7  |  F8  |   @  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |  _   |  F9  |  F10 |  F11 |      |      | |      |  ENT | BSPC |      |  F12 |   -  |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

[_RAISE] = LAYOUT( \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, DF(QGMLWY) \
  ),
    /* ADJUST
   * ,-----------------------------------------, ,-----------------------------------------,
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * |------+------+------+------+------+------| |------+------+------+------+------+------|
   * |      |      |      |      |      |      | |      |      |      |      |      |      |
   * `-----------------------------------------' `-----------------------------------------'
   */

[_ADJUST] = LAYOUT( \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, DF(QGMLWY) \
  ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  TXLED0;
  RXLED0;
}

void matrix_scan_user(void) {
  TXLED0;
  RXLED0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QGMLWY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QGMLWY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

#ifdef RGBLIGHT_ENABLE

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  switch (layer) {
    case _QGMLWY:
      rgblight_mode(16);
      break;
    case _RAISE:
      rgblight_mode(6);
      break;
    case _LOWER:
      rgblight_mode(7);
      break;
    default:
      break;
  }

  return state;
}
#endif
