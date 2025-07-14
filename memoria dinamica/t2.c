#include <stdio.h>
#include <stdlib.h>

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

Alumno* leerAlumnos(const char *archivo, int *n) {
    FILE *fp = fopen(archivo, "rb");
    if (!fp) return NULL;
    fseek(fp, 0, SEEK_END);
    *n = ftell(fp) / sizeof(Alumno);
    rewind(fp);
    Alumno *a = (Alumno *)malloc(*n * sizeof(Alumno));
    fread(a, sizeof(Alumno), *n, fp);
    fclose(fp);
    return a;
}

int main() {
    int n = 3;
    Alumno *a = (Alumno *)malloc(n * sizeof(Alumno));
    for (int i = 0; i < n; i++) {
        printf("Nombre: ");
        scanf("%s", a[i].nombre);
        printf("Promedio: ");
        scanf("%f", &a[i].promedio);
    }

    guardarAlumnos("alumnos_dinamicos.bin", a, n);
    free(a);

    int m;
    Alumno *leidos = leerAlumnos("alumnos_dinamicos.bin", &m);
    Alumno *p = leidos;
    for (int i = 0; i < m; i++, p++)
        printf("Nombre: %s, Promedio: %.2f\n", p->nombre, p->promedio);

    free(leidos);
    return 0;
}
