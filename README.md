# CUBE_STUDIO MIX — QMK / Vial firmware

QMK + Vial firmware for the CUBE_STUDIO MIX split keyboard (RP2040, NOLOGO RP2040 ProMicro).
ZMK version: [felixm12138/zmk-mix](https://github.com/felixm12138/zmk-mix)

## Contents

| Path | Description |
| --- | --- |
| `keyboards/cube_studio/mix/` | Keyboard definition, `default` and `vial` keymaps |
| `firmware/cube_studio_mix_vial.uf2` | Prebuilt Vial firmware |

Hardware details (pin map, OLED, Cirque trackpad, encoders, handedness) are in
[`keyboards/cube_studio/mix/readme.md`](keyboards/cube_studio/mix/readme.md).

## Flashing

1. Hold BOOT (or double-tap reset) to enter the RP2040 bootloader — an `RPI-RP2` drive appears.
2. Copy `firmware/cube_studio_mix_vial.uf2` onto it.
3. Repeat for the other half (flash **both** halves).

## Building from source

```bash
git clone --recurse-submodules https://github.com/vial-kb/vial-qmk.git
cd vial-qmk
cp -r /path/to/this/repo/keyboards/cube_studio keyboards/
make cube_studio/mix:vial
```

Output: `cube_studio_mix_vial.uf2`.
