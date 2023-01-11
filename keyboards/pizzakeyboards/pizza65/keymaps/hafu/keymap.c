/* Copyright 2020 'mm0nte'
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

// enum for layers - _FN1 layer is has highest priority
enum {
    _BASE,
    _CAPS,
    // _NUM,
    _FN0,
    _FN1,
};

// Tap Dance declarations
enum {
    TD_MINS_F11,
    TD_EQL_F12,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for minus, twice for F11
    [TD_MINS_F11] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_F11),
    // Tap once for equal, twice for F12
    [TD_EQL_F12] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_F12),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_65_iso_blocker(
        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     TD(TD_MINS_F11), TD(TD_EQL_F12), KC_BSPC, KC_HOME,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,         KC_RBRC,                 KC_PGUP,
        MO(_FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,         KC_NUHS,        KC_ENT,  KC_PGDN,
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,         KC_RSFT,        KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FN0),                  KC_LEFT,        KC_DOWN, KC_RGHT
    ),
    // layer to activate Caps Lock key
    [_CAPS] = LAYOUT_65_iso_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    ),
    [_FN0] = LAYOUT_65_iso_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
        _______, _______, _______, _______, _______,   _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______,          KC_VOLU,
        _______, _______, _______, _______, _______,   _______, _______, KC_VOLD, KC_VOLU, _______, _______, _______, _______, QK_BOOT, KC_VOLD,
        _______, _______, _______, _______, TG(_CAPS), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                     _______,                            _______, _______,          _______, _______, _______
    ),
    [_FN1] = LAYOUT_65_iso_blocker(
        _______, _______, _______, KC_SLEP, KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    ),
};

#ifdef CAPS_WORD_ENABLE
/**
 * Keep caps enabled on KC_SLSH, which is `-` in ISO DE layout. Therefore a
 * `_` is typed.
 */
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // ANSI (EN) Layout
        // case KC_MINS:
        //     add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
        //     return true;
        // ISO (DE) Layout
        case KC_SLSH:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
#endif
