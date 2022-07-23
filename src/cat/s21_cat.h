#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct opt_cat{
    int opt_b;
    int opt_e;
    int opt_n;
    int opt_s;
    int opt_t;
    int opt_v;
};

int parser(int count, char **pars_str, struct opt_cat *pars);
int file_open(int argc, char **pars_str, struct opt_cat *pars);
void print_file_def(char *str, struct opt_cat *pars);

#endif  // SRC_CAT_S21_CAT_H_
