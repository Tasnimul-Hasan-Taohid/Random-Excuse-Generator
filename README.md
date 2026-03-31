# Random Excuse Generator 🎉

> *An Arduino-based device that generates random "I can't, because..." excuses to help you avoid meetings!*

## Overview

The Random Excuse Generator is a fun and practical Arduino project that displays random, pre-programmed excuses whenever you need to skip a meeting. Simply press the button to cycle through 50 creative excuses, or hold it for 2 seconds to save your favorites!

Perfect for:
- Avoiding unwanted meetings
- Getting creative inspiration for excuses
- Learning Arduino button handling and EEPROM storage
- Adding a bit of humor to your desk

## Features ✨

- **50 Unique Excuses** - A curated collection of funny and creative reasons to avoid meetings
- **Button Control** - Quick press to display the next random excuse
- **Favorite Marking** - Hold the button for 2 seconds to mark/unmark favorite excuses
- **Persistent Memory** - Your favorite excuses are saved to EEPROM and survive power cycles
- **Simple Hardware** - Works with Arduino Uno, Nano, or Mega
- **Serial Monitor Output** - Easy to read excuse display with formatting
- **Visual Feedback** - LED indicator shows when favorites are being marked

## Hardware Requirements 🔧

### Bill of Materials (BOM)

| Component | Qty | Notes |
|-----------|-----|-------|
| Arduino Uno/Nano/Mega | 1 | Main microcontroller |
| Push Button (normally open) | 1 | 6mm x 6mm standard size |
| Resistor 10kΩ | 1 | Pull-up resistor (optional if using INPUT_PULLUP) |
| LED (optional) | 1 | 5mm red/green for visual feedback |
| Resistor 220Ω | 1 | LED current limiting (if using LED) |
| USB Cable | 1 | For programming and power |
| Breadboard | 1 | For prototyping |
| Jumper Wires | 4-6 | Various colors |

### Wiring Diagram
