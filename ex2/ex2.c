// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("text.txt", "r+");

    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed");
    }
    else if (rc == 0)
    {
        printf("child\n");
        while (1)
        {
            int c = fgetc(fp);
            if (feof(fp))
            {
                break;
            }
            printf("%c", c);
        }

        fprintf(fp, "child says moo\n");

        fclose(fp);
    }
    else if (rc > 0)
    {
        printf("Parent\n");
        while (1)
        {
            int c = fgetc(fp);
            if (feof(fp))
            {
                break;
            }
            printf("%c", c);
        }
        fprintf(fp, "parent says meow\n");
        fclose(fp);
    }

    return 0;
}
