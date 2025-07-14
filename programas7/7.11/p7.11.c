#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    char p, cad[51];  // 50 + 1 para el '\0'
    int n, len;

    printf("\nIngrese la cadena de caracteres (máximo 50): ");
    if (fgets(cad, sizeof(cad), stdin) == NULL)
    {
        printf("Error al leer la cadena.\n");
        return 1;
    }

    // Eliminar salto de línea si existe
    len = strlen(cad);
    if (len > 0 && cad[len - 1] == '\n')
        cad[len - 1] = '\0';

    printf("\nIngrese la posición en la cadena que desea verificar: ");
    if (scanf("%d", &n) != 1)
    {
        printf("Entrada inválida.\n");
        return 1;
    }

    if (n > 0 && n <= len)
    {
        p = cad[n - 1];
        if (islower((unsigned char)p))
            printf("\n%c es una letra minúscula\n", p);
        else
            printf("\n%c no es una letra minúscula\n", p);
    }
    else
    {
        printf("\nEl valor ingresado de n es incorrecto\n");
    }

    return 0;
}
