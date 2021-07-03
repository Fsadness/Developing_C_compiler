// Copyright (c) 2021 Fsadness, All rights reserved.
// function_scan.c: The scan and some other functions

#include "token_defines.h"
#include "function_defines.h"
#include "extern_data.h"

static int CharPosition(char*, char);

static int NextChar(void);

static int Putback(int);

static int SkipWhitespace(void);

static int ScanIntenger(int);

//get the value of a dight, instead return -1
static int CharPosition(char *str, char c) 
{
  char *p = strchr(str, c);
  return p != NULL? p - str: -1;
}

static int NextChar(void)
{
  int c;

  if (charPutback != 0) {
    c = charPutback;
    charPutback = 0;
    ++fileColumn;
    return c;
  }

  c = fgetc(inFile);
  if (c == '\n') {
    ++fileLine;
    fileColumn = 1;
  }
  return c;
}

static int Putback(int c)
{
  charPutback = c;
}

static int SkipWhitespace(void)
{
  int c = NextChar();
  while (c == ' '  ||
         c == '\t' ||
         c == '\n' ||
         c == '\r' ||
         c == '\f') {
    c = NextChar();
  }
  return c;
}

static int ScanIntenger(int c)
{
  int k, value = 0;
  while ((k = CharPosition("0123456789", c)) >= 0) {
    value = value * 10 + k;
    c = NextChar();
  }
  Putback(c);
  
  return value;
}

int Scan(struct Token *t)
{
  int c = SkipWhitespace();

  switch (c) {
    case EOF:
      return 0;
    case '+': {
      t->token = kPlus;
      break;
    }
    case '-': {
      t->token = kMinus;
      break;
    }
    case '*': {
      t->token = kStar;
      break;
    }
    case '/': {
      t->token = kSlash;
      break;
    }
    default: {
      if (isdigit(c)) {
        t->token = kIntenger;
        t->int_value = ScanIntenger(c);
      } else {
        fprintf(stderr, "%s:%d:%d: Error: Unrecognised character \'%c\';\n", 
                fileName, fileLine, fileColumn, c);
        exit(1);
      }
    }
  }

  return 1;
}
