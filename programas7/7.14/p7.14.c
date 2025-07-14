#include <stdio.h>

/* Calcula longitud en forma recursiva.
El programa calcula de manera recursiva la longitud de la cadena sin utilizar
la función strlen. */

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
    // Eliminar salto de línea final
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
/* Esta función calcula la longitud de la cadena en forma recursiva. */
{
    if (cadena[0] == '\0')
        return 0;
    else
        return 1 + cuenta(&cadena[1]);
}
