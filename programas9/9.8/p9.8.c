#include <stdio.h>
#include <string.h>


typedef struct {
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void escribe(FILE *);

int main(void)
{
    FILE *ar;
    if ((ar = fopen("ad1.dat", "wb")) != NULL) {
        escribe(ar);
        fclose(ar);
    } else {
        printf("\nEl archivo no se puede abrir\n");
    }
    return 0;
}

void escribe(FILE *ap)
{
    alumno alu;
    int i = 0, r;

    printf("\n¿Desea ingresar información sobre alumnos? (Sí-1 No-0): ");
    scanf("%d", &r);
    getchar(); // Limpia el salto de línea pendiente en el búfer

    while (r)
    {
        i++;
        printf("Matrícula del alumno %d: ", i);
        scanf("%d", &alu.matricula);
        getchar();

        printf("Nombre del alumno %d: ", i);
        fgets(alu.nombre, sizeof(alu.nombre), stdin);
        alu.nombre[strcspn(alu.nombre, "\n")] = '\0'; // Elimina el salto de línea

        printf("Carrera del alumno %d: ", i);
        scanf("%d", &alu.carrera);

        printf("Promedio del alumno %d: ", i);
        scanf("%f", &alu.promedio);
        getchar();

        fwrite(&alu, sizeof(alumno), 1, ap);

        printf("\n¿Desea ingresar información sobre más alumnos? (Sí-1 No-0): ");
        scanf("%d", &r);
        getchar();
    }
}
