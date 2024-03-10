#include "my_cat.h"

int main(int argc, char *argv[]) {
  int stop = 1;
  int *ps = &stop;
  struct flags flag;
  makeFlagStruct(&flag);
  get_arg(argc, argv, &flag, ps);
  if (stop) {
    open_files(argc, argv, &flag);
  }
  return 0;
}

void makeFlagStruct(struct flags *flag) {
  flag->b = 0;
  flag->e = 0;
  flag->n = 0;
  flag->s = 0;
  flag->t = 0;
  flag->v = 0;
}

void get_arg(int argc, char *argv[], struct flags *flag, int *ps) {
  int opchar = 0;
  int optindex = 0;
  while (-1 !=
         (opchar = getopt_long(argc, argv, "benvstET", opts, &optindex))) {
    switch (opchar) {
      case 'b':
        flag->b = 1;
        break;

      case 'e':
        flag->v = 1;
        flag->e = 1;
        break;

      case 'n':
        flag->n = 1;
        break;

      case 's':
        flag->s = 1;
        break;

      case 't':
        flag->v = 1;
        flag->t = 1;
        break;

      case 'v':
        flag->v = 1;
        break;

      case 'E':
        flag->e = 1;
        break;

      case 'T':
        flag->t = 1;
        break;

      default:
        printf("usage: cat [-benstuv] [file ...]\n");
        *ps = 0;
        break;
    }
  }
}

void open_files(int argc, char *argv[], struct flags *flag) {
  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file) {
      printfile(file, flag);
      fclose(file);
    } else {
      printf("my_cat: %s: No such file or directory\n", argv[i]);
    }
  }
}

void printfile(FILE *file, struct flags *flag) {
  int ext = 1;
  int ch_prev = '\n';
  int emptyline = 0;
  int Sflag = 1;
  int lineCount = 1;

  while (ext) {
    int ch = getc(file);

    if (ch == EOF) {
      ext = 0;
    } else {
      if (flag->s && ch == '\n' && ch_prev == '\n')  //  flag s
      {
        emptyline++;
        if (emptyline > 1) {
          Sflag = 0;
        }
      }

      else {
        Sflag = 1;
        emptyline = 0;
      }

      if (Sflag) {
        if (((flag->n && !flag->b) || (flag->b && ch != '\n')) &&
            ch_prev == '\n') {  //  flag n and b
          printf("%6d\t", lineCount);
          lineCount++;
        }

        if (flag->t && ch == '\t')  // flag t
        {
          printf("^");
          ch = 'I';
        }

        if (flag->e && ch == '\n')  // flag e
        {
          printf("$");
        }

        if (flag->v)  // flag v
        {
          if (ch < -96) {
            printf("M-^");
            ch += 192;
          } else if (ch < 0) {
            printf("M-");
            ch += 128;
          } else if (ch == 9 || ch == 10) {
            ch = ch;
          } else if (ch < 32) {
            printf("^");
            ch += 64;
          } else if (ch < 127) {
            ch = ch;
          } else {
            printf("^");
            ch = '?';
          }
        }

        printf("%c", ch);
        ch_prev = ch;
      }
    }
  }
}