enum layers {
    _DEF,
    _SWE,
    _SYM,
    _NUM,
    _NAV
};

enum my_keycodes {
    MY_TILD = SAFE_RANGE,    
    MY_SLSH,
    MY_CIRC,
    TG_SWE,
    LT_DEF,
    LT_SYM,
    LT_NUM,
    LT_NAV
};

#define TH_SCLN LT(0, KC_A)
#define TH_MINS LT(0, KC_B)
#define TH_COMM LT(0, KC_C)
#define TH_SLSH LT(0, KC_D)