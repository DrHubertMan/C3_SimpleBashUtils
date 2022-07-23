CC = gcc
CFLAGS = -Wall -Werror -Wextra -c -fsanitize=address
OFLAGS = -Wall -Werror -Wextra -o

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(OFLAGS) s21_grep s21_grep.o
	rm -rf *.o

s21_grep.o:
	$(CC) $(CFLAGS) s21_grep.c

lint: 
	python3 ../cpplint.py --extensions=c  *.c *.h

valgrind:
	valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes  ./s21_grep -v A 5

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	rm -rf *.o s21_grep log.txt

rebuild:clean all