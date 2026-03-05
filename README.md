# 4x4x4 LED Cube Custom Firmware

This repository contains custom firmware for the **Hobby Components V2 4x4x4 LED Cube**. It completely replaces the default factory demo with a continuous, endlessly looping 3D light show, pushing the ATmega328 chip to its limits to create volumetric effects, physics simulations, and custom text.

## 🎬 Demo
<p align="center">
  <img src="images/cube_demo.gif" alt="4x4x4 LED Cube Animations" width="600">
</p>


## 📑 Table of Contents
- [Software Prerequisites](#-software-prerequisites)
- [Hardware Setup](#%EF%B8%8F-hardware-setup)
- [MiniCore Settings](#%EF%B8%8F-minicore-settings)
- [Upload Process](#-upload-process)
- [Included Animations](#-included-animations)

---

## 💻 Software Prerequisites
Before you can compile and upload the firmware, you need to install the correct hardware definitions and the LED cube library into your Arduino IDE.

<details>
<summary><strong>Click to view installation instructions</strong></summary>

### 1. Install the MiniCore Board Manager
Because the LED cube uses a standalone ATmega328 chip, you need the MiniCore hardware package to communicate with it.
1. Open the Arduino IDE and go to **File > Preferences**.
2. In the "Additional Boards Manager URLs" field, paste:  
   `https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json`
3. Go to **Tools > Board > Boards Manager**.
4. Search for "MiniCore" and click **Install**.
   *(See the [MiniCore GitHub Repository](https://github.com/MCUdude/MiniCore) for more details).*

### 2. Install the HC4x4x4 V2 Library
This library handles the complex multiplexing required to control the 64 LEDs.
1. Download the HC4x4x4 library `.zip` file from the Repository.
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
3. Select the downloaded .zip file to install it.
</details>

---

## 🛠️ Hardware Setup
Because the LED cube does not have a built-in USB port, you can use a spare Arduino (like an Elegoo UNO R3) to bridge the USB connection from your computer to the cube's serial pins.


To do this, you first need to disable the "brain" on the programmer Arduino so it doesn't intercept the code meant for the LED cube.

<details>
<summary><strong>Click to view Arduino passthrough methods</strong></summary>

### Method 1: Remove the Microcontroller Chip (Recommended)
If your Arduino uses a large, socketed rectangular chip (like the Elegoo UNO R3), use a small flathead screwdriver to gently pry the ATmega chip completely out of its socket. Place it somewhere safe. This physically disconnects the brain, turning the board into a dedicated, clean USB-to-Serial adapter.

### Method 2: The Jumper Wire Method
If your Arduino has a tiny surface-mount chip permanently soldered to the board, you cannot remove it. Instead, take a single jumper wire and connect the Arduino's **RESET** pin directly to one of its **GND** pins. This forces the chip into a permanent "sleep" state, allowing the USB data to pass directly through to the LED cube.
</details>

---

## ⚙️ MiniCore Settings
To successfully compile and upload code to the standalone ATmega328 chip inside the cube, open the Arduino IDE, go to the **Tools** menu, and set it up exactly like this:

> [!IMPORTANT]
> The LED cube does not have an external crystal and relies on the **8 MHz internal clock**. Selecting the standard 16 MHz clock setting will completely prevent code uploads!

* **Board:** MiniCore > ATmega328
* **Clock:** 8 MHz internal
* **BOD:** 2.7V (Brown-out detection)
* **EEPROM:** EEPROM retained
* **Compiler LTO:** LTO disabled
* **Variant:** 328P / 328 (If your chip says "ATmega328-PU", select the non-P variant)
* **Bootloader:** Yes (UART0)
* **Port:** Select your Arduino's COM port.

---

## 🚀 Upload Process
Since you are using your Arduino as a makeshift serial adapter, upload the code using the standard method (do not select "Upload using Programmer").

<details>
<summary><strong>Click to view step-by-step upload instructions</strong></summary>

1. Ensure your Arduino (with its chip removed/bypassed) is wired to the cube's 5-pin header:
   * **RX** to **RX**
   * **TX** to **TX**
   * **5V** to **5V**
   * **GND** to **GND**
2. Connect the Arduino's **RESET** pin to the Cube's **DTR** pin.
3. Click the standard **Upload** button in the Arduino IDE.

**Troubleshooting Sync Errors:** If the IDE gets stuck on "Uploading..." and throws a sync error, the automatic reset failed. To upload manually:
1. Unplug the wire from the DTR pin.
2. Click **Upload**.
3. Press the physical push-button switch on your cube the **exact moment** the IDE switches from "Compiling" to "Uploading".
</details>

---

## 🌟 Included Animations
The custom master loop runs through the following 3D sequences continuously:

* **Scrolling "KCL":** The letters "KCL" scroll smoothly left-to-right across the front face.
* **Striking K-C-L (with Thunder LEDs):** The letters K, C, and L flash one by one onto the rear wall. Each letter is punctuated by a synchronized camera-flash effect using the 4 base accent LEDs.
* **Digital Rain:** A classic "Matrix-style" effect where randomized single LED "raindrops" fall through the Z-axis.
* **Breathing 3D Box:** A hollow 2x2x2 inner cube that repeatedly expands into a full 4x4x4 outer cube, creating a pulsing depth effect.
* **3D Auto-Snake:** A 3-pixel-long "snake" that randomly slithers and hunts its way around the 64-LED grid.
* **Revolving Radar:** A solid vertical plane of LEDs that spins 360 degrees around the center axis.
* **3D Rolling Wave:** A height-mapped mathematical wave that fluidly rolls diagonally across the X and Z axes.
* **Wobbling Tornado:** A spinning 3D funnel cloud that sweeps around the top perimeter while anchored to the bottom center.

---
