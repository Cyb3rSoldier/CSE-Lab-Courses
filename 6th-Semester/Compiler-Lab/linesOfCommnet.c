#include <stdio.h>
#include <string.h>

int main()
{
    char comment[500];
    int lines = 0;
    printf("Enter comment:\n");

    while (fgets(comment, sizeof(comment), stdin))
    {
        lines++;

        if (lines == 1 && comment[0] == '/' && comment[1] == '/')
        {
            printf("\nThis is a single line comment!\n");
            printf("Number of lines: 1\n");
            return 0;
        }

        if (lines == 1 && comment[0] == '/' && comment[1] == '*')
        {
            if (strstr(comment, "*/") != NULL)
            {
                printf("\nThis is a multiple line comment!\n");
                printf("Number of lines: 1\n");
                return 0;
            }

            while (fgets(comment, sizeof(comment), stdin))
            {
                lines++;

                if (strstr(comment, "*/") != NULL)
                {
                    printf("\nThis is a multiple line comment!\n");
                    printf("Number of lines: %d\n", lines);
                    return 0;
                }
            }

            printf("\nInvalid comment\n");
            return 0;
        }

    
        if (lines == 1)
        {
            printf("\nNot a comment!\n");
            return 0;
        }
    }

    return 0;
}