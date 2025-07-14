#include <stdio.h>
#include <string.h>
#include <ctype.h>

void minymay(char *cad); // Prototipo corregido

int main(void)
{
    int i, n;
    char FRA[20][50];

    printf("\nIngrese el número de filas del arreglo: ");
    scanf("%d", &n);
    getchar(); // Limpia el salto de línea pendiente del scanf

    for (i = 0; i < n; i++) {
        printf("Ingrese la línea %d de texto: ", i + 1);
        fgets(FRA[i], sizeof(FRA[i]), stdin);
        // Elimina el salto de línea si existe
        size_t len = strlen(FRA[i]);
        if (len > 0 && FRA[i][len - 1] == '\n')
            FRA[i][len - 1] = '\0';
    }

    printf("\n");
    for (i = 0; i < n; i++) {
        printf("\nCadena %d: %s", i + 1, FRA[i]);
        minymay(FRA[i]);
    }

    return 0;
}

void minymay(char *cadena)
{
    int i = 0, mi = 0, ma = 0;
    while (cadena[i] != '\0') {
        if (islower(cadena[i]))
            mi++;
        else if (isupper(cadena[i]))
            ma++;
        i++;
    }
    printf("\nNúmero de letras minúsculas: %d", mi);
    printf("\nNúmero de letras mayúsculas: %d\n", ma);
}
