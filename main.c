#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>



typedef struct {
	int num_correct;
	int num_wrong;
	int total_words;

} scoring_data;

scoring_data sd;

typedef struct {
	bool curr_is_wrong;


} word_flags;

word_flags wf;

void setup_terminal() 
{
	struct termios options;
	tcgetattr(STDIN_FILENO, &options);
	options.c_lflag &= ~(ICANON);
	options.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &options);


}

char *read_from_file() {
	FILE *src;
	src = fopen("a.txt", "r");
	char *t = malloc(8 * sizeof(char));
	fgets(t, 8, src);
	fclose(src);
	return t;
	

}

int main() {
	char test;
	sd.num_correct = 0;
	sd.num_wrong = 0;
	sd.total_words = 0;
	printf("\n\033[31;1mCommand Line Typing Tester\033[0m\n\n");
	char *text = "Lorem ipsum dolor";
	//char* text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit";
	//char *text = "This is me. This is the shape that let others recognize me as myself. It is my symbol for myself. This is, this is, and this is as well. Representations. Everything is merely a description, not the real myself. Everything is simply a shape, a form, an identifier to let others recognize me as me. Then what am I?";
	printf("%s\n", text);
	printf("\n");
	setup_terminal();
	char *typed_word;	
	wf.curr_is_wrong = false;
	time_t init, end;
	init = time(NULL);
	for(int i = 0; i < strlen(text); i++) {
		read(STDIN_FILENO, &test, 1);
		if(test == text[i]) {
			write(STDOUT_FILENO, "\e[32;1m|\e[0m", 14);
		
		} else {
			write(STDOUT_FILENO, "\e[31;1m|\e[0m", 14);
			
			write(STDOUT_FILENO, "\e[1A", 5);	
			write(STDOUT_FILENO, "\e[1B", 5);	
			wf.curr_is_wrong = true;	
		}
		if(text[i] == ' ') {
			if(wf.curr_is_wrong) {
				sd.num_wrong++;
			} else {
				sd.num_correct++;
			}
			wf.curr_is_wrong = false;
			sd.total_words++;
		}
		if(i == strlen(text) - 1) {
			if(test == text[i] && wf.curr_is_wrong == false) {
				sd.num_correct++;	
			} else {
				sd.num_wrong++;
			}
			sd.total_words++;
		}


	}
	end = time(NULL);
	int time_diff = end - init;
	printf("\n\n");
	printf("Correct:  %d\n", sd.num_correct);
	printf("Wrong:  %d\n", sd.num_wrong);
	printf("Total Words: %d\n", sd.total_words);
	double percent_accuracy = ((double) sd.num_correct / (double) sd.total_words) * 100;
	printf("Accuracy: %2.1f%%\n", percent_accuracy);
	float min = ((float)time_diff/60.0); 
	printf("Speed: %3.f WPM\n", (float)sd.total_words/min);

	return 0;
}

