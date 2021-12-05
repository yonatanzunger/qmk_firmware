 /* Copyright 2021 Laneware Peripherals
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 

#include QMK_KEYBOARD_H

#define NUMPAD 0
#define FUNCTIONS 1

#define TOGGLE TG(FUNCTIONS)

/* 
 * ┌───┐   ┌───┬───┐ 
 * │K00│   │K02│K03│
 * └───┘   └───┴───┘ 
 * ┌───┬───┬───┬───┐
 * │K10│K11│K12│K13│
 * ├───┼───┼───┼───┤ 
 * │K20│K21│K22│K23│
 * ├───┼───┼───┤   │ 
 * │K30│K31│K32│   │
 * ├───┼───┼───┼───┤ 
 * │K40│K41│K42│K43│
 * ├───┴───┼───┤   │ 
 * │K50    │K52│   │
 * └───────┴───┴───┘
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // NB: KC_MINUS is taken over for tap-dance controls, so that 5 hits on it
  // resets the keyboard. (We have to use a basic keycode for this, not a
  // custom one)
	[NUMPAD] = LAYOUT_numpad(
		KC_MPLY, KC_MPRV,     KC_MNXT, 
		TOGGLE,  KC_KP_SLASH, KC_KP_ASTERISK, TD(KC_MINUS), 
		KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS, 
		KC_KP_4, KC_KP_5,     KC_KP_6, 
		KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER, 
		KC_KP_0, KC_KP_DOT),

  // This layer will send ctrl+Fxx
	[FUNCTIONS] = LAYOUT_numpad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, XXXXXXX, XXXXXXX, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_ENTER, 
		KC_TRNS, XXXXXXX),
};

void magic_minus(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 5) {
      reset_tap_dance(state);
      reset_keyboard();
    } else if (IS_LAYER_ON(NUMPAD)) {
      register_code(KC_KP_MINUS);
      unregister_code(KC_KP_MINUS);
    }
    // In function mode, the MINUS key is silent.
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [KC_MINUS] = ACTION_TAP_DANCE_FN(magic_minus),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } 
    return false; 
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed &&
        IS_LAYER_ON(FUNCTIONS) && (
        keycode >= KC_KP_1 &&
        keycode <= KC_KP_0
    )) {
      register_code(KC_LGUI);
      register_code(KC_LCTL);
      register_code(keycode);
      unregister_code(keycode);
      unregister_code(KC_LCTL);
      unregister_code(KC_LGUI);
      return false;
    }
    return true;
}
