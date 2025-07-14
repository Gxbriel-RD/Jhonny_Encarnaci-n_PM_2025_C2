#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[30];
    float promedio;
} Alumno;

void guardarAlumnos(const char *archivo, Alumno *alumnos, int n) {
    FILE *fp = fopen(archivo, "wb");
    if (!fp) return;
    fwrite(alumnos, sizeof(Alumno), n, fp);
    fclose(fp);
}

int leerAlumnos(const char *archivo, Alumno **alumnos) {
    FILE *fp = fopen(archivo, "rb");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(Alumno);
    rewind(fp);
    *alumnos = (Alumno *)malloc(n * sizeof(Alumno));
    fread(*alumnos, sizeof(Alumno), n, fp);
    fclose(fp);
    return n;
}

void bubbleSortNombre(Alumno *a, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(a[j].nombre, a[j + 1].nombre) > 0) {
                Alumno temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

void bubbleSortPromedio(Alumno *a, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j].promedio > a[j + 1].promedio) {
                Alumno temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
}

void imprimir(Alumno *a, int n) {
    for (int i = 0; i < n; i++)
        printf("Nombre: %s, Promedio: %.2f\n", a[i].nombre, a[i].promedio);
}

int main() {
    Alumno datos[] = {{"Carlos", 85.2}, {"Ana", 90.4}, {"Luis", 78.9}, {"Bea", 92.1}};
    int n = 4;
    guardarAlumnos("alumnos.bin", datos, n);

    Alumno *alumnos = NULL;
    n = leerAlumnos("alumnos.bin", &alumnos);

    printf("Orden alfabético:\n");
    bubbleSortNombre(alumnos, n);
    imprimir(alumnos, n);

    printf("\nOrden por promedio:\n");
    bubbleSortPromedio(alumnos, n);
    imprimir(alumnos, n);

    free(alumnos);
    return 0;
}
