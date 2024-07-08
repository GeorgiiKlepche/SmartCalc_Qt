#include "s21_calc.h"

void calculateExpression(Node** valueStack, Node** operatorStack,
                         int nextPriority, char operation) {
  if (*operatorStack != NULL) {
    Data operand1 = 0;
    Data operand2 = 0;
    Data result = 0;
    char stackOperator = (*operatorStack)->operato;

    if (operation == ')') {
      result = calculateTotal(valueStack, operatorStack);
    } else if (nextPriority > (*operatorStack)->priority || operation == '(') {
      pushStack(operatorStack, 0, operation, nextPriority);
    } else {
      while (*operatorStack != NULL &&
             nextPriority <= (*operatorStack)->priority) {
        stackOperator = popOperatorStack(operatorStack);

        if (stackOperator >= 'A' && stackOperator <= 'Z') {
          operand1 = popStack(valueStack);
          result = calculateTrigonometric(operand1, stackOperator);
          pushStack(valueStack, result, '0', NUMBER_PRIORITY);
        } else {
          operand1 = popStack(valueStack);
          operand2 = popStack(valueStack);

          switch (stackOperator) {
            case '+':
              result = operand2 + operand1;
              break;
            case '-':
              result = operand2 - operand1;
              break;
            case '/':
              result = operand2 / operand1;
              break;
            case '*':
              result = operand2 * operand1;
              break;
            case '^':
              result = pow(operand2, operand1);
              break;
            case '%':
              result = fmod(operand2, operand1);
              break;
            default:
              // Обработка неизвестного оператора
              break;
          }
          pushStack(valueStack, result, '0', NUMBER_PRIORITY);
        }
      }
      pushStack(operatorStack, 0, operation, nextPriority);
    }
  } else {
    pushStack(operatorStack, 0, operation, nextPriority);
  }
}

Data calculateTotal(Node** valueStack, Node** operatorStack) {
  Data operand1 = 0;
  Data operand2 = 0;
  Data result = 0;
  Data totalResult;
  char operatorSign;
  int flag = 0;

  while (*operatorStack != NULL) {
    operatorSign = popOperatorStack(operatorStack);
    if (operatorSign == '(') {
      flag = 1;
      break;
    }
    if (operatorSign >= 'A' && operatorSign <= 'Z') {
      result = calculateTrigonometric(popStack(valueStack), operatorSign);
    } else {
      operand1 = popStack(valueStack);
      operand2 = popStack(valueStack);

      switch (operatorSign) {
        case '+':
          result = operand2 + operand1;
          break;
        case '-':
          result = operand2 - operand1;
          break;
        case '/':
          result = operand2 / operand1;
          break;
        case '*':
          result = operand2 * operand1;
          break;
        case '^':
          result = pow(operand2, operand1);
          break;
        case '%':
          result = fmod(operand2, operand1);
          break;
        default:
          // Обработка неизвестного оператора
          break;
      }
    }
    pushStack(valueStack, result, '0', 0);
  }

  if (flag == 1) {
    totalResult = result;
  } else {
    totalResult = popStack(valueStack);
  }

  return totalResult;
}

Data calculateTrigonometric(Data operand, char stackOperator) {
  Data result = 0;
  switch (stackOperator) {
    case 'B':
      result = cos(operand);
      break;
    case 'C':
      result = sin(operand);
      break;
    case 'D':
      result = tan(operand);
      break;
    case 'E':
      result = acos(operand);
      break;
    case 'F':
      result = asin(operand);
      break;
    case 'G':
      result = atan(operand);
      break;
    case 'H':
      result = sqrt(operand);
      break;
    case 'J':
      result = log(operand);
      break;
    default:
      // Обработка неизвестного оператора
      break;
  }
  return result;
}

int parsePriority(char value) {
  int priority = 0;
  switch (value) {
    case '+':
    case '-':
      priority = ADD_SUB_PRIORITY;
      break;
    case '/':
    case '*':
    case '%':
      priority = MUL_DIV_MOD_PRIORITY;
      break;
    case '^':
      priority = EXP_PRIORITY;
      break;
    case '(':
    case ')':
      priority = PARENTHESIS_PRIORITY;
      break;
    default:
      // Обработка неизвестного оператора
      break;
  }
  return priority;
}
