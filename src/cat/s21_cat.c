#include"s21_cat.h"

int main(int argc, char *argv[]) {
  struct opt_cat pars = {0};
  int opt_i = 0;
  int next_c = 0;
  int counter = 0, new_line = 0, prev_c = 1, test = 0, test_y = 0, allright = 1;
  static struct option long_opt[] = {{"--number-nonblank", 0, 0, 'b'},
                                       {"--number", 0, 0, 'n'},
                                       {"--squeeze-blank", 0, 0, 's'},
                                       {0, 0, 0, 0}};

  while ((next_c = getopt_long(argc, argv, "benstvET", long_opt, &opt_i)) !=
         -1) {
    test++;
    switch (next_c) {
      case 'E':
        pars.opt_e = 1;
        break;
      case 'T':
        pars.opt_t = 1;
        break;
      case 'b':
        pars.opt_b = 1;
        break;
      case 'e':
        pars.opt_e = 1;
        pars.opt_v = 1;
        break;
      case 'n':
        pars.opt_n = 1;
        break;
      case 's':
        pars.opt_s = 1;
        break;
      case 't':
        pars.opt_t = 1;
        pars.opt_v = 1;
        break;
      case 'v':
        pars.opt_v = 1;
        break;
      default:
        break;
    }
  }
  if (pars.opt_b == 1) {
    pars.opt_n = 0;
  }
  while (*argv[1] == '-') {
    test_y++;
    argv++;
  }

  argv++;
  argc--;

  while (argc > test_y) {
    FILE *test1 = fopen(*argv, "r");
    while ((next_c = getc(test1)) != EOF) {
      if (pars.opt_s == 1) {
        if (next_c == '\n') {
          prev_c++;
          if (prev_c == 3) {
            prev_c--;
            continue;
          }
        } else {
          prev_c = 0;
        }
      }
      if (pars.opt_b == 1) {
        if (next_c != '\n') {
          if (new_line == 0) {
            printf("%6d\t", ++counter);
            new_line = 1;
          }
        } else {
          new_line = 0;
        }
      }
      if (pars.opt_n == 1) {
        if (new_line == 0) {
          printf("%6d\t", ++counter);
          new_line = 1;
        }
        if (next_c == '\n') {
          new_line = 0;
        }
      }
      if (pars.opt_e == 1) {
        if (next_c == '\n') {
          printf("%c", '$');
        }
      }
      if (pars.opt_t == 1) {
        if (next_c == '\t') {
          printf("^I");
          allright = 0;
        }
      }
      if (pars.opt_v == 1) {
        if (next_c <= 31 && next_c != 9 && next_c != 10) {
          printf("^%c", next_c + 64);
          allright = 0;
        }
      }
      if (allright == 1) {
        printf("%c", next_c);
      }
      allright = 1;
    }
    argc--;
    argv++;
    counter = 0;
    prev_c = 1;
    fclose(test1);
  }
  return 0;
}
