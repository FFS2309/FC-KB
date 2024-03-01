# FC-KB diy keyboard software for milk-v duo
A keyboard software meant to run on a Milk-V duo.

## Features
- [x] Modifier key input
- [x] Normal key inputs
- [x] (partial) LED support
- [x] N-Key rollover (The currently included hid descriptor "only" supports 80 key rollover but adapting to more keys would be fairly trivial)
- [x] Multiple bindings per key
- [x] Debouncing (immediate on, 5ms until key turns off)
### Todo
- [ ] RGB
- [ ] Layer support

## General project structure
### kbdrv-main.c
This file contains all the program code required to scan the keyboard matrix as well as assemble and send the hid reports.

### keyboard\_mapping.h
This file contains all the configuration and mapping of the device you are working with. This includes the GPIO pin mapping to rows/columns, matrix to binding
identifier and binding identifier to hid-modifiers/hid-usage codes.

## Important notes

While this project is designed to be used with the Milk-V duo range of devices it does **not** work out of the box because it assumes that a USB HID gadget is
configured in the UDC. To achieve this you need to modify the /etc/usb-run.sh script to be able to probe usb-hid *and* recompile the kernel to enable the
USB HID gadget support and configuration of this feature through configfs.

The project should also be easily portable to any linux device with a configured USB HID gadget and GPIO support through wiringX.
