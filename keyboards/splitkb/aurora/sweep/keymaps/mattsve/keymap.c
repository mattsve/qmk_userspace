#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "gpio.h"
#include "sendstring_swedish.h"
#include "custom_keycodes.h"
#include "features/custom_keys.h"

enum {
    TD_A_AO_AE,
    TD_O_OE
};

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(SE_Q,           SE_W, SE_F,        SE_P,        SE_B,   SE_J, SE_L,        SE_U,           SE_Y,          SE_SCLN,
                    TD(TD_A_AO_AE), SE_R, GUI_T(SE_S), ALT_T(SE_T), SE_G,   SE_M, ALT_T(SE_N), GUI_T(SE_E),    SE_I,          TD(TD_O_OE),
                    SE_Z,           SE_X, SE_C,        SE_D,        SE_V,   SE_K, SE_H,        LT(0, SE_COMM), LT(0, SE_DOT), LT(0, US_SLSH),
                    MEH_T(KC_SPC), OSM(MOD_LSFT),                           OSM(MOD_RCTL), TO(_SYM)),

    [_SYM] = LAYOUT(KC_ESC,  SE_AT,   SE_HASH, SE_DLR,  SE_PERC,    MY_CIRC, SE_AMPR, SE_ASTR, SE_SCLN, KC_BSPC,
                    KC_TAB,  SE_EQL,  MY_ACUT, MY_GRV,  SE_QUOT,    SE_BSLS, SE_LCBR, SE_RCBR, SE_PIPE, KC_ENT,
                    MY_TILD, SE_EURO, SE_LABK, SE_RABK, SE_MINS,    SE_LBRC, SE_LPRN, SE_RPRN, SE_RBRC, TO(_FUN),
                    TO(_DEF), _______,                              OSM(MOD_LALT), TO(_NUM)),

    [_NUM] = LAYOUT(KC_ESC,  KC_HOME, KC_UP,   KC_PGUP, LT(0, NUM_ASTR),    SE_EQL,          SE_7, SE_8, SE_9, KC_BSPC,
                    KC_TAB,  KC_LEFT, KC_DOWN, KC_RGHT, SE_PLUS,            LT(0, NUM_COMM), SE_4, SE_5, SE_6, KC_ENT,
                    QK_BOOT, KC_END,  KC_APP,  KC_PGDN, SE_MINS,            SE_0,            SE_1, SE_2, SE_3, TO(_FUN),
                    TO(_DEF), _______,                                      OSM(MOD_LALT), TO(_SYM)),
                    
    [_FUN] = LAYOUT(_______, _______, _______, _______, _______,   KC_F12, KC_F7, KC_F8, KC_F9, KC_BSPC,
                    _______, _______, _______, _______, _______,   KC_F11, KC_F4, KC_F5, KC_F6, KC_ENT,
                    _______, _______, _______, _______, _______,   KC_F10, KC_F1, KC_F2, KC_F3, _______,
                    TO(_DEF), _______,                             _______, TO(_SYM)),
};

const custom_key_t custom_keys[] = {
    {US_SLSH, SE_SLSH, SE_QUES},
    {SE_SCLN, SE_SCLN, SE_COLN},
    {SE_COMM, SE_COMM, SE_LABK},
    {SE_DOT, SE_DOT, SE_RABK},
    {SE_QUOT, SE_QUOT, SE_DQUO},
    {SE_EURO, SE_EURO, SE_PND}
};
uint8_t NUM_CUSTOM_KEYS = sizeof(custom_keys) / sizeof(custom_key_t);

void dance_a_ao_ae(tap_dance_state_t *state, void *user_data) {
        if (state->count == 1) tap_code16(SE_A);
        if (state->count == 2) tap_code16(SE_ARNG);
        if (state->count == 3) tap_code16(SE_ADIA);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_A_AO_AE] = ACTION_TAP_DANCE_FN(dance_a_ao_ae),
    [TD_O_OE] = ACTION_TAP_DANCE_DOUBLE(SE_O, SE_ODIA),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_keys(keycode, record)) return false;
    switch (keycode) {
        case MY_ACUT:
            if (record->event.pressed) SEND_STRING("´");
            return false;
        case MY_GRV:
            if (record->event.pressed) SEND_STRING("`");
            return false;    
        case MY_TILD:
            if (record->event.pressed) SEND_STRING("~");
            return false;
        case MY_CIRC:
            if (record->event.pressed) SEND_STRING("^");
            return false;
        case LT(0, SE_COMM):
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_MINS);
            return false; 
        case LT(0, SE_DOT):
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_EXLM);
            return false; 
        case LT(0, US_SLSH):
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_PIPE);            
            return false; 
        case LT(0, NUM_ASTR):
            if (record->tap.count && record->event.pressed) tap_code16(SE_ASTR);
            else if (record->event.pressed) tap_code16(SE_SLSH);
            return false; 
        case LT(0, NUM_COMM):
            if (record->tap.count && record->event.pressed) tap_code16(SE_COMM);
            else if (record->event.pressed) tap_code16(SE_DOT);
            return false; 
    }
    return true;
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
