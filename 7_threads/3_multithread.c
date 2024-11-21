#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/* Переделать программу для доказательстава: sin*sin + cos*cos ==1
 * Квадрат синуса считать в одном потоке, косинуса во втором,
 * а результат суммировать в главной программе.*/

long double pow(long double a, int b)
{
  long double res = 1;
  for (;b > 0;--b)
  {
    res *= a;
  }
  return res;
}

long double factorial(long double n)
{
  long double res = 1;
  while (n)
  {
    res *= n;
    n--;
  }

  return res;
}

long double sin_sq, cos_sq;
void * thread_func1 (void * arg)
{
	fprintf (stderr, "thread1\n");

  /* coeff = (-1)^n x^(2n+1) / (2n+1)! */
  long double sin = 0;
  for(long double n = 0; n < 10; ++n)
  {
    long double coeff = pow(-1.0, n) * pow(*(long double*)arg, 2*n+1) / factorial(2*n+1);
    sin += coeff;
  }

  sin_sq = sin * sin;
	return (void*)&sin_sq;
}

void * thread_func2 (void * arg)
{
	fprintf (stderr, "thread2\n");

  /* coeff = (-1)^n x^(2n) / (2n)! */
  long double cos = 0;
  for(long double n = 0; n < 10; ++n)
  {
    long double coeff = pow(-1.0, n) * pow(*(long double*)arg, 2*n) / factorial(2*n);
    cos += coeff;
  }

  cos_sq = cos * cos;
	return (void*)&cos_sq;
}

long double a = 0;
void* thread_func3 (void* arg)
{
  a += *((double*)arg);

  return (void*)&a;
}

int main (void)
{
	pthread_t thread1, thread2;
  long double sin_arg = 3.5;
  long double cos_arg = 3.5;

	if (pthread_create (&thread1, NULL,
			                &thread_func1, (void*)&sin_arg) != 0)
	{
		fprintf (stderr, "Error (thread1)\n");
		return 1;
	}

	if (pthread_create (&thread2, NULL,
			                &thread_func2, (void*)&cos_arg) != 0) 
	{
		fprintf (stderr, "Error (thread2)\n");
		return 1;
	}
	
  long double res1 = 0;
  pthread_join(thread1, (void*)&res1);
  long double res2 = 0;
  pthread_join(thread2, (void*)&res2);

  printf("sin^2(%Lf) + cos^2(%Lf) = %Lf\n", sin_arg, cos_arg, cos_sq + sin_sq);

	return 0;
}
