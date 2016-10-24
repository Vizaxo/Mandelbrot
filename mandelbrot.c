#include "mandelbrot.h"

int mandelbrot_pixel(double const x, double const y);
double pixel_location(double fractal_centre, int counter, 
		int pixel_count_dimension, double fractal_size_dimension);

int *mandelbrot_array;
fractal_parameters params = {0, 0, 0.0, 0.0, 0.0, 0.0};


/*
 * Calculates the array of return values for a given frame of the mandelbrot
 * set. Returns 0 if there were no errors.
 */
int *calculate_mandelbrot_frame()
{
	mandelbrot_array = realloc(mandelbrot_array, sizeof(int) * 
			screen_height * screen_width);
	if(		params.screen_width == screen_width &&
			params.screen_height == screen_height &&
			params.fractal_width == fractal_width &&
			params.fractal_height == fractal_height &&
			params.fractal_centre_x == fractal_centre_x &&
			params.fractal_centre_y == fractal_centre_y) {
		printf("quick\n");
		return mandelbrot_array;
	}
	printf("LONG TIME\n");
	params.screen_width = screen_width;
	params.screen_height = screen_height;
	params.fractal_width = fractal_width;
	params.fractal_height = fractal_height;
	params.fractal_centre_x = fractal_centre_x;
	params.fractal_centre_y = fractal_centre_y;
	double x, y;
	for(int i = 0; i < screen_height; i++) {
		y = pixel_location(- fractal_centre_y, i, 
				screen_height, fractal_height);
		for(int j = 0; j < screen_width; j++) {
			x = fractal_centre_x + (j - (screen_width / 2.0)) * 
				fractal_width / screen_width;
			x = pixel_location(fractal_centre_x, j, 
					screen_width, fractal_width);
			mandelbrot_array[i * screen_width + j] = 
				mandelbrot_pixel(x, y);
		}
		//printf(":%f, %f, %d, %d\n", x, y, mandelbrot_pixel(x, y), 
	}
	return mandelbrot_array;
}

double pixel_location(double fractal_centre, int counter, 
		int pixel_count_dimension, double fractal_size_dimension)
{
	return fractal_centre + (counter - (pixel_count_dimension / 2.0)) * 
				fractal_size_dimension / pixel_count_dimension;
}

/*
 * Returns 0 if the complex number x + yi is in the Mandelbrot set.
 */
int mandelbrot_pixel(double const x, double const y)
{
	//fc(z) = z^2 + c
	int counter = 0;
	double zr, zi, zr_temp;
	zr_temp = zr = zi = 0;
	do {
		zr_temp = (zr * zr) - (zi * zi) + x;
		zi = 2 * zi * zr + y;
		zr = zr_temp;
		//printf("x: %f, y: %f, zi: %.15f, zr: %.15f\n", x, y, zi, zr);
		counter++;
		if(zi == 0.0 && zr == 0.0)
			return 0;
			;
		if(counter > MAX_ITERATIONS)
			return 0;
		else if(counter == 1 || counter % 1 == 0)
			//printf("x: %f, y: %f, zi: %f, zr: %f\n", x, y, zi, zr);
			;
	} while(zr * zr + zi * zi <= 4);
	//printf("%d, %f::\n", i, z);
	return counter;
}
