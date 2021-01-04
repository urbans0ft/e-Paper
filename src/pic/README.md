Creating an image via the command line using [ImageMagick](https://imagemagick.org/).

    $ convert -font Bookman-Light -size 600x448 -depth 1 -type bilevel -pointsize 36 -gravity Center label:'Hello World!' BMP3:hello_world.bmp
    $ file hello_world.bmp
    hello_world.bmp: PC bitmap, Windows 3.x format, 600 x 448 x 1


