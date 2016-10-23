#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>

#define FRACTAL_WIDTH 3.0
#define FRACTAL_HEIGHT 2.0
#define FRACTAL_CENTRE_X -0.75
#define FRACTAL_CENTRE_Y 0.0
#define BG_COLS 15

int calculate_mandel_val(double const x, double const y);

const int bg_colors[BG_COLS] = {
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	100,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
};

/*{
	100,
	41,
	101,
	107,
};*/

/*
 * Returns 1 if the complex number x + yi is in the Mandelbrot set.
 */
int calculate_mandel_val_2(double const x, double const y)
{
	int it;
	double r,  i;
	double r2, i2;
	double tmp;

	it = 4096;
	r = i = 0; r2= 0; i2 =0;
	do
	{
		tmp = r2 - i2 + x;
		i = 2 * r * i + y;
		r = tmp;
		r2 = r*r; i2 = i*i;
	} while((r2 + i2) <= 4.0 && --it);

	if(it == 0)
		return 1;
	else
		return 0;
}

int calculate_mandel_val_3(double const x, double const y)
{
	//fc(z) = z^2 + c
	double z = 0;
	double c = sqrt(x * x + y * y);
	int i = 0;
	do {
		z = z * z + c;
		i++;
		if(i > 10000)
			return 0;
	} while(z <= 2);
	//printf("%d, %f::\n", i, z);
	return 1;
}

int calculate_mandel_val(double const x, double const y)
{
	//fc(z) = z^2 + c
	int counter = 0;
	long double zr, zi, zr_temp;
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
		if(counter > 10000)
			return 0;
		else if(counter == 1 || counter % 1 == 0)
			//printf("x: %f, y: %f, zi: %f, zr: %f\n", x, y, zi, zr);
			;
	} while(zr * zr + zi * zi <= 4);
	//printf("%d, %f::\n", i, z);
	return counter;
}

/*
 * Loops through the width and height of the printing space, printing an ascii
 * representation of the Mandelbrot set.
 */
int main()
{
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

	int win_height = window.ws_row - 1; /* -1 to accout for the prompt */
	int win_width = window.ws_col; 

	int mandel_val;
	//printf("\e[0;33m");
	
	for(int i = 0; i < win_height; i++) {
		double y = FRACTAL_CENTRE_Y + (i - (win_height - 1)/2.0) * (FRACTAL_HEIGHT/(win_height));
		for(int j = 0; j < win_width; j++) {
			double x = FRACTAL_CENTRE_X + (j - (win_width - 1)/2.0) * (FRACTAL_WIDTH/(win_width));
			//printf("%f, %f, %d\n", x, y, calculate_mandel_val(x,y));
			mandel_val = calculate_mandel_val(x, y);
			if(mandel_val == 0)
				printf(" ");
			else
				printf("\e[%dm \e[m", bg_colors[(int)logl(mandel_val) % BG_COLS]);
		}
		printf("\n");
	}
}
