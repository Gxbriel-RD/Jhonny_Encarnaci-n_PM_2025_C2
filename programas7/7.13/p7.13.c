#include <stdio.h>

int cuenta(char *); /* Prototipo de función. */

int main(void)
{
    int i;
    char cad[50];
    printf("\nIngrese la cadena de caracteres: ");
    if (fgets(cad, sizeof(cad), stdin) == NULL)
    {
        printf("Error al leer la cadena.\n");
        return 1;
    }

    // Eliminar salto de línea si existe
    int j = 0;
    while (cad[j] != '\0')
    {
        if (cad[j] == '\n')
        {
            cad[j] = '\0';
            break;
        }
        j++;
    }

    i = cuenta(cad);
    printf("\nLongitud de la cadena: %d\n", i);

    return 0;
}

int cuenta(char *cadena)
/* La función calcula la longitud de la cadena. */
{
    int c = 0;
    while (cadena[c] != '\0')
        c++;
    return c;
}
