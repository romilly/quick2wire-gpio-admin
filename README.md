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

Usage
-----

To access the GPIO pins you must add yourself to the gpio group:

    sudo adduser $USER gpio
    
Then log out and back in again.

Usage instructions are installed as a man page, and so can be read with the command:

    man gpio-admin


Copyright & License
-------------------
       
Copyright © 2012 Quick2Wire Ltd. <http://quick2wire.com/>

See LICENSE.md for license information.
