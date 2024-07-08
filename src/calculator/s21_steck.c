#include "s21_calc.h"

void clearCurrentToken(char *token, int size) {
  for (int i = 0; i < size; i++) {
    token[i] = '\0';
  }
}

Data evaluateExpression(char *expression, Data xValue) {
  Node *valueStack = NULL;
  Node *operatorStack = NULL;
  Data result = 0;
  int numFlag = 0;
  int haveTrigonometry = 0;
  Data num = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  char currentToken[256] = {'\0'};
  int length = strlen(expression);
  length += 1;

  if (expression[0] == '-' || expression[0] == '+') {
    pushStack(&valueStack, 0, '0', 0);
  }

  while (i != length) {
    if ((expression[i] >= '0' && expression[i] <= '9') ||
        expression[i] == '.') {
      currentToken[j] = expression[i];
      numFlag = 1;
      j++;
      if (expression[i + 1] == '(' || expression[i - 1] == ')') {
        pushStack(&operatorStack, 0, '*', 3);
      }
    } else if (expression[i] == 'X') {
      pushStack(&valueStack, xValue, '0', 0);
      if ((expression[i - 1] >= '0' && expression[i - 1] <= '9') ||
          (expression[i + 1] >= '0' && expression[i + 1] <= '9')) {
        pushStack(&operatorStack, 0, '*', 3);
      }
    } else if (expression[i] == '(' && (i + 1 < length) &&
               (expression[i + 1] == '+' || expression[i + 1] == '-')) {
      pushStack(&valueStack, 0, 0, 0);
      pushStack(&operatorStack, 0, '(', -1);
    } else {
      j = 0;
      if (numFlag) {
        num = atof(currentToken);
        pushStack(&valueStack, num, '0', 0);
        clearCurrentToken(currentToken, sizeof(currentToken));
      }
      numFlag = 0;

      if ((expression[i] >= 'a' && expression[i] <= 'z') ||
          (expression[i] >= 'A' && expression[i] <= 'Z')) {
        currentToken[k] = expression[i];
        haveTrigonometry = 1;
        k++;
      } else if (haveTrigonometry) {
        handleTrigonometry(&operatorStack, currentToken);
        haveTrigonometry = 0;
        pushStack(&operatorStack, 0, '(', -1);
        clearCurrentToken(currentToken, sizeof(currentToken));
      } else {
        if (expression[i] != '\0') {
          int priority = parsePriority(expression[i]);
          if (priority != 0) {
            calculateExpression(&valueStack, &operatorStack, priority,
                                expression[i]);
          }
        } else {
          break;
        }
      }
    }
    i++;
  }

  result = calculateTotal(&valueStack, &operatorStack);
  popAndFreeStack(&valueStack);
  popAndFreeOperatorStack(&operatorStack);

  return result;
}

const TrigFunction trigFunctions[] = {
    {"cos", 'B'},  {"sin", 'C'},  {"tan", 'D'}, {"acos", 'E'}, {"asin", 'F'},
    {"atan", 'G'}, {"sqrt", 'H'}, {"ln", 'I'},  {"log", 'J'}};

int handleTrigonometry(Node **operatorStack, char *word) {
  int error = SUCCESS;
  char currentToken[5] = {'\0'};

  for (int i = 0; word[i] != '\0'; i++) {
    currentToken[i] = word[i];
  }

  for (size_t i = 0; i < sizeof(trigFunctions) / sizeof(trigFunctions[0]);
       i++) {
    if (!strcmp(currentToken, trigFunctions[i].token)) {
      error = FAIL;
      pushStack(operatorStack, 0, trigFunctions[i].operat,
                TRIG_OPERATOR_PRIORITY);
      break;
    }
  }

  return error;
}

Data popStack(Node **stack) {
  Node *p = *stack;
  Data result = p->value;
  *stack = p->next;
  free(p);
  p = NULL;
  return result;
}

void pushStack(Node **stack, Data value, char operator, int priority) {
  Node *p = malloc(sizeof(Node));
  p->value = value;
  p->operato = operator;
  p->priority = priority;
  p->next = *stack;
  *stack = p;
}

char popOperatorStack(Node **stack) {
  Node *p = *stack;
  char result = p->operato;
  *stack = p->next;
  free(p);
  p = NULL;
  return result;
}

void popAndFreeStack(Node **stack) {
  while (*stack != NULL) {
    popStack(stack);
  }
}

void popAndFreeOperatorStack(Node **stack) {
  while (*stack != NULL) {
    popOperatorStack(stack);
  }
}
