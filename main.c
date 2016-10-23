#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "xlibsetup.c"
//#include "mandelbrot.c"


void setup_bash();
void setup_x();

int main(int argc, char *argv[])
{
	if((argc > 1) && (!argc && strcmp(argv[1], "x") || strcmp(argv[1], "X"))) {
		setup_x();
	} else {
		setup_bash();
	}	
	return 0;
}

void setup_x()
{
	x_display display;
	make_x_display(&display);

	display_loop(&display);
	close_display(&display);
}

void setup_bash()
{
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	int win_height = window.ws_row - 1; /* -1 for prompt */
	int win_width = window.ws_col; 

	int mandelbrot_array[1920 * 1080]; //TODO: setup dynamic array
	calculate_mandelbrot_frame(win_width, win_height, 3.0, 2.0, 0, 0, 
			mandelbrot_array);
	for(int i = 0; i < win_height; i++) {
		for(int j = 0; j < win_width; j++) {
			if(mandelbrot_array[i * win_width + j] != 0)
				//printf("%2d", j);
				printf("@");
			else
				printf(" ");
		}
		printf("\n");
	}
}

//Testing
