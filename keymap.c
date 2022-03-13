#include QMK_KEYBOARD_H
#include "sendstring_german.h" // implicitly includes german keymap
#include <stdio.h>
#include <string.h>

/*
* Declarations
*/

// Custom keycodes
enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    HK_COSL,               // Clear held-down keys
    MD_BOOT,               //Restart into bootloader after hold timeout
};

// Layers
enum my_layers {
    _QWERTY = 0,
    _FUNCTION,
    _NUMPAD,
};

// Custom Tapdance keycodes
enum my_tap_dance {
    TD_A_UMLAUT,
    TD_O_UMLAUT,
    TD_U_UMLAUT,
    TD_S_UMLAUT,
    TD_ESC_CAPS
};

// Unicodes
enum unicode_names {
    BANG,
    IRONY,
    SNEK,
};

// Holding information about a specific key state
typedef struct my_custom_key_state
{
    uint16_t tracked_key;
    bool pressed;
} my_key_state_t;


// keys to track
my_key_state_t my_mod_key_state, my_normal_key;

/*
* Registered Keys
*/

// needs to be changed
#define MO_FUNC  MO(_FUNCTION)     // Hold for function layer
#define TG_NUMP  TG(_NUMPAD)       // Toggle numpad layer

// Tapdance definitions
#define TYPING_TAP_TERM 275

#define CTL_ESC TD(TD_ESC_CAPS)
#define A_UMLT TD(TD_A_UMLAUT)
#define O_UMLT TD(TD_O_UMLAUT)
#define U_UMLT TD(TD_U_UMLAUT)
#define S_UMLT TD(TD_S_UMLAUT)


/*
* Maps
*/

// corresponding keycode map
const uint16_t my_td_keycode_map[] = {
    [A_UMLT] = KC_Q,
    [O_UMLT] = KC_P,
    [U_UMLT] = KC_Y,
    [S_UMLT] = KC_S,
};

const uint16_t my_keycode_map[] = {
    [KC_Q] = KC_A,
    [KC_P] = KC_O,
    [KC_Y] = KC_U,
    [KC_S] = KC_S,
};

// unicode map
const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_1,      KC_2,       KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,      KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,      KC_W,       KC_E,    KC_R,    KC_T,    KC_Y,    U_UMLT,   KC_I,    O_UMLT,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        CTL_ESC, A_UMLT,    S_UMLT,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,      KC_SCLN,  KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,      KC_X,       KC_C,    KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT,    KC_SLSH,  KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI,   KC_LALT,                            KC_SPC,                        KC_RALT,   MO_FUNC,           KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FUNCTION] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_END,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, TG_NUMP, KC_MUTE,
        KC_CAPS, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD,
        _______, _______, _______,                            HK_COSL,                            _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
    [_NUMPAD] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PEQL, _______,          _______, _______,
        _______, _______, _______,                                     KC_P0,                     KC_PDOT, _______, _______, _______, _______
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    */
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case KC_LSFT:
            my_mod_key_state.tracked_key = keycode;
            my_mod_key_state.pressed = record->event.pressed;
            return true;
        case KC_RSFT:
            my_mod_key_state.tracked_key = keycode;
            my_mod_key_state.pressed = record->event.pressed;
            return true;
        case HK_COSL:
            clear_keyboard();
            reset_oneshot_layer();
            return true;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}


/*
* Tap Dance
*/

// Umlaut

// Helper function to get the necessary keycodes
void each_umlaut_tap(qk_tap_dance_state_t *state, void *user_data) {
    my_normal_key.tracked_key = my_keycode_map[my_td_keycode_map[state->keycode]];
}

// Registers the key to be used depending on the nunber of tabs
void dance_umlaut_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Depending on pressed modifiers registered key will be equally modified
        if (my_mod_key_state.pressed && (my_mod_key_state.tracked_key == KC_LSFT || my_mod_key_state.tracked_key == KC_RSFT)) { 
            register_code16(S(my_normal_key.tracked_key)); 
        } else { 
            register_code16(my_normal_key.tracked_key);
        }
    } else {
        if (my_mod_key_state.pressed && (my_mod_key_state.tracked_key == KC_LSFT || my_mod_key_state.tracked_key == KC_RSFT)) { 
            register_code16(S(RALT(my_td_keycode_map[state->keycode])));
        } else {
            register_code16(RALT(my_td_keycode_map[state->keycode]));
        }
    }
}

// After the tap dancing is done the registered key will be replaced by the defined tab dance key
void dance_umlaut_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { 
        if (my_mod_key_state.pressed && (my_mod_key_state.tracked_key == KC_LSFT || my_mod_key_state.tracked_key == KC_RSFT)) { 
            unregister_code16(S(my_normal_key.tracked_key));
        } else { 
            unregister_code16(my_normal_key.tracked_key);
        }
    } else {
        if (my_mod_key_state.pressed && (my_mod_key_state.tracked_key == KC_LSFT || my_mod_key_state.tracked_key == KC_RSFT)) { 
            unregister_code16(S(RALT(my_td_keycode_map[state->keycode]))); 
        } else { 
            unregister_code16(RALT(my_td_keycode_map[state->keycode]));
        }
    }
}

// All tab dance actions will be registered here
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_A_UMLAUT]   = ACTION_TAP_DANCE_FN_ADVANCED_TIME(each_umlaut_tap, dance_umlaut_finished, dance_umlaut_reset, TYPING_TAP_TERM),
    [TD_O_UMLAUT]   = ACTION_TAP_DANCE_FN_ADVANCED_TIME(each_umlaut_tap, dance_umlaut_finished, dance_umlaut_reset, TYPING_TAP_TERM),
    [TD_U_UMLAUT]   = ACTION_TAP_DANCE_FN_ADVANCED_TIME(each_umlaut_tap, dance_umlaut_finished, dance_umlaut_reset, TYPING_TAP_TERM),
    [TD_S_UMLAUT]   = ACTION_TAP_DANCE_FN_ADVANCED_TIME(each_umlaut_tap, dance_umlaut_finished, dance_umlaut_reset, TYPING_TAP_TERM),
    [TD_ESC_CAPS]   = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};
