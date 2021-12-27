#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>


typedef struct {
	int curr;
	int start; 

} position; 

position ps;

void setup_terminal() 
{
	struct termios options;
	tcgetattr(STDIN_FILENO, &options);
	options.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &options);


}

char *get_word_from_text(char *t)
{
	char *word; 	
	int len = 0;
	for(int i = ps.start; i < strlen(t); i++)
	{
		if(t[i] == ' ')
		{
			len = ps.curr - ps.start;
			word = malloc(len * sizeof(char));
			strncpy(word, t+ps.start, len);
			ps.curr++;
			ps.start = ps.curr;
			len = 0;
			return word;
		} else {
			ps.curr++;	
		}

	}


}


int main()
{
	char test;
	ps.curr = 0;
	ps.start = 0;
	printf("\n\033[31;1mCommand Line Typing Tester\033[0m\n\n");
	char *text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
	printf("%s\n", text);
	printf("%s\n", get_word_from_text(text));
	printf("%s\n", get_word_from_text(text));
	printf("%s\n", get_word_from_text(text));
	printf("%s\n", get_word_from_text(text));
	printf("%s\n", get_word_from_text(text));
	printf("%s\n", get_word_from_text(text));
	printf("%s\n", get_word_from_text(text));
	setup_terminal();
	while(read(STDIN_FILENO, &test, 1) == 1)
	{
		if(test == ' ') {
			write(STDOUT_FILENO, "\e[1K\n", 5);
			break;
		}

	}
	return 0;
}

