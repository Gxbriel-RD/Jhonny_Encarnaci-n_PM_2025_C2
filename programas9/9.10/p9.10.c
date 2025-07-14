#include <stdio.h>

typedef struct {
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void modifica(FILE *);

int main(void) {
    FILE *ar;
    if ((ar = fopen("ad1.dat", "r+b")) != NULL) {
        modifica(ar);
        fclose(ar);
    } else {
        printf("\nEl archivo no se puede abrir\n");
    }
    return 0;
}

void modifica(FILE *ap) {
    int d;
    alumno alu;

    printf("\nIngrese el número de registro que desea modificar: ");
    scanf("%d", &d);

    if (d < 1) {
        printf("\nNúmero de registro inválido.\n");
        return;
    }

    fseek(ap, (d - 1) * sizeof(alumno), SEEK_SET);

    if (fread(&alu, sizeof(alumno), 1, ap) != 1) {
        printf("\nNo se pudo leer el registro. Puede que no exista.\n");
        return;
    }

    printf("\nRegistro actual:");
    printf("\nMatrícula: %d", alu.matricula);
    printf("\nNombre: %s", alu.nombre);
    printf("\nCarrera: %d", alu.carrera);
    printf("\nPromedio actual: %.2f", alu.promedio);

    printf("\n\nIngrese el nuevo promedio del alumno: ");
    scanf("%f", &alu.promedio);

    fseek(ap, (d - 1) * sizeof(alumno), SEEK_SET);
    fwrite(&alu, sizeof(alumno), 1, ap);

    printf("\nRegistro actualizado correctamente.\n");
}
