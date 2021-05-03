# rawdata

## Three programs:

- raw2tiff: Reads a camera raw file and outputs a 1-channel TIFF of the pre-demosaic image array.
- raw2dat:  Reads a camera raw file and outputs a .dat file of the pre-demosaic image array, just a file full of unsigned shorts.
- reallyraw2dat: Uses an undocumented access method to the Libraw internals to retrieve the unmodified (uncompressed, etc...) image data
from the camera raw file and write it to a .dat file.

## Prerequisites
All three programs require Libraw; raw2tiff also requires libtiff.  On Ubuntu:

$ sudo apt-get install libraw-dev libtiff-dev

## Building

$ mkdir build
$ cd build
$ cmake ..
$ make

