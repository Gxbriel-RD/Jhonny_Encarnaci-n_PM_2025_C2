#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int i;
    double d;
    long l;
    char cad0[100], *cad1;

    printf("\nIngrese una cadena de caracteres (entero): ");
    fgets(cad0, sizeof(cad0), stdin);
    cad0[strcspn(cad0, "\n")] = '\0';  // Elimina el salto de línea

    i = atoi(cad0);
    printf("\n%s \t %d", cad0, i + 3);

    printf("\nIngrese una cadena de caracteres (decimal): ");
    fgets(cad0, sizeof(cad0), stdin);
    cad0[strcspn(cad0, "\n")] = '\0';

    d = atof(cad0);
    printf("\n%s \t %.2lf", cad0, d + 1.50);

    d = strtod(cad0, &cad1);
    printf("\nParte convertida con strtod: %.2lf", d + 1.50);
    if (*cad1 != '\0')
        printf("\nParte no numérica: %s", cad1);

    l = atol(cad0);
    printf("\n%s \t %ld", cad0, l + 10);

    l = strtol(cad0, &cad1, 0);
    printf("\nParte convertida con strtol: %ld", l + 10);
    if (*cad1 != '\0')
        printf("\nParte no numérica: %s", cad1);

    return 0;
}
