/* добавить вторую функцию, сравнивающую количество букв,
   добавить вызов различных функций в зависимости от аргумента программы
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check(char *a, char *b,
           int (*cmp)(const char *, const char *))
{
  printf("Проверка на совпадение.\n");
  if(!(*cmp)(a, b)) printf("Равны");
  else printf("Не равны");
}

int len_comp(const char* s1, const char* s2)
// If s1 is shorter than s2, return 0, 1 otherwise.
{
  return strlen(s1) > strlen(s2);
}

int main(int argc, char* argv[])
{
  char s1[80], s2[80];
  /* указатель на функцию */

  printf("Введите две строки.\n");
  fgets(s1, 80, stdin);
  fgets(s2, 80, stdin);

  if (argc <= 1)
  {
    // Default 
    int (*p)(const char *, const char *) = strcmp;
    check(s1, s2, p); /* Передает адрес функции strcmp
                       посредством указателя p */
  } else
  {
    // Comaparison is specified
    const char* comp_name = argv[1];
    if ( strcmp(comp_name, "strcmp") == 0 )
    {
      puts("strcmp");
      check(s1, s2, strcmp);
    } else
    {
      puts("len_cmp");
      check(s1, s2, len_comp);
    }
  }

  return 0;
}

