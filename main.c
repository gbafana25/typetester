#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>


void setup_terminal() 
{
	struct termios options;
	tcgetattr(STDIN_FILENO, &options);
	options.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &options);


}


int main()
{
	char test;
	printf("\n\033[31;1mCommand Line Typing Tester\033[0m\n\n");
	printf("This is me. This is the shape that let others recognize me as myself.\n\n");
	setup_terminal();
	while(read(STDIN_FILENO, &test, 1) == 1 && test != ' '); 
	write(STDOUT_FILENO, "\e[1K\n", 5);
	fflush(stdout);
	return 0;
}

