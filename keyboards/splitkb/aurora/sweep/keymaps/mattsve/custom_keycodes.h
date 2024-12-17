#pragma once

enum layers {
    _DEF,
    _NAV
    _SYM,
    _FUN,
    _NUM,
};

#define US_SLSH KC_LNG9
#define MS_BTN13 KC_LNG8
#define NUM_ASTR KC_LNG7

enum my_keycodes {
    MY_ACUT = SAFE_RANGE,
    MY_GRV,
    MY_TILD,
    MY_CIRC,
};

#define TH_BTN1 LT(0, KC_FN24)