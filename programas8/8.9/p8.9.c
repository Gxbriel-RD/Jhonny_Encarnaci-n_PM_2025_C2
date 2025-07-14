#include <stdio.h>
#include <string.h>

typedef struct {
    char zona[20];
    char calle[20];
    char colo[20];
} ubicacion;

typedef struct {
    char clave[6]; // 5 caracteres + '\0'
    float scu;
    float ste;
    char car[50];
    ubicacion ubi;
    float precio;
    char dispo;
} propiedades;

void Lectura(propiedades[], int);
void F1(propiedades[], int);
void F2(propiedades[], int);

int main(void)
{
    propiedades PROPIE[100];
    int TAM;

    do {
        printf("Ingrese el número de propiedades: ");
        scanf("%d", &TAM);
        while(getchar() != '\n');
    } while (TAM > 100 || TAM < 1);

    Lectura(PROPIE, TAM);
    F1(PROPIE, TAM);
    F2(PROPIE, TAM);

    return 0;
}

void Lectura(propiedades A[], int T)
{
    int I;
    for (I = 0; I < T; I++) {
        printf("\n\tIngrese datos de la propiedad %d\n", I + 1);

        printf("Clave: ");
        fgets(A[I].clave, 6, stdin);
        A[I].clave[strcspn(A[I].clave, "\n")] = 0;

        printf("Superficie cubierta: ");
        scanf("%f", &A[I].scu);
        while(getchar() != '\n');

        printf("Superficie terreno: ");
        scanf("%f", &A[I].ste);
        while(getchar() != '\n');

        printf("Características: ");
        fgets(A[I].car, 50, stdin);
        A[I].car[strcspn(A[I].car, "\n")] = 0;

        printf("\tZona: ");
        fgets(A[I].ubi.zona, 20, stdin);
        A[I].ubi.zona[strcspn(A[I].ubi.zona, "\n")] = 0;

        printf("\tCalle: ");
        fgets(A[I].ubi.calle, 20, stdin);
        A[I].ubi.calle[strcspn(A[I].ubi.calle, "\n")] = 0;

        printf("\tColonia: ");
        fgets(A[I].ubi.colo, 20, stdin);
        A[I].ubi.colo[strcspn(A[I].ubi.colo, "\n")] = 0;

        printf("Precio: ");
        scanf("%f", &A[I].precio);
        while(getchar() != '\n');

        printf("Disponibilidad (Venta-V Renta-R): ");
        scanf("%c", &A[I].dispo);
        while(getchar() != '\n');
    }
}

void F1(propiedades A[], int T)
{
    int I;
    printf("\n\t\tListado de Propiedades para Venta en Miraflores\n");
    for (I = 0; I < T; I++) {
        if ((A[I].dispo == 'V' || A[I].dispo == 'v') && strcmp(A[I].ubi.zona, "Miraflores") == 0) {
            if (A[I].precio >= 450000 && A[I].precio <= 650000) {
                printf("\nClave de la propiedad: %s\n", A[I].clave);
                printf("Superficie cubierta: %.2f\n", A[I].scu);
                printf("Superficie terreno: %.2f\n", A[I].ste);
                printf("Características: %s\n", A[I].car);
                printf("Calle: %s\n", A[I].ubi.calle);
                printf("Colonia: %s\n", A[I].ubi.colo);
                printf("Precio: %.2f\n", A[I].precio);
            }
        }
    }
}

void F2(propiedades A[], int T)
{
    int I;
    float li, ls;
    char zon[20];

    printf("\n\t\tListado de Propiedades para Renta\n");
    printf("Ingrese zona geográfica: ");
    fgets(zon, 20, stdin);
    zon[strcspn(zon, "\n")] = 0;

    printf("Ingrese el límite inferior del precio: ");
    scanf("%f", &li);
    while(getchar() != '\n');

    printf("Ingrese el límite superior del precio: ");
    scanf("%f", &ls);
    while(getchar() != '\n');

    for (I = 0; I < T; I++) {
        if ((A[I].dispo == 'R' || A[I].dispo == 'r') && strcmp(A[I].ubi.zona, zon) == 0) {
            if (A[I].precio >= li && A[I].precio <= ls) {
                printf("\nClave de la propiedad: %s\n", A[I].clave);
                printf("Superficie cubierta: %.2f\n", A[I].scu);
                printf("Superficie terreno: %.2f\n", A[I].ste);
                printf("Características: %s\n", A[I].car);
                printf("Calle: %s\n", A[I].ubi.calle);
                printf("Colonia: %s\n", A[I].ubi.colo);
                printf("Precio: %.2f\n", A[I].precio);
            }
        }
    }
}
