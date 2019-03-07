#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MISC 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DYNAMIC_MACRO_RANGE
};

enum {
  TD_LPLN = 0,
  TD_RPLN
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LPLN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LBRC),
  [TD_RPLN] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RBRC)
};

#include "dynamic_macro.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* QWERTY
   * ,------------------------------------------------.   ,------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |  T   |      |   |      |  Y   |   U  |   I  |   O  |   P  | MISC |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |  G   |      |   |      |  H   |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------+------|   |------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |  B   |      |   |      |  N   |   M  |   ,  |  .   |  UP  |  /   |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * | Ctrl |  _   |   -  |  Alt |  Gui |LOWER |Space |   | Bksp | RAISE|  GUI |      | LEFT | DOWN | RIGHT|
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  XXXXXXX, XXXXXXX, KC_Y,   KC_U,    KC_I,    KC_O,   KC_P, MO(_MISC), \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  XXXXXXX, XXXXXXX, KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_LCTL, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  XXXXXXX, XXXXXXX, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_UP, KC_SLSH, \
    KC_LCTL, KC_UNDS, KC_MINS, KC_LALT, KC_LGUI, LOWER, KC_SPC,  KC_BSPC, RAISE,  KC_LGUI, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT\
  ),
  /* RAISE
   * ,------------------------------------------------.   ,------------------------------------------------.
   * |      |   1  |   2  |   3  |   4  |   5  |      |   |      |  6   |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |   -  |   _  |   =  |   [  |   ]  |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |   `  |      |      |      |      |      |   |      |      |      |   \  |   '  |      |      |
   * |------+------+------+------+------+------+------|   |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   |      |!raise|      |      |      |      |      |
   * `------------------------------------------------'   `------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
    XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, XXXXXXX, \
    XXXXXXX, KC_GRV, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_QUOT, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
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
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE, TD(TD_LPLN), TD(TD_RPLN), XXXXXXX, \
      XXXXXXX, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,     XXXXXXX,\
      XXXXXXX, KC_TILD, _______, _______, _______, _______, XXXXXXX, XXXXXXX, KC_COLN, KC_SLSH, KC_PIPE, KC_DQT,  _______,     XXXXXXX,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI, _______, XXXXXXX, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     XXXXXXX \
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
    XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  )

};
