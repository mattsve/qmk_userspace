#pragma once

enum layers {
    _DEF,
    _NAV,
    _SYM,
    _FUN,
};

#define US_SLSH KC_LNG9
#define MS_BTN13 KC_LNG8

enum my_keycodes {
    MY_ACUT = SAFE_RANGE,
    MY_GRV,
};

#define TH_BTN1  LT(0, KC_F24)
#define TH_COMMI LT(0, SE_COMM)
#define TH_DOTEX LT(0, SE_DOT)
#define TH_SLHPI LT(0, US_SLSH)
#define TH_TABGU LT(0, KC_TAB)
#define TH_DELAP LT(0, KC_DEL)
#define TH_HOMCT LT(0, KC_HOME)
#define TH_ENDCT LT(0, KC_END)
#define TH_PLUMI LT(0, SE_PLUS)
#define TH_ASTSL LT(0, KC_F23)
#define TH_BRC   LT(0, KC_F22)
#define TH_CBR   LT(0, KC_F21)
#define TH_PRN   LT(0, KC_F20)
#define TH_TICI  LT(0, KC_F19)
#define TH_SCPS  LT(0, KC_SCRL)
#define TH_CODO  LT(0, KC_F18)