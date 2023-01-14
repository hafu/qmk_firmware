/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

Copyright 2021 Hannes Fuchs (hafu) - keymaps

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
#include "rgb_matrix_map.h"

#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])

// enum for layers - _FN1 layer is has highest priority
enum {
    _BASE,
    _GAMING,
    _NUM,
    _FN0,
    _FN1,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance declarations
enum {
    TD_PGUP_HOME,
    TD_PGDN_END,
    TD_INS_SFTINS,
    TD_DEL_SFTDEL
};

// custom keycode
enum custom_keycodes {
    KC_CST_TGL_RTRY_FNC = SAFE_RANGE
};

#ifdef ENCODER_ENABLE
// rotary encoder functions
enum custom_rotary_encoder_functions {
    RTRY_VOL_UP_DN,
    RTRY_PG_UP_DN,
    RTRY_UP_DN
};
uint8_t cur_rotary_encoder_function = RTRY_VOL_UP_DN;
#endif // ENCODER_ENABLE


#ifdef ENCODER_ENABLE
// save current settings in EEPROM (saves rotary encoder state)
typedef union {
  uint32_t raw;
  struct {
    uint8_t active_rotary_encoder_function;
  };
} user_config_t;
user_config_t user_config;
#endif // ENCODER_ENABLE

td_state_t cur_dance(qk_tap_dance_state_t *state);

// function definitons
void td_pgup_home_finished(qk_tap_dance_state_t *state, void *user_data);
void td_pgup_home_reset(qk_tap_dance_state_t *state, void *user_data);
void td_pgdn_end_finished(qk_tap_dance_state_t *state, void *user_data);
void td_pgdn_end_reset(qk_tap_dance_state_t *state, void *user_data);
void td_ins_sftins_finished(qk_tap_dance_state_t *state, void *user_data);
void td_ins_sftins_reset(qk_tap_dance_state_t *state, void *user_data);
void td_del_sftdel_finished(qk_tap_dance_state_t *state, void *user_data);
void td_del_sftdel_reset(qk_tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     // tap once: home, tap twice: insert
//     [TD_PGUP_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, KC_HOME),
//     // tap one: end, tap twice: delete
//     [TD_PGDN_END] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, KC_END),

// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
//      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.

    // The default layer:
    // Notable change is Caps Lock -> Left Control
    [_BASE] = LAYOUT(
        KC_ESC,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,                   KC_PGUP,
        MO(_FN1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT,    KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,    KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN0), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // Gaming layer, only difference is that default keycode for Caps Lock key (used by CP77 for example)
    [_GAMING] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PSLS, KC_PAST, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PMNS, KC_PPLS,                   _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, KC_PENT,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_NUM,  KC_P0,   KC_P0,   KC_PDOT, KC_PMNS,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
    [_FN0] = LAYOUT(
        _______, _______, _______, KC_SLEP, KC_PWR,  _______,     _______, KC_MPRV,  KC_MNXT, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG,           KC_CST_TGL_RTRY_FNC,
        _______, _______, _______, _______, _______, _______,     _______, _______,  _______, _______, _______, _______, _______,  KC_DEL,           KC_INS,
        _______, _______, _______, _______, _______, _______,     _______, _______,  _______, _______, RGB_HUI, RGB_SAI, RGB_SPI,                    KC_VOLU,
        _______, _______, _______, _______, _______, TG(_GAMING), _______, _______,  _______, _______, RGB_HUD, RGB_SAD, RGB_SPD, QK_BOOT,           KC_VOLD,
        _______, _______, _______, _______, _______, _______,     _______, TG(_NUM), _______, _______, _______, _______,          _______,  RGB_VAI, _______,
        _______, _______, _______,                                _______,                             _______, _______, _______, RGB_RMOD, RGB_VAD, RGB_MOD
    ),
    [_FN1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
//    [X] = LAYOUT(
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
//        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
//    ),


};

// tap dance functions
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'pgup' tap dance.
static td_tap_t td_pgup_home_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t td_pgdn_end_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t td_ins_sftins_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

static td_tap_t td_del_sftdel_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void td_pgup_home_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_pgup_home_tap_state.state = cur_dance(state);
    switch (td_pgup_home_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_PGUP);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
            register_code(KC_HOME);
            break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_PGUP);
            register_code(KC_PGUP);
        default:
            break;
    }
}

void td_pgup_home_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_pgup_home_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_PGUP);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
            unregister_code(KC_HOME);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code(KC_PGUP);
        default:
            break;
    }
    td_pgup_home_tap_state.state = TD_NONE;
}

void td_pgdn_end_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_pgdn_end_tap_state.state = cur_dance(state);
    switch (td_pgdn_end_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_PGDN);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
            register_code(KC_END);
            break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_PGDN);
            register_code(KC_PGDN);
        default:
            break;
    }
}

void td_pgdn_end_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_pgdn_end_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_PGDN);
            break;
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_TAP:
            unregister_code(KC_END);
            break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code(KC_PGDN);
        default:
            break;
    }
    td_pgdn_end_tap_state.state = TD_NONE;
}

void td_ins_sftins_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_ins_sftins_tap_state.state = cur_dance(state);
    switch (td_ins_sftins_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_INS);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_INS);
            break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_INS);
            register_code(KC_INS);
        default:
            break;
    }
}

void td_ins_sftins_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_ins_sftins_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_INS);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_INS);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code(KC_INS);
        default:
            break;
    }
    td_ins_sftins_tap_state.state = TD_NONE;
}

void td_del_sftdel_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_del_sftdel_tap_state.state = cur_dance(state);
    switch (td_del_sftdel_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            register_code(KC_DEL);
            break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_DEL);
            register_code(KC_DEL);
        default:
            break;
    }
}

void td_del_sftdel_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_del_sftdel_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_DEL);
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code(KC_DEL);
        default:
            break;
    }
    td_del_sftdel_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PGUP_HOME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_pgup_home_finished, td_pgup_home_reset),
    [TD_PGDN_END] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_pgdn_end_finished, td_pgdn_end_reset),
    [TD_INS_SFTINS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ins_sftins_finished, td_ins_sftins_reset),
    [TD_DEL_SFTDEL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_del_sftdel_finished, td_del_sftdel_reset)
};

// end tap dance functions

#ifdef RGB_MATRIX_ENABLE
// globals
uint8_t rgb_matrix_current_mode = 0;

// custom function(s)
// set color by list of led indexes
void rgb_matrix_set_color_led_list(const uint8_t* led_array, size_t size, RGB* rgb) {
    for (uint8_t i=0; i<size; i++) {
        rgb_matrix_set_color(led_array[i], rgb->r, rgb->g, rgb->b);
    }
}
#endif // RGB_MATRIX_ENABLE

#ifdef ENCODER_ENABLE
// rotary encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (cur_rotary_encoder_function) {
        case RTRY_VOL_UP_DN:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case RTRY_PG_UP_DN:
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
            break;
        // case RTRY_UP_DN:
        default:
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
            break;
    }
    return false;
}
#endif // ENCODER_ENABLE

// turn off leds on suspend
void suspend_power_down_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif // RGB_MATRIX_ENABLE
}

// turn on leds on wakeup
void suspend_wakeup_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif // RGB_MATRIX_ENABLE
}

// save the current rgb matrix mode after init (from eeprom)
void keyboard_post_init_user(void) {
#ifdef ENCODER_ENABLE
    user_config.raw = eeconfig_read_user();
    cur_rotary_encoder_function = user_config.active_rotary_encoder_function;
#endif // ENCODER_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_current_mode = rgb_matrix_get_mode();
#endif // RGB_MATRIX_ENABLE
}

// process keycodes, used for:
//  - save rgb matrix mode on changing effect
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef ENCODER_ENABLE
        // toggle rotary encoder function
        case KC_CST_TGL_RTRY_FNC:
            if(record->event.pressed) {
                switch (cur_rotary_encoder_function) {
                    case RTRY_PG_UP_DN:
                        cur_rotary_encoder_function = RTRY_UP_DN;
                        user_config.active_rotary_encoder_function = RTRY_UP_DN;
                        eeconfig_update_user(user_config.raw);
                        break;
                    case RTRY_UP_DN:
                        cur_rotary_encoder_function = RTRY_VOL_UP_DN;
                        user_config.active_rotary_encoder_function = RTRY_VOL_UP_DN;
                        eeconfig_update_user(user_config.raw);
                        break;
                    //case RTRY_VOL_UP_DN:
                    default:
                        cur_rotary_encoder_function = RTRY_PG_UP_DN;
                        user_config.active_rotary_encoder_function = RTRY_PG_UP_DN;
                        eeconfig_update_user(user_config.raw);
                        break;
                }
            }
            return false;   // skip all further processing of this key
#endif // ENCODER_ENABLE
#ifdef RGB_MATRIX_ENABLE
        // save current rgb mode when switching, to restore on layer change
        case RGB_MOD:
        case RGB_RMOD:
            rgb_matrix_current_mode = rgb_matrix_get_mode();
            return true;
#endif // RGB_MATRIX_ENABLE
        default:
            return true;
    }
}


// set rgb matrix mode on layer change
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGB_MATRIX_ENABLE
    // go through the layers from up to down, currently only one effect
    if (IS_LAYER_ON_STATE(state, _GAMING)) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_GAMING_FIXED_COLORS);
    } else {
        rgb_matrix_mode_noeeprom(rgb_matrix_current_mode);
    }
#endif // RGB_MATRIX_ENABLE
    return state;
}

#ifdef RGB_MATRIX_ENABLE
// toggle numpad leds on
void numpad_leds_on(void) {
    HSV hsv1 = { HSV_MAGENTA };
    hsv1.v = rgb_matrix_config.hsv.v;
    RGB rgb1 = hsv_to_rgb(hsv1);
    HSV hsv2 = { HSV_CYAN };
    hsv2.v = rgb_matrix_config.hsv.v;
    RGB rgb2 = hsv_to_rgb(hsv2);

    rgb_matrix_set_color_led_list(LED_LIST_NUMPAD, ARRAYSIZE(LED_LIST_NUMPAD), &rgb1);
    rgb_matrix_set_color_led_list(LED_LIST_NUMPAD_EXTRAS, ARRAYSIZE(LED_LIST_NUMPAD_EXTRAS), &rgb2);
}

// indicators for
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // num lock enabled
    uint8_t host_led = host_keyboard_leds();
    if (IS_LED_ON(host_led, USB_LED_NUM_LOCK)) {
        // numpad_leds_on();
        // sidebar leds
        HSV hsv = { HSV_MAGENTA };
        hsv.v = rgb_matrix_config.hsv.v;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(LED_L8, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R8, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_L7, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R7, rgb.r, rgb.g, rgb.b);
    }
    // caps lock enabled
    if (IS_LED_ON(host_led, USB_LED_CAPS_LOCK)) {
        HSV hsv = { HSV_WHITE };
        hsv.v = rgb_matrix_config.hsv.v;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(LED_L6, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R6, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_L5, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R5, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_CAPS, rgb.r, rgb.g, rgb.b);
    }
#ifdef ENCODER_ENABLE
    // rotary encoder vol up/down
    if (cur_rotary_encoder_function == RTRY_PG_UP_DN) {
        HSV hsv = { HSV_GREEN };
        hsv.v = rgb_matrix_config.hsv.v;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(LED_L4, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R4, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_L3, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R3, rgb.r, rgb.g, rgb.b);
    }
    // rotary encoder up/down
    if (cur_rotary_encoder_function == RTRY_UP_DN) {
        HSV hsv = { HSV_CYAN };
        hsv.v = rgb_matrix_config.hsv.v;
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(LED_L4, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R4, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_L3, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(LED_R3, rgb.r, rgb.g, rgb.b);
    }
#endif // ENCODER_ENABLE

    switch (get_highest_layer(layer_state)) {
        case _GAMING:
            break;
        case _NUM:
            numpad_leds_on();
            break;
        case _FN0:
            // highlight fn keys, lower brightness, change color
            HSV hsv = rgb_matrix_config.hsv;
            hsv.v = rgb_matrix_config.hsv.v / 4;
            // change color
            #define VALUE_OFFSET 128
            if (hsv.h + VALUE_OFFSET < 0xff) {
                hsv.h += VALUE_OFFSET;
            } else {
                hsv.h = 0xff - hsv.v + VALUE_OFFSET;
            }
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i=0; i<ARRAYSIZE(LED_LIST_FN0_KEYS); i++) {
                rgb_matrix_set_color(LED_LIST_FN0_KEYS[i], rgb.r, rgb.g, rgb.b);
            }
            break;
        default:
            break;
    }
    return false;
}
#endif // RGB_MATRIX_ENABLE


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

#ifdef ENCODER_ENABLE
void eeconfig_init_user(void) {  // EEPROM is getting reset!
    user_config.raw = 0;
    user_config.active_rotary_encoder_function = RTRY_VOL_UP_DN;
    eeconfig_update_user(user_config.raw);
}
#endif // ENCODER_ENABLE
