#include "custom_keys.h"

bool process_custom_keys(uint16_t keycode, keyrecord_t *record) {
    static uint16_t registered_keycode = KC_NO;
    // If a custom shift key is registered, then this event is either
    // releasing it or manipulating another key at the same time. Either way,
    // we release the currently registered key.
    if (registered_keycode != KC_NO) {
        unregister_code16(registered_keycode);
        registered_keycode = KC_NO;
    }

    if (record->event.pressed) {  // Press event.
        // Continue default handling if this is a tap-hold key being held.
        if ((IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) && record->tap.count == 0) return true;

        custom_key_t custom_key = { 0, 0, 0 };
        if (IS_QK_MOD_TAP(keycode)) keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        else if (IS_QK_LAYER_TAP(keycode)) keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
        for (int i = 0; i < NUM_CUSTOM_KEYS; ++i) {
            if (keycode == custom_keys[i].keycode) {
                custom_key = custom_keys[i];
                break;
            }
        }

        if (custom_key.keycode == 0) return true;
        const uint8_t saved_mods = get_mods();
#ifndef NO_ACTION_ONESHOT
        const uint8_t mods = saved_mods | get_weak_mods() | get_oneshot_mods();
#else
        const uint8_t mods = saved_mods | get_weak_mods();
#endif  // NO_ACTION_ONESHOT
#if CUSTOM_SHIFT_KEYS_LAYER_MASK != 0
        const uint8_t layer = read_source_layers_cache(record->event.key);
#endif  // CUSTOM_SHIFT_KEYS_LAYER_MASK
        if ((mods & MOD_MASK_SHIFT) != 0) {  // Shift is held.
            registered_keycode = custom_key.shifted_keycode;
            if (IS_QK_MODS(registered_keycode) &&  // Should key be shifted?
                (QK_MODS_GET_MODS(registered_keycode) & MOD_LSFT) != 0) {
                register_code16(registered_keycode);  // If so, press directly.
                print("shifted\n");
            } else {
                // If not, cancel shift mods, press the key, and restore mods.
                del_weak_mods(MOD_MASK_SHIFT);
#ifndef NO_ACTION_ONESHOT
                del_oneshot_mods(MOD_MASK_SHIFT);
#endif  // NO_ACTION_ONESHOT
                unregister_mods(MOD_MASK_SHIFT);
                register_code16(registered_keycode);
                set_mods(saved_mods);
                print("unshifted\n");
            }
            return false;            
        }
        else {
            registered_keycode = custom_key.normal_keycode;
            register_code16(registered_keycode);
            return false;
        }
    }

    return true;  // Continue with default handling.
}