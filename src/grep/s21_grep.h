#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>

struct opt_grep{
    int opt_e;
    int opt_i;
    int opt_v;
    int opt_c;
    int opt_l;
    int opt_n;
    int file_n;
};

int parser(int count, char **pars_str, struct opt_grep *pars, char *template);
int file_open(int argc, char **pars_str, struct opt_grep *pars, char *template);
void print_file(char **str, int x, struct opt_grep *pars, char *template);

#endif  // SRC_GREP_S21_GREP_H_
