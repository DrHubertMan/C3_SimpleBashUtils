#include"s21_cat.h"

int main(int argc, char **argv) {
    int exit_flag = 0;
    if (argc > 1) {
        struct opt_cat pars;
        int a = parser(argc, argv, &pars);
        if (a == 0) {
            file_open(argc, argv, &pars);
        } else {
            exit_flag = 1;
        }
    }
    return exit_flag;
}

int parser(int count, char **pars_str, struct opt_cat *pars) {
    int parser_exit_flag = 0;
    pars -> opt_b = 0;
    pars -> opt_e = 0;
    pars -> opt_n = 0;
    pars -> opt_s = 0;
    pars -> opt_t = 0;
    pars -> opt_v = 0;
    for (int j = 1; j < count; j++) {
        int len_opt = strlen(pars_str[j]);
        for (int i = 0; i < len_opt; i++) {
            if (pars_str[j][i] == '-') {
                if (pars_str[j][i+1] == 'b' && pars_str[j][i+2] == '\0') {
                    pars -> opt_b = 1;
                    continue;
                } else if (pars_str[j][i+1] == '-' && pars_str[j][i+2] == 'n' && \
                strcmp(pars_str[j], "--number-nonblank") == 0) {
                    pars -> opt_b = 1;
                    j++;
                    continue;
                } else if (pars_str[j][i+1] == 'e' && pars_str[j][i+2] == '\0') {
                    pars -> opt_e = 1;
                    pars -> opt_v = 1;
                    continue;
                } else if (pars_str[j][i+1] == 'E' && pars_str[j][i+2] == '\0') {
                    pars -> opt_e = 1;
                    continue;
                } else if (pars_str[j][i+1] == 'n' && pars_str[j][i+2] == '\0') {
                    pars -> opt_n = 1;
                    continue;
                } else if (pars_str[j][i+1] == '-' && pars_str[j][i+2] == 'n' && \
                strcmp(pars_str[j], "--number") == 0) {
                    pars -> opt_n = 1;
                    j++;
                    continue;
                } else if (pars_str[j][i+1] == 's' && pars_str[j][i+2] == '\0') {
                    pars -> opt_s = 1;
                    continue;
                } else if (pars_str[j][i+1] == '-' && pars_str[j][i+2] == 's' && \
                strcmp(pars_str[j], "--squeeze-blank") == 0) {
                    pars -> opt_s = 1;
                    j++;
                    continue;
                } else if (pars_str[j][i+1] == 't' && pars_str[j][i+2] == '\0') {
                    pars -> opt_t = 1;
                    pars -> opt_v = 1;
                    continue;
                } else if (pars_str[j][i+1] == 'v' && pars_str[j][i+2] == '\0') {
                    pars -> opt_v = 1;
                    continue;
                } else if (pars_str[j][i+1] == 'T' && pars_str[j][i+2] == '\0') {
                    pars -> opt_t = 1;
                    continue;
                } else {
                    fprintf(stderr, \
                    "s21_cat: illegal option -- %c\nusage: ./s21_cat [-benstv] [file ...]\n", \
                    pars_str[j][i+1]);
                    parser_exit_flag = 1;
                    break;
                }
            }
        }
    }
    if (pars -> opt_b) pars -> opt_n = 0;
    return parser_exit_flag;
}

int file_open(int argc, char **pars_str, struct opt_cat *pars) {
    for (int i = 1; i < argc; i++) {
        if (pars_str[i][0] == '-') {
            continue;
        } else {
            FILE *fp = fopen(pars_str[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "s21_cat: %s: No such file or directory\n", pars_str[i]);
            } else {
                fclose(fp);
                print_file_def(pars_str[i], pars);
            }
        }
    }
    return 0;
}

void print_file_def(char *str, struct opt_cat *pars) {
    char print_c, next_c;
    FILE *fp = fopen(str, "r");
    int i = 1, helper = 0, helper_s = 0;
    next_c = getc(fp);
    if (pars -> opt_n && next_c != -1) {
        printf("%6d\t", i);
        i++;
        if (pars -> opt_s && next_c == '\n') helper_s += 1;
        if (pars -> opt_e && next_c == '\n' && !pars -> opt_s) {
            helper += 1;
        }
    } else if (pars -> opt_b == 1 && (next_c != '\n' && next_c != -1)) {
        printf("%6d\t", i);
        i++;
    }
    if (pars -> opt_s && next_c == '\n') print_c = next_c;
    while (next_c != EOF) {
        if (pars -> opt_e && next_c == '\n' && ((!pars -> opt_n || pars -> opt_b) \
        || (pars -> opt_n && print_c != '\n'))) {
            if (pars -> opt_s && print_c != '\n') {
                printf("$");
                if (helper) {
                    printf("\b");
                    helper += 1;
                }
            } else if (!pars -> opt_s) {
                printf("$");
            }
        }
        if (pars -> opt_s && (next_c == '\n' && print_c == '\n')) {
            while (next_c == '\n') next_c = getc(fp);
            if (pars -> opt_n && helper_s != 1 && !pars -> opt_b) {
                printf("%6d\t", i);
                i++;
                helper_s++;
            }
            if (pars -> opt_e) {
                printf("$");
            }
            printf("\n");
            helper_s++;
            continue;
        }
        if ((pars -> opt_n && print_c == '\n') || \
        (pars -> opt_b && (print_c == '\n' && next_c != '\n'))) {
            printf("%6d\t", i);
            i++;
            if (pars -> opt_e && next_c == '\n') {
                printf("$");
            }
        }
        if (pars -> opt_t && next_c == 9) {
            printf("^I");
            print_c = next_c;
            next_c = getc(fp);
            continue;
        }
        if (pars -> opt_v && (next_c <= 31 || next_c > 126)) {
            if (next_c == 127) {
                printf("^?");
                print_c = next_c;
                next_c = getc(fp);
                continue;
            } else if (next_c > 126) {
                printf("M-^%c", next_c - 64);
                print_c = next_c;
                next_c = getc(fp);
                continue;
            } else if (next_c != 9 && next_c != 10) {
                printf("^%c", next_c + 64);
                print_c = next_c;
                next_c = getc(fp);
                continue;
            }
        }
        print_c = next_c;
        printf("%c", print_c);
        next_c = getc(fp);
    }
    fclose(fp);
}
