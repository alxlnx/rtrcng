#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
#define BUFF_SIZE 100

void flips(char* s) 
{
  if (*s == 0) return;

  int len = strlen(s) - 1;
  char* start = s;
  char* end = s + len;
  if (*end == '\n') 
  {
    end--;
  }
  char tmp;
  while(end > start)
  {
    tmp = *start;
    *start = *end;
    *end = tmp;

    start++;
    end--;
  }
}

int main() {
  char string1[BUFF_SIZE];
  char string2[BUFF_SIZE];
  printf("%s", "Enter the string:\n");
  fgets(string1, sizeof(string1), stdin);

  strcpy(string2, string1);
  printf("\n");
  int i = 0;
  for (char *p = strtok(string1," "); p != NULL; p = strtok(NULL, " "))
  {
    if (i % 2 == 1)
      printf("%s ", p);
    ++i;
  }
  i = 0;
  printf("\n");
  for (char *p = strtok(string2, " "); p != NULL; p = strtok(NULL, " "))
  {
    // flip here
    if (i % 2 == 0) 
    { 
      flips(p);
      printf("%s ", p);
    }
    ++i;
  }
}