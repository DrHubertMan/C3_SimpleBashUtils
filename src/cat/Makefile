CC = gcc
CFLAGS = -Wall -Werror -Wextra -c -g -fanalyzer
OFLAGS = -Wall -Werror -Wextra -g -o

all:s21_cat 

s21_cat: s21_cat.o
	$(CC) $(OFLAGS) s21_cat s21_cat.o

s21_cat.o:
	$(CC) $(CFLAGS) s21_cat.c

lint:
	python3 ../cpplint.py --extensions=c  *.c *.h

valgrind:
	valgrind  --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes  ./s21_cat ../bytes.txt

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	rm -rf *.o s21_cat log.txt

rebuild:clean all