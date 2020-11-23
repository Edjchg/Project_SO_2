#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "sobel.h"
//Compiling gcc -o using_sobel using_sobel.c sobel.c -lm
int main(int argc, char **argv)
{	
	char filename[] = "brain_492.pgm";
	apply_sobel(filename, 1);
	/*
	pgm image, out_image;
	char dir[200];
	printf("Enter the file name: ");
	scanf("%s", dir);
	
	read_pgm_file(dir, &image);
	padding(&image);
	init_out_image(&out_image, image);
	sobel_edge_detector(&image, &out_image);	
	
	min_max_normalization(&out_image, out_image.imageData);
	//min_max_normalization(&out_image, out_image.gx);
	//min_max_normalization(&out_image, out_image.gy);

	//write_pgm_file(&out_image, dir, out_image.imageData, ".G.pgm");
	write_pgm_file(&out_image, dir, out_image.imageData, "0.pgm");
	printf("\nGradient saved: %s \n", dir);
	//write_pgm_file(&out_image, dir, out_image.gx, ".GX.pgm");
	//write_pgm_file(&out_image, dir, out_image.gx, "1.pgm");
	//printf("Gradient X saved: %s \n", dir);
	//write_pgm_file(&out_image, dir, out_image.gy, ".GY.pgm");
	//write_pgm_file(&out_image, dir, out_image.gy, "2.pgm");
	//printf("Gradient Y saved: %s \n", dir);

	free(image.imageData);
	free(out_image.imageData);*/
	//free(out_image.gx);
	//free(out_image.gy);
	
	return 0;
}
