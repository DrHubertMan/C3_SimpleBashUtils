#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <getopt.h>
#define buff_size 999999

struct opt_grep {
    int opt_e;
    int opt_i;
    int opt_v;
    int opt_c;
    int opt_l;
    int opt_n;
    int opt_h;
    int opt_s;
    int opt_f;
    int opt_o;
};

int parser(int argc, char *argv[], struct opt_grep *pars, char *template);
void filework(struct opt_grep *pars, FILE *fp, regex_t reg, char *file);
void grep_file(struct opt_grep *pars, char *template, char *file);
int save_patt_file(char *template, char *temp);
void grep(struct opt_grep *pars, int argc, char **argv, char *template);

#endif  // SRC_GREP_S21_GREP_H_
