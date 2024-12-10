#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "gpio.h"
#include "sendstring_swedish.h"
#include "custom_keycodes.h"
#include "g/keymap_combo.h"

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(SE_Q, SE_W, SE_F, SE_P, SE_B,   SE_J, SE_L, SE_U,           SE_Y,           LT(0, MY_COLN),
                    SE_A, SE_R, SE_S, SE_T, SE_G,   SE_M, SE_N, SE_E,           SE_I,           SE_O,
                    SE_Z, SE_X, SE_C, SE_D, SE_V,   SE_K, SE_H, LT(0, SE_COMM), LT(0, SE_MINS), LT(0, MY_SLSH),
                    KC_SPC, OSM(MOD_LSFT),          OSM(MOD_RCTL), LT_SYM),
    [_SWE] = LAYOUT(_______, _______, _______, _______, _______,   _______, _______, _______, _______, SE_ARNG,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, SE_ODIA, SE_ADIA,
                    _______, _______,                               _______, _______),
    [_SYM] = LAYOUT(KC_ESC,  SE_AT,   SE_HASH, SE_DLR,  SE_PERC,    MY_CIRC, SE_AMPR, SE_ASTR, LT(0, MY_COLN), KC_BSPC,
                    KC_TAB,  _______, _______, _______, _______,    SE_BSLS, SE_LCBR, SE_RCBR, SE_PIPE,        KC_ENT,
                    MY_TILD, _______, _______, _______, _______,    SE_LBRC, SE_LPRN, SE_RPRN, SE_RBRC,        LT_NAV,
                    LT_DEF, OSM(MOD_LSFT),                           OSM(MOD_LALT), LT_NUM),
    [_NUM] = LAYOUT(KC_ESC,  _______, _______, SE_ASTR, SE_SLSH,          SE_MINS, SE_7, SE_8, SE_9, KC_BSPC,
                    KC_TAB,  _______, _______, _______, SE_PLUS,          SE_EQL,  SE_4, SE_5, SE_6, KC_ENT,
                    QK_BOOT, _______, _______, _______, LT(0, SE_COMM),   SE_0,    SE_1, SE_2, SE_3, LT_NAV,
                    LT_DEF, _______,                                      OSM(MOD_LALT), LT_SYM),
    [_NAV] = LAYOUT(_______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    LT_DEF, _______,                               _______, LT_SYM),
};

void change_layer(uint16_t layer) {
    layer_on(layer);
    layer_and(1 << _DEF | 1 << _SWE | 1 << layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0, MY_COLN): // send colon on tap, semi colon on hold
            if (record->tap.count && record->event.pressed) {
                SEND_STRING(":");
                return false;
            }
            else if (record->event.pressed) {
                SEND_STRING(";"); 
                return false; // Return false to ignore further processing of key
            }
            return true;
        case LT(0, SE_MINS): // send minus on tap, underscore on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            }
            else if (record->event.pressed) {
                SEND_STRING("_"); 
                return false; // Return false to ignore further processing of key
            }
            return true;
        case LT(0, SE_COMM): // send comma on tap, dot on hold
            if (record->tap.count && record->event.pressed) {
                return true;
            }
            else if (record->event.pressed) {
                tap_code(SE_DOT); 
                return false; // Return false to ignore further processing of key
            }
            return true;
        case LT(0, MY_SLSH): // send slash on tap, pipe on hold
            if (record->tap.count && record->event.pressed) {
                SEND_STRING("/");
                return false;
            }
            else if (record->event.pressed) {
                SEND_STRING("|");
                return false; // Return false to ignore further processing of key
            }
            return true;
        case MY_TILD:
            if (record->event.pressed) {
                SEND_STRING("~");
            }
            return false;
        case MY_CIRC:
            if (record->event.pressed) {
                SEND_STRING("^");
            }
        case TG_SWE:
            if (record->event.pressed) {
                layer_invert(_SWE);
            }
            return false;
        case LT_DEF:
            change_layer(_DEF);
            return false;
        case LT_SYM:
            change_layer(_SYM);
            return false;
        case LT_NUM:
            change_layer(_NUM);
            return false;
    }
    return true;
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
