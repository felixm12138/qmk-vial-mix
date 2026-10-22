# MIX

QMK/Vial firmware skeleton for the CUBE_STUDIO MIX keyboard, based on the ZMK layout from `felixm12138/zmk-mix`.

This is an RP2040 wired split build scaffold for the NOLOGO RP2040 ProMicro board.

Ported from the current ZMK layout:

- Split matrix: 5 rows x 6 columns per half, exposed to Vial as 10 rows x 6 columns
- Four default layers: Base, Fn, Symbols, and the original Bluetooth layer as a wired placeholder layer. Vial dynamic keymap is set to 16 layers.
- One EC11 encoder per half
- Left-hand 0.91-inch SSD1306 128x32 I2C OLED (address 0x3C), showing layer 00-15 and Caps Lock status
- Cirque Pinnacle trackpad on the right half over SPI, in relative mode with tap, secondary tap, and side scroll enabled
- Vial unlock combo matching the ZMK boot combo positions: `0`, `11`, `54`, `53`

Pin mapping lives in `keyboard.json`. Both halves use the same column pin order; the right half is mirrored in the layout matrix coordinates instead of by reversing GPIO pins.

| MIX schematic / ZMK net | NOLOGO RP2040 ProMicro pin used by QMK |
| --- | --- |
| row 0, `pro_micro 16` | `GP23` |
| row 1, `pro_micro 10` | `GP21` |
| row 2 | `GP16` |
| row 3 | `GP15` |
| row 4 | `GP14` |
| left col 0..5, `pro_micro 21,20,19,18,15,14` | `GP29, GP28, GP27, GP26, GP22, GP20` |
| right col 0..5 | `GP29, GP28, GP27, GP26, GP22, GP20` |
| encoder A/B | `GP1, GP9` |
| split single-wire serial, schematic `TX` | `GP12` |
| split handedness detect, schematic `RX` | `GP13` |
| Cirque SPI SCK | `GP6` |
| Cirque SPI MOSI | `GP7` |
| Cirque SPI MISO | `GP4` |
| Cirque SPI CS | `GP5` |
| Cirque DR | `GP8` |
| Left OLED SDA | `GP2` |
| Left OLED SCL | `GP3` |

Rows 2..4 follow the MIX schematic GPIO labels supplied for the RP2040 board. Cirque uses a separate SPI0 pin group so it does not share GPIOs with the matrix rows. The Cirque DR line is wired to `GP8`; QMK does not enable it as `POINTING_DEVICE_MOTION_PIN` because that option is not compatible with `SPLIT_POINTING_ENABLE`, so the sensor is polled instead.

Handedness is detected from the schematic `RX` pin, so `EE_HANDS` is intentionally not used. This board pulls `GP13` high on the right half, so `SPLIT_HAND_PIN_LOW_IS_LEFT` is enabled: low = left, high = right.

The left OLED uses I2C1. Layer and host LED state are synchronized so the display also works when USB is connected to the right half. Flash both halves after this change because the split synchronization configuration has changed. Connect OLED power to 3.3 V and GND.

The OLED is mounted vertically with the connector at the bottom. The Vial keymap uses `OLED_ROTATION_270` (corrected after hardware feedback) and a 32x128 portrait layout: a MIX pixel wordmark, large two-digit layer number (00-15), thin dividers, and a CAPS label that turns black-on-white while Caps Lock is enabled. All artwork is monochrome and rendered at native pixel coordinates.

The original ZMK build had wireless, display, and Cirque pointing support. This QMK/Vial build keeps wireless out and supports the right-hand Cirque SPI trackpad and left-hand OLED.

Build:

```bash
make cube_studio/mix:vial
```

The RP2040 build output is `cube_studio_mix_vial.uf2`.
