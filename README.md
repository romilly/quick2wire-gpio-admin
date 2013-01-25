GPIO Admin
==========

A command-line tool to export or unexport the Raspberry Pi's GPIO pins
and allow only the user to control then.


Installation
------------

To install the gpio-admin command & manual page, and create the gpio
group if it does not already exist, run the following commands from the
root of the source tree:

    make
    sudo make install


To uninstall, run the command:

    sudo make uninstall


Getting Started
---------------

To access the GPIO pins you must add yourself to the gpio group:

    sudo adduser $USER gpio
    
Then log out and back in again. (Your membership of the gpio group won't take effect until you do.)

You can now export GPIO pins and use them without having to log in as root or use the sudo command.

    % gpio-admin export 22
    % cat /sys/devices/virtual/gpio/gpio22/value
    0
    % echo out > /sys/devices/virtual/gpio/gpio22/direction
    % echo 1 > /sys/devices/virtual/gpio/gpio22/value
    
When finished with a pin, unexport it again:

    % gpio-admin unexport 22
    

GPIO Pin Identifiers
--------------------

The gpio-admin command works with the GPIO identifiers defined by the SOC, *not* Raspberry Pi 
header pin numbers or the GPIO numbers assigned to header pins by the Raspberry Pi documentation.

The example above uses SOC GPIO 22, which corresponds to header pin 8 on the Raspberry Pi, and that
pin is named GPIO 3 in the Raspberry Pi documentation.

All very confusing!

We provide [higher level APIs](https://github.com/quick2wire/quick2wire-python-api/) that map between the pin identifiers that users understand and the 
identifiers defined by the SOC, and use gpio-admin behind the scenes to export/unexport GPIO pins as
required.

Enabling the Pi's Pull Up and Pull Down Resistors
-------------------------------------------------

The Pi supports pull up and pull down resistors for each GPIO pin. To enable this add either "pullup" or "pulldown" as a 3rd parameter. Assumming that pin 17 is floating:

    % gpio-admin export 17 pullup
    % cat /sys/class/gpio/gpio17/value
    1
    % gpio-admin unexport 17
    % gpio-admin export 17 pulldown
    % cat /sys/class/gpio/gpio17/value
    0


More Information
----------------

Usage instructions are installed as a man page, and so can be read with the command:

    man gpio-admin


Copyright & License
-------------------
       
Copyright © 2012 Quick2Wire Ltd. <http://quick2wire.com/>

See LICENSE.md for license information.
