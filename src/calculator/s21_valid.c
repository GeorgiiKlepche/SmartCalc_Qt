#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "s21_calc.h"

int validation(char *expression) {
  int errorFlag = FAIL;
  int numFlag = FAIL;
  int currentIndex = 0;
  int decimalPointCount = 0;
  int expressionLength = strlen(expression);

  if (expressionLength != 0) {
    if (expression[0] == '^' || expression[0] == '.' || expression[0] == '/' ||
        expression[0] == '*' || expression[0] == ')' ||
        expression[currentIndex] == '%') {
      errorFlag = FAIL;
    } else {
      int openBracketCount = 0;
      while (expression[currentIndex] != '\0') {
        char currentChar = expression[currentIndex];
        char nextChar = expression[currentIndex + 1];

        if (((currentChar > ')' && currentChar <= '/') || currentChar == '^' ||
             currentChar == '%') &&
            ((nextChar >= ')' && nextChar <= '/') || nextChar == '^' ||
             nextChar == '%')) {
          if ((currentChar != ')' && expression[currentIndex - 1] != ')') ||
              (currentChar != ')' && nextChar != ')'))
            break;
        } else if (currentChar == '(' &&
                   ((nextChar >= ')' && nextChar <= '/') || nextChar == '^' ||
                    nextChar == '%') &&
                   (nextChar != '-' || nextChar != '+')) {
          break;
        } else if (currentChar == '*' || currentChar == '+' ||
                   currentChar == '/' || currentChar == '-') {
          decimalPointCount = 0;
        } else if (currentChar == '.') {
          decimalPointCount++;
          if (decimalPointCount > 1) {
            return FAIL;
            break;
          }
        } else if (currentChar == '(') {
          openBracketCount++;
        } else if (currentChar == ')') {
          if (openBracketCount > 0) {
            openBracketCount--;
          } else {
            break;
          }
        } else if (isdigit(currentChar) || currentChar == 'X') {
          numFlag = FAIL;
        }
        currentIndex++;

        if (currentIndex == expressionLength && openBracketCount == 0 &&
            numFlag == FAIL) {
          char lastChar = expression[currentIndex - 1];
          if (isdigit(lastChar) || lastChar == ')' || lastChar == 'X') {
            errorFlag = SUCCESS;
          }
        }
      }
    }
  }
  return errorFlag;
}

int plotValid(double xMax, double xMin, double yMax, double yMin) {
  int returnValue = SUCCESS;

  if (xMin >= xMax || yMin >= yMax) {
    returnValue = FAIL;
  }

  return returnValue;
}
