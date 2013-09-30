# ScampKey - Alternative firmware for the ShrimpKey

At the mini maker fair 2013 in Kerkrade I bought a shrimpkey kit.
 http://fromscratched.nl/index.php/category/shrimpkey/

The Shrimpkey is a MakeyMakey clone, but I could not get it to operate properly.
 http://web.media.mit.edu/~ericr/makeymakey/

After talking with the author of the Shrimpkey, it was not clear what was wrong, we started to think it must be a hardware problem.

So after some long debugging hours and looking at the prototyping board I was sure the soldering was OK, and the problem was located in the firmware.

There was only thing left for me to do, to get it all to work... write my own firmware for the Shrimpkey.

So here it is... Scampkey, an alternative firmware for the Shrimpkey.

Enjoy...

Johan

## Usage

Copy the UsbKeyboard folder to your Arduino libraries folder (~/Documents/Arduino/libraries on OSX) and open the sketch in the Arduino IDE.

Some settings, like the key codes and pins can be configured in the 'Scampkey_settings.h' tab.

If you set the 'REPEAT' flag to false then the key repeat is disbaled when holding an input.

The 9 key codes default to WASD, IJKL and space. Gamers and vim users should feel at home ;-)

## Credits

Thanks to Sjoerd Dirk Meijer for creating the shrimpkey!
 http://fromscratched.nl/index.php/category/shrimpkey/

Thanks go the original MakeyMakey people!
