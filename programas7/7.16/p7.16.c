#include <stdio.h>
#include <string.h>

/* Cuenta cadenas.
El programa, al recibir dos cadenas de caracteres, calcula e imprime cuántas
veces se encuentra la segunda cadena en la primera. */

int main(void)
{
    char cad1[50], cad2[50];
    char *cad0;
    int i = 0;

    printf("\nIngrese la primera cadena de caracteres: ");
    if (fgets(cad1, sizeof(cad1), stdin) == NULL) {
        printf("Error al leer la cadena.\n");
        return 1;
    }
    // Eliminar salto de línea final si existe
    cad1[strcspn(cad1, "\n")] = '\0';

    printf("\nIngrese la cadena a buscar: ");
    if (fgets(cad2, sizeof(cad2), stdin) == NULL) {
        printf("Error al leer la cadena.\n");
        return 1;
    }
    // Eliminar salto de línea final si existe
    cad2[strcspn(cad2, "\n")] = '\0';

    cad0 = cad1;  // Cad0 apunta al inicio de cad1
    while ((cad0 = strstr(cad0, cad2)) != NULL)
    {
        i++;
        cad0++; // Avanzar el puntero para buscar la siguiente ocurrencia
    }

    printf("\nEl número de veces que aparece la segunda cadena es: %d\n", i);

    return 0;
}
