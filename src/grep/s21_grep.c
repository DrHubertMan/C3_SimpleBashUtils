#include"s21_grep.h"

int main(int argc, char **argv) {
    int exit_flag = 0;
    if (argc > 1) {
        struct opt_grep pars;
        char *template = malloc(1024);
        int a = parser(argc, argv, &pars, template);
        if (a == 0) {
            file_open(argc, argv, &pars, template);
        } else {
            exit_flag = 1;
        }
        free(template);
    }
    return exit_flag;
}

int parser(int count, char **pars_str, struct opt_grep *pars, char *template) {
    int exit_flag = 0, helper = 0;
    pars -> opt_e = 0;
    pars -> opt_i = 0;
    pars -> opt_v = 0;
    pars -> opt_c = 0;
    pars -> opt_l = 0;
    pars -> opt_n = 0;
    pars -> file_n = 0;
    for (int i = 1; i < count; i++) {
        int len_argv = strlen(pars_str[i]);
        for (int j = 0; j < len_argv; j++) {
            if (pars_str[i][j] == '-') {
                if (pars_str[i][j+1] == 'e') {
                    pars -> opt_e = 1;
                    memset(pars_str[i], 0, 1);
                    strcat(template, pars_str[i+1]);
                    memset(pars_str[i+1], 0, 1);
                    continue;
                } else if (pars_str[i][j+1] == 'i') {
                    pars -> opt_i = 1;
                    memset(pars_str[i], 0, 1);
                    continue;
                } else if (pars_str[i][j+1] == 'v') {
                    pars -> opt_v = 1;
                    memset(pars_str[i], 0, 1);
                    continue;
                } else if (pars_str[i][j+1] == 'c') {
                    pars -> opt_c = 1;
                    memset(pars_str[i], 0, 1);
                    continue;
                } else if (pars_str[i][j+1] == 'l') {
                    pars -> opt_l = 1;
                    memset(pars_str[i], 0, 1);
                    continue;
                } else if (pars_str[i][j+1] == 'n') {
                    pars -> opt_n = 1;
                    memset(pars_str[i], 0, 1);
                    continue;
                } else {
                    exit_flag = 1;
                }
            }
        }
    }
    for (int j = 1; j < count; j++) {
        if (helper == 0 && !pars -> opt_e && pars_str[j][0] != '\0') {
            strcat(template, pars_str[j]);
            helper++;
            continue;
        }
        FILE *fp = fopen(pars_str[j], "r");
        if (fp != NULL) {
            pars -> file_n += 1;
        }
    }
    return exit_flag;
}

int file_open(int argc, char **pars_str, struct opt_grep *pars, char *template) {
    int exit_flag = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(pars_str[i], template) == 0) continue;
        FILE *fp = fopen(pars_str[i], "r");
        if (fp == NULL) {
            exit_flag = 1;
            continue;
        } else {
            fclose(fp);
            exit_flag = 0;
            print_file(pars_str, i, pars, template);
        }
    }
    return exit_flag;
}

void print_file(char **str, int x, struct opt_grep *pars, char *template) {
    char *file_str = malloc(1024);
    char *strend = malloc(1024);
    FILE *fp = fopen(str[x], "r");
    regex_t rg;
    int i = 0, c = 0, len, l_count = 0, reg_flaf = REG_EXTENDED;
    if (pars -> opt_i) reg_flaf = REG_ICASE;
    while (fgets(file_str, 256, fp) != NULL) {
        int proof_co, proof_ex;
        if (pars -> file_n > 1 && !pars -> opt_c && !pars -> opt_l) printf("%s:", str[x]);
        if (pars -> opt_n) i++;
        proof_co = regcomp(&rg, template, reg_flaf);
        if (proof_co) fprintf(stderr, "regular expression error");
        proof_ex = regexec(&rg, file_str, 0, NULL, 0);
        if (pars -> opt_v) {
            if (proof_ex) {
                if (pars -> opt_c) {
                    c++;
                    regfree(&rg);
                    memset(file_str, '\0', 1);
                }
                if (pars -> opt_l) {
                    l_count = 1;
                    regfree(&rg);
                    break;
                }
                if (pars -> opt_n && (!pars -> opt_c && !pars -> opt_l)) printf("%d:", i);
                printf("%s", file_str);
                strcat(strend, file_str);
            }
        } else if (!proof_ex) {
            if (pars -> opt_c) {
                c++;
                regfree(&rg);
                memset(file_str, '\0', 1);
            }
            if (pars -> opt_l) {
                l_count = 1;
                regfree(&rg);
                break;
            }
            if (pars -> opt_n && (!pars -> opt_c && !pars -> opt_l)) printf("%d:", i);
            printf("%s", file_str);
            strcat(strend, file_str);
        }
        regfree(&rg);
    }
    if (pars -> opt_c) {
        if (pars->file_n > 1) printf("%s:", str[x]);
        printf("%d\n", c);
    }
    if (pars -> opt_l && l_count) printf("%s\n", str[x]);
    len = strlen(strend);
    if (!pars -> opt_c && !pars -> opt_l) {
        if (strend[len-1] != '\n') printf("\n");
    }
    free(file_str);
    free(strend);
    fclose(fp);
}
