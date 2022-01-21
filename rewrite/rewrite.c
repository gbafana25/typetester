#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>



typedef struct {
	int curr;
	int start; 
} position; 

position global_ps;

void setup_terminal() 
{
	struct termios options;
	tcgetattr(STDIN_FILENO, &options);
	options.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &options);


}
void get_word_from_text(char *t, char *ret)
{
	int len = 0;
	for(int i = global_ps.start; i < strlen(t); i++)
	{
		if(t[i] == ' ')
		{
			len = global_ps.curr - global_ps.start;
			memset(&ret, 0, sizeof(ret));
			ret = malloc(len * sizeof(char));
			strncpy(ret, t+global_ps.start, len);
			global_ps.curr++;
			global_ps.start = global_ps.curr;
			//break;
		} else {
			global_ps.curr++;	
		}

	}


}

int main()
{
	char test;
	global_ps.start = 1;
	global_ps.curr = 1;
	printf("\n\033[31;1mCommand Line Typing Tester\033[0m\n\n");
	char *text = "Lorem ipsum dolor";
	printf("%s\n", text);
	printf("\n");
	setup_terminal();
	char *typed_word;	
	char *cw;
	while(read(STDIN_FILENO, &test, 1) == 1)
	{
		if(test == ' ') {
			get_word_from_text(text, cw);
			//printf("%s\n", cw);
			if(strcmp(cw, typed_word) == 0) {
				
				printf("\033[32;1mCorrect word\033[0m\n");


			} else {
				printf("\033[31;1mWrong word\033[0m\n");
			}
			memset(typed_word, 0, strlen(typed_word));
			
		} else {
			strncat(typed_word, &test, 1);	
			
		}
		printf("%d\n", global_ps.curr);
		printf("%d\n", global_ps.start);
		
	}
	return 0;
}

