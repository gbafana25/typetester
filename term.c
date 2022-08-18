#include <stdio.h>
#include <unistd.h>
#include <termios.h>

struct termios options;

// change terminal settings
void setup_terminal() 
{
	tcgetattr(STDIN_FILENO, &options);
	struct termios new_opt = options;
	// disable echo, canonical mode, Ctrl-C
	new_opt.c_lflag &= ~(ICANON | ECHO | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_opt);


}

void reset_terminal() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &options);


}

void clr_screen() {
	write(STDOUT_FILENO, "\e[2J", 4);
	write(STDOUT_FILENO, "\e[H", 3);

}
