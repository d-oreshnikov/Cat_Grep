#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FILESIZE 2048

char *fname[FILESIZE];

struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
};

struct option opts[] = {

    // set flag example
    {"number-nonblank", no_argument, 0, 'b'},
    {"number", no_argument, 0, 'n'},
    {"squeeze-blank", no_argument, 0, 's'},
    {0, 0, 0, 0},
};

void makeFlagStruct(struct flags *flag);
void get_arg(int argc, char *argv[], struct flags *flag, int *ps);
void open_files(int argc, char *argv[], struct flags *flag);
void printfile(FILE *file, struct flags *flag);
