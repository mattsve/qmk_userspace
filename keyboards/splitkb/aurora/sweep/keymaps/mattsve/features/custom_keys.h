#pragma once
#include QMK_KEYBOARD_H

typedef struct {
  uint16_t keycode;
  uint16_t normal_keycode;
  uint16_t shifted_keycode;
} custom_key_t;

extern const custom_key_t custom_keys[];
extern uint8_t NUM_CUSTOM_KEYS;

bool process_custom_keys(uint16_t keycode, keyrecord_t *record);