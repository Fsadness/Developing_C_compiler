// Copyright (c) 2021 Fsadness, All rights reserved.
// main.c

#include <errno.h>

#include "token_defines.h"
#include "function_defines.h"
#define extern_
#include "extern_data.h"
#undef extern_

static void Init(void)
{
  fileLine = 1;
  fileColumn = 1;
  charPutback = 0;
}

static void Usage(char *program)
{
  fprintf(stderr, "Usage: %s infile\n", program);
  exit(1);
}

char *kTokenString[] = {
  "+", "-", "*", "/",
  "int"
};

static void ScanFile(void)
{
  struct Token tmp;

  while (Scan(&tmp) == 1) {
    printf("Token %s", kTokenString[tmp.token]);
    if (tmp.token == kIntenger)
      printf(", value %d", tmp.int_value);
    putchar('\n');
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    Usage(argv[0]);
    exit(1);
  }

  Init();
  fileName = argv[1];
  if ((inFile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", 
            argv[1], strerror(errno));
    exit(1);
  }

  ScanFile();
  exit(0);
}