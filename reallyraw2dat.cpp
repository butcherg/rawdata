

#include <stdio.h>
#include <libraw/libraw.h>

int main(int argc, char * argv[])
{
	char * img;
	if (argc < 2) {
		printf("reallyraw2dat: Opens a raw file from a digital camera,\n");
		printf("extracts the really raw image array, and saves it to a\n");
		printf("16-bit unsigned integer .dat with absolutely no processing.\n");
		printf("\nUsage: $ reallyraw2dat rawfile.(NEF|CR2|whatever...) (whatevernameyouwant).dat\n\n"); 
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

	//Get the essential data from the opened raw file.
	//raw_image is an array of 16-bit integers of size width*height:
	int width = RawProcessor.imgdata.sizes.raw_width;
	int height = RawProcessor.imgdata.sizes.raw_height;
	
	libraw_internal_data_t * libraw_internal_data = RawProcessor.get_internal_data_pointer();
	char * rawimage = (char *) libraw_internal_data->unpacker_data.data_offset;
	long imagesize = libraw_internal_data->unpacker_data.data_size;
	
	printf("width: %d  height: %d\n", width, height);

	//Write the array of bytes comprising the image data
	//to a file:
	FILE *f = fopen(argv[2], "wb");
	fwrite (rawimage , 1, imagesize, f);
	fclose(f);

	RawProcessor.recycle();	

}