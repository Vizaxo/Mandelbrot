#ifndef __MANDELBROT_H__
#define __MANDELBROT_H__

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <math.h>

#define BLUE_EXPONENT 0.1
#define GREEN_EXPONENT 0.4
#define RED_EXPONENT 0.3
#define POWER_EXPONENT_BASE 10000

/*
#define FRACTAL_WIDTH 0.00010
#define FRACTAL_HEIGHT 0.00005
#define FRACTAL_CENTRE_X -1.0103
#define FRACTAL_CENTRE_Y 0.25045
*/
#define FRACTAL_WIDTH 0.0003
#define FRACTAL_HEIGHT 0.0002
#define FRACTAL_CENTRE_X -0.7565
#define FRACTAL_CENTRE_Y -0.06

#define MAX_ITERATIONS 10000

typedef struct {
	Display *display;
	int width;
	int height;
	int screen_num;
	Window root_window;
	Window program_window;
	unsigned long white_pixel;
	unsigned long black_pixel;
	GC gc;
	Colormap screen_colormap;
} x_display;

int screen_height, screen_width;
double fractal_height, fractal_width;
double fractal_centre_x, fractal_centre_y;

void make_x_display(x_display *display);
void display_loop(x_display *display);
void close_display(x_display *display);
int *calculate_mandelbrot_frame();

#endif
