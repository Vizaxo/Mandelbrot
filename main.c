#include "mandelbrot.h"

void setup_bash();
void setup_x();
void print_bash_mandelbrot();

int main(int argc, char *argv[])
{
	fractal_width = 0.0003;
	fractal_height = 0.0002;
	fractal_centre_x = -0.7565;
	fractal_centre_y = -0.06;

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
	make_x_display(&display);

	display_loop(&display);
	close_display(&display);
}

void setup_bash()
{
	printf("bash\n");
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	screen_height = window.ws_row - 1; /* -1 for prompt */
	screen_width = window.ws_col; 

	print_bash_mandelbrot();
}

void print_bash_mandelbrot()
{
	int *mandelbrot_array;

	mandelbrot_array = calculate_mandelbrot_frame(screen_width, screen_height, 3.0, 2.0, 0, 0);
	for(int i = 0; i < screen_height; i++) {
		for(int j = 0; j < screen_width; j++) {
			if(mandelbrot_array[i * screen_width + j] != 0)
				printf("@");
			else
				printf(" ");
		}
		printf("\n");
	}
}
