#include"s21_grep.h"

int main(int argc, char *argv[]) {
    struct opt_grep pars;
    int exit_flag = 0;
    char template[buff_size] = {0};
    memset(&pars, 0, sizeof(pars));
    exit_flag = parser(argc, argv, &pars, template);
    if ((argc >= 3) && (exit_flag != 1)) {
        grep(&pars, argc, argv, template);
    }
    return exit_flag;
}


int parser(int argc, char *argv[], struct opt_grep *pars, char *template) {
    int i = 0, result = 0;
    while ((i = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        if (i == 'e') {
            pars->opt_e = 1;
            snprintf(template, buff_size, optarg);
        } else if (i == 'i') {
            pars->opt_i = 1;
        } else if (i == 'v') {
            pars->opt_v = 1;
        } else if (i == 'c') {
            pars->opt_c = 1;
        } else if (i == 'l') {
            pars->opt_l = 1;
        } else if (i == 'n') {
            pars->opt_n = 1;
        } else if (i == 'h') {
            pars->opt_h = 1;
        } else if (i == 's') {
            pars->opt_s = 1;
        } else if (i == 'f') {
            pars->opt_f = 1;
            snprintf(template, buff_size, optarg);
        } else if (i == 'o') {
            pars->opt_o = 1;
        } else {
            result = 1;
        }
    }
    return result;
}

void grep(struct opt_grep *pars, int argc, char **argv, char *temp) {
  char templateL[buff_size] = {0};
  int cols = 0;
  if (!pars->opt_f && !pars->opt_e) snprintf(templateL, buff_size, argv[optind++]);
  if (pars->opt_f) cols = save_patt_file(templateL, temp);
  if (!pars->opt_f && pars->opt_e) snprintf(templateL, buff_size, temp);
  if (cols != -1) {
    int file_c = (argc - optind > 1) ? 1 : 0;
    for (int i = optind; i < argc; i++) {
      if (file_c && !pars->opt_h && !pars->opt_l) printf("%s:", argv[i]);
      grep_file(pars, templateL, argv[i]);
    }
  }
}

int save_patt_file(char *template, char *temp) {
  FILE *fp;
  fp = fopen(temp, "r");
  int i = 0;
  if (fp == NULL) {
    i = -1;
  } else {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 13 || ch == 10) template[i++] = '|';
      if (ch != 13 && ch != 10) template[i++] = ch;
    }
    if (template[i - 1] == '|') template[i - 1] = '\0';
    fclose(fp);
  }
  return (i == -1) ? -1 : (i + 1);
}

void grep_file(struct opt_grep *pars, char *template, char *file) {
  int cflags = (pars->opt_i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  regex_t reg;
  FILE *fp;
  fp = fopen(file, "r");

  if (fp == NULL) {
  } else {
    regcomp(&reg, template, cflags);
    filework(pars, fp, reg, file);
    regfree(&reg);
    fclose(fp);
  }
}

void filework(struct opt_grep *pars, FILE *fp, regex_t reg, char *file) {
  char text[buff_size] = {0};
  regmatch_t pmatch[1];
  int line_matches = 0, nline = 1;

  while (fgets(text, buff_size - 1, fp) != NULL) {
    int status = regexec(&reg, text, 1, pmatch, 0);
    int match = 0;

    if (status == 0 && !pars->opt_v) match = 1;
    if (status == REG_NOMATCH && pars->opt_v) match = 1;
    if (match && !pars->opt_l && !pars->opt_c && pars->opt_n) printf("%d:", nline);
    if (match && !pars->opt_l && !pars->opt_c && !pars->opt_o) printf("%s", text);

    if (pars->opt_o && match) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", text[i]);
      }
      printf("\n");
    }
    line_matches += match;
    nline++;
  }

  if (pars->opt_l && line_matches > 0) printf("%s\n", file);
  if (pars->opt_c && !pars->opt_l) printf("%d\n", line_matches);
}