e-Paper
=======

__Currently in beta statium!__

Preamble
--------

Originally forked from the [waveshare/e-Paper repository](https://github.com/waveshare/e-Paper).

This repository has been reduced to work with the [Waveshare](https://www.waveshare.com/) [5.83'' e-Paper display](https://www.waveshare.com/wiki/5.83inch_e-Paper_HAT) on a Raspberry Pi. Support for other displays has been removed completely. Moreover it's meant to support only the C(++) programming language using the [bcm2835 library](https://www.airspayce.com/mikem/bcm2835/) instaed of [Wiring Pi](http://wiringpi.com/).

Prerequisites
-------------

- git: `sudo apt install git`
- bcm2835 lib
	- Download latest (bcm2835-1.XX.tar.gz)[http://www.airspayce.com/mikem/bcm2835/].
		
		```
		tar zxvf bcm2835-1.XX.tar.gz
		cd bcm2835-1.XX
		./configure
		make
		sudo make check
		sudo make install
		```

- libconfig: ` sudo apt install libconfig++-dev`
- [ImageMagick](https://imagemagick.org/) (_recommended_): `sudo apt install imagemagick`

Compile
-------

Use the (master) _Makefile_ provided in the _src/_ directory. There are other _Makefile_ files whithin subdirectories which will get invoked automatically by the (master) _Makefile_.

	cd src
	make
	sudo ./epd

To-Dos
------

- [x] Move `EPD_5IN83_*` functions to the `MonochromeDisplay` class.
- [x] Create a driver class to handle SPI communication.
	- [ ] Make the class a singleton
	- [ ] Make the SPI pins configurable
- [ ] Create conditional _DEBUG_ output information.
- [ ] Extend documentation.

Bugs
----

- [ ] Destructor code is missing (**Memory leaks may occur!**).
    - [ ] MonochromeBitmap
    - [ ] MonochromeScreen
    - [ ] MonochromeDispaly
