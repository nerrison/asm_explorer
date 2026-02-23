#include <stdio.h>

#define SIZE 6

int main(void)
{
    int arr [SIZE]={12,3,4,5};
    int cpyArr[SIZE];

    for ( int i = 0; i <SIZE; i++)
    {
        cpyArr[i]= arr[i];

        if (arr[i]==0)
        {
         printf("> NULL\n");
        }
        else
            printf("> %d\n", cpyArr[i]<<1);
    }
}