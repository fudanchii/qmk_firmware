#include "kbod.h"

#define _____ KC_TRNS

#define MODS_PRESSED(btn)  (get_mods() & (MOD_BIT(KC_L##btn)|MOD_BIT(KC_R##btn)))

#define SET_WHETHER(mask, btn1, btn2) \
if (record->event.pressed) {          \
    if (mask) {                       \
        add_key(btn2);                \
        send_keyboard_report();       \
    } else {                          \
        add_key(btn1);                \
        send_keyboard_report();       \
    }                                 \
} else {                              \
    if (mask) {                       \
        del_key(btn2);                \
        send_keyboard_report();       \
    } else {                          \
        del_key(btn1);                \
        send_keyboard_report();       \
    }                                 \
}                                     \

enum kaomoji
{
  DISAPPROVAL_LOOK = SAFE_RANGE,
  SAD_LOOK,
  SHRUG_LOOK,
  HUG_LOOK,
  TABLEFLIP_LOOK,

  OS_WIN,
  OS_LNX,
  OS_MAC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  KEYMAP( /* Base */
      F(0), KC_1, KC_2, KC_3, F(1), KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQUAL, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLASH,
      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENTER,
      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSFT,
      TT(1), KC_LCTL, KC_LALT, KC_SPACE, KC_RALT, KC_RGUI, KC_APP, KC_RCTL
  ),
  KEYMAP(/* Cursor layer */
      KC_GRAVE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
      TT(3), _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_INSERT,
      TT(2), _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_HOME, _____,
      _____, _____, _____, _____, _____, _____, _____, _____, KC_PGUP, KC_PGDN, KC_END, KC_UP,
      _____, _____, _____, _____, TO(4), KC_LEFT, KC_DOWN, KC_RIGHT
  ),
  KEYMAP(/* Keypad layer */
      TO(0), KC_1, KC_2, KC_3, F(1), KC_5, KC_6, KC_P7, KC_P8, KC_P9, KC_P0, KC_PMNS, KC_PPLS, KC_BSPC,
      _____, _____, _____, _____, _____, _____, _____, KC_P4, KC_P5, KC_P6, _____, _____, _____, _____,
      _____, _____, _____, _____, _____, _____, _____, KC_P1, KC_P2, KC_P3, _____, _____, _____,
      _____, _____, _____, _____, _____, _____, _____, KC_P0, KC_PDOT, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,
      _____, _____, _____, _____, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_BTN3
  ),
  KEYMAP(/* Multimedia layer */
      TO(0), _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _____,
      _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_MSTP, KC_MPRV, KC_MNXT, _____,
      _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,
      _____, _____, _____, _____, _____, _____, _____, _____, _____, KC_MS_BTN1, KC_MS_WH_UP, KC_MS_BTN2,
      _____, _____, _____, KC_MPLY, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, KC_MS_BTN3
  ),
  KEYMAP(/* Emoticons layer */
      TO(0), _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,
      DISAPPROVAL_LOOK, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, DISAPPROVAL_LOOK,
      SAD_LOOK, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,
      SHRUG_LOOK, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, HUG_LOOK,
      _____, _____, _____, TABLEFLIP_LOOK, _____, OS_WIN, OS_LNX, OS_MAC
  ),
};

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(0),
  [1] = ACTION_FUNCTION(1),
};

void tap(uint16_t keycode)
{
  register_code(keycode);
  unregister_code(keycode);
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  uint8_t shift_esc_mask;
  uint8_t alt_mask;
  switch (id) {
  case 0:
    shift_esc_mask = MODS_PRESSED(SHIFT);
    SET_WHETHER(shift_esc_mask, KC_ESC, KC_GRAVE);
    break;
  case 1:
    alt_mask = MODS_PRESSED(ALT);
    SET_WHETHER(alt_mask, KC_4, KC_F4);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case OS_LNX:
    set_unicode_input_mode(UC_LNX);
    return false;
  case OS_WIN:
    set_unicode_input_mode(UC_WINC);
    return false;
  case OS_MAC:
    set_unicode_input_mode(UC_OSX);
    return false;
  case DISAPPROVAL_LOOK:
    if (record->event.pressed) {
      process_unicode((0x0CA0 | QK_UNICODE), record); // Eye
      register_code(KC_RSFT);
      tap(KC_MINS);
      unregister_code(KC_RSFT);
      process_unicode((0x0CA0 | QK_UNICODE), record); // Eye
    }
    return false;
  case SAD_LOOK:
    if (record->event.pressed) {
      register_code(KC_RSFT);
      tap(KC_9);
      unregister_code(KC_RSFT);
      process_unicode((0x00B4 | QK_UNICODE), record);
      process_unicode((0x30FB | QK_UNICODE), record);
      process_unicode((0x03C9 | QK_UNICODE), record);
      process_unicode((0x30FB | QK_UNICODE), record);
      tap(KC_GRAVE);
      register_code(KC_RSFT);
      tap(KC_0);
      unregister_code(KC_RSFT);
    }
    return false;
  case SHRUG_LOOK:
    if (record->event.pressed) {
      process_unicode((0x00AF | QK_UNICODE), record); // Hand
      tap(KC_BSLS);                                   // Arm
      register_code(KC_RSFT);
      tap(KC_UNDS); // Arm
      tap(KC_LPRN); // Head
      unregister_code(KC_RSFT);
      process_unicode((0x30C4 | QK_UNICODE), record); // Face
      register_code(KC_RSFT);
      tap(KC_RPRN); // Head
      tap(KC_UNDS); // Arm
      unregister_code(KC_RSFT);
      tap(KC_SLSH);                                   // Arm
      process_unicode((0x00AF | QK_UNICODE), record); // Hand
    }
    return false;
  case HUG_LOOK:
    if (record->event.pressed) {
      register_code(KC_RSFT);
      tap(KC_9);
      unregister_code(KC_RSFT);
      process_unicode((0x3065 | QK_UNICODE), record);
      process_unicode_ext(0xFF61, record);
      process_unicode((0x25D5 | QK_UNICODE), record);
      process_unicode((0x203F | QK_UNICODE), record);
      process_unicode((0x203F | QK_UNICODE), record);
      process_unicode((0x25D5 | QK_UNICODE), record);
      process_unicode_ext(0xFF61, record);
      register_code(KC_RSFT);
      tap(KC_0);
      unregister_code(KC_RSFT);
      process_unicode((0x3065 | QK_UNICODE), record);
    }
    return false;
  case TABLEFLIP_LOOK:
    if (record->event.pressed) {
      register_code(KC_RSFT);
      tap(KC_9);
      unregister_code(KC_RSFT);
      process_unicode((0x256F | QK_UNICODE), record); // Arm
      process_unicode((0x00B0 | QK_UNICODE), record); // Eye
      process_unicode((0x25A1 | QK_UNICODE), record); // Mouth
      process_unicode((0x00B0 | QK_UNICODE), record); // Eye
      register_code(KC_RSFT);
      tap(KC_0);
      unregister_code(KC_RSFT);
      process_unicode((0x256F | QK_UNICODE), record); // Arm
      tap(KC_SPC);
      process_unicode((0x0361 | QK_UNICODE), record); // Flippy
      tap(KC_SPC);
      tap(KC_SPC);
      process_unicode((0x253B | QK_UNICODE), record); // Table
      process_unicode((0x2501 | QK_UNICODE), record); // Table
      process_unicode((0x2501 | QK_UNICODE), record); // Table
      process_unicode((0x2501 | QK_UNICODE), record); // Table
      process_unicode((0x253B | QK_UNICODE), record); // Table
    }
    return false;
  }
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE;
};

void led_set_user(uint8_t usb_led) {
  if (usb_led & _BV(USB_LED_CAPS_LOCK)) {
    PORTB |= _BV(PB0);
  } else {
    PORTB &= ~_BV(PB0);
  }
}

void matrix_init_user(void) {
  DDRB |= _BV(PB0);
  DDRC |= _BV(PC7);
}

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  if (layer) {
    PORTC |= _BV(PC7);
  } else {
    PORTC &= ~_BV(PC7);
  }
}