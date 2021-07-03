// Copyright (c) 2021 Fsadness, All rights reserved.
// token_defines.h: Define the main struct token

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//tokens
enum {
  kPlus, kMinus, kStar, kSlash, kIntenger
};

//Token structure
struct Token {
  int token;
  int int_value;
};
