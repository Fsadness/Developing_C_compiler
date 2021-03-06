## Part 1 实现一个基本的词汇扫描器（lexical scanner）

Readme in English is **[Here]([acwj/Readme.md at master · DoctorWkt/acwj (github.com)](https://github.com/DoctorWkt/acwj/blob/master/01_Scanner/Readme.md))**.

### 英汉翻译

| English words    | 汉语含义   |
| ---------------- | ---------- |
| lexical scanner  | 词汇扫描器 |
| lexical elements | 词汇成分   |
| token            | 令牌       |

### 目标

实现一个基本的词汇扫描器，它能够读取文件，识别并存储其中的有效字符（当前仅考虑`+`、`-`、`*`、`/`四个基本运算符号以及十进制数字`0~9`）

### Tokens定义

定义一个`token`结构体，用于存储每一个词汇成分。其中，当`token == kIntenger`（即当前结构体存储元素为一个整数）时，`Int_value`存储该整数的值。

```c
struct Token {
  int token;
  int int_value;
};

enum {
  kPlus, kMinus, kStar, kSlash, kIntenger
};
```

### 获取文件中的下一个字符

声明一个函数`next()`，在每次声明的时候返回文件的下一个字符值。同时，为方便后续的**错误定位**，同时确定当前字符所在的行号（此处使用全局变量定义）。

- 要点：对于某些需要持续读入字符直至循环条件终止时跳出的函数，可能会出现**使循环条件终止的字符被抛弃**的情况。因此需要采用一个全局变量避免**字符丢失**。

### 跳过空白字符

在读取文件时，对于无意义的空白字符选择忽略~~(又不是什么`brainfuck`)~~，直至获取一个**可打印字符**为止。

### 文件扫描函数`scan()`

函数传入token指针格式的参数，使用`switch`结构扫描字符以确定token类型。如果遇到`EOF`则返回`0`说明文件结尾（否则返回1继续进行扫描循环）

#### 对整数的读取

在读取的时候使用`strchr()`函数，通过确定字符在字符串`"0123456789"`中的位置，并返回以读取字符`'0'~'9'`的值。

- 要点：这里采用的方法虽然相较于`c - '0'`速度更慢，但可以通过延长比较字符串`"0123456789ABCDEF"`的方式更为便捷地实现对十六进制整数地支持。

### 主函数

使用**命令行参数**实现对文件的“编译”（当前仅仅实现了文本的读取）

（这里添加了一个测试函数检测扫描函数是否正常运行）

### 文件树

```
main.c
+-extern_data.h
+-token_defines.h
+-functiom_defines.h
	+-function_scan.c

Makefile
scanner
+-main.o
	+-function_scan.o
```

