#include "mandelbrot.h"

int screen_height, screen_width;
double fractal_height, fractal_width;
double fractal_centre_x, fractal_centre_y;

void setup_bash();
void setup_x();

int main(int argc, char *argv[])
{
	fractal_height = 2.0;
	fractal_width = 3.0;
	fractal_centre_y = 0.0;
	fractal_centre_x = 0.0;

	if(argc > 1) {
		if(strcmp(argv[1], "x") == 0 || strcmp(argv[1], "X") == 0) {
			printf("x if\n");
			setup_x();
		} else if (strcmp(argv[1], "bash") == 0) {
			printf("bash if\n");
			setup_bash();
		} else if (strcmp(argv[1], "ascii") == 0) {
			printf("ascii if\n");
			;
		} else {
			printf("i have no idea what's going on\n");
		}
	}
	return 0;
}

void setup_x()
{
	printf("x\n");
	x_display display;
	make_x_display(&display, &screen_width, &screen_height);

	display_loop(&display);
	close_display(&display);
}

void setup_bash()
{
	printf("bash\n");
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	int win_height = window.ws_row - 1; /* -1 for prompt */
	int win_width = window.ws_col; 

	int *mandelbrot_array;

	mandelbrot_array = calculate_mandelbrot_frame(win_width, win_height, 3.0, 2.0, 0, 0);
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
