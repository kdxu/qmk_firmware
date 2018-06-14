#include "helix.h"
#include "bootloader.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#include "LUFA/Drivers/Peripheral/TWI.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

#define ALFRED LALT(KC_SPC)
#define EISU_KANA LGUI(KC_SPC)
#define GSLSH GUI_T(KC_SLSH)
#define ALCLN ALT_T(KC_SCLN)
#define GQUOT GUI_T(KC_QUOT)
#define ARBRC ALT_T(KC_RBRC)
#define COPY   LGUI(KC_C)
#define PASTE  LGUI(KC_V)
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum {
  TD_ALF = 0,
  TD_LPLN = 1,
  TD_RPLN = 2,
  TD_SAKN = 3,
  TD_DESC = 4
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ALF] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, ALFRED),
  [TD_LPLN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LBRC),
  [TD_RPLN] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RBRC),
  [TD_SAKN] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, EISU_KANA),
  [TD_DESC] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ESC)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Adj  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |  Up  | Shift|
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |  _   |   -  |  Alt |  Gui |LOWER |Space | Bksp | RAISE|  GUI |  Alt | LEFT | DOWN | RIGHT|
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = KEYMAP( \
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ADJUST, \
      KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_SLSH, \
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_LSFT, \
      XXXXXXX, KC_UNDS, KC_MINS, KC_LALT, KC_LGUI,  LOWER, KC_SPC,  KC_BSPC,   RAISE,  KC_LGUI,  KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT\
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  Tab | Left | Down |  Up  | Right|             |   -  |   _  |   =  |   [  |   ]  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   `  |      | Copy | Paste|      |             |      |      |      |   \  |   '  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = KEYMAP( \
      _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
      _______,  KC_TAB,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,             KC_MINS, KC_UNDS, KC_EQL,  KC_LBRC, ARBRC, _______, \
      _______,  KC_GRV,  XXXXXXX,  COPY, PASTE, XXXXXXX,               _______, _______, _______, KC_BSLS,  GQUOT, _______,\
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),


  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  Esc |      |      |      |      |             |   -  |   _  |   +  |   {  |  }   |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   ~  |      |      |      |      |             |      |   :  |   /  |   |  |   "  |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      | Enter|      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = KEYMAP( \
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                  KC_CIRC, KC_AMPR, KC_ASTR, TD(TD_LPLN), TD(TD_RPLN), _______,\
      _______, KC_ESC,  _______, _______, _______, _______,                  KC_MINS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, \
      _______, KC_TILD, _______, _______, _______, _______,                  _______, KC_COLN, KC_SLSH, KC_PIPE,  KC_DQT, _______, \
      _______, _______, _______, _______, _______, _______, _______, KC_ENT, _______, _______, _______, _______, _______, _______ \
      ),

  /* Adjust
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      | Reset|      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             |      |Qwerty|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  KEYMAP( \
      _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  _______, \
      _______, _______, _______, _______, _______, AG_NORM,                   _______, QWERTY,  _______, _______,  _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD \
      )
};



// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
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
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256
#define L_ADJUST 65536
#define L_ADJUST_TRI 65542

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
}



void render_status(struct CharacterMatrix *matrix) {
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\n"));
  switch (layer_state) {
    case L_BASE:
      matrix_write_P(matrix, PSTR("DEFAULT"));
      break;
    case L_LOWER:
      matrix_write_P(matrix, PSTR("LOWER"));
      break;
    case L_RAISE:
      matrix_write_P(matrix, PSTR("RAISE"));
      break;
    case L_ADJUST:
    case L_ADJUST_TRI:
      matrix_write_P(matrix, PSTR("ADJUST"));
      break;
    default:
      matrix_write(matrix, buf);
  }
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
