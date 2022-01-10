#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
	int curr;
	int start; 
	int cpos;

} position; 

position ps;

typedef struct {
	int num_correct;
	int num_wrong;
	int total_words;

} scoring_data;

scoring_data sd;

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
			memset(&word, 0, sizeof(word));
			word = malloc(len * sizeof(char));
			strncpy(word, t+ps.start, len);
			ps.curr++;
			ps.start = ps.curr;
			//printf("Source: %d\n", len);
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
	ps.cpos = 0;
	printf("\n\033[31;1mCommand Line Typing Tester\033[0m\n\n");
	//char *text = "Lorem ipsum dolor";
	char *text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ornare lectus sit amet. Nec sagittis aliquam malesuada bibendum.";
	printf("%s\n", text);
	printf("\n");
	setup_terminal();
	char *typed_word;	
	//memset(&typed_word, 0, sizeof(typed_word));
	while(read(STDIN_FILENO, &test, 1) == 1)
	{
				
		
		if(test == ' ') {
			char *cw = get_word_from_text(text);
			if(strcmp(cw, typed_word) == 0)// && strlen(cw) == strlen(typed_word))//, strlen(cw)) == 0)
			{
				
				
				write(STDOUT_FILENO, "\e[2K", 5);
				write(STDOUT_FILENO, "\r", 2);
				write(STDOUT_FILENO, "\e[1A", 5);	
				write(STDOUT_FILENO, "\e[2K", 5);

				printf("\033[32;1mCorrect word\033[0m\n");


			} else {
				write(STDOUT_FILENO, "\e[2K", 5);
				write(STDOUT_FILENO, "\r", 2);
				
				write(STDOUT_FILENO, "\e[1A", 5);	
				write(STDOUT_FILENO, "\e[2K", 5);

				printf("\033[31;1mWrong word\033[0m\n");
			}
			memset(typed_word, 0, strlen(typed_word));
			sd.total_words++;
		} else {
			strncat(typed_word, &test, 1);	
			
		}
		
		ps.cpos++;
	}
	return 0;
}

