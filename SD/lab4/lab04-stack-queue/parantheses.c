#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length)
{
  // 🤓
  int i;
  Stack *stack = createStack();
  for (i = 0; i < length; i++)
  {
    if (str[i] == '(')
    {
      push(stack, str[i]);
      continue;
    }
    if (str[i] == ')')
    {
      if (isStackEmpty(stack) == 1)
      {
        return 0;
      }
      if (top(stack) == '(')
      {
        pop(stack);
      }
    }
  }
  if (isStackEmpty(stack) == 0)
  {
    return 0;
  }
  return 1;

  // for (i = 0; i < length; i++)
  // {
  //   push(stack, str[i]);
  // }
  // int leftP = 0, rightP = 0;
  // while (stack->head != NULL)
  // {
  //   char c = top(stack);
  //   pop(stack);
  //   if (strcmp(&c, "(") == 0)
  //   {
  //     leftP += 1;
  //   }
  //   else if (strcmp(&c, ")") == 0)
  //   {
  //     rightP += 1;
  //   }
  // }
  // if (rightP == leftP)
  // {
  //   return 1;
  // }
}

int main()
{
  int len;
  char buffer[MAX_INPUT_LEN];
  FILE *inputFile = fopen("input-parantheses.txt", "r");
  if (inputFile == NULL)
    return 1;

  while (fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL)
  {
    buffer[strcspn(buffer, "\r\n")] = 0;
    len = strlen(buffer);
    if (len == 0)
      break;

    if (isBalanced(buffer, len))
      printf("%s ---> is balanced.\n", buffer);
    else
      printf("%s ---> not balanced.\n", buffer);
  }

  fclose(inputFile);

  return 0;
}
