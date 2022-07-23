CC = gcc
CFLAGS = -Wall -Werror -Wextra -c 
OFLAGS = -Wall -Werror -Wextra -o

all: s21_cat s21_grep

s21_cat: s21_cat.o
	$(CC) $(OFLAGS) s21_cat s21_cat.o
	rm -rf *.o

s21_cat.o:
	$(CC) $(CFLAGS) cat/s21_cat.c

s21_grep: s21_grep.o
	$(CC) $(OFLAGS) s21_grep s21_grep.o
	rm -rf *.o

s21_grep.o:
	$(CC) $(CFLAGS) grep/s21_grep.c

lint:
	python3 cpplint.py --extensions=c  cat/*.c cat/*.h
	python3 cpplint.py --extensions=c  grep/*.c grep/*.h

clean:
	rm -rf *.o s21_cat s21_grep

rebuild:clean all