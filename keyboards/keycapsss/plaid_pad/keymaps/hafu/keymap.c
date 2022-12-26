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

enum custom_keycodes {
  KC_CST_TGL_MOUSE_JIGGLE = SAFE_RANGE
};
#if defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)
deferred_token mouse_jiggle_token = INVALID_DEFERRED_TOKEN;
// define defaults if not defined
#ifndef MOUSE_JIGGLER_MIN_SEC
#define MOUSE_JIGGLER_MIN_SEC 1
#endif
#ifndef MOUSE_JIGGLER_MAX_SEC
#define MOUSE_JIGGLER_MAX_SEC 60
#endif
#ifdef OLED_ENABLE
deferred_token mouse_jiggle_animation_token = INVALID_DEFERRED_TOKEN;
// animation index
uint8_t mouse_jiggle_animation_index = 0;
#ifndef MOUSE_JIGGLER_ANIMATION_SPEED
#define MOUSE_JIGGLER_ANIMATION_SPEED 100
#endif
#endif  // OLED_ENABLE
#endif  // defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)

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
    * |      |  UP  |      | MS_J |
    * |------+------+------+------|
    * | LEFT | DOWN | RGHT |      |
    * `---------------------------'
    * - Toggle Mouse Jiggle:  - MS_J
    */
    [_NAVIGATION] = LAYOUT_ortho_4x4(
        KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,
        KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
        XXXXXXX, KC_UP,   XXXXXXX, KC_CST_TGL_MOUSE_JIGGLE,
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

#if defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)
uint32_t mouse_jiggler_callback(uint32_t trigger_time, void *cb_arg) {
  int mouse_direction = rand() % 4; // 0-3
  int mouse_jiggle_timer_seconds = rand() % MOUSE_JIGGLER_MAX_SEC + MOUSE_JIGGLER_MIN_SEC;
  switch (mouse_direction)
  {
  case 0:
    tap_code(KC_MS_L);
    break;
  case 1:
    tap_code(KC_MS_U);
    break;
  case 2:
    tap_code(KC_MS_R);
    break;
  // can only be 3
  default:
    tap_code(KC_MS_D);
    break;
  }
  return (uint32_t)mouse_jiggle_timer_seconds*1000;
}

void start_mouse_jiggler(void) {
  mouse_jiggle_token = defer_exec(1, mouse_jiggler_callback, NULL);
}

void stop_mouse_jiggler(void) {
  cancel_deferred_exec(mouse_jiggle_token);
  mouse_jiggle_token = INVALID_DEFERRED_TOKEN;
}

#ifdef OLED_ENABLE
uint32_t mouse_jiggler_animation_callback(uint32_t trigger_time, void *cb_arg) {
  // set index of animation
  mouse_jiggle_animation_index = (mouse_jiggle_animation_index >= 3) ? 0 : mouse_jiggle_animation_index+1;
  return MOUSE_JIGGLER_ANIMATION_SPEED;
}

void start_mouse_jiggle_animation(void) {
  mouse_jiggle_animation_token = defer_exec(1, mouse_jiggler_animation_callback, NULL);
}

void stop_mouse_jiggle_animation(void) {
  cancel_deferred_exec(mouse_jiggle_animation_token);
  mouse_jiggle_animation_token = INVALID_DEFERRED_TOKEN;
}
#endif  // OLED_ENABLE

#endif  // defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CST_TGL_MOUSE_JIGGLE:
      if (record->event.pressed) {
#if defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)
        if (mouse_jiggle_token == INVALID_DEFERRED_TOKEN) {
          start_mouse_jiggler();
          #ifdef OLED_ENABLE
          start_mouse_jiggle_animation();
          #endif
        } else {
          stop_mouse_jiggler();
          #ifdef OLED_ENABLE
          stop_mouse_jiggle_animation();
          #endif
        }
#endif // defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_scroll_set_speed(0xff);

    return rotation;
}

#if defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)
void oled_render_animation_mouse_jiggle_animation(void) {
  switch (mouse_jiggle_animation_index)
  {
  case 0:
    oled_write_P(PSTR("|"), false);
    break;
  case 1:
    oled_write_P(PSTR("/"), false);
    break;
  case 2:
    oled_write_P(PSTR("-"), false);
    break;
  default:
    oled_write_P(PSTR("\\"), false);
    break;
  }
}
#endif  // defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)

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

#if defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)
  oled_set_cursor(0, oled_max_lines()-1);
  if (mouse_jiggle_token != INVALID_DEFERRED_TOKEN) {
    oled_write_P(PSTR("Jiggle Jiggle "), false);
    oled_render_animation_mouse_jiggle_animation();
  } else {
    oled_write_P(PSTR("               "), false);
  }

#endif  // defined(DEFERRED_EXEC_ENABLE) && defined(MOUSE_JIGGLER_ENABLE)

  return false;
}

#endif
