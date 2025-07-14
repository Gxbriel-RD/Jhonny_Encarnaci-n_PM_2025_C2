#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char c;
    char cad[50];
    int i = 0;
    float sum = 0.0;

    printf("\nDesea ingresar una cadena de caracteres (S/N)? ");
    c = getchar();

    // Limpiar el buffer después de getchar
    while (getchar() != '\n');

    while (c == 'S' || c == 's')
    {
        printf("\nIngrese la cadena de caracteres: ");
        if (fgets(cad, sizeof(cad), stdin) != NULL)
        {
            // Eliminar salto de línea final si existe
            size_t len = strlen(cad);
            if (len > 0 && cad[len - 1] == '\n')
                cad[len - 1] = '\0';

            sum += atof(cad);
            i++;
        }

        printf("\nDesea ingresar otra cadena de caracteres (S/N)? ");
        c = getchar();
        while (getchar() != '\n');  // limpiar buffer
    }

    if (i > 0)
    {
        printf("\nSuma: %.2f", sum);
        printf("\nPromedio: %.2f\n", sum / i);
    }
    else
    {
        printf("\nNo se ingresaron números.\n");
    }

    return 0;
}

