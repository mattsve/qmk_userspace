#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "gpio.h"
#include "sendstring_swedish.h"
#include "custom_keycodes.h"
#include "features/custom_keys.h"

// Inspiration
// https://github.com/anarion80/sweep_qmk?tab=readme-ov-file

enum {
    TD_A_AO_AE,
    TD_O_OE,
    TD_CURR,
};

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(
        SE_Q,           SE_W, SE_F,        SE_P,        SE_B,   SE_J, SE_L,        SE_U,        SE_Y,     SE_SCLN,
        TD(TD_A_AO_AE), SE_R, GUI_T(SE_S), ALT_T(SE_T), SE_G,   SE_M, ALT_T(SE_N), GUI_T(SE_E), SE_I,     TD(TD_O_OE),
        SE_Z,           SE_X, SE_C,        SE_D,        SE_V,   SE_K, SE_H,        TH_COMMI,    TH_DOTEX, TH_SLHPI,
                                 MEH_T(KC_SPC), OSM(MOD_LSFT),  OSM(MOD_RCTL), TO(_NAV)
    ),

    [_NAV] = LAYOUT(
        KC_ESC,        MS_WHLL, MS_UP,   MS_WHLR, KC_PGUP,      C(S(KC_TAB)), A(KC_LEFT), KC_UP,   A(KC_RGHT), KC_BSPC,
        TH_TABGU,      MS_LEFT, MS_DOWN, MS_RGHT, TH_DELAP,     C(KC_TAB),    KC_LEFT,    KC_DOWN, KC_RGHT,    KC_ENT,
        OSM(MOD_LCTL), MS_WHLU, MS_WHLD, MS_BTN2, KC_PGDN,      TH_BTN1,      TH_HOMCT,   KC_INS,  TH_ENDCT,   TO(_FUN),
                                   TO(_DEF), OSM(MOD_LSFT),     OSM(MOD_LCTL), TO(_SYM)
    ),

    [_SYM] = LAYOUT(
        KC_ESC,  MY_ACUT, MY_GRV,  SE_QUOT, TD(TD_CURR),    SE_EQL,  SE_7, SE_8, SE_9, KC_BSPC,
        KC_TAB,  TH_BRC,  TH_CBR,  TH_PRN,  TH_PLUMI,       TH_CODO, SE_4, SE_5, SE_6, KC_ENT,
        TH_TICI, SE_AT,   SE_HASH, SE_BSLS, TH_ASTSL,       KC_0,    SE_1, SE_2, SE_3, KC_DEL,
                                TO(_DEF), OSM(MOD_LSFT),    OSM(MOD_LALT), OSM(MOD_RCTL)
    ),

    [_FUN] = LAYOUT(
        KC_ESC,  KC_MPLY, KC_MPRV, KC_MNXT, TH_SCPS,    KC_F12, KC_F7, KC_F8, KC_F9, KC_BSPC,
        KC_TAB,  KC_MUTE, KC_VOLD, KC_VOLU, KC_PAUS,    KC_F11, KC_F4, KC_F5, KC_F6, KC_ENT,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,    KC_F10, KC_F1, KC_F2, KC_F3, KC_DEL,
                            TO(_DEF), OSM(MOD_LSFT),    OSM(MOD_LALT), OSM(MOD_RCTL)
    ),    
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

void dance_curr(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) tap_code16(SE_DLR);
    if (state->count == 2) tap_code16(SE_EURO);
    if (state->count == 3) tap_code16(SE_PND);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_A_AO_AE] = ACTION_TAP_DANCE_FN(dance_a_ao_ae),
    [TD_O_OE] = ACTION_TAP_DANCE_DOUBLE(SE_O, SE_ODIA),
    [TD_CURR] = ACTION_TAP_DANCE_FN(dance_curr),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_keys(keycode, record)) return false;
    switch (keycode) {
        case TH_COMMI:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_MINS);
            return false; 
        case TH_DOTEX:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_EXLM);
            return false; 
        case TH_SLHPI:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_PIPE);            
            return false; 
        case TH_TABGU:
            if (record->tap.count && record->event.pressed) tap_code16(KC_TAB);
            else if (record->event.pressed) tap_code16(LGUI(KC_TAB));            
            return false; 
        case TH_DELAP:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(KC_APP);
            return false; 
        case TH_BTN1:
            if (record->tap.count && record->event.pressed) tap_code16(MS_BTN1);
            else if (record->event.pressed) tap_code16(MS_BTN2);
            return false; 
        case TH_HOMCT:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(C(KC_HOME));
            return false; 
        case TH_ENDCT:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(C(KC_END));
            return false;         
        case TH_PLUMI:
            if (record->tap.count && record->event.pressed) return true;
            else if (record->event.pressed) tap_code16(SE_MINS);
            return false; 
        case TH_TICI:
            if (record->tap.count && record->event.pressed) SEND_STRING("~");
            else if (record->event.pressed) SEND_STRING("^");
            return false; 
        case TH_ASTSL:
            if (record->tap.count && record->event.pressed) tap_code16(SE_ASTR);
            else if (record->event.pressed) tap_code16(US_SLSH);
            return false; 
        case TH_BRC:
            if (record->tap.count && record->event.pressed) tap_code16(SE_LBRC);
            else if (record->event.pressed) tap_code16(SE_RBRC);
            return false; 
        case TH_CBR:
            if (record->tap.count && record->event.pressed) tap_code16(SE_LCBR);
            else if (record->event.pressed) tap_code16(SE_RCBR);
            return false; 
        case TH_PRN:
            if (record->tap.count && record->event.pressed) tap_code16(SE_LPRN);
            else if (record->event.pressed) tap_code16(SE_RPRN);
            return false; 
        case MY_ACUT:
            if (record->event.pressed) SEND_STRING("´");
            return false;
        case MY_GRV:
            if (record->event.pressed) SEND_STRING("`");
            return false;
        case TH_SCPS:
            if (record->tap.count && record->event.pressed)  tap_code16(KC_SCRL);
            else if (record->event.pressed) tap_code16(KC_PSCR);
            return false;
        case TH_CODO:
            if (record->tap.count && record->event.pressed)  tap_code16(SE_COMM);
            else if (record->event.pressed) tap_code16(SE_DOT);
            return false;
    }
    return true;
}

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C
