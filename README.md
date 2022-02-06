# typetester

Typing practice for the command line on Linux.

## Description/Program Structure

- loads text from `a.txt`

- enable canonical mode in terminal (read by character) 
- disable echoing of characters
- scan character by character
	- a wrong keypress trigger flag 
	- checked every space
- show stats at end of segment
	- number of words right/wrong and accuracy


## Usage

`make run`


`make debug` will run `ltrace`

- type `reset` if cursor doesn't start at the correct place

## TODO



