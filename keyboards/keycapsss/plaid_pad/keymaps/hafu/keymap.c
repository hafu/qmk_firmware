#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    _NUMPAD,
    _NAVIGATION,
    _MEDIA,
    _BROWSER
};

enum combos {
  COMBO1,
  COMBO2,
  COMBO3,
  COMBO4
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* NUMPAD layer
    * ,-----------------------,
    * |  7  |  8  |  9  |  /  |
    * |-----+-----+-----+-----|
    * |  4  |  5  |  6  |  *  |
    * |-----+-----+-----+-----|
    * |  1  |  2  |  3  |  -  |
    * |-----+-----+-----+-----|
    * |  0  |  .  | ENT |  +  |
    * `-----------------------'
    */
    [_NUMPAD] = LAYOUT_ortho_4x4(
        KC_P7, KC_P8,   KC_P9,    KC_PSLS,
        KC_P4, KC_P5,   KC_P6,    KC_PAST,
        KC_P1, KC_P2,   KC_P3,    KC_PMNS,
        KC_P0, KC_PDOT, KC_PENT,  KC_PPLS
    ),
    /* Navigation layer
    * ,---------------------------,
    * | BTN1 | MS_U | BTN2 | WH_U |
    * |------+------+------+------|
    * | MS_L | MS_D | MS_R | WH_D |
    * |------+------+------+------|
    * |      |  UP  |      |      |
    * |------+------+------+------|
    * | LEFT | DOWN | RGHT |      |
    * `---------------------------'
    */
    [_NAVIGATION] = LAYOUT_ortho_4x4(
        KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,
        KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
        XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,
        KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX
    ),
    /* MEDIA layer
    * ,--------------------------,
    * |      | VOLU |      | F13 |
    * |------+------+------+-----|
    * | MPRV | MPLY | MNXT | F14 |
    * |------+------+------+-----|
    * | MSTP | VOLD | MUTE | F15 |
    * |------+-----+-------+-----|
    * | F13  | F14  | F15  | F16 |
    * `--------------------------'
    * - Mute          - KC_MUTE
    * - Stop Track    - KC_MSTP
    */
    [_MEDIA] = LAYOUT_ortho_4x4(
        XXXXXXX, KC_VOLU, XXXXXXX, KC_F13,
        KC_MPRV, KC_MPLY, KC_MNXT, KC_F14,
        KC_MSTP, KC_VOLD, KC_MUTE, KC_F15,
        KC_F13,  KC_F14,  KC_F15,  KC_F16
    ),
    /* Browser layer
    * - Last Tab:     Alt+9           LST_TB
    * - Prev Tab:     Ctrl+PGUP       LFT_TB
    * - Next Tab:     Ctrl+PGDN       RGT_TB
    * - New Tab:      Ctrl+T          NEW_TB
    * - Close Tab:    Ctrl+W          CLS_TB
    * - Restore Tab:  Ctrl+Shift+T    RST_TB
    * - PGUP
    * - PGDN
    * - WH_U
    * - WH_D
    * - Home
    * - End
    * - Bookmarks:    Ctrl+B          CTR_B
    * - Screenshot?   Ctrl+Shift+S
    * - Addressbar?   Alt+D, Ctrl+L, F6
    * ,-----------------------------------,
    * | HOME   | WH_U   | PGUP   | LST_TB |
    * |--------+--------+--------+--------|
    * | LFT_TB | CTL_F5 | RGT_TB | RST_TB |
    * |--------+--------+--------+--------|
    * | END    | WH_D   | PGDN   | CLS_TB |
    * |--------+--------+--------+--------|
    * | LSFT   | LCTL   | CTR_B  | NEW_TB |
    * `-----------------------------------'
    * ####################
    * HOME WHUP PGUP LSTTB
    */
   [_BROWSER] = LAYOUT_ortho_4x4(
      KC_HOME,       KC_WH_U,     KC_PGUP,       LALT(KC_9),
      LCTL(KC_PGUP), LCTL(KC_F5), LCTL(KC_PGDN), LCTL(LSFT(KC_T)),
      KC_END,        KC_WH_D,     KC_PGDN,       LCTL(KC_W),
      KC_LSFT,       KC_LCTL,     LCTL(KC_B),    LCTL(KC_T)
   ),

};

// Combos for switching layers
const uint16_t PROGMEM zeroDot_combo[] = {KC_P0, KC_PDOT, COMBO_END};
const uint16_t PROGMEM leftDown_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM f13f14_combo[] = {KC_F13, KC_F14, COMBO_END};
const uint16_t PROGMEM lsft_lctl_combo[] = {KC_LSFT, KC_LCTL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO1] = COMBO_ACTION(zeroDot_combo),
  [COMBO2] = COMBO_ACTION(leftDown_combo),
  [COMBO3] = COMBO_ACTION(f13f14_combo),
  [COMBO4] = COMBO_ACTION(lsft_lctl_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case COMBO1:
      if (pressed) {
        layer_move(_NAVIGATION);
      }
      break;
    case COMBO2:
      if (pressed) {
        layer_move(_MEDIA);
      }
      break;
    case COMBO3:
      if (pressed) {
        layer_move(_BROWSER);
      }
      break;
    case COMBO4:
      if (pressed) {
        layer_move(_NUMPAD);
      }
      break;
  }
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_scroll_set_speed(0xff);

    return rotation;
}

void oled_render_layer_state(void) {

  oled_write_P(PSTR("Layer: "), false);
  if(layer_state_is(_MEDIA)) {
    oled_write_ln_P(PSTR("Media"), false);
  } else if(layer_state_is(_NAVIGATION)) {
    oled_write_ln_P(PSTR("Navigation"), false);
  } else if(layer_state_is(_BROWSER)) {
    oled_write_ln_P(PSTR("Browser"), false);
  } else {
    oled_write_ln_P(PSTR("Numpad"), false);
  }
}

bool oled_task_user(void) {

  // Indicate LED:  "Plaid-Pad ////N/C/S//"
  //                "Plaid-Pad ///////////"
  //                "Plaid-Pad //////-/-/-"
  oled_write_P(PSTR("Plaid-Pad ////"), false);
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("N/") : PSTR("//"), false);
  oled_write_P(led_state.caps_lock ? PSTR("C/") : PSTR("//"), false);
  oled_write_P(led_state.scroll_lock ? PSTR("S//") : PSTR("///"), false);
  oled_render_layer_state();

  return false;
}

#endif
