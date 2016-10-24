#include "mandelbrot.h"

void open_display(x_display *display);
void init_gc(x_display *display);
void create_window(x_display *display, int x, int y, int width, int height);
void draw_mandelbrot_frame(x_display *display);
void draw_screen(x_display *display);

void make_x_display(x_display *display)
{
	open_display(display);
	init_gc(display);
	create_window(display, 0, 0, 100, 100);
}

void open_display(x_display *display)
{
	(*display).display = XOpenDisplay(NULL);
	if((*display).display == NULL) {
		fprintf(stderr, "Couldn't open the X display.\n");
		exit(1);
	}
	(*display).screen_num = DefaultScreen((*display).display);
	(*display).root_window = RootWindow((*display).display, 
			(*display).screen_num);
	(*display).black_pixel = BlackPixel((*display).display, 
			(*display).screen_num);
	(*display).white_pixel = WhitePixel((*display).display, 
			(*display).screen_num);
}

void init_gc(x_display *display)
{
	(*display).gc = XDefaultGC((*display).display, (*display).screen_num);
}

void create_window(x_display *display, int x, int y, int width, int height)
{
	int border_width = 0;

	screen_width = width;
	screen_height = height;

	(*display).program_window = XCreateSimpleWindow((*display).display, 
			(*display).root_window, x, y, width, height, 
			border_width, (*display).black_pixel, (*display).black_pixel);
	XSelectInput((*display).display, (*display).program_window, 
			ExposureMask | KeyPressMask | StructureNotifyMask);
	XMapWindow((*display).display, (*display).program_window);

	(*display).screen_colormap = DefaultColormap((*display).display, 
			(*display).screen_num);
}

void draw_mandelbrot_frame(x_display *display)
{
	XColor system_color;
	int *mandelbrot_array;
	int mandel_value = 0;

	mandelbrot_array = calculate_mandelbrot_frame();
	system_color.red = 0;
	system_color.blue = 0;
	system_color.green = 0;
	XSetForeground((*display).display, (*display).gc, (*display).black_pixel);
	for(int i = 0; i < screen_height; i++) {
		for(int j = 0; j < screen_width; j++) {
			mandel_value= mandelbrot_array[i * screen_width + j];
			if(mandel_value != 0) {
				system_color.blue = (pow(mandel_value, BLUE_EXPONENT)/pow(POWER_EXPONENT_BASE, BLUE_EXPONENT)) * 256.0;
				system_color.green = (pow(mandel_value, GREEN_EXPONENT)/pow(POWER_EXPONENT_BASE, GREEN_EXPONENT)) * 256.0;
				system_color.red = (pow(mandel_value, RED_EXPONENT)/pow(MAX_ITERATIONS, RED_EXPONENT)) * 256.0;
				system_color.pixel = (((unsigned long)(unsigned char)system_color.red) << 16) + 
					(((unsigned long)(unsigned char)system_color.green) << 8) +
					((unsigned long)(unsigned char)system_color.blue);
				XSetForeground((*display).display, (*display).gc, system_color.pixel);
				XDrawPoint((*display).display, (*display).program_window, (*display).gc, j, i);
			} else {
				//XSetForeground((*display).display, (*display).gc, (*display).black_pixel);
				//XDrawPoint((*display).display, (*display).program_window, (*display).gc, j, i);
			}
		}
	}
}

void draw_screen(x_display *display)
{
	printf("Drawing screen: %d, %d\n", screen_width, screen_height);
	draw_mandelbrot_frame(display);
}

void display_loop(x_display *display)
{
	XEvent event;
	while(1) {
		XNextEvent((*display).display, &event);

		if(event.type == Expose) {
			draw_screen(display);
		} else if(event.type == ConfigureNotify) {
			XConfigureEvent xce = event.xconfigure;
			screen_width = xce.width;
			screen_height = xce.height;
			draw_screen(display);
		} else if(event.type == KeyPress)
			;
	}
}

void close_display(x_display *display)
{
	XCloseDisplay((*display).display);
}
