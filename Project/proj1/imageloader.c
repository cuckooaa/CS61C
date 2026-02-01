/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp=fopen(filename,"r");
	if(fp==NULL) return NULL;
	
	char tag[3];
	uint32_t rows,cols,max_val;

	fscanf(fp,"%s %u %u %u",tag,&cols,&rows,&max_val);
	
	Image *myimage=(Image*) malloc(sizeof(Image));
	myimage->rows=rows;
	myimage->cols=cols;
	myimage->image=(Color**) malloc(rows*sizeof(Color*));
	for(int i=0;i<rows;++i){
		myimage->image[i]=(Color*) malloc(cols*sizeof(Color));
		for(int j=0;j<cols;j++){
			Color *pixel=&myimage->image[i][j];
			fscanf(fp,"%hhu %hhu %hhu",&pixel->R,&pixel->G,&pixel->B);
		}
	}

	fclose(fp);
	return myimage;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
    printf("P3\n");
	uint32_t rows=image->rows;
	uint32_t cols=image->cols;
	printf("%u %u\n",cols,rows);
	printf("255\n");

	for(int i=0;i<rows;++i){
		for(int j=0;j<cols;j++){
			Color *pixel=&image->image[i][j];
			printf("%3hhu %3hhu %3hhu",pixel->R,pixel->G,pixel->B);
			if(j!=cols-1) printf("   ");
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE	
	for(int i=0;i<image->rows;++i){
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}
