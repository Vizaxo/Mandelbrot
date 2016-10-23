#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	Display *display;
	GC gc;

	display = XOpenDisplay(NULL);
	if(display == NULL) {
		fprintf(stderr, "No X today");
		exit(-1);
	}
	/* check the number of the default screen for our X server. */
	int screen_num = DefaultScreen(display);

	/* find the width of the default screen of our X server, in pixels. */
	int screen_width = DisplayWidth(display, screen_num);

	/* find the height of the default screen of our X server, in pixels. */
	int screen_height = DisplayHeight(display, screen_num);

	/* find the ID of the root window of the screen. */
	Window root_window = RootWindow(display, screen_num);

	/* find the value of a white pixel on this screen. */
	unsigned long white_pixel = WhitePixel(display, screen_num);

	/* find the value of a black pixel on this screen. */
	unsigned long black_pixel = BlackPixel(display, screen_num);

	Window win = XCreateSimpleWindow(display, root_window, 0, 0, 200, 200, 2, black_pixel, white_pixel);
	XMapWindow(display, win);
	XFlush(display);
	
	XGCValues values;
	unsigned long valuemask = 0;
	gc = XCreateGC(display, win, valuemask, &values);
	if(gc < 0)
		fprintf(stderr, "XCreateGC: \n");
	XSync(display, 0);

	XSetForeground(display, gc, white_pixel);
	XSetBackground(display, gc, black_pixel);

	XSetLineAttributes(display, gc, 2, LineSolid, CapRound, JoinRound);
	XSetFillStyle(display, gc, FillSolid);

	XDrawPoint(display, win, gc, 5, 5);
	XDrawLine(display, win, gc, 20, 20, 40, 100);

	XFlush(display);
	sleep(6);
	XCloseDisplay(display);
}
