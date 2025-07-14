#include <stdio.h>
#include <string.h>

char * inverso(char *);

int main(void)
{
    char fra[50];

    if (fgets(fra, sizeof(fra), stdin) != NULL)
    {
        fra[strcspn(fra, "\n")] = '\0';
        inverso(fra);
        printf("%s\n", fra);
    }

    return 0;
}

char * inverso(char *cadena)
{
    int i = 0, j = strlen(cadena) - 1;
    char cad;

    while (i < j)
    {
        cad = cadena[i];
        cadena[i] = cadena[j];
        cadena[j] = cad;
        i++;
        j--;
    }

    return cadena;
}
