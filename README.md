#  一个简单的语法制导翻译器

## 保留字表定义

| 保留字 | 说明               |
| ------ | ------------------ |
| float  | 定义一个浮点型变量 |
| int    | 定义一个整型变量   |
| write  | 输出一个变量的值   |

## 文法定义

### 终结符号

S = {***\*float\****, ***\*int\****, ***\*write\****, ***\*number\****, ***\*id\****, +, -, *, /, (, ), ;}

非终结符号 V = {STMT, EXPR, TERM, TYPE}

### 产生式集合

TYPE → ***\*float\**** | ***\*int\****

TERM → ***\*id\**** | ***\*number\**** | TERM * number | TERM / number |

TERM * ***\*id\**** | TERM / ***\*id\**** | ( TERM )

STMT → TYPE ***\*id\**** ;

| ***\*id\**** = EXPR ;

| ***\*write\****(***\*id\****) ;

 

##### 消除文法左递归后

(***\*op\**** = {‘+’, ’-’, ’*’, ’/’})

TYPE → ***\*float\**** | ***\*int\****

TERM → ***\*id\**** | ***\*number\**** | TERM * ***\*number\**** | TERM / ***\*number\**** |

TERM * ***\*id\**** | TERM / ***\*id\**** | ( TERM )

TERM → F R

R → ***\*op\**** F R | ℇ

F → (TERM) | ***\*id\**** | ***\*number\****

STMT → TYPE ***\*id\**** ;

| ***\*id\**** = TERM ;

| ***\*write\****(***\*id\****) ;

开始符号：STMT

 

## 语法规则

1) 支持浮点数和整数两种类型，整数可以转换成浮点；浮点数不可以转换成整数；

2) 每个语句需要以“；”结束，以“#”表示全部输入的结束；

3) 变量需要先声明再使用；

4) 变量名可以是由数字和字母组成，但首字符必须是字母。

5) 每个表达式中使用的变量需要在之前已经有赋值。

6) 输出语句使用write(a)，输出并换行，其中a为int类型或者float类型的变量名。

## 文件说明

main.cpp/head.h主函数文件

id_table.cpp/id_table.h 符号表的维护

parsing.cpp/parsing.h 语法分析模块

lexical.cpp/lexical.h 词法分析模块

math_.cpp/math_.h 相关的数学函数

stack.cpp/stack.h 堆栈结构体的实现与相关方法

strt.h 结构体定义

err_deal.cpp/err_deal.h 错误处理模块

 

## 错误处理

  ERR_UNDETECTED_SYM 编译器无法识别的字符

  ERR_INPUT_OUTLENTH 变量长度过长

  ERR_NUM_OUTLENTH 输入数字过长

  ERR_ID_REDEFINITION 变量重定义

  ERR_MISSING_SEMI 语句缺少分号

  ERR_ILLEGAL_ID 变量名不合法

  ERR_ID_UNDEFINITON 变量未定义

  ERR_WRITE_FORMAT write函数调用错误

  ERR_STATEMENT 无法识别的语句格式

  ERR_DIFFERENT_TYPE 变量类型出错（将浮点数赋值给整型变量）

ERR_MISSING_RIGHTPAREN 缺少匹配的右括号

遇到无法识别的错误的时候，编译器报错”Segment fault.”

## 使用说明

在calculator.exe的同文件夹下准备可以编译的输入文本，运行exe文件，输入 输出文本文件名与结果保存文件名，以空格区分，以回车为结尾。

如 输入a.txt b.txt\n，即将a.txt文本编译，结果输出到b.txt内。