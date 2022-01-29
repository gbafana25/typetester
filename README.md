# typetester

Typing practice for the command line on Linux

## Outline

- enable canonical mode in terminal (read by character) 
- react to space keypress (advance to next word)
- clear typed word with ansi escape sequence
- show stats at end of segment

## TODO
- ^ fix first word not reading correctly ^
- calculate words per minute at end of run 


compare char by char, increment total word counter when space is reached 

- struct with worng word flag
	- set to 1 when in middle of word
	- reset at space (in text)

^ ltrace shows null byte (\001) at beginning of string

