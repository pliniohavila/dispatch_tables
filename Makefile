CC 		= clang
FLAGS	= -Wall -Wextra -Werror -g


main:
	$(CC) $(FLAGS) main.c -o main

run:
	./main 5 + 6

clean:
	rm -r main