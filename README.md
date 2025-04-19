# STM32 Register Level

Welcome to this repository of STM32 bare-metal code examples! This project is focused on learning and working directly with **STM32F1 series microcontrollers**, especially the popular **STM32F103C8T6 (Blue Pill)** board, using **register-level programming** — no HAL, no abstraction layers, just raw control over the hardware.

## 📌 What’s Inside

This repository includes:

- 🧠 Educational examples for understanding how peripherals work at the register level
- 💡 Minimal, clean, and well-commented C code for STM32F1 series
- 🔧 Peripheral demos such as:
  - RCC
  - GPIO
  - External interrupts
  - ADC
  - Timer
  - RTC
  - UART
  - SPI
  - I2C
  - CRC
  - Low Power Mode
  - Flash memory
  - FreeRTOS (basic demo)

## 🔧 Why Register-Level?

While HAL and LL libraries are convenient, register-level programming gives you:
- Better understanding of how the MCU works
- More control and efficiency
- Smaller and faster code
- A solid foundation for working with resource-constrained systems

## 📦 Target Hardware

- **MCU**: STM32F103C8T6
- **Board**: Blue Pill (the cheap and popular STM32F1 dev board)
- **Toolchain**: STM32CubeIDE
- **Debugger**: ST-Link V2 or similar

## 🚀 Getting Started

1. Clone this repo:
   ```bash
   git clone https://github.com/Tdieney/STM32_Register_Level.git
   cd stm32-register-examples
   ```

2. Open STM32CubeIDE (version 1.8 or lower).

3. You can flash to your Blue Pill board and debug using ST-Link and OpenOCD or any familiar tools.
  - Refer this link if you have problem when debugging with Bluepill board: https://tapit.vn/loi-va-cach-khac-phuc-khi-su-dung-stm32cubeide-de-lap-trinh-debug-cho-board-stm32f103-bluepill/

## 📁 Project Structure

Each folder contains an isolated example for a specific peripheral or concept.

## 🧠 Notes

- Code is meant for learning purposes. Use at your own risk in production.
- Pull requests and contributions are welcome!

## 📬 Contact

Have questions or suggestions? Feel free to open an issue or reach out!

