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
    [_DEF] = LAYOUT(SE_Q,           SE_W, SE_F,        SE_P,        SE_B,  SE_J, SE_L,        SE_U,           SE_Y,          US_SCLN,
                    TD(TD_A_AO_AE), SE_R, GUI_T(SE_S), ALT_T(SE_T), SE_G,  SE_M, ALT_T(SE_N), GUI_T(SE_E),    SE_I,          TD(TD_O_OE),
                    SE_Z,           SE_X, SE_C,        SE_D,        SE_V,  SE_K, SE_H,        LT(0, SE_COMM), LT(0, SE_DOT), LT(0, US_SLSH),
                    MEH_T(KC_SPC), OSM(MOD_LSFT),          OSM(MOD_RCTL), TO(_SYM)),
    [_SYM] = LAYOUT(KC_ESC,  SE_AT,   SE_HASH, SE_DLR,  SE_PERC,    MY_CIRC, SE_AMPR, SE_ASTR, US_SCLN, KC_BSPC,
                    KC_TAB,  SE_EQL,  _______, _______, _______,    SE_BSLS, SE_LCBR, SE_RCBR, SE_PIPE, KC_ENT,
                    MY_TILD, _______, _______, _______, _______,    SE_LBRC, SE_LPRN, SE_RPRN, SE_RBRC, TO(_NAV),
                    TO(_DEF), OSM(MOD_LSFT),                           OSM(MOD_LALT), TO(_NUM)),
    [_NUM] = LAYOUT(KC_ESC,  _______, _______, SE_ASTR, SE_SLSH,    SE_MINS, SE_7, SE_8, SE_9, KC_BSPC,
                    KC_TAB,  _______, _______, _______, SE_PLUS,    SE_EQL,  SE_4, SE_5, SE_6, KC_ENT,
                    QK_BOOT, _______, _______, _______, SE_COMM,    SE_0,    SE_1, SE_2, SE_3, TO(_NAV),
                    TO(_DEF), _______,                                OSM(MOD_LALT), TO(_SYM)),
    [_NAV] = LAYOUT(_______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
                    TO(_DEF), _______,                               _______, TO(_SYM)),
};

const custom_key_t custom_keys[] = {
    {US_SLSH, SE_SLSH, SE_QUES},
    {US_SCLN, SE_SCLN, SE_COLN},
    {SE_COMM, SE_COMM, SE_LABK},
    {SE_DOT, SE_DOT, SE_RABK},
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
        case MY_TILD:
            if (record->event.pressed) SEND_STRING("~");
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
        case MY_CIRC:
            if (record->event.pressed) SEND_STRING("^");
            return false;        
    }
    return true;
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
