#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char cad[51]; // 50 caracteres + '\0'
    int i = 0, mi = 0, ma = 0;

    printf("\nIngrese la cadena de caracteres (máximo 50 caracteres): ");
    if (fgets(cad, sizeof(cad), stdin) == NULL)
    {
        printf("Error al leer la cadena.\n");
        return 1;
    }

    // Eliminar salto de línea si existe
    while (cad[i] != '\0')
    {
        if (cad[i] == '\n')
        {
            cad[i] = '\0';
            break;
        }
        i++;
    }

    // Resetear i para contar
    i = 0;

    while (cad[i] != '\0')
    {
        if (islower((unsigned char)cad[i]))
            mi++;
        else if (isupper((unsigned char)cad[i]))
            ma++;
        i++;
    }

    printf("\nNúmero de letras minúsculas: %d", mi);
    printf("\nNúmero de letras mayúsculas: %d\n", ma);

    return 0;
}
