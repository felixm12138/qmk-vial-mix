# MIX QMK / Vial Firmware

![Keyboard](https://img.shields.io/badge/Keyboard-MIX-black)
![Firmware](https://img.shields.io/badge/Firmware-QMK%20%2B%20Vial-blue)
![Controller](https://img.shields.io/badge/Controller-RP2040-green)

QMK + Vial firmware for the **CUBE_STUDIO MIX** wired split keyboard (RP2040), with the right-hand Cirque trackpad, a rotary encoder on each half and a 128×32 OLED on the left half.

**CUBE_STUDIO MIX** 有线分体键盘的 QMK + Vial 固件（RP2040），支持右手 Cirque 触控板、左右滚轮和左手 128×32 OLED 屏幕，可用 Vial 实时改键。

## 官方资源 / Official Resources

购买、使用说明和教程都在工作室官网 [cubekb.com](https://cubekb.com)。 / Shop, user guides and tutorials live on the studio website [cubekb.com](https://cubekb.com).

* MIX 使用说明 / MIX user guide: [cubekb.com/wiki/products/mix](https://cubekb.com/wiki/products/mix)
* 刷机教程 / Flashing firmware: [guides/flash-firmware](https://cubekb.com/wiki/guides/flash-firmware)
* Vial 改键 / Vial remapping: [guides/vial](https://cubekb.com/wiki/guides/vial)
* 故障排查 / Troubleshooting: [guides/troubleshooting](https://cubekb.com/wiki/guides/troubleshooting)
* 邮箱 / Email: [cubekb_studio@outlook.com](mailto:cubekb_studio@outlook.com) · QQ 群 / QQ group: **1037094476**

---

## 固件版本 / Firmware Editions

MIX 有三种固件，按购买时选择的配置使用对应的仓库。 / MIX ships with one of three firmwares — use the repository that matches your configuration.

| 版本 Edition | 仓库 Repository | 连接 Connection | 主控 Controller | 触控板 Touchpad | 改键 Remapping |
| --- | --- | --- | --- | --- | --- |
| ZMK | [zmk-mix](https://github.com/felixm12138/zmk-mix) | 无线 BLE + USB / Wireless | nRF52840 | ✓ | ZMK Studio |
| QMK + Vial | [qmk-vial-mix](https://github.com/felixm12138/qmk-vial-mix) | 有线 USB / Wired | RP2040 | ✓ | Vial |
| RMK | [rmk_mix](https://github.com/felixm12138/rmk_mix) | 无线 BLE + USB / Wireless | nRF52840 | — | Vial |

三个版本的默认键位一致。 / All three share the same default keymap.

---

## 功能特性 / Features

* 有线分体：USB-C 接任意一侧，左右手之间用线连接 / Wired split: plug USB-C into either half; the halves are linked by cable
* Cirque 触控板（右手）：轻触为左键，右上角轻触为右键，沿外圈滑动滚动 / Cirque trackpad (right): tap = left click, top-right tap = right click, circular scroll along the edge
* 左右各一个滚轮（EC11） / A roller (EC11 encoder) on each half
* 左手 OLED：MIX 标志、当前层号（00–15）、大写锁定 / Left OLED: MIX logo, layer number (00–15), Caps Lock
* Vial 实时改键，16 层 / Live remapping in Vial, 16 layers

---

## 刷机 / Flashing

**进入刷机模式 / Enter the bootloader**（任选其一 / any of these）

* 快速双击控制器上的复位键 / Double-tap the reset button on the controller
* 按住左上角 `Esc` 再插上 USB（左手） / Hold `Esc` while plugging in USB (left half)
* 按住第 3 层键（RCtrl 左侧的 Space）再按 `Esc` / Hold the layer-3 key (the `Space` next to RCtrl) and press `Esc`

电脑上会出现名为 `RPI-RP2` 的 U 盘，把 `.uf2` 文件拖进去，键盘会自动重启。**左右手都要刷。**
A drive named `RPI-RP2` appears; copy the `.uf2` onto it and the board reboots. **Flash both halves.**

预编译固件 / Prebuilt firmware: [`firmware/cube_studio_mix_vial.uf2`](firmware/cube_studio_mix_vial.uf2)

---

## 按键 / Keymap

| 层 Layer | 进入方式 Access | 内容 Contents |
| --- | --- | --- |
| 0 Base | — | 数字行 + QWERTY / Number row + QWERTY |
| 1 Fn | 按住左手 `MO 1` / hold left `MO 1` | F1–F12、`- = [ ]` |
| 2 Sym | 按住右手 `MO 2` / hold right `MO 2` | 上档符号 / Shifted symbols `! @ # … { } < > ?` |
| 3 | 按住 RCtrl 左侧的 Space（单击为空格） / hold the `Space` next to RCtrl (tap = space) | `Esc` 位：进入刷机模式；`Tab` 位：清除 Vial 设置 / `Esc`: bootloader; `Tab`: clear Vial settings (EEPROM) |

**滚轮 / Rollers**

| 层 Layer | 左滚轮 Left | 右滚轮 Right |
| --- | --- | --- |
| 0 | 音量 / Volume | 滚动 / Scroll |
| 1 | 音量 / Volume | 翻页 / Page Up · Down |
| 2、3 | 音量 / Volume | 方向键 / Arrow Up · Down |

**Vial 改键 / Remapping in Vial**

用 [Vial](https://get.vial.today) 桌面版或网页版 [vial.rocks](https://vial.rocks) 连接键盘即可实时改键。解锁组合键为 **Esc + Backspace + 拇指区 Space + Enter**。
Open the [Vial](https://get.vial.today) app or [vial.rocks](https://vial.rocks) to remap live. The unlock combo is **Esc + Backspace + thumb Space + Enter**.

---

## 自行编译 / Building

```bash
git clone --recurse-submodules https://github.com/vial-kb/vial-qmk.git
cd vial-qmk
cp -r /path/to/qmk-vial-mix/keyboards/cube_studio keyboards/
make cube_studio/mix:vial
```

输出文件 / Output: `cube_studio_mix_vial.uf2`。Windows 可使用 [QMK MSYS](https://msys.qmk.fm) 编译。 / On Windows, build with [QMK MSYS](https://msys.qmk.fm).

### 仓库结构 / Repository structure

```text
.
├── firmware/
│   └── cube_studio_mix_vial.uf2      # Prebuilt firmware
└── keyboards/cube_studio/mix/
    ├── keyboard.json                 # Matrix, pins, layout
    ├── config.h                      # Split, OLED, Cirque settings
    ├── readme.md                     # Hardware notes and full pin map
    └── keymaps/
        ├── default/                  # Plain QMK keymap
        └── vial/                     # Vial keymap (with OLED rendering)
```

硬件细节（引脚表、OLED、触控板、左右手识别）见 [`keyboards/cube_studio/mix/readme.md`](keyboards/cube_studio/mix/readme.md)。
Hardware details (pin map, OLED, trackpad, handedness) are in [`keyboards/cube_studio/mix/readme.md`](keyboards/cube_studio/mix/readme.md).

---

## 常见问题 / Troubleshooting

* **某一半不工作 / One half dead**：确认左右手都刷了同一份固件，连接线插好。 / Make sure both halves run the same firmware and the link cable is seated.
* **Vial 无法修改 / Vial won't save changes**：先按解锁组合键。 / Press the unlock combo first.
* **键位乱了 / Keymap messed up**：按住第 3 层键再按 `Tab` 恢复默认。 / Hold the layer-3 key and press `Tab` to reset to defaults.
* 更多 / More: [故障排查 Troubleshooting](https://cubekb.com/wiki/guides/troubleshooting)

---

## 致谢 / Credits

* [QMK Firmware](https://github.com/qmk/qmk_firmware) · [Vial](https://github.com/vial-kb/vial-qmk)
