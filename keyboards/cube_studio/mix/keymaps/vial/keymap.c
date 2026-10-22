#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
    _SYM,
    _BT
};

#ifdef OLED_ENABLE
// Column-major 1-bit artwork; bit zero is the top pixel.
static const uint8_t PROGMEM mix_logo[] = {
    0x7F, 0x06, 0x1C, 0x06, 0x7F, 0x00,
    0x00, 0x7F, 0x00, 0x00,
    0x63, 0x36, 0x1C, 0x36, 0x63,
};

static const uint8_t PROGMEM layer_label[] = {
    0x7F, 0x40, 0x40, 0x40, 0x40, 0x00,
    0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00,
    0x03, 0x04, 0x78, 0x04, 0x03, 0x00,
    0x7F, 0x49, 0x49, 0x49, 0x41, 0x00,
    0x7F, 0x09, 0x19, 0x29, 0x46,
};

static const uint8_t PROGMEM caps_label[] = {
    0x3E, 0x41, 0x41, 0x41, 0x22, 0x00,
    0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00,
    0x7F, 0x09, 0x09, 0x09, 0x06, 0x00,
    0x46, 0x49, 0x49, 0x49, 0x31,
};

static const uint8_t PROGMEM layer_digits[10][5] = {
    {0x3E, 0x41, 0x41, 0x41, 0x3E},
    {0x00, 0x42, 0x7F, 0x40, 0x00},
    {0x62, 0x51, 0x49, 0x49, 0x46},
    {0x22, 0x41, 0x49, 0x49, 0x36},
    {0x18, 0x14, 0x12, 0x7F, 0x10},
    {0x27, 0x45, 0x45, 0x45, 0x39},
    {0x3E, 0x49, 0x49, 0x49, 0x32},
    {0x01, 0x71, 0x09, 0x05, 0x03},
    {0x36, 0x49, 0x49, 0x49, 0x36},
    {0x26, 0x49, 0x49, 0x49, 0x3E},
};

static void oled_draw_glyph(uint8_t x, uint8_t y, const uint8_t *columns, uint8_t width, uint8_t scale_x, uint8_t scale_y) {
    for (uint8_t dx = 0; dx < width * scale_x; ++dx) {
        uint8_t bits = pgm_read_byte(columns + dx / scale_x);
        for (uint8_t dy = 0; dy < 7 * scale_y; ++dy) {
            oled_write_pixel(x + dx, y + dy, (bits & (1 << (dy / scale_y))) != 0);
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (!is_keyboard_left()) {
        return false;
    }

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    bool caps_lock = host_keyboard_led_state().caps_lock;

    oled_draw_glyph(1, 12, mix_logo, sizeof(mix_logo), 2, 2);
    oled_draw_glyph(1, 48, layer_label, sizeof(layer_label), 1, 1);
    oled_draw_glyph(4, 64, layer_digits[layer / 10], 5, 2, 3);
    oled_draw_glyph(18, 64, layer_digits[layer % 10], 5, 2, 3);

    for (uint8_t x = 4; x < 28; ++x) {
        oled_write_pixel(x, 34, true);
        oled_write_pixel(x, 96, true);
    }

    // Write the entire status area once, including padding, to erase old states.
    for (uint8_t x = 0; x < 28; ++x) {
        for (uint8_t y = 0; y < 11; ++y) {
            bool pixel = false;
            if (x >= 2 && x < 25 && y >= 2 && y < 9) {
                pixel = (pgm_read_byte(caps_label + x - 2) & (1 << (y - 2))) != 0;
            }
            oled_write_pixel(x + 2, y + 106, pixel ^ caps_lock);
        }
    }
    return false;
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NUBS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_MUTE, KC_LALT, KC_LGUI, MO(_FN), KC_SPC,  KC_ENT,  MO(_SYM),KC_LGUI, KC_RALT, LT(_BT, KC_SPC), KC_RCTL
    ),

    [_FN] = LAYOUT(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, _______, _______, _______, _______, KC_PIPE,
        _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, KC_COLN, KC_DQUO,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LT,   KC_GT,   KC_QUES, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_BT] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
    [_FN]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_SYM]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [_BT]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_DOWN, KC_UP) }
};
#endif
