#include <stdio.h>
#include <string.h>

int main()
{
    char com[100];
    int count = 0, a = 0;
    printf("Enter comment: ");
    fgets(com, sizeof(com), stdin);

    if (com[0] == '/')
    {
        for (int i = 0; i < strlen(com) - 1; i++)
        {
            if ((com[i] >= 'A' && com[i] <= 'Z') || (com[i] >= 'a' && com[i] <= 'z'))
            {
                count++;
            }
        }
        if (com[1] == '/')
        {
            printf("It is a Single line Comment!");
        }
        else if (com[1] == '*')
        {
            for (int i = 2; i < strlen(com) - 1; i++)
            {
                if (com[i] == '*' && com[i + 1] == '/')
                {
                    printf("It is a Multiple line Comment!");
                    a = 1;
                    break;
                }
            }

            if (a == 0)
                printf("It is not a Comment!");
        }
        else
        {
            printf("It is not a Comment!");
        }
    }
    else
    {
        printf("It is not a Comment!");
    }
    printf("\nNumber of letters: %d", count);

    return 0;
}