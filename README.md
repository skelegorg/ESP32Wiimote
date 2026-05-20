# ESP32Wiimote

ESP32Wiimote is an Arduino library for ESP32 devices, that connects over Bluetooth with a Wii remote (Wiimote), and its optional connected Nunchuk.

This fork has the following improvements:
- support for the IR camera (supporting light bar)

On the ESP32, it reports easily at 100Hz:
- all regular button presses (A/B/C/Z/1/2/-/Home/+/D-Pad)
- the 3-dimensional acceleration/orientation of both Wiimote and Nunchuk
- the analog joystick of the Nunchuk
- the output of the IR camera (the X/Y position and size of up to 4 infrared targets in the remote's FOV)

NOTE: to support both IR camera and the nunchuck, the nunchuck must be plugged in prior to connecting. Going to try to fix this soon. ALSO, due to limitations from the Wii remote reporting system, size information is unavailable when plugged into an extension. See [the Wiibrew wiki page](https://wiibrew.org/wiki/Wiimote) for more information on data reporting modes.

## Requirement

- ESP32 board (any)
- Arduino IDE (Version >= 1.8.5)
  - Use version 2.0.17 of the Espressif ESP32 board manager libraries.
- Wii Remote (RVL-CNT-01)
- Wii Nunchuk (optional)

## Installation
1. Download the zip file.
2. Move the zip file to your libraries directory.
3. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library.
4. Select the zip file.

## Examples

A full example can be found at [ESP32WiimoteDemo.ino](./examples/ESP32WiimoteDemo/ESP32WiimoteDemo.ino)

- Caution: the accelerometers and IR camera report a lot of data
- This can get filtered/prevented by using 'add filter(ACTION_IGNORE,...)'
- The reports from the analog joystick of the Nunchuk can als be configured for larger minimal steps
- The IR camera is disabled by default. Call `wiimote.useIRCamera(true)` in `setup()` to enable it (like in the example).

## Usage 
No need to pair the controller over Bluetooth. Just do:
1. To connect, press the 1 and 2 buttons on Wii Remote
2. The LED1 will be on when they have finished connecting  
<img width="30%" src="./remocon_led1_on.png" />  

## Licence

   see [LICENSE.md](./LICENSE.md)
