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
#define NAVPAD 1
#define UNUSED 2

#define TOGGLE TG(NAVPAD)

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

	[NUMPAD] = LAYOUT_numpad(
		KC_MPLY, KC_MPRV,     KC_MNXT, 
		TOGGLE,  KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, 
		KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS, 
		KC_KP_4, KC_KP_5,     KC_KP_6, 
		KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER, 
		KC_KP_0, KC_KP_DOT),

	[NAVPAD] = LAYOUT_numpad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		TOGGLE,  XXXXXXX, XXXXXXX, XXXXXXX, 
		KC_HOME, KC_MS_U, KC_PGUP, KC_BTN2, 
		KC_MS_L, XXXXXXX, KC_MS_R, 
		KC_END,  KC_MS_D, KC_PGDN, KC_BTN1, 
		XXXXXXX, XXXXXXX),

	[UNUSED] = LAYOUT_numpad(
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS),
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (IS_LAYER_ON(NAVPAD)) {
          tap_code(clockwise ? KC_MS_WH_DOWN : KC_MS_WH_UP);
        } else {
          tap_code(clockwise ? KC_VOLU : KC_VOLD);
        }
    } 
    return false; 
}
