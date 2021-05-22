#include "minidox.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  | Vim/T|           |  Y   |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  | Alt/;|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  | ,/Sft|  .   | GUI//|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE| Shift|
 *                  `-------------| Space|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[QWERTY] = LAYOUT( \
  MI_Q,    KC_W,    KC_E,    KC_R,    V_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    ALCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    COMM,   KC_DOT,  GSLSH, \
                    KC_LCTL, MO(LOWER), KC_SPC,      KC_BSPC, MO(RAISE), OSM(MOD_LSFT)   \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |   -  |   _  |   =  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | eisu | kana |      |      |      |           |      |      |      |   \  |   '  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[RAISE] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      KC_MINS, KC_UNDS, KC_EQL,  KC_LBRC, ARBRC, \
  KC_LANG2, KC_LANG1, _______, _______, _______,      _______, _______, _______, KC_BSLS,  GQUOT, \
                    _______, _______, _______,      _______, _______, _______                 \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   ~  |   `  |      |      |      |           |   -  |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |   |  |   "  |
 * `----- -----------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[LOWER] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_TILD, KC_GRV,  _______, _______, _______,      KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  _______, _______, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_DQT, \
                    _______, _______, _______,      KC_ENT,  _______, _______   \
),

/*  Vim
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |      |      | xxxx |           |      |      |      |      | Esc  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | RESET|      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|   :  |    |  Ent |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[VIM] =  LAYOUT( \
  _______,  _______,  _______, _______, _______,      _______, _______, _______, _______, KC_ESC, \
  _______,  _______,  _______, _______, _______,      _______, _______, _______, _______, _______, \
  _______,  _______, _______, _______, _______,      _______, _______, _______, _______,  _______, \
                     _______, _______, KC_COLN,      KC_ENT,  _______, _______                    \
  ),

/* MISC
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |      |      |      |           |  1ps |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    | Term |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[MISC] =  LAYOUT( \
  _______,  _______,  _______, _______, _______,    LGUI(LSFT(KC_T)), _______, _______, _______, _______, \
  _______,  _______,  _______, _______, _______,    _______, _______, _______, _______, _______, \
  RESET,   _______, _______, _______, _______,      _______, _______, _______, _______,  _______, \
                     _______, _______, _______,     LALT(KC_A),  _______, _______                    \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}