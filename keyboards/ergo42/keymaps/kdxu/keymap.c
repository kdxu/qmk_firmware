#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MISC 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RGB_RST,
  DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

enum {
  TD_LPRN = 0,
  TD_RPRN = 1,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LBRC),
  [TD_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RBRC),
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define LPRN TD(TD_LPRN)
#define RPRN TD(TD_RPRN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |  T   |      |   |      |  Y   |   U  |   I  |   O  |   P  | MISC |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |  G   |      |   |      |  H   |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |  B   |      |   |      |  N   |   M  |   ,  |  .   |  UP  |  /   |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl |  _   |   -  |  Alt |  Gui |LOWER |Space |   | Bksp | RAISE|  GUI |      | LEFT | DOWN | RIGHT|
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  XXXXXXX, XXXXXXX, KC_Y,   KC_U,    KC_I,    KC_O,   KC_P, MO(_MISC), \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  XXXXXXX, XXXXXXX, KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  XXXXXXX, XXXXXXX, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_UP, KC_SLSH, \
    KC_LCTL, KC_UNDS, KC_MINS, KC_LALT, KC_LGUI, LOWER, KC_SPC,  KC_BSPC, RAISE,  KC_LGUI, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT\
  ),

  /* RAISE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      |   1  |   2  |   3  |   4  |   5  |      |   |      |  6   |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |   -  |   _  |   =  |   [  |   ]  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |   `  |      |      |      |      |      |   |      |      |      |   \  |      |      |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |!raise|      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, XXXXXXX, \
    XXXXXXX, KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),

  /* LOWER
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |      |   |      |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |  Esc |      |      |      |      |      |   |      |   -  |   _  |   +  |   {  |   }  |      |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * |      |  ~   |      |      |      |      |      |   |      |   :  |   /  |   |  |  "   |      |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |!lower|      |   | Enter|      |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
    XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX, XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, LPRN,    RPRN, XXXXXXX,\
    XXXXXXX, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, XXXXXXX,\
    XXXXXXX, KC_TILD, _______, _______, _______, _______, XXXXXXX, XXXXXXX, KC_COLN, KC_SLSH, KC_PIPE, KC_DQT,  _______, XXXXXXX,\
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, KC_ENT,  _______, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX \
  ),
  /* MISC
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      | RESET|      |      |      |      |      |   |QWERTY|      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |      |      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_MISC] =  LAYOUT( \
    XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY, RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, _______, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case RGB_RST:
#ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
      }
#endif
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  switch (layer) {
    case _QWERTY:
      rgblight_mode_noeeprom(7);
      break;
    case _RAISE:
      rgblight_mode_noeeprom(21);
      break;
    case _LOWER:
      rgblight_mode_noeeprom(22);
      break;
    case _MISC:
      rgblight_mode_noeeprom(8);
      break;
    default:
      break;
  }

  return state;
}
