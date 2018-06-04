#include "lets_split.h"
#include "pro_micro.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#define QWERTY 0
#define LOWER 1
#define RAISE 2
#define MISC 3

enum {
  TD_ALF = 0,
  TD_LPLN = 1,
  TD_RPLN = 2,
  TD_SAKN = 3,
  CT_CLN = 4
};

#define _____ KC_TRNS
#define XXXXX KC_NO

#define RN LT(RAISE, KC_N)
#define LB LT(LOWER, KC_B)
#define M_T LT(MISC, KC_T)
#define ALF LALT(KC_SPC)
#define EK  LGUI(KC_SPC)
#define TRPN TD(TD_RPLN)
#define TLPN TD(TD_LPLN)
#define CLN  TD(CT_CLN)
#define TALF TD(TD_ALF)

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else {
    register_code (KC_SCLN);
  }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_SCLN);
  }
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ALF] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, ALF),
  [TD_LPLN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LBRC),
  [TD_RPLN] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RBRC),
  [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------.       ,----------------------------------
   * |   Q  |   W  |   E  |   R  |   T  |        |   Y  |   U  |   I  |   O  |  P   |
   * |------+------+------+------+------|        |------+------+------+------+------+
   * |   A  |   S  |   D  |   F  |   G  |        |   H  |   J  |   K  |   L  | BKSP |
   * |------+------+------+------+------+        |------+------+------+------+------+
   * |   Z  |   X  |   C  |   V  |   B  |        |   N  |   M  |   ,  |   .  |  /   |
   * |------+------+------+------+------+-       +------+------+------+------+------+
   */
[QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    M_T,  XXXXX, XXXXX,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  XXXXX, XXXXX,  KC_H,    KC_J,    KC_K,    KC_L,    KC_BSPC, \
  KC_Z,    KC_X,    KC_C,    KC_V,    LB,    XXXXX, XXXXX,  RN,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
  XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX, XXXXX, XXXXX,  XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX   \
  ),

   /* LOWER
     ,----------------------------------.        ,----------------------------------.
   * |   !  |   @  |   #  |   $  |   %  |        |   ^  |   &  |   *  |   (  |   )  |
   * |------+------+------+------+------|        |------+------+------+------+------|
   * |  Esc | SHIFT|   '  |   `  |   =  |        |   -  |   _  |   +  |   {  |  }   |
   * |------+------+------+------+------|        |------+------+------+------+------|
   * |   ~  |      |      |      |      |        |  SPC |   ;  |   /  |   |  |   "  |
   * `----------------------------------'        `----------------------------------'
   */

[LOWER] = LAYOUT( \
  KC_EXLM,    KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXX, XXXXX,  KC_CIRC, KC_AMPR, KC_ASTR, TLPN,    TRPN,\
  TALF,       XXXXX,   KC_QUOT, KC_GRV,  KC_EQL,  XXXXX, XXXXX,  KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  KC_TILD,    XXXXX,   XXXXX,   XXXXX,   _____,   XXXXX, XXXXX,  KC_SPC,  CLN, KC_SLSH, KC_PIPE,  KC_DQT, \
  XXXXX,      XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX, XXXXX,  XXXXX,   XXXXX,   XXXXX,   XXXXX,   XXXXX  \
  ),


  /* RAISE
   * ,----------------------------------,        ,----------------------------------.
   * |  1   |  2   |   3  |  4   |  5   |        |   6  |   7  |   8  |   9  |   0  |
   * |------+------+------+------+------|        |------+------+------+------+------|
   * |  TAB | LEFT | DOWN |  UP  |RIGHT |        |  EK  |      |      |      |      |
   * |------+------+------+------+------|        |------+------+------+------+------|
   * |      |      |      |      | ENT  |        |      |      |      |      |      |
   * `----------------------------------'        `----------------------------------'
   */

[RAISE] = LAYOUT( \
    KC_1,    KC_2,  KC_3,  KC_4,  KC_5,   XXXXX, XXXXX, KC_6,  KC_7, KC_8,  KC_9, KC_0, \
    KC_TAB, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,  XXXXX, XXXXX, EK,    XXXXX, XXXXX, XXXXX, KC_AT, \
    XXXXX,   XXXXX, XXXXX, XXXXX, KC_ENT, XXXXX, XXXXX, _____, XXXXX, XXXXX, XXXXX, XXXXX, \
    XXXXX,   XXXXX, XXXXX, XXXXX, XXXXX,  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX \
  ),

  /* MISC
   * ,----------------------------------,        ,----------------------------------.
   * |  Mod |      |      |      |      |        |      |      |      |      |RESET |
   * |------+------+------+------+------|        |------+------+------+------+------|
   * |  hui | hud  |      |      |      |        |      |      |      |      |      |
   * |------+------+------+------+------|        |------+------+------+------+------|
   * |  sai | sad  |      |      |      |        |      |      |      |      |      |
   * `----------------------------------'        `----------------------------------'
   */

[MISC] = LAYOUT( \
    RGB_MOD, XXXXX, XXXXX, XXXXX, _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, RESET,     \
    RGB_HUI, RGB_HUD, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    RGB_SAI, RGB_SAD, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     \
    XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, DF(QWERTY) \
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

#ifdef RGBLIGHT_ENABLE

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  switch (layer) {
    case QWERTY:
      rgblight_mode(25);
      break;
    case RAISE:
      rgblight_mode(6);
      break;
    case LOWER:
      rgblight_mode(7);
      break;
    case MISC:
      rgblight_mode(15);
      break;
    default:
      break;
  }

  return state;
}
#endif
