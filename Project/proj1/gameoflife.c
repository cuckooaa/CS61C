/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int helper(Image* image,int i,int row_change,int col_change,int row,int col,uint32_t rows,uint32_t cols){
	row=(row+rows+row_change)%rows;
	col=(col+cols+col_change)%cols;
	uint32_t comb=((image->image[row][col]).R<<16)+((image->image[row][col]).G<<8)+(image->image[row][col]).B;
	return (comb & 1<<i)!=0? 1 : 0;
}

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	uint32_t rows=image->rows;
	uint32_t cols=image->cols;
	Color *pixel=(Color *)malloc(sizeof(Color));
	if(!pixel){
		return NULL;
	}
	pixel->B=0;
	pixel->G=0;
	pixel->R=0;
	for(int i=0;i<24;i++){
		int alive=helper(image,i,0,0,row,col,rows,cols);
		int count=0;
		count+=helper(image,i,-1,-1,row,col,rows,cols);
		count+=helper(image,i,-1,0,row,col,rows,cols);
		count+=helper(image,i,-1,1,row,col,rows,cols);
		count+=helper(image,i,0,-1,row,col,rows,cols);
		count+=helper(image,i,0,1,row,col,rows,cols);
		count+=helper(image,i,1,-1,row,col,rows,cols);
		count+=helper(image,i,1,0,row,col,rows,cols);
		count+=helper(image,i,1,1,row,col,rows,cols);
		int next_state = 0;
        if (alive) {
            if (rule & (1 << (count + 9))) {
                next_state = 1;
            }
        } else {
            if (rule & (1 << count)) {
                next_state = 1;
            }
        }
		if(next_state){
			int bit_idx=i%8;
			if (i < 8) {
				pixel->B |= 1<<bit_idx;
			} else if (i < 16) {
				pixel->G |= 1<<bit_idx;
			} else {
				pixel->R |= 1<<bit_idx;
			}
		} 
	}
	return pixel;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *newImage = (Image *)malloc(sizeof(Image));
	if (!newImage) {
		return NULL;
	}

	uint32_t rows=image->rows;
	uint32_t cols=image->cols;

	newImage->rows = rows;
	newImage->cols = cols;
	newImage->image=(Color **)malloc(rows*sizeof(Color*));
	for(int i=0;i<rows;i++){
		newImage->image[i]=(Color *)malloc(cols*sizeof(Color));
		for(int j=0;j<cols;j++){
			Color *temp_p=evaluateOneCell(image,i,j,rule);
			newImage->image[i][j]=*temp_p;
			free(temp_p);
		}	
	}
	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc!=3){
		fprintf(stderr,"the number of argv is not correct");
		exit(-1);
	}
	uint32_t rule;
	sscanf(argv[2],"%x",&rule);
	Image *originalimage=readData(argv[1]);
	Image *nextgeneratioinimage=life(originalimage,rule);
	writeData(nextgeneratioinimage);
	freeImage(nextgeneratioinimage);
	freeImage(originalimage);
	return 0;
}
