build:
	clang -std=c99 -Wall main.c -o main
clean:
	rm main
	rm -rf main.dSYM