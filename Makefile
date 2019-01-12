CC=g++

LFLAGS=$(shell pkg-config --libs libraw libtiff-4)
CFLAGS=$(shell pkg-config --cflags libraw libtiff-4)

#Uncomment for mingw32/msys2:
#EXT=.exe
#CFLAGS+= -DLIBRAW_NODLL

rawdata: rawdata.o
	$(CC) -o rawdata$(EXT) rawdata.o $(LFLAGS)

rawdata.o: rawdata.cpp
	$(CC) $(CFLAGS) -o rawdata.o -c rawdata.cpp

clean:
	rm -f rawdata.o rawdata$(EXT) 
