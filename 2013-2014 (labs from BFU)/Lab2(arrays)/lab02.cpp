// lab02.cpp: определяет точку входа для консольного приложения.

//Дана последовательность целых чисел {aj}j=1...n (n<=40). Упорядочить
//  элементы последовательности до первого отрицательного числа
//  (включительно) по невозрастанию, а остальные элементы - по неубыванию
//  количества четных цифр.

#include "stdafx.h"
#include<sstream>
#include<cstdlib>
#define B 40
using namespace std;


int sdigit(int n)
{int s=0, i;
for (i=0; n!= 0; i++)
{s=s+n%10;
n /= 10;
}
if (s<0) return -s;
return s;
}

void selection(int a[B], int n) 
{
for (int i = 0; i<=n ; i++) {
int min = i;
for(int j = i + 1; j <= n; j++) {
            if(sdigit(a[j]) < sdigit(a[min]))
                min = j;
        }
        if(min != i)
           swap(a[i], a[min]);
    }
for (int i=0; i<=n; i++)
{printf("%d\n", a[i]);}
/* */
for (int i = n+1; i<=B-1 ; i++) {
int max = i;
for(int j = i + 1; j <= B-1; j++) {
            if(sdigit(a[j]) > sdigit(a[max]))
               max = j;
        }
        if(max != i)
           swap(a[i], a[max]);
    }
for (int i=n+1; i<B; i++)
{printf("%d\n", a[i]);}
}

int _tmain(int argc, _TCHAR* argv[])
{int i, k=0, a[B], n;
for (i=20; i>=-19; i--)
{a[k]=i;
/* printf("%d\n", a[k]); */
k=k+1;}
for (i=0; i<=B-1; i++)
	if (a[i]<0) 
		{n=i;
		break;}
selection(a, n);
system("pause");
return 1;
}

