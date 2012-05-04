GPIO Admin
==========

A command-line tool to export or unexport the Raspberry Pi's GPIO pins
and allow users in the gpio group to control then.


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
    
Then log out and back in again. (Your membership of the gpio group won't take effect until you do).

You can now export GPIO pins and use them without having to log in as root or use the sudo command.

    % gpio-admin export 22
    % cat /sys/devices/virtual/gpio/gpio22/value
    0
    % echo out > /sys/devices/virtual/gpio/gpio22/direction
    % echo 1 > /sys/devices/virtual/gpio/gpio22/value
    
When finished with a pin, unexport it again:

    % gpio-admin unexport 22
    

More Information
----------------

Usage instructions are installed as a man page, and so can be read with the command:

    man gpio-admin


Copyright & License
-------------------
       
Copyright © 2012 Quick2Wire Ltd. <http://quick2wire.com/>

See LICENSE.md for license information.
