#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define buff_size 2048

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

void makeFlagStruct(struct flags *flag);
void get_flags(int argc, char *argv[], struct flags *flag, char *patterne,
               char *patternf, int *ps);
void processing(struct flags *flag, FILE *fp, regex_t reg, char *file,
                int filecount);
void grep_file(struct flags *flag, char *pattern, char *file, int filecount);
int f_flag(char *pattern, char *temp);
void filework(char *pattern, char *patternf);
void grep(int argc, char *argv[], struct flags *flag, char *patterne,
          char *patternf);
