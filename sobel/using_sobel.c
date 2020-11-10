#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sobel.h"
//Compiling gcc -o using_sobel using_sobel.c sobel.c -lm
int main(int argc, char **argv)
{
	pgm image, out_image;
	char dir[200];
	printf("Enter the file name: ");
	scanf("%s", dir);
	
	read_pgm_file(dir, &image);
	padding(&image);
	init_out_image(&out_image, image);
	sobel_edge_detector(&image, &out_image);	
	
	min_max_normalization(&out_image, out_image.imageData);
	min_max_normalization(&out_image, out_image.gx);
	min_max_normalization(&out_image, out_image.gy);

	write_pgm_file(&out_image, dir, out_image.imageData, ".G.pgm");
	printf("\nGradient saved: %s \n", dir);
	write_pgm_file(&out_image, dir, out_image.gx, ".GX.pgm");
	printf("Gradient X saved: %s \n", dir);
	write_pgm_file(&out_image, dir, out_image.gy, ".GY.pgm");
	printf("Gradient Y saved: %s \n", dir);

	free(image.imageData);
	free(out_image.imageData);
	free(out_image.gx);
	free(out_image.gy);
	
	return 0;
}