#pragma once

enum layers {
    _DEF,
    _SWE,
    _SYM,
    _NUM,
    _NAV
};

#define US_SLSH KC_LNG9
#define US_SCLN KC_LNG8

enum my_keycodes {
    MY_TILD = SAFE_RANGE,
    MY_CIRC,
    TG_SWE,
    LT_DEF,
    LT_SYM,
    LT_NUM,
    LT_NAV
};

#define TH_SCLN LT(0, US_SCLN)
#define TH_MINS LT(0, KC_B)
#define TH_COMM LT(0, KC_C)
#define TH_SLSH LT(0, US_SLSH)