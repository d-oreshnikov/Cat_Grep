#include "my_grep.h"

int main(int argc, char *argv[]) {
  int stop = 1;
  int *ps = &stop;
  struct flags flag;
  char patterne[buff_size] = {0};
  char patternf[buff_size] = {0};
  makeFlagStruct(&flag);  // make struct flag
  get_flags(argc, argv, &flag, patterne, patternf,
            ps);  //  take flags to struct
  if ((stop) && (argc >= 3)) {
    grep(argc, argv, &flag, patterne, patternf);  // main work func
  }
  return 0;
}

void makeFlagStruct(struct flags *flag) {
  flag->e = 0;
  flag->i = 0;
  flag->v = 0;
  flag->c = 0;
  flag->l = 0;
  flag->n = 0;
  flag->h = 0;
  flag->s = 0;
  flag->f = 0;
  flag->o = 0;
}

void get_flags(int argc, char *argv[], struct flags *flag, char *patterne,
               char *patternf, int *ps) {
  int opchar = 0;
  while (-1 != (opchar = getopt(argc, argv, "+e:ivclnhsf:o"))) {
    switch (opchar) {
      case 'e':
        flag->e = 1;
        strcat(patterne, optarg);
        strcat(patterne, "|");
        break;

      case 'f':
        flag->f = 1;
        strcat(patternf, optarg);
        strcat(patternf, "|");
        break;

      case 'i':
        flag->i = 1;
        break;

      case 'v':
        flag->v = 1;
        break;

      case 'c':
        flag->c = 1;
        break;

      case 'l':
        flag->l = 1;
        break;

      case 'n':
        flag->n = 1;
        break;

      case 'h':
        flag->h = 1;
        break;

      case 's':
        flag->s = 1;
        break;

      case 'o':
        flag->o = 1;
        break;

      default:
        *ps = 0;
        break;
    }
  }
}

void processing(struct flags *flag, FILE *fp, regex_t reg, char *file,
                int filecount) {
  char text[buff_size] = {0};
  regmatch_t pmatch[1];  // подготавливаем слово к поиску
  int linecount = 0;     // номер строки
  int clinecount = 0;  // колличество подходящих строк

  while (fgets(text, buff_size - 1, fp) != NULL) {
    int len = strlen(text);
    if (text[len - 1] != '\n') {
      strcat(text, "\n");
    }
    int success = regexec(&reg, text, 1, pmatch,
                          0);  // ищем совпадения строки с регулярным выражением
    if (flag->o && success == 0) {
      printf("%.*s\n", (int)(pmatch->rm_eo - pmatch->rm_so),
             text + pmatch->rm_so);
    }
    if (!flag->o) {
      if (!flag->v) {
        linecount++;
        if (success == 0) clinecount++;
        if (success == 0 && !flag->h && filecount && !flag->c && !flag->l) {
          if (flag->n) printf("%s:%d:%s", file, linecount, text);
          if (!flag->n) printf("%s:%s", file, text);
        }

        if (((success == 0 && !filecount) || (success == 0 && flag->h)) &&
            !flag->c && !flag->l) {
          if (flag->n) printf("%d:%s", linecount, text);
          if (!flag->n) printf("%s", text);
        }
      }
      if (flag->v) {
        linecount++;
        if (success == REG_NOMATCH) clinecount++;
        if (success == REG_NOMATCH && !flag->h && filecount && !flag->c &&
            !flag->l) {
          if (flag->n) printf("%s:%d:%s", file, linecount, text);
          if (!flag->n) printf("%s:%s", file, text);
        }

        if (((success == REG_NOMATCH && !filecount) ||
             (success == REG_NOMATCH && flag->h)) &&
            !flag->c && !flag->l) {
          if (flag->n) printf("%d:%s", linecount, text);
          if (!flag->n) printf("%s", text);
        }
      }
    }
  }
  if (flag->l && flag->c && !filecount)
    printf("%d\n", ((clinecount > 0) ? 1 : 0));
  if (flag->l && flag->c && filecount)
    printf("%s:%d\n", file, ((clinecount > 0) ? 1 : 0));
  if (flag->c && !filecount && !flag->l) printf("%d\n", clinecount);
  if (flag->c && filecount && !flag->l) printf("%s:%d\n", file, clinecount);
  if (flag->l && clinecount > 0) printf("%s\n", file);
}

void grep_file(struct flags *flag, char *pattern, char *filename,
               int filecount) {  // получаем паттерн и файл поиска
  int cflags = REG_EXTENDED;  // флаг для стандартных регулярок
  regex_t reg;  // создаем структуру регулярных выражений
  FILE *file;
  file = fopen(filename, "r");

  if (flag->i) cflags = REG_ICASE;  // флаг для игнорирования case

  regcomp(&reg, pattern,
          cflags);  // переносим pattern в структуру регулярных выражений
  processing(flag, file, reg, filename,
             filecount);  // функция поиска совпадений
  regfree(&reg);          // очищаем память
  fclose(file);
}

int f_flag(char *pattern, char *filename) {
  FILE *file;
  file = fopen(filename, "r");
  char patternff[buff_size] = {0};  // patterns from all files

  int i = 0;
  if (file != NULL) {
    int ch;
    while ((ch = fgetc(file)) != EOF) {
      if (ch == 13 || ch == 10) patternff[i++] = '|';
      if (ch != 13 && ch != 10) patternff[i++] = ch;
    }
  } else {
    i = -1;
  }
  if (i != -1) {
    if (patternff[i - 1] == '|') patternff[i - 1] = '\0';

    strcat(pattern, patternff);
    strcat(pattern, "|");
    fclose(file);
  }
  return i;
}

void filework(char *pattern, char *patternf) {
  char *token, *last;
  token = strtok_r(patternf, "|", &last);
  int f_patt = 0;  // flag if file is ok
  (void)f_patt;
  while (token != NULL) {
    f_patt = f_flag(pattern, token);  //  take pattern as "A|B|C" from file
    if (f_patt == -1) {
      printf("my_grep: %s: No such file or directory\n", token);
      exit(1);
    }
    token = strtok_r(NULL, "|", &last);
  }
}

void grep(int argc, char *argv[], struct flags *flag, char *patterne,
          char *patternf) {
  char pattern[buff_size] = {0};

  if (!flag->f && !flag->e) {
    snprintf(pattern, buff_size, "%s",
             argv[optind++]);  //  take pattern if it's not f or e flag
  }

  if (flag->f && !flag->e) {  // flag f
    filework(pattern, patternf);
    int len = strlen(pattern);
    pattern[len - 1] = '\0';
  }

  if (!flag->f && flag->e) {  // flag e
    int len = strlen(patterne);
    patterne[len - 1] = '\0';
    strcpy(pattern, patterne);
  }

  if (flag->f && flag->e) {  // flag e anf flag f

    filework(pattern, patternf);
    int lene = strlen(patterne);
    patterne[lene - 1] = '\0';
    strcat(pattern, patterne);
  }

  for (int i = optind; i < argc; i++) {
    FILE *file;
    file = fopen(argv[i], "r");
    int filecount = (argc - optind > 1);
    if (file != NULL) {
      grep_file(flag, pattern, argv[i], filecount);
    }
    if (file == NULL && !flag->s)
      printf("my_grep: %s: No such file or directory\n", argv[i]);
    if (file != NULL) {
      fclose(file);
    }
  }
}
