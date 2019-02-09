srcdir=.
CC=g++

LFLAGS=$(shell pkg-config --libs libraw libtiff-4 rtprocess)
CFLAGS=$(shell pkg-config --cflags libraw libtiff-4 rtprocess)

#Uncomment for mingw32/msys2:
#EXT=.exe
#CFLAGS+= -DLIBRAW_NODLL

rawdata: rawdata.o
	$(CC) -o rawdata$(EXT) rawdata.o $(LFLAGS)

rawdata.o: $(srcdir)/rawdata.cpp
	$(CC) $(CFLAGS) -o rawdata.o -c $(srcdir)/rawdata.cpp

clean:
	rm -f rawdata.o rawdata$(EXT) 
