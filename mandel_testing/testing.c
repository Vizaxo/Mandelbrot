#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

int win_height;
void print_a()
{
	srand(234234234);
	for(int i = 0; i < win_height; i++) {
		for(int q = 0; q < 1000; q++)
			calculate_mandel_val((double)i, 0.3);
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		printf("\n");
	}
}
void print_b()
{
	srand(234234234);
	for(int i = 0; i < win_height; i++) {
		for(int q = 0; q < 1000; q++)
			calculate_mandel_val((double)i, 0.3);
		for(int j = 0; j < 1000; j++)
			printf("@");
		printf("\n");
	}
}

int calculate_mandel_val(double const x, double const y)
{
	int it;
	double r,  i;
	double r2, i2;
	double tmp;

	it = 4096;
	r = i = 0; r2= 0; i2 =0;
	do
	{
		tmp = r2 - i2 + x;
		i = 2 * r * i + y;
		r = tmp;
		r2 = r*r; i2 = i*i;
	} while((r2 + i2) <= 4.0 && --it);

	if(it == 0)
		return 1;
	else
		return 0;
}

int main()
{
	float a = 1.0f;
	double b = 1.0f;
	long double c = 1.0f;

	printf("%d, %d, %d\n", sizeof(a), sizeof(b), sizeof(c));
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

	win_height = window.ws_row - 1; /* -1 to accout for the prompt */
	win_height = 70000;

	clock_t begin = clock();
	//print_a();
	clock_t end = clock();

	double time_a = (double)(end - begin);
	begin = clock();
	//print_b();
	end = clock();
	double time_b = (double)(end - begin);

	printf("a: %f. b: %f. a/b: %f\n", time_a, time_b, time_a/time_b);
}					
