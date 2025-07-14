#include <stdio.h>
#include <string.h>

typedef struct {
    char noba[10];
    char nucu[10];
} banco;

typedef union {
    banco che;
    banco nomi;
    char venta;
} fpago;

typedef struct {
    char cnu[20];
    char col[20];
    char cp[6];
    char ciu[15];
} domicilio;

typedef struct {
    int num;
    char nom[20];
    float ven[12];
    domicilio domi;
    float sal;
    fpago pago;
    int cla;
} vendedor;

void Lectura(vendedor *, int);
void F1(vendedor *, int);
void F2(vendedor *, int);
void F3(vendedor *, int);
void F4(vendedor *, int);

int main(void)
{
    vendedor VENDEDORES[100];
    int TAM;

    do {
        printf("Ingrese el número de vendedores: ");
        scanf("%d", &TAM);
        while(getchar() != '\n');
    } while (TAM > 100 || TAM < 1);

    Lectura(VENDEDORES, TAM);
    F1(VENDEDORES, TAM);
    F2(VENDEDORES, TAM);
    F3(VENDEDORES, TAM);
    F4(VENDEDORES, TAM);
    printf("\n\tFIN DEL PROGRAMA\n");

    return 0;
}

void Lectura(vendedor A[], int T)
{
    int I, J;
    for (I = 0; I < T; I++) {
        printf("\n\tIngrese datos del vendedor %d\n", I + 1);

        printf("Número de vendedor: ");
        scanf("%d", &A[I].num);
        while(getchar() != '\n');

        printf("Nombre del vendedor: ");
        fgets(A[I].nom, 20, stdin);
        A[I].nom[strcspn(A[I].nom, "\n")] = 0;

        printf("Ventas del año:\n");
        for (J = 0; J < 12; J++) {
            printf("\tMes %d: ", J + 1);
            scanf("%f", &A[I].ven[J]);
            while(getchar() != '\n');
        }

        printf("Domicilio del vendedor:\n");

        printf("\tCalle y número: ");
        fgets(A[I].domi.cnu, 20, stdin);
        A[I].domi.cnu[strcspn(A[I].domi.cnu, "\n")] = 0;

        printf("\tColonia: ");
        fgets(A[I].domi.col, 20, stdin);
        A[I].domi.col[strcspn(A[I].domi.col, "\n")] = 0;

        printf("\tCódigo Postal: ");
        fgets(A[I].domi.cp, 6, stdin);
        A[I].domi.cp[strcspn(A[I].domi.cp, "\n")] = 0;

        printf("\tCiudad: ");
        fgets(A[I].domi.ciu, 15, stdin);
        A[I].domi.ciu[strcspn(A[I].domi.ciu, "\n")] = 0;

        printf("Salario del vendedor: ");
        scanf("%f", &A[I].sal);
        while(getchar() != '\n');

        printf("Forma de Pago (Banco-1 Nómina-2 Ventanilla-3): ");
        scanf("%d", &A[I].cla);
        while(getchar() != '\n');

        switch (A[I].cla) {
            case 1:
                printf("\tNombre del banco: ");
                fgets(A[I].pago.che.noba, 10, stdin);
                A[I].pago.che.noba[strcspn(A[I].pago.che.noba, "\n")] = 0;

                printf("\tNúmero de cuenta: ");
                fgets(A[I].pago.che.nucu, 10, stdin);
                A[I].pago.che.nucu[strcspn(A[I].pago.che.nucu, "\n")] = 0;
                break;

            case 2:
                printf("\tNombre del banco: ");
                fgets(A[I].pago.nomi.noba, 10, stdin);
                A[I].pago.nomi.noba[strcspn(A[I].pago.nomi.noba, "\n")] = 0;

                printf("\tNúmero de cuenta: ");
                fgets(A[I].pago.nomi.nucu, 10, stdin);
                A[I].pago.nomi.nucu[strcspn(A[I].pago.nomi.nucu, "\n")] = 0;
                break;

            case 3:
                A[I].pago.venta = 'S';
                break;

            default:
                printf("Opción inválida de forma de pago.\n");
                A[I].pago.venta = 'N';
                break;
        }
    }
}

void F1(vendedor A[], int T)
{
    int I, J;
    float SUM;

    printf("\n\t\tVentas Totales de los Vendedores\n");
    for (I = 0; I < T; I++) {
        SUM = 0.0;
        for (J = 0; J < 12; J++) {
            SUM += A[I].ven[J];
        }
        printf("\nVendedor: %d\nVentas: %.2f\n", A[I].num, SUM);
    }
}

void F2(vendedor A[], int T)
{
    int I, J;
    float SUM;

    printf("\n\t\tIncremento a los Vendedores con Ventas > 1,500,000$\n");
    for (I = 0; I < T; I++) {
        SUM = 0.0;
        for (J = 0; J < 12; J++) {
            SUM += A[I].ven[J];
        }
        if (SUM > 1500000.00) {
            A[I].sal *= 1.05;
            printf("\nNúmero de empleado: %d\nVentas: %.2f\nNuevo salario: %.2f\n",
                A[I].num, SUM, A[I].sal);
        }
    }
}

void F3(vendedor A[], int T)
{
    int I, J;
    float SUM;

    printf("\n\t\tVendedores con Ventas < 300,000\n");
    for (I = 0; I < T; I++) {
        SUM = 0.0;
        for (J = 0; J < 12; J++) {
            SUM += A[I].ven[J];
        }
        if (SUM < 300000.00) {
            printf("\nNúmero de empleado: %d\nNombre: %s\nVentas: %.2f\n",
                A[I].num, A[I].nom, SUM);
        }
    }
}

void F4(vendedor A[], int T)
{
    int I;
    printf("\n\t\tVendedores con Cuenta en el Banco\n");
    for (I = 0; I < T; I++) {
        if (A[I].cla == 1) {
            printf("\nNúmero de vendedor: %d\nBanco: %s\nCuenta: %s\n",
                A[I].num, A[I].pago.che.noba, A[I].pago.che.nucu);
        }
    }
}
