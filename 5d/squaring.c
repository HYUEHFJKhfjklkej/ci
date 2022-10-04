#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main()
{
    int n, data[NMAX];
    input(data, &n);
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n)
{
    if(scanf("%d", n) == 1){
        for(int *p = a; p - a < *n; p++)
        {
        scanf("%d", p);
        }
    } else {
        printf("n/a");
    }
}

void output(int *a, int n)
{
   for (int i = 0 ; i < n; i ++)
   {
       if ((n-1) == i){
            printf ("%d", a[i]);
       } else{
           printf ("%d ", a[i]);
       }
    
   }

}

void squaring(int *a, int n)
{
    for (int i = 0 ; i < n; i ++)
    {
        a[i]*=a[i];
    }
    
}

