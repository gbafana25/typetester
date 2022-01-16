all: main

main: $(wildcard *.c)
	gcc $(wildcard *.c) -o main

clean:
	rm main
debug:
	ltrace ./main

run: all
	./main
