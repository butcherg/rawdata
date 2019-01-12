

#include <stdio.h>
#include <libraw/libraw.h>
#include <tiffio.h>

int main(int argc, char * argv[])
{
	if (argc < 2) {
		printf("rawdata: Opens a raw file from a digital camera,\n");
		printf("extracts the raw image array, and saves it to a\n");
                printf("16-bit integer TIFF with absolutely no processing.\n");
                printf("There's no metadata other than what TIFF needs to\n");
                printf("describe it as an image, and you'll even find the\n");
                printf("black borders where the sensor is masked.\n");
                printf("\nUsage: $ rawdata rawfile.(NEF|CR2|whatever...) (whatevernameyouwant).tif\n\n"); 
		return 1; 
	}

	if (argc < 3) {
		printf("No output filename specified.\n"); 
		return 1; 
	}

	//Use libraw to open the raw file and extract its parts:
	LibRaw RawProcessor;
	if (RawProcessor.open_file(argv[1]) != LIBRAW_SUCCESS) {
		printf("Raw file open failed...\n"); 
		return 1;
	}
	RawProcessor.unpack();

	//Get the essential data from the opened raw file.
	//raw_image is an array of 16-bit integers of size width*height:
	int width = RawProcessor.imgdata.sizes.raw_width;
	int height = RawProcessor.imgdata.sizes.raw_height;
	unsigned short *rawimage = RawProcessor.imgdata.rawdata.raw_image;

	//Use libtiff to write the TIFF image file:
	TIFF* tif = TIFFOpen(argv[2], "w");

	if (tif) {
		TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);  
		TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);    
		TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 1);   
		TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 16);

		TIFFSetField(tif, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_UINT);
		TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);   

		TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
		TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
		TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);

		//about the simplest TIFF format to write, one big strip:
		TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP, height);
		TIFFWriteEncodedStrip(tif, 0, rawimage, width*height*2);

		(void) TIFFClose(tif);

	}
	else {
		printf("TIFF file save failed...\n"); 
		return 1;
	}

	RawProcessor.recycle();	

}
