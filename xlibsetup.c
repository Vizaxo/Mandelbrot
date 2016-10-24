#include "fractal.h"

x_display *display;

void open_display();
void create_window(int x, int y, int width, int height);

void make_x_display()
{
	display = malloc(sizeof(x_display));

	open_display();
	create_window(0, 0, 200, 200);
}

void open_display()
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
	(*display).gc = XDefaultGC((*display).display, (*display).screen_num);
}

void create_window(int x, int y, int width, int height)
{
	int border_width = 0;
	screen_width = width;
	screen_height = height;

	(*display).program_window = XCreateSimpleWindow((*display).display, 
			(*display).root_window, x, y, width, height, 
			border_width, (*display).black_pixel, 
			(*display).black_pixel);
	XSelectInput((*display).display, (*display).program_window, 
			ExposureMask | KeyPressMask | StructureNotifyMask);
	XMapWindow((*display).display, (*display).program_window);
	(*display).screen_colormap = DefaultColormap((*display).display, 
			(*display).screen_num);
}

void print_x_pixel(int j, int i, int *values)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned long pixel;

	int value= values[i * screen_width + j];
	if(value != 0) {
		blue = (pow(value, BLUE_EXPONENT)/pow(POWER_EXPONENT_BASE, BLUE_EXPONENT)) * 256.0;
		green = (pow(value, GREEN_EXPONENT)/pow(POWER_EXPONENT_BASE, GREEN_EXPONENT)) * 256.0;
		red = (pow(value, RED_EXPONENT)/pow(MAX_ITERATIONS, RED_EXPONENT)) * 256.0;
		pixel = (((unsigned long)red) << 16) + 
			(((unsigned long)green) << 8) +
			((unsigned long)blue);
		XSetForeground((*display).display, (*display).gc, pixel);
		XDrawPoint((*display).display, (*display).program_window, (*display).gc, j, i);
	}
}

void display_loop()
{
	XEvent event;
	while(1) {
		XNextEvent((*display).display, &event);

		if(event.type == Expose) {
			printf("Drawing screen: %d, %d\n", screen_width, screen_height);
			draw_frame(display);
		} else if(event.type == ConfigureNotify) {
			XConfigureEvent xce = event.xconfigure;
			screen_width = xce.width;
			screen_height = xce.height;
			printf("Drawing screen: %d, %d\n", screen_width, screen_height);
			draw_frame(display);
		} else if(event.type == KeyPress)
			;
	}
}

void close_display()
{
	XCloseDisplay((*display).display);
}
