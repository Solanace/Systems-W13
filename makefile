all: main.c
	gcc main.c

run: all
	./a.out

clean:
	rm a.out
