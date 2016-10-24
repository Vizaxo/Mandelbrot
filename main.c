#include "fractal.h"

void setup_bash();
void setup_x();
void (*print_pixel)(int, int, int *);
int *(*calculate_fractal)();

int main(int argc, char *argv[])
{
	fractal_width = 0.0003;
	fractal_height = 0.0002;
	fractal_centre_x = -0.7565;
	fractal_centre_y = -0.06;


	if(argc > 1) {
		calculate_fractal = &calculate_mandelbrot_frame;
		if(strcmp(argv[1], "x") == 0 || strcmp(argv[1], "X") == 0) {
			print_pixel = &print_x_pixel;
			setup_x();
		} else if (strcmp(argv[1], "bash") == 0) {
			print_pixel = &print_bash_char;
			setup_bash();
		} else if (strcmp(argv[1], "ascii") == 0)
			;
		draw_frame();
	}
	return 0;
}

void setup_x()
{
	make_x_display();
	display_loop();
	close_display();
}

void setup_bash()
{
	get_terminal_size();
}

void draw_frame()
{
	int *values;

	values = calculate_fractal();
	for(int i = 0; i < screen_height; i++) {
		for(int j = 0; j < screen_width; j++) {
			print_pixel(j, i, values);
		}
	}
}
