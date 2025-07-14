#include <stdio.h>

typedef struct {
    int clave;
    int departamento;
    float salario;
    float ventas[12];
} empleado;

void incrementa(FILE *);

int main(void) {
    FILE *ar;
    if ((ar = fopen("ad5.dat", "r+b")) != NULL) {
        incrementa(ar);
        fclose(ar);
    } else {
        printf("\nEl archivo no se puede abrir\n");
    }
    return 0;
}

void incrementa(FILE *ap) {
    int i, j;
    float sum;
    empleado emple;
    int t = sizeof(empleado);
    fread(&emple, t, 1, ap);
    while (!feof(ap)) {
        i = ftell(ap) / t;
        sum = 0;
        for (j = 0; j < 12; j++)
            sum += emple.ventas[j];
        if (sum > 1000000) {
            emple.salario *= 1.10;
            fseek(ap, (i - 1) * t, SEEK_SET);
            fwrite(&emple, t, 1, ap);
            fseek(ap, i * t, SEEK_SET);
        }
        fread(&emple, t, 1, ap);
    }
}
