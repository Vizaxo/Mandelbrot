#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	Display *display;
	XEvent event;

	display = XOpenDisplay(NULL);
	if(display == NULL) {
		fprintf(stderr, "No X today");
		exit(-1);
	}

	int screen_num = DefaultScreen(display);
	int screen_width = DisplayWidth(display, screen_num);
	int screen_height = DisplayHeight(display, screen_num);
	Window root_window = RootWindow(display, screen_num);
	unsigned long white_pixel = WhitePixel(display, screen_num);
	unsigned long black_pixel = BlackPixel(display, screen_num);
	GC gc = DefaultGC(display, screen_num);

	Window win = XCreateSimpleWindow(display, root_window, 0, 0, 200, 200, 2, black_pixel, white_pixel);
	XSelectInput(display, win, ExposureMask | KeyPressMask | StructureNotifyMask);
	XMapWindow(display, win);

	char *msg = "hello";
	int width, height = 0;
	while(1) {
		XNextEvent(display, &event);

		if(event.type == Expose) {
			XDrawPoint(display, win, gc, 5, 5);
			XDrawLine(display, win, gc, 20, 20, 40, 100);
		} else if(event.type == ConfigureNotify) {
			XConfigureEvent xce = event.xconfigure;

			width = xce.width;
			height = xce.height;
			printf("oeutnhonuet\n");
			XDrawLine(display, win, gc, 20, 20, 40, 100);
		} else if(event.type == KeyPress)
			//break;
			printf("hi\n");
		printf("%d, %d\n", width, height);
	}

	XCloseDisplay(display);
	return 0;
}
