#include <stdio.h>
int main()
{
    int a, b, c;
    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    printf("Enter the value of c: ");
    scanf("%d", &c);
    if (a > b && a > c)
    {
        printf("A is greater!");
    }
    else if (b > a && b > c)
    {
        printf("B is greater!");
    }
    else
    {
        printf("C is greater!");
    }
    return 0;
}