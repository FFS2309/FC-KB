# FC-KB diy keyboard software for milk-v duo

## General project structure
### kbdrv-main.c
This file contains all the program code required to scan the keyboard matrix as well as assemble and send the hid reports.

### keyboard\_mapping.h
This file contains all the configuration and mapping of the device you are working with. This includes the GPIO pin mapping to rows/columns, matrix to binding
identifier and binding identifier to hid-modifiers/hid-usage codes. Currently there is no support for binding multiple actions to one key.

## Important notes

While this project is designed to be used with the Milk-V duo range of devices it does **not** work out of the box because it assumes that a USB HID gadget is
configured in the UDC. To achieve this you need to modify the /etc/usb-run.sh script to be able to probe usb-hid *and* recompile the kernel to enable the
USB HID gadget support and configuration of this feature through configfs.

The project should also be easily portable to any linux device with a configured USB HID gadget and GPIO support through wiringX.
