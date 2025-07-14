#include <stdio.h>

typedef struct {
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void ordena(FILE *, FILE *);

int main(void) {
    FILE *ar1 = fopen("ad5.dat", "r");
    FILE *ar2 = fopen("ad6.dat", "w");
    if ((ar1 != NULL) && (ar2 != NULL))
        ordena(ar1, ar2);
    else
        printf("\nEl o los archivos no se pudieron abrir");
    if (ar1) fclose(ar1);
    if (ar2) fclose(ar2);
    return 0;
}

void ordena(FILE *ap1, FILE *ap2) {
    alumno alu;
    int t, n, i;
    t = sizeof(alumno);
    fseek(ap1, 0, SEEK_END);
    n = (ftell(ap1) / t);
    for (i = n - 1; i >= 0; i--) {
        fseek(ap1, i * t, SEEK_SET);
        fread(&alu, t, 1, ap1);
        fwrite(&alu, t, 1, ap2);
    }
}
