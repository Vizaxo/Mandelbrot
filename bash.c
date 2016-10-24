#include "fractal.h"

void get_terminal_size()
{
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	screen_height = window.ws_row - 1; /* -1 for prompt */
	screen_width = window.ws_col; 
}

void print_bash_char(int j, int i, int *values)
{
	if(values[i * screen_width + j] != 0)
		printf("@");
	else
		printf(" ");
}
