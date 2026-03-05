# 4x4x4 LED Cube – Custom Firmware

Custom firmware for the **Hobby Components V2 4×4×4 LED Cube**.

This firmware **replaces the default factory demo** with a **continuous 3D animation loop**, pushing the **ATmega328** to generate volumetric lighting effects, physics-style simulations, and custom text displays.

# 💻 Software Prerequisites

Before you can compile and upload the firmware, you need to install the correct **hardware definitions** and the **LED cube control library** into your Arduino IDE.

## 1. Install the MiniCore Board Manager

Because the LED cube uses a **standalone ATmega328 chip** instead of a standard Arduino board, the **MiniCore hardware package** is required to communicate with it.

### Steps

1. Open the **Arduino IDE**
2. Go to **File → Preferences**
3. In the **Additional Boards Manager URLs** field, paste the following URL:
`https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json`
4. Click **OK**
5. Go to **Tools → Board → Boards Manager**
6. Search for **MiniCore**
7. Click **Install**

For more information, see the **MiniCore GitHub repository**.

## 2. Install the HC4x4x4 V2 Library

The **HC4x4x4 library** handles the complex **multiplexing required to drive the 64 LEDs smoothly**.

### Steps

1. Download the latest version of the **HC4x4x4 library** as a **`.zip` file** from the **Repository**
2. In the **Arduino IDE**, go to: **Sketch → Include Library → Add .ZIP Library...**
3. Select the **`.zip` file** you downloaded

The library will now be installed and available in your sketches.


# 🛠 Hardware Setup  
## Using an Arduino as a Programmer

The LED cube **does not include a USB interface**, so a spare Arduino (for example an **Elegoo UNO R3**) can be used as a **USB-to-Serial bridge** between your computer and the cube.

Before programming, you must **disable the Arduino’s microcontroller** so it does not intercept the code intended for the cube.

You can do this using **one of the following methods**.


## Method 1 — Remove the Microcontroller *(Recommended)*

If your Arduino has a **socketed ATmega chip** (e.g. Elegoo UNO R3):

- Use a **small flathead screwdriver**
- Carefully **pry the ATmega chip out of its socket**
- **Store the chip safely**

**Result:**  
The board becomes a **dedicated USB-to-Serial adapter**, allowing direct communication with the LED cube.


## Method 2 — Jumper Wire Reset Method

If the Arduino uses a **surface-mount microcontroller** that cannot be removed:

1. Take a **single jumper wire**
2. Connect **RESET → GND** on the Arduino

**Result:**  
This forces the Arduino chip into a **permanent reset state**, allowing the USB interface to pass data **directly to the LED cube**.


# ⚙ MiniCore Configuration

To compile and upload code to the **standalone ATmega328 inside the cube**, install and use the **MiniCore board package**.

Open **Arduino IDE → Tools** and configure the following settings:

### Board
- `MiniCore → ATmega328`

### Clock
- `8 MHz internal`
- ⚠ **Important:** The cube **does not use an external crystal**

### BOD (Brown-Out Detection)
- `2.7 V`
- Prevents unstable operation if supply voltage drops

### EEPROM
- `EEPROM retained`

### Compiler LTO
- `LTO disabled`

### Variant

Choose based on the chip marking:

- `328` → if the chip says **ATmega328-PU**
- `328P` → if the chip says **ATmega328P**

### Bootloader
- `Yes (UART0)`

### Port
- Select the **COM port corresponding to your Arduino**


# 🚀 Upload Process

Because the Arduino is acting as a **serial adapter**, you will use the **standard Upload button**.

⚠ **Do NOT select** *Upload Using Programmer*.

### Wiring

Connect the Arduino to the cube’s **5-pin programming header**:

- **RX → RX**
- **TX → TX**
- **5V → 5V**
- **GND → GND**

Additional connection:

- **Arduino RESET → Cube DTR**

### Upload Steps

1. Connect the Arduino to your computer
2. Open the Arduino IDE
3. Click the **Upload button (→)**
4. Wait for compilation and upload to complete


## Troubleshooting — Sync Error

If the IDE becomes stuck on **Uploading…** and reports a **sync error**, the automatic reset may have failed.

Try a **manual reset**:

1. Disconnect the **DTR wire**
2. Click **Upload**
3. Press the **cube’s reset button** exactly when the IDE switches from  
   **“Compiling” → “Uploading”**

This manually triggers the bootloader.


# 🌟 Included Animations

The firmware runs a **continuous master loop** of 3D animations.

### Scrolling “KCL”
- The text **KCL** scrolls smoothly across the **front face** of the cube.

### Striking K-C-L (Thunder Effect)
- Letters **K**, **C**, and **L** appear one-by-one on the **rear wall**
- Each letter triggers a **camera-flash burst** from the **4 accent LEDs in the base**

### Digital Rain
- A **Matrix-style effect** where random LED droplets fall from **top → bottom layers**

### Breathing 3D Box
- A **2×2×2 inner cube** expands into a **4×4×4 cube**
- Creates a **pulsing depth illusion**

### 3D Auto-Snake
- A **3-pixel snake** randomly navigates the cube
- Movement logic ensures it **never leaves the cube boundaries**

### Revolving Radar
- A **vertical LED plane** rotates **360° around the center axis**
- Simulates a **radar sweep**

### 3D Rolling Wave
- A **mathematical wave pattern** flowing diagonally across the **X and Z axes**

### Wobbling Tornado
- A rotating **3D funnel cloud** formed by intersecting LED lines
- Anchored at the **bottom center** while sweeping around the **top perimeter**
