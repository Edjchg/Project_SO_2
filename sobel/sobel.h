#ifndef SOBEL_H
#define SOBEL_H
#include <stdio.h>
typedef struct {
	char version[3]; 
	int width;
	int height;
	int maxGrayLevel;
	int **imageData;
	int **gx;
	int **gy;
} pgm;
int isspace(int argument);
void init_out_image( pgm* out, pgm image);
void read_comments(FILE *input_image);
void read_pgm_file(char* dir, pgm* image);
void padding(pgm* image);
int convolution(pgm* image, int kernel[3][3], int row, int col);
void sobel_edge_detector(pgm* image, pgm* out_image);
void min_max_normalization(pgm* image, int** matrix);
void write_pgm_file(pgm* image, char dir[], int** matrix, char name[]);
void apply_sobel(char* filename,int index);
#endif
