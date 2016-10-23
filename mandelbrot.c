#define MAX_ITERATIONS 100000

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

/*
 * Calculates the array of return values for a given frame of the mandelbrot
 * set. Returns 0 if there were no errors.
 */
int calculate_mandelbrot_frame(int screen_width, int screen_height, 
		double fractal_width, double fractal_height, 
		double fractal_centre_x, double fractal_centre_y, 
		int mandelbrot_values_array[])
{
	double x, y;
	for(int i = 0; i < screen_height; i++) {
		y = - fractal_centre_y + (i - (screen_height / 2.0)) * 
			fractal_height / screen_height;
		for(int j = 0; j < screen_width; j++) {
			x = fractal_centre_x + (j - (screen_width / 2.0)) * 
				fractal_width / screen_width;
			mandelbrot_values_array[i * screen_width + j] = 
				mandelbrot_pixel(x, y);
		}
		//printf(":%f, %f, %d, %d\n", x, y, mandelbrot_pixel(x, y), 
				//mandelbrot_values_array[i*screen_width + screen_height - 1]);
	}
	return 0;
}
