/* Copyright 2021 Sleepdealer, James Young for QMK (@noroadsleft)
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
#define FUNC 1
#define NAV 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [NUMPAD] = LAYOUT_all(
        KC_MUTE,          KC_PGUP, KC_PGDN,
        TO(FUNC),KC_PSLS, KC_PAST, KC_PMNS,
        KC_P1,   KC_P2,   KC_P3,   KC_PPLS,  KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PIPE,
        KC_P7,   KC_P8,   KC_P9,   KC_ENTER, KC_ENTER,
        KC_P0,   MC_00,   KC_PDOT, KC_PDOT,
        KC_P0
    ),

    [FUNC] = LAYOUT_all(
        KC_TRNS,          RGB_HUI, RGB_VAI,
        TO(NAV), RGB_TOG, RGB_HUD, RGB_VAD,
        KC_PGUP, KC_UP,   KC_PGDN, RGB_MOD,  RGB_MOD,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
        KC_HOME, KC_INS,  KC_END,  RESET,    RESET,
        KC_ESC,  KC_TRNS, KC_DEL,  KC_TRNS,
        KC_ESC
    ),

    [NAV] = LAYOUT_all(
        KC_TRNS,          RGB_HUI, RGB_VAI,
        TO(NUMPAD), RGB_TOG, RGB_HUD, RGB_VAD,
        KC_P1,   KC_P2,   KC_P3,   RGB_MOD,  RGB_MOD,
        KC_P4,   KC_P5,   KC_P6,   KC_TRNS,
        KC_P7,   KC_P8,   KC_P9,   RGB_RMOD, RGB_RMOD,
        KC_P0,   KC_P0,   KC_PDOT, KC_PDOT,
        KC_P0
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && IS_LAYER_ON(NAV) && (keycode >= KC_KP_1 && keycode <= KC_KP_DOT)) {
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
