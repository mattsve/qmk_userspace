#pragma once
#include QMK_KEYBOARD_H
#include "keymap_swedish.h"
#include "quantum.h"
#include "quantum/action.h"
#include "quantum/quantum_keycodes.h"

enum layers {
    _DEFAULT,
    _SWEDISH,
    _SYMBOL,
    _NUMPAD,
};

enum my_keycodes {
    MY_TILD = SAFE_RANGE,
    MY_COLN,
    MY_SLSH,
    TG_SWE,
    LT_DEF,
    LT_SYM,
    LT_NUM
};