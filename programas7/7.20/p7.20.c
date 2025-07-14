#include <stdio.h>
#include <string.h>

int longitud(char *);

int main(void)
{
    int i, n, l = -1, p = -1, t;
    char cad[50], FRA[20][50];

    printf("\nIngrese el número de filas del arreglo: ");
    scanf("%d", &n);
    getchar();  // limpiar el buffer después de scanf

    for (i = 0; i < n; i++)
    {
        printf("Ingrese la línea %d de texto. Máximo 50 caracteres: ", i + 1);
        if (fgets(FRA[i], sizeof(FRA[i]), stdin) != NULL)
        {
            FRA[i][strcspn(FRA[i], "\n")] = '\0';  // eliminar salto de línea
        }
    }

    for (i = 0; i < n; i++)
    {
        strcpy(cad, FRA[i]);
        t = longitud(cad);
        if (t > l)
        {
            l = t;
            p = i;
        }
    }

    if (p != -1)
    {
        printf("\nLa cadena con mayor longitud es: ");
        puts(FRA[p]);
        printf("Longitud: %d\n", l);
    }

    return 0;
}

int longitud(char *cadena)
{
    int cue = 0;
    while (cadena[cue] != '\0')
        cue++;
    return cue;
}
