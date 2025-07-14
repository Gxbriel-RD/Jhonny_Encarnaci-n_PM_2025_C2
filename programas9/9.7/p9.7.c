#include <stdio.h>

/* Archivos con variables enteras y reales.
   El programa lee información de los alumnos desde un archivo usando una función. */

void promedio(FILE *); // Prototipo de función

int main(void)
{
    FILE *ar;

    if ((ar = fopen("arc9.txt", "r")) != NULL)
    {
        promedio(ar);  // Llamada a la función con el archivo como parámetro
        fclose(ar);
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }

    return 0;
}

void promedio(FILE *ar1)
/* Esta función lee los datos de los alumnos desde un archivo,
   e imprime tanto la matrícula como el promedio de cada alumno. */
{
    int i, j, n, mat;
    float pro, cal;

    fscanf(ar1, "%d", &n);

    for (i = 0; i < n; i++)
    {
        fscanf(ar1, "%d", &mat);
        printf("Matrícula: %d\t", mat);

        pro = 0;
        for (j = 0; j < 5; j++)
        {
            fscanf(ar1, "%f", &cal);
            pro += cal;
        }

        printf("Promedio: %.2f\n", pro / 5);
    }
}
