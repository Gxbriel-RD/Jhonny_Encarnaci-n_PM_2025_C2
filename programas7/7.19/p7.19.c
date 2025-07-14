#include <stdio.h>
#include <string.h>

int cuentap(char *);

int main(void)
{
    int i;
    char fra[50];
    printf("\nIngrese la línea de texto: ");
    if (fgets(fra, sizeof(fra), stdin) != NULL)
    {
        fra[strcspn(fra, "\n")] = '\0';
        strcat(fra, " ");
        i = cuentap(fra);
        printf("\nLa línea de texto tiene %d palabras\n", i);
    }
    return 0;
}

int cuentap(char *cad)
{
    int i = 0;
    char *cad0 = cad;

    while ((cad0 = strchr(cad0, ' ')) != NULL)
    {
        i++;
        cad0++;
    }
    return i;
}
