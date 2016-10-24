#ifndef __MANDELBROT_H__
#define __MANDELBROT_H__

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <math.h>

#define MAX_ITERATIONS 1000

#define BLUE_EXPONENT 0.1
#define GREEN_EXPONENT 0.4
#define RED_EXPONENT 0.3
#define POWER_EXPONENT_BASE 10000

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

typedef struct {
	int screen_width;
	int screen_height;
	double fractal_width;
	double fractal_height; 
	double fractal_centre_x;
	double fractal_centre_y;
} fractal_parameters;

//main.c
void draw_frame();

//mandelbrot.c
int *calculate_mandelbrot_frame();

//xlibsetup.c
void make_x_display();
void display_loop();
void close_display();
void print_x_pixel(int j, int i, int *values);

//bash.c
void get_terminal_size();
void print_bash_char(int j, int i, int *values);

#endif
