BOOTLOADER EXPERIMENT
=====================

This repository consists of two different projects:

- easyboot: the bootloader
- blink: a sophisticated million dollars blinky application

Usage
=====

Build the two separate applications and flash them. Use either `app1` or `app2`
shield for blink application but you should flash both to complete the
experiment.

Partitions
==========

The following partitions are created:

- `boot`: bootloader area.
- `settings`: shared NVS settings.
- `app1`: firmware image 1.
- `app2`: firmware image 2.

easyboot
--------

The bootloader is flashed at the default board ROM offset and will select the
application to use depending on the default user button being pressed at
startup. If the button is not pressed, application starts at partition `app1`
otherwise at `app2`.

blink
-----

This application simply blinks the led0 or led1 depending on the application
offset.

For convenience, it is designed using a shield to select if the application
must be flashed on `app1` or `app2`.

Configure by passing an additional shield as specified in the zephyr documentation.

Example:

    cmake -S. -Bbuild -GNinja -DSHIELD=app2
    or
    west build --shield app2

Future directions
=================

1. Use zephyr flash API to download a firmware from SPI.
2. Register in the settings partition which app should boot from.
