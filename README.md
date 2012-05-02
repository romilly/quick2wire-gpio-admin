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

    make uninstall

Usage
-----

Users that want to access GPIO pins must be added to the gpio group.

Usage instructions are installed as a man page.


Copyright & License
-------------------
       
Copyright © 2012 Quick2Wire Ltd. <http://quick2wire.com/>

See LICENSE.md for license information.
