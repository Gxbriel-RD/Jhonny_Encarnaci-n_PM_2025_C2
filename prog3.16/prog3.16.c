#include <stdio.h>
/* Calificaciones.
El programa, al recibir un grupo de calificaciones de un alumno, obtiene el promedio de calificaciones de cada uno de ellos y, adem�s, los alumnos con el mejor
y peor promedio.
I, MAT, MAMAT y MEMAT: variables de tipo entero.
CAL, SUM, MAPRO, MEPRO y PRO: variables de tipo real.*/

int main(void)
{
    int I, MAT, MAMAT = 0, MEMAT = 0;
    float SUM, PRO, CAL, MAPRO = 0.0, MEPRO = 11.0;

    printf("Ingrese la matr�cula del primer alumno:\t");
    scanf("%d", &MAT);

    while (MAT)
    {
        SUM = 0;
        for (I = 1; I <= 5; I++)
        {
            printf("\tIngrese la calificaci�n %d del alumno: ", I);
            scanf("%f", &CAL);
            SUM += CAL;
        }

        PRO = SUM / 5.0;
        printf("\nMatr�cula: %d\tPromedio: %5.2f\n", MAT, PRO);

        if (PRO > MAPRO)
        {
            MAPRO = PRO;
            MAMAT = MAT;
        }
        if (PRO < MEPRO)
        {
            MEPRO = PRO;
            MEMAT = MAT;
        }

        printf("\nIngrese la matr�cula del siguiente alumno (0 para terminar): ");
        scanf("%d", &MAT);
    }

    if (MAMAT != 0 && MEMAT != 0) {
        printf("\nAlumno con mejor promedio:\t%d\t%5.2f\n", MAMAT, MAPRO);
        printf("Alumno con peor promedio:\t%d\t%5.2f\n", MEMAT, MEPRO);
    } else {
        printf("\nNo se ingresaron alumnos.\n");
    }

    return 0;
}
