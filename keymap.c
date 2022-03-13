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
    TD_CT_CLN,
    TD_ESC_CAPS
};

// Unicodes
enum unicode_names {
    BANG,
    IRONY,
    SNEK,
};

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};

// Holding information about a specific key state
typedef struct my_custom_key_state
{
    uint16_t keycode;
    bool pressed;
} my_key_state_t;


// keys to track
my_key_state_t my_lshift_state, my_rshift_state;

/*
* Registered Keys
*/

// needs to be changed
#define MO_FUNC  MO(_FUNCTION)     // Hold for function layer
#define TG_NUMP  TG(_NUMPAD)       // Toggle numpad layer

// Tapdance definitions
#define CTL_ESC TD(TD_ESC_CAPS)
#define CT_CLN TD(TD_CT_CLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬────────────┬───────┐
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * │   `   │   1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │   0   │   -   │   =   │ BackSpace  │ Home  │
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * ├───────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬─────────┼───────┤
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * │    Tab   │   Q   │   W   │   E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │   [   │   ]   │    \    │  Del  │
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * ├──────────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─────────┼───────┤
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * │  Ctrl/Esc  │   A   │   S   │   D   │   F   │   G   │   H   │   J   │   K   │   L   │   ;   │   '   │    Return     │ PgUp  │
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * ├────────────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴───────┬───────┼───────┤
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * │     Shift     │   Z   │   X   │   C   │   V   │   B   │   N   │   M   │   ,   │   .   │   /   │   Shift    │  Up   │ PgDn  │
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * ├─────────┬─────┴───┬───┴─────┬─┴───────┴───────┴───────┴───────┴───────┴─────┬─┴───────┼───────┴─┬──┬───────┼───────┼───────┤
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * │  Ctrl   │   GUI   │   Alt   │                     Space                     │   Alt   │  Func   │▒▒│ Left  │ Down  │ Right │
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * └─────────┴─────────┴─────────┴───────────────────────────────────────────────┴─────────┴─────────┴──┴───────┴───────┴───────┘
     */
    [_QWERTY] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    CT_CLN,  KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO_FUNC, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* Function layer
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬────────────┬───────┐
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * │  Esc  │  F1   │  F2   │  F3   │  F4   │  F5   │  F6   │  F7   │  F8   │  F9   │  F10  │  F11  │  F12  │    Del     │  End  │
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * ├───────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬─────────┼───────┤
     * │          │  RGB  │  RGB  │  RGB  │  RGB  │  RGB  │       │  USB  │  USB  │       │       │       │       │         │       │
     * │          │ Speed │  Val  │ Speed │  Hue  │  Sat  │       │  Port │  GCR  │       │ PrtSc │ ScrLk │ Pause │ NumPad  │ Mute  │
     * │          │   -   │   +   │   +   │   +   │   +   │       │       │       │       │       │       │       │         │       │
     * ├──────────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─────────┼───────┤
     * │            │  RGB  │  RGB  │  RGB  │  RGB  │  RGB  │       │       │       │ (Mac) │       │       │               │       │
     * │  CapsLock  │  Mode │  Val  │  Mode │  Hue  │  Sat  │       │       │       │ Lock  │       │       │               │ Vol+  │
     * │            │   -   │   -   │   +   │   -   │   -   │       │       │       │       │       │       │               │       │
     * ├────────────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴───────┬───────┼───────┤
     * │               │  RGB  │       │       │       │       │ 6KRO/ │       │       │       │       │            │       │       │
     * │               │ On/Off│       │       │       │Restart│ NKRO  │ Debug │       │       │ Layout│            │ PgUp  │ Vol-  │
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * ├─────────┬─────┴───┬───┴─────┬─┴───────┴───────┴───────┴───────┴───────┴─────┬─┴───────┼───────┴─┬──┬───────┼───────┼───────┤
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * │         │         │         │               Clear modifiers                 │         │         │▒▒│ Home  │ PgDn  │  End  │
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * └─────────┴─────────┴─────────┴───────────────────────────────────────────────┴─────────┴─────────┴──┴───────┴───────┴───────┘
     */
    [_FUNCTION] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_END,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, TG_NUMP, KC_MUTE,
        KC_CAPS, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD,
        _______, _______, _______,                            HK_COSL,                            _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
        /* Number pad (FN-\ to toggle)
     * ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬────────────┬───────┐
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * │       │       │       │       │       │       │       │       │   /   │   *   │   -   │       │       │            │       │
     * │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │
     * ├───────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬─────────┼───────┤
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * │          │       │       │       │       │       │       │   7   │   8   │   9   │   +   │       │       │         │       │
     * │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │
     * ├──────────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─────────┼───────┤
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * │            │       │       │       │       │       │       │   4   │   5   │   6   │   +   │       │               │       │
     * │            │       │       │       │       │       │       │       │       │       │       │       │               │       │
     * ├────────────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴───────┬───────┼───────┤
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * │               │       │       │       │       │       │       │   1   │   2   │   3   │   =   │            │       │       │
     * │               │       │       │       │       │       │       │       │       │       │       │            │       │       │
     * ├─────────┬─────┴───┬───┴─────┬─┴───────┴───────┴───────┴───────┴───────┴─────┬─┴───────┼───────┴─┬──┬───────┼───────┼───────┤
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * │         │         │         │                                     0         │    .    │         │▒▒│       │       │       │
     * │         │         │         │                                               │         │         │▒▒│       │       │       │
     * └─────────┴─────────┴─────────┴───────────────────────────────────────────────┴─────────┴─────────┴──┴───────┴───────┴───────┘
     */
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
            my_lshift_state.keycode = keycode;

            if (record->event.pressed) {
                my_lshift_state.pressed = true;
            } else {
                my_lshift_state.pressed = false;
            }
            return true;
        case KC_RSFT:
            my_rshift_state.keycode = keycode;

            if (record->event.pressed) {
                my_rshift_state.pressed = true;
            } else {
                my_rshift_state.pressed = false;
            }
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



// Tap Dance
void dance_umlaut_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (my_lshift_state.pressed) {
            //tap_code16(KC_LSFT);
            register_code16(S(KC_P));
        } else {
            register_code16(KC_P);
        }
    } else {
        if (my_lshift_state.pressed) {
            register_code16(KC_RALT);
            //tap_code16(KC_LSFT);
            register_code16(S(KC_P));
        } else {
            register_code16(KC_RALT);
            register_code16(KC_P);
        }
    }
}

void dance_umlaut_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (my_lshift_state.pressed) {
            //tap_code16(KC_LSFT);
            unregister_code16(S(RKC_P));
        } else {
            unregister_code16(KC_P);
        }
    } else {
        if (my_lshift_state.pressed) {
            unregister_code16(KC_RALT);
            //tap_code16(KC_LSFT);
            unregister_code16(S(KC_P));
        } else {
            unregister_code16(KC_RALT);
            unregister_code16(KC_P);
        }
    }
}
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CT_CLN]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_umlaut_finished, dance_umlaut_reset),
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};
