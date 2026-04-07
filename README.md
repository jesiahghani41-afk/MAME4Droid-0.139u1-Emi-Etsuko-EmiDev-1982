# Emi Etsuko (EmiDev, 1982)

A Brand New Classic 80's Arcade Game for **Emi Etsuko** by **EmiDev** at 1982. This repository contains the source code and integration files for **MAME4Droid (0.139u1)**.

## Game Information

| Field | Value |
| :--- | :--- |
| **Game Name** | Emi Etsuko |
| **Manufacturer** | EmiDev |
| **Year** | 1982 |
| **Genre** | Action/Platform (Vertical Screen) |
| **Players** | 1-2 |
| **Hardware** | Scramble |
| **Control** | 4-Way Joystick, 2 Button |
| **Source Code** | `emietsko.cpp` |
| **Emulator** | MAME4Droid (0.139u1) |
| **Rom Parent** | `emietsko.zip` |

## Repository Structure

- `emietsko.cpp`: The main MAME driver source code.
- `drivers.txt`: Driver registration entry for the MAME build system.
- `mame.mak`: Makefile fragment for compiling the new driver.
- `Arcade - Emi Etsuko (EmiDev, 1982).png`: Game artwork reference.

## Technical Details

The game runs on modified **Konami Scramble** hardware, featuring:
- **Main CPU**: Zilog Z80 @ 3.072 MHz
- **Sound CPU**: Zilog Z80 @ 1.78975 MHz
- **Sound Chips**: 2x AY-3-8910 @ 1.78975 MHz
- **Resolution**: 224x256 (Vertical), 32 colors

---
EmiDev © 1982
