/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include "quantum.h"

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
};

enum {
    TD_LOWLNG = 0,
    MACRO_CMD_SHIFT_4,
    MACRO_CMD_SHIFT_5,
    WINDOW_BACK,
    WINDOW_FORWARD,
    WINDOW_INSPECT,
    WINDOW_RELOAD,
    VOICE_OVER
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int dance_lang (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 6;
}

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished_1 (tap_dance_state_t *state, void *user_data) {
  xtap_state.state = dance_lang(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
        register_code(KC_F13);
        register_code(KC_LNG2);
        break;
    case SINGLE_HOLD:
        layer_on(1);
        break;
    case DOUBLE_TAP:
        register_code(KC_F16);
        register_code(KC_LNG1);
        break;
  }
}

void x_reset_1 (tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_F13);
        unregister_code(KC_LNG2);
        break;
    case SINGLE_HOLD:
        layer_off(1);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_F16);
        unregister_code(KC_LNG1);
        break;
  }
  xtap_state.state = 0;
}

// マクロ組んだらなんかバグるので、viaで設定
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case MACRO_CMD_SHIFT_4:
//       if (record->event.pressed) {
//         // Cmd + Shift + 4を送信
//         register_code(KC_LGUI);    // Cmd (Mac)
//         register_code(KC_LSFT);    // Shift
//         register_code(KC_4);       // 4
//       } else {
//         unregister_code(KC_4);     // 4
//         unregister_code(KC_LSFT);  // Shift
//         unregister_code(KC_LGUI);  // Cmd (Mac)
//       }
//       return false;

//     case MACRO_CMD_SHIFT_5:
//         if (record->event.pressed) {
//             // Cmd + Shift + 5を送信
//             register_code(KC_LGUI);    // Cmd (Mac)
//             register_code(KC_LSFT);    // Shift
//             register_code(KC_5);       // 5
//         } else {
//             unregister_code(KC_5);     // 5
//             unregister_code(KC_LSFT);  // Shift
//             unregister_code(KC_LGUI);  // Cmd (Mac)
//         }
//         return false;

//     case WINDOW_BACK:
//         if (record->event.pressed) {
//             // Cmd + [ を送信
//             register_code(KC_LGUI);    // Cmd (Mac)
//             register_code(KC_LBRC);    // [
//         } else {
//             unregister_code(KC_LBRC);  // [
//             unregister_code(KC_LGUI);  // Cmd (Mac)
//         }
//         return false;

//     case WINDOW_FORWARD:
//         if (record->event.pressed) {
//             // Cmd + ] を送信
//             register_code(KC_LGUI);    // Cmd (Mac)
//             register_code(KC_RBRC);    // ]
//         } else {
//             unregister_code(KC_RBRC);  // ]
//             unregister_code(KC_LGUI);  // Cmd (Mac)
//         }
//         return false;

//     case WINDOW_INSPECT:
//         if (record->event.pressed) {
//             // Cmd + Opt + I を送信
//             register_code(KC_LGUI);    // Cmd (Mac)
//             register_code(KC_LALT);    // Opt (Mac)
//             register_code(KC_I);       // I
//         } else {
//             unregister_code(KC_I);     // I
//             unregister_code(KC_LALT);  // Opt (Mac)
//             unregister_code(KC_LGUI);  // Cmd (Mac)
//         }
//         return false;

//     case WINDOW_RELOAD:
//         if (record->event.pressed) {
//             // Cmd + R を送信
//             register_code(KC_LGUI);    // Cmd (Mac)
//             register_code(KC_LSFT);    // Shift (Mac)
//             register_code(KC_R);       // R
//         } else {
//             unregister_code(KC_R);     // R
//             unregister_code(KC_LSFT);  // Shift (Mac)
//             unregister_code(KC_LGUI);  // Cmd (Mac)
//         }
//         return false;

//     case VOICE_OVER:
//         if (record->event.pressed) {
//             // VOICE_OVER を送信
//             register_code(KC_LGUI);    // Cmd (Mac)
//             register_code(KC_F5);    // F5
//         } else {
//             unregister_code(KC_F5);     // F5
//             unregister_code(KC_LGUI);  // Cmd (Mac)
//         }
//         return false;
//   }
//   return true;
// }

tap_dance_action_t tap_dance_actions[] = {
  [TD_LOWLNG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LCTL, KC_TAB),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    MT(MOD_LALT, KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LGUI, TD(TD_LOWLNG),LT(3, KC_SPACE), KC_ENT,  LT(2, KC_BSPC), TL_UPPR
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      S(KC_GRV), S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                    S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_BSLS),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_MPRV,  KC_MSTP, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, S(KC_LBRC),S(KC_RBRC),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, KC_BRID, KC_BRIU,                      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_LBRC,  KC_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      S(KC_7), S(KC_BSLS), S(KC_EQL), S(KC_MINS), S(KC_9),  S(KC_0),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
