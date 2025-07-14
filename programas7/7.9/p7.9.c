#include <stdio.h>
#include <string.h>

int cuenta(char *, char); // Prototipo correcto

int main(void)
{
    char car, cad[50];
    int res;

    printf("\nIngrese la cadena de caracteres: ");
    fgets(cad, sizeof(cad), stdin);

    // Eliminar el salto de línea si lo hay
    size_t len = strlen(cad);
    if (len > 0 && cad[len - 1] == '\n')
        cad[len - 1] = '\0';

    printf("\nIngrese el caracter: ");
    car = getchar();

    res = cuenta(cad, car);

    printf("\n\n%c se encuentra %d veces en la cadena %s\n", car, res, cad);

    return 0;
}

int cuenta(char *cad, char car)
{
    int i = 0, r = 0;
    while (cad[i] != '\0') {
        if (cad[i] == car)
            r++;
        i++;
    }
    return r;
}
