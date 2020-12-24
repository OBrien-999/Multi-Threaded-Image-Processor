#ifndef BMPPROCESSOR
#define BMPPROCESSOR
#include <stdio.h>
#include "PixelProcessor.h"

struct BMP_Header {
	char signature[2];		//ID field
	int size;			//Size of the BMP file
	short reserved1;		//Application specific
	short reserved2;		//Application specific
	int offset_pixel_array;  	//Offset where the pixel array (bitmap data) can be found
};

struct DIB_Header{

	int size; 		//Size of this header
	int width; 		//width of bitmap in pixels
	int height; 		//height of bitmapin pixels
	short planes;		// the number of cvolor planes
	short bitsPerPixel; 	//the number of bits per pixel, which is the color depth of the image.
	int compression; 	//the compression method being used
	int imageSize; 		//the image size. This is the size of the raw bitmap data
	int horizRes; 		// the horizontal resolution of the image. (pixel per meter, signed integer)
	int vertRes; 		//	the vertical resolution of the image. (pixel per meter, signed integer)
	int colorNum; 		// the number of colors in the color palette
	int importantColorNum; 	// the number of important colors used

};

/**
 * read BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read
 * @param  header: Pointer to the destination BMP header
 */
void readBMPHeader(FILE* file, struct BMP_Header* header);


/**
 * write BMP header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being written
 * @param  header: The header to write to the file
 */
void writeBMPHeader(FILE* file, struct BMP_Header* header);


/**
 * read DIB header from a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being read
 * @param  header: Pointer to the destination DIB header
 */
void readDIBHeader(FILE* file, struct DIB_Header* header);


/**
 * write DIB header of a file. Useful for converting files from PPM to BMP.
 *
 * @param  file: A pointer to the file being written
 * @param  header: The header to write to the file
 */
void writeDIBHeader(FILE* file, struct DIB_Header* header);


/**
 * make BMP header based on width and height. 
 * The purpose of this is to create a new BMPHeader struct using the information 
 * from a PPMHeader when converting from PPM to BMP. (NOT NEEDED FOR THREADING HW.)
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeBMPHeader(struct BMP_Header* header, int width, int height);


 /**
 * Makes new DIB header based on width and height. Useful for converting files
 * from PPM to BMP. (NOT NEEDED FOR THREADING HW.)
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeDIBHeader(struct DIB_Header* header, int width, int height);


/**
 * read Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read
 * @param  pArr: Pixel array to store the pixels being read
 * @param  width: Width of the pixel array of this image
 * @param  height: Height of the pixel array of this image
 */
void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);


/**
 * write Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written
 * @param  pArr: Pixel array of the image to write to the file
 * @param  width: Width of the pixel array of this image
 * @param  height: Height of the pixel array of this image
 */
void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

#endif
