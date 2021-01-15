e-Paper
=======

__Currently under development!__

Preamble
--------

Originally forked from the [waveshare/e-Paper repository](https://github.com/waveshare/e-Paper).

This repository has been reduced to work with the [Waveshare](https://www.waveshare.com/) [5.83'' e-Paper display](https://www.waveshare.com/wiki/5.83inch_e-Paper_HAT) on a Raspberry Pi. Support for other displays has been removed completely. Moreover it's meant to support only the C(++) programming language using the [bcm2835 library](https://www.airspayce.com/mikem/bcm2835/) instaed of [Wiring Pi](http://wiringpi.com/).

Prerequisites
-------------

- git: sudo apt install git
- [ImageMagick](https://imagemagick.org/) (_recommended_): sudo apt install imagemagick

Compile
-------

Use the (master) _Makefile_ provided in the _src/_ directory. There are other _Makefile_ files whithin subdirectories which will get invoked automatically by the (master) _Makefile_.

	cd src
	make
	sudo ./epd

To-Dos
------

- [ ] Move `EPD_5IN83_*` functions to the `MonochromeDisplay` class.
- [ ] Create a driver class to handle SPI communication.
- [ ] Create conditional _DEBUG_ output information.
- [ ] Extend documentation.

Bugs
----

- [ ] Destructor code is missing (**Memory leaks may occur!**).
    - [ ] MonochromeBitmap
    - [ ] MonochromeScreen
    - [ ] MonochromeDispaly
