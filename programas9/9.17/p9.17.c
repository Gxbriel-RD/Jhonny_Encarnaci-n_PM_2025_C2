#include <stdio.h>
#include <string.h>

void cambia(FILE *, FILE *);

int main(void) {
    FILE *ar = fopen("arc.txt", "r");
    FILE *ap = fopen("arc1.txt", "w");
    if (ar != NULL && ap != NULL) {
        cambia(ar, ap);
        fclose(ar);
        fclose(ap);
    } else {
        printf("No se pueden abrir los archivos\n");
    }
    return 0;
}

void cambia(FILE *ap1, FILE *ap2) {
    char cad[30], aux[30];
    char *cad1, *cad2;
    while (fgets(cad, 30, ap1) != NULL) {
        cad1 = cad;
        cad2 = strstr(cad1, "méxico");
        while (cad2 != NULL) {
            cad2[0] = 'M';
            int i = strlen(cad1);
            int j = strlen(cad2);
            int k = i - j;
            if (k) {
                strncpy(aux, cad1, k);
                aux[k] = '\0';
                strcat(aux, cad2);
                strcpy(cad1, aux);
            } else {
                strcpy(cad1, cad2);
            }
            cad2 = strstr(cad1, "méxico");
        }
        fputs(cad1, ap2);
    }
}
