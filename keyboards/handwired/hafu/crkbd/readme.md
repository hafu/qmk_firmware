# Handwired Corne (crkbd)


```
┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │
├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │
└───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
          ┌───┐                   ┌───┐
          │GUI├───┐           ┌───┤Alt│
          └───┤Bsp├───┐   ┌───┤Ent├───┘
              └───┤   │   │   ├───┘
                  └───┘   └───┘
```

A 3D printed handwired Corne (CRKBD) with a 3x5\_3 matrix only using 1U keys.

I was curious about split keyboards and using fewer keys to experiment with
layouts like Colemak(-DH) and [Miryoku](https://github.com/manna-harbour/miryoku).

So I started using parts which I had lying around. I put some Cherry MX Blacks
and two Atmega328p together and failed miserably. It worked kinda, but the
communication between the halves didn't work well. After replacing the
Atmega328p's with RP2040 it worked flawlessly.

Now at the start of autumn 2025 it is my daily driver since over a year.

* Keyboard Maintainer: [hafu](https://github.com/hafu)
* Hardware Supported: [Raspberry Pi Pico (1)](https://www.raspberrypi.com/products/raspberry-pi-pico/)
* Hardware Availability: [Raspberry Pi Pico 1 Resellers](https://www.raspberrypi.com/products/raspberry-pi-pico/#find-reseller)

Make example for this keyboard (after setting up your build environment):

    make handwired/hafu/crkbd/pi_pico:default

or

    qmk compile -kb handwired/hafu/crkbd/pi_pico -km default

Flashing example for this keyboard:

* Enter the [bootloader](#bootloader) of the RP2040
* Copy the uf2 file onto the appearing mass storage

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**:
  * Option 1:
    * Unplug the board
    * Hold the reset button
    * Connect the board to the computer
    * A new disk drive should appear
  * Option 2 (only if this firmware is flashed)
    * Double-tap the reset button on start up
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
