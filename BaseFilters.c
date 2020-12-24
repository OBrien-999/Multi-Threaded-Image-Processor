/**
* Applies blur and swiss cheese filter to bmp file
* @author Noah O'Brien
* @version 1.0
*/
////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include "BmpProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

//problem assumptions
#define BMP_HEADER_SIZE 14		// Bits
#define BMP_FILE_SIZE 24		// Bits uncompressed
#define BMP_DIB_HEADER_SIZE 40		// Bits
#define MAXIMUM_IMAGE_SIZE 4096		// Pixels
#define THREAD_COUNT 4			// Threads
#define ARRAY_SIZE 3			// Size of individual pixel array

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

struct Input {

	char *folder;
	char *in;
	char *out;
	char *filter;

};

typedef struct Array {

	int width;
	int height;
	struct Pixel **pixel;

} Array;

typedef struct Instructions {

	int start;
	int finish;

} inst;


////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE

Array* array1;
Array* array2;
Array* results;

// Creates a new empty copy array
struct Pixel** createArray(FILE* file, int width, int height){

	struct Pixel **pixel = malloc(height * sizeof(struct Pixel*));
	for(int i = 0; i < height; i++){

			 pixel[i] = malloc(width * sizeof(struct Pixel*));

	}

	readPixelsBMP(file, pixel, width, height);

	return pixel;

}

// Adds two arrays that contain the pixel data
Array* addArrays() {


	results = (Array*) malloc(sizeof(Array));
	results->width = ARRAY_SIZE;
	results->pixel = malloc(sizeof(unsigned char) * ARRAY_SIZE);

	pthread_t threads[THREAD_COUNT];
	inst instructions[THREAD_COUNT];

	for(int i = 0; i < THREAD_COUNT; i++){



	}

	for(int i = 0; i < THREAD_COUNT; i++) {



	}

	return results;

}

// Destroys array in memory
void destroyArray(Array** array){

	free((*array)->pixel);
	free(*array);
	*array = NULL;

}

void* runner(void* args) {

	inst* instructions = (inst*) args;

	for(int i = instructions->start; i < instructions->finish; i++) {

		//results->pixel[i] = array1->pixel[i] + array2->pixel[i];

	}

	return 0;

}

// Applies the blur affect to an image using threading
void boxBlur(FILE* fileIn, FILE* fileOut, struct Pixel **pixel, struct BMP_Header *bmp, struct DIB_Header *dib) {

	struct Pixel **copy = createArray(fileIn, dib->width, dib->height);
	readPixelsBMP(fileIn, copy, dib->width, dib->height);

	int i, j;
	unsigned char REDavg, GREENavg, BLUEavg, counter;

	for (i = 0; i < dib->height; i++) {

		for (j = 0; j < dib->width; j++) {

			REDavg = 0;
			GREENavg = 0;
			BLUEavg = 0;
			counter = 0;


			int rowStart = -1;
	        int rowEnd = 1;
	        int columnStart = -1;
	        int columnEnd = 1;

	        if (i + rowStart < 0) { rowStart = 0; }
	        if (j + columnStart < 0) { columnStart = 0; }
	        if (i + rowEnd >= dib->height) { rowEnd = 0; }
	        if (j + columnEnd >= dib->width) { columnEnd = 0; }

	            // go across the pixels around
	        for (int rowPixel = rowStart; rowPixel <= rowEnd; rowPixel++) {

	        	for (int columnPixel = columnStart; columnPixel <= columnEnd; columnPixel++) {

	        		int row = i + rowPixel;
	                int column = j + columnPixel;

	                REDavg += copy[row][column].red;
	                GREENavg += copy[row][column].green;
	                BLUEavg += copy[row][column].blue;
	                counter ++;

	              }

	         }

		}

		pixel[i][j].red = round(REDavg / (unsigned char) counter);
		pixel[i][j].green = round(GREENavg / (unsigned char) counter);
		pixel[i][j].blue = round(BLUEavg / (unsigned char) counter);

	}

	    writeBMPHeader(fileOut, bmp);
	    writeDIBHeader(fileOut, dib);
	    writePixelsBMP(fileOut, pixel, dib->width, dib->height);
	    return;

}

// Applies the swiss cheese affect to an image using threading
void swissCheese(FILE* fileIn, FILE* fileOut, struct Pixel **pixel, struct BMP_Header *bmp, struct DIB_Header *dib) {

	struct Pixel **copy = createArray(fileIn, dib->width, dib->height);
	readPixelsBMP(fileIn, copy, dib->width, dib->height);

}


int main(int argc, char* argv[]) {

	// Creates new structs to hold command line input/hold image file
	struct Input* input = malloc(sizeof(struct Input));
	struct BMP_Header* BMP = malloc(sizeof(struct BMP_Header));
	struct DIB_Header* DIB = malloc(sizeof(struct DIB_Header));

	// Stores command line input into struct
	input->folder = argv[1];
	input->in = argv[3];
	input->out = argv[5];
	input->filter = argv[7];

	// Sets up folder and file name to be combined
	int length = strlen(input->folder);
	input->folder[length] = '/';
	input->folder[length + 1] = '\0';

	// Allocates the exact amount of space needed for file location
	char fileLocationIn[strlen(input->folder) + strlen(input->in)];
	char fileLocationOut[strlen(input->folder) + strlen(input->out)];

	// Combines folder and file name to create new FILE types
	strcpy(fileLocationIn, input->folder);
	strcat(fileLocationIn, input->in);
	strcpy(fileLocationOut, input->folder);
	strcat(fileLocationOut, input->out);

	// Creates new FILE types based on input
	FILE *inFile;
	FILE *outFile;
	inFile = fopen(fileLocationIn, "r");
	outFile = fopen(fileLocationOut, "w");

	// Reads the complete BMP file and stores it
	readBMPHeader(inFile, BMP);
	readDIBHeader(inFile, DIB);
	struct Pixel **PIXEL = malloc(DIB->height * sizeof(struct Pixel*));
	for(int i = 0; i < DIB->height; i++){

		PIXEL[i] = malloc(DIB->width * sizeof(struct Pixel*));

	}

	readPixelsBMP(inFile, PIXEL, DIB->width, DIB->height);

	fclose(inFile);
	inFile = fopen(fileLocationIn, "r");

	// Determines if user wants to create a blur filter
	if(*input->filter == 'b'){

		printf("Initiating blur filter...\n");
		boxBlur(inFile, outFile, PIXEL, BMP, DIB);

		fclose(inFile);
		fclose(outFile);

	}


	// Determines if user wants to create a swiss cheese filter
	if(*input->filter == 'c'){

		printf("Initiating cheese filter...\n");
		swissCheese(inFile, outFile, PIXEL, BMP, DIB);

		fclose(inFile);
		fclose(outFile);

	}

	return 0;

}
