#include <stdio.h>

void add(int a, int b)
{
   int rs = a + b;
   printf("%d + %d = %d\n", a,b,rs);
}

int main(void)
{
    add(1,79); 

    return 0;
}
