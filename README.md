# typetester (Multiplayer branch)

Typing practice for the command line on Linux. Use this branch for interfacing with [typesrv](https://github.com/gbafana25/typesrv)

## Description/Program Structure

- loads text from `a.txt`

- enable canonical mode in terminal (read by character) 
- disable echoing of characters
- scan character by character
	- a wrong keypress trigger flag 
	- checked every space
- show stats at end of segment
	- number of words right/wrong and accuracy
- to enable multiplayer mode, clone from the multi branch and run: `./main mp`


## Usage

`make run`


`make debug` will run `ltrace`



