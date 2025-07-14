#include <stdio.h>
#include <string.h>

void inverso(char *);

int main(void)
{
    char fra[50];
    if (fgets(fra, sizeof(fra), stdin) != NULL)
    {
        fra[strcspn(fra, "\n")] = '\0';
        inverso(fra);
        putchar('\n');
    }
    return 0;
}

void inverso(char *cadena)
{
    if (cadena[0] != '\0')
    {
        inverso(&cadena[1]);
        putchar(cadena[0]);
    }
}
