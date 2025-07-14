#include <stdio.h>

/* Archivos con variables enteras y reales.
   El programa almacena datos de un grupo de alumnos en un archivo. */

int main(void)
{
    int i, j, n, mat;
    float cal;
    FILE *ar;

    printf("\nIngrese el número de alumnos: ");
    scanf("%d", &n);
    // Se asume que el valor que ingresa el usuario está comprendido entre 1 y 35.

    if ((ar = fopen("arc8.txt", "w")) != NULL)
    {
        fprintf(ar, "%d\n", n); // Se escribe el número de alumnos

        for (i = 0; i < n; i++)
        {
            printf("\nIngrese la matrícula del alumno %d: ", i + 1);
            scanf("%d", &mat);
            fprintf(ar, "%d ", mat); // Se escribe la matrícula

            for (j = 0; j < 5; j++)
            {
                printf("Calificación %d: ", j + 1);
                scanf("%f", &cal);
                fprintf(ar, "%.2f ", cal); // Se escribe cada calificación
            }

            fprintf(ar, "\n"); // Nueva línea para el siguiente alumno
        }

        fclose(ar);
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }

    return 0;
}
