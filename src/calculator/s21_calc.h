#ifndef S21_CALC_H
#define S21_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAIL 1
#define SUCCESS 0

#define ADD_SUB_PRIORITY 2
#define MUL_DIV_MOD_PRIORITY 3
#define EXP_PRIORITY 5
#define TRIG_OPERATOR_PRIORITY 4
#define PARENTHESIS_PRIORITY -1
#define NUMBER_PRIORITY 0

typedef double Data;

typedef struct {
  const char *token;
  char operat;
} TrigFunction;

typedef struct Node {
  Data value;
  char operato;
  int priority;
  struct Node *next;
} Node;

int validation(char *value);
int plotValid(double xMax, double xMin, double yMax, double yMin);

Data evaluateExpression(char *expression, Data xValue);
int handleTrigonometry(Node **operatorStack, char *word);
Data popStack(Node **stack);
void pushStack(Node **stack, Data value, char operato, int priority);
char popOperatorStack(Node **stack);
void popAndFreeStack(Node **stack);
void popAndFreeOperatorStack(Node **stack);

Data calculateTotal(Node **list, Node **s_lst);
void calculateExpression(Node **list, Node **s_list, int next_prior, char oper);
Data calculateTrigonometric(Data var, char stek_oper);
int parsePriority(char val);

#endif  // S21_CALC_H
