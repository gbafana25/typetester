#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>

#include "client.h"
#include "term.h"


//struct termios options;

// holds number of correct, wrong, and total words
typedef struct {
	int num_correct;
	int num_wrong;
	int total_words;

} scoring_data;

scoring_data sd;

// flag to mark the current word wrong
typedef struct {
	bool curr_is_wrong;


} word_flags;

word_flags wf;



char *read_from_file(char *fname) {
	FILE *src;
	src = fopen(fname, "r");
	// move pointer to end of file
	fseek(src, 0L, SEEK_END);
	// get string length
	size_t size = ftell(src);
	rewind(src);
	char *t = malloc((size) * sizeof(char));
	size_t file = fread(t, sizeof(char), size, src);	
	fclose(src);
	return t;
	

}

int main(int argc, char *argv[]) {
	if(argc == 3) {
		int enable_multiplayer = strncmp(argv[1], "mp", 2);
		if(enable_multiplayer == 0 && strlen(argv[2]) <= 9) {
			setup_terminal();
			connect_to_server(argv[2]);	
			reset_terminal();
			exit(0);
		}
	}
	char test;
	// all variables need to be zeroed
	sd.num_correct = 0;
	sd.num_wrong = 0;
	sd.total_words = 0;
	clr_screen();	
	printf("\n\033[31;1mCommand Line Typing Tester\033[0m\n\n");//Hit enter at end of paragraph!\033[0m\n\n");
	// save current cursor position
	write(STDOUT_FILENO, "\e7", 3);
	char *text = read_from_file("a.txt");	
	printf("%s\n", text);
	// restore saved cursor position
	write(STDOUT_FILENO, "\e8", 3);
	setup_terminal();
	char *typed_word;	
	wf.curr_is_wrong = false;
	// time instances
	time_t init, end;
	// starting time
	init = time(NULL);
	for(int i = 0; i < strlen(text); i++) {
		// read current character (memset not used on variable `test`)
		read(STDIN_FILENO, &test, 1);
		// if input equals current character... 
		if(test == text[i]) {
			write(STDOUT_FILENO, "\e[32;1m", 8);
			write(STDOUT_FILENO, (void *) &test, 1);
			write(STDOUT_FILENO, "\e[0m", 5);
		
		} else {
			write(STDOUT_FILENO, "\e[31;1m", 8);
			write(STDOUT_FILENO, (void *) &text[i], 1);
			write(STDOUT_FILENO, "\e[0m", 5);
			
			wf.curr_is_wrong = true;	
		}
		/* 
			add to total word count at spaces
			check `curr_is_wrong` flag, increment
			correct/wrong counter
		*/
		if(text[i] == ' ') {
			if(wf.curr_is_wrong) {
				sd.num_wrong++;
			} else {
				sd.num_correct++;
			}
			wf.curr_is_wrong = false;
			sd.total_words++;
		}	
		// workaround to read the last character
		if(i == strlen(text) - 1) {
			if(test == text[i] && wf.curr_is_wrong == false) {
				sd.num_correct++;	
			} else {
				sd.num_wrong++;
			}
			sd.total_words++;
		}	


	}
	// ending time
	end = time(NULL);
	int time_diff = end - init;
	printf("\n\n");
	printf("Correct:  %d\n", sd.num_correct);
	printf("Wrong:  %d\n", sd.num_wrong);
	printf("Total Words: %d\n", sd.total_words);
	double percent_accuracy = ((double) sd.num_correct / (double) sd.total_words) * 100;
	printf("Accuracy: %2.1f%%\n", percent_accuracy);
	// when doing floating point division, cast each non-float invidually
	float min = ((float)time_diff/60.0); 
	printf("Speed: %3.f WPM\n", (float)sd.num_correct/min);
	printf("Raw Speed: %3.f WPM\n", (float)sd.total_words/min);
	reset_terminal();

	return 0;
}

