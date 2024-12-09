#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "sendstring_swedish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(SE_Q, SE_W, SE_F, SE_P, SE_B,      SE_J, SE_L, SE_U,           SE_Y,         SE_SCLN,
                 SE_A, SE_R, SE_S, SE_T, SE_G,      SE_M, SE_N, SE_E,           SE_I,         SE_O,
                 SE_Z, SE_X, SE_C, SE_D, SE_V,      SE_K, SE_H, LT(0, SE_COMM), LT(0,SE_DOT), LT(0, SE_SLSH),
                 KC_SPC, OSM(MOD_LSFT),             OSM(MOD_RCTL), TO(1)),
    [1] = LAYOUT(KC_ESC,  _______, _______, _______, SE_UNDS,      SE_MINS, SE_7, SE_8, SE_9, KC_BSPC,
                 KC_TAB,  _______, _______, _______, SE_PLUS,      SE_EQL,  SE_4, SE_5, SE_6, KC_ENT,
                 QK_BOOT, _______, _______, _______, SE_COMM,      SE_0,    SE_1, SE_2, SE_3, KC_NO,
                 TO(0), _______,                                   _______, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0, SE_DOT): // send dot on tap, exclamation mark on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            }
            else if (record->event.pressed) {
                SEND_STRING("!"); 
                return false; // Return false to ignore further processing of key
            }
            return true;
        case LT(0, SE_COMM): // send comma on tap, minus on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            }
            else if (record->event.pressed) {
                tap_code(SE_MINS); 
                return false; // Return false to ignore further processing of key
            }
            return true;
        case LT(0, SE_SLSH): // send slash on tap, pipe on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            }
            else if (record->event.pressed) {
                SEND_STRING("|");
                return false; // Return false to ignore further processing of key
            }
            return true;
    }
    return true;
}


#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
