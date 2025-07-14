#include <stdio.h>
#include <string.h>

union datos {
    char celular[15];
    char correo[20];
};

typedef struct {
    int matricula;
    char nombre[20];
    char carrera[20];
    float promedio;
    union datos personales;
} alumno;

void Lectura(alumno *a);

int main(void)
{
    alumno a1 = {120, "María", "Contabilidad", 8.9, .personales.celular = "5-158-40-50"};
    alumno a2, a3;

    printf("Alumno 2\n");
    printf("Ingrese la matrícula: ");
    scanf("%d", &a2.matricula);
    while(getchar() != '\n'); // limpiar buffer

    printf("Ingrese el nombre: ");
    fgets(a2.nombre, sizeof(a2.nombre), stdin);
    a2.nombre[strcspn(a2.nombre, "\n")] = 0;

    printf("Ingrese la carrera: ");
    fgets(a2.carrera, sizeof(a2.carrera), stdin);
    a2.carrera[strcspn(a2.carrera, "\n")] = 0;

    printf("Ingrese el promedio: ");
    scanf("%f", &a2.promedio);
    while(getchar() != '\n');

    printf("Ingrese el correo electrónico: ");
    fgets(a2.personales.correo, sizeof(a2.personales.correo), stdin);
    a2.personales.correo[strcspn(a2.personales.correo, "\n")] = 0;

    printf("Alumno 3\n");
    Lectura(&a3);

    // Mostrar datos alumno 1
    printf("\nDatos del alumno 1\n");
    printf("Matrícula: %d\n", a1.matricula);
    printf("Nombre: %s\n", a1.nombre);
    printf("Carrera: %s\n", a1.carrera);
    printf("Promedio: %.2f\n", a1.promedio);
    printf("Celular: %s\n", a1.personales.celular);
    // Imprimir correo dará basura porque es unión y el último dato asignado fue celular
    // printf("Correo: %s\n", a1.personales.correo);

    // Mostrar datos alumno 2
    printf("\nDatos del alumno 2\n");
    printf("Matrícula: %d\n", a2.matricula);
    printf("Nombre: %s\n", a2.nombre);
    printf("Carrera: %s\n", a2.carrera);
    printf("Promedio: %.2f\n", a2.promedio);
    printf("Correo: %s\n", a2.personales.correo);
    // Si se imprime celular, mostrará basura, porque la unión guarda solo uno a la vez

    printf("Ingrese el teléfono celular del alumno 2: ");
    fgets(a2.personales.celular, sizeof(a2.personales.celular), stdin);
    a2.personales.celular[strcspn(a2.personales.celular, "\n")] = 0;

    printf("Celular ingresado: %s\n", a2.personales.celular);
    // Ahora correo contiene basura, porque la unión guarda solo un dato a la vez

    // Mostrar datos alumno 3
    printf("\nDatos del alumno 3\n");
    printf("Matrícula: %d\n", a3.matricula);
    printf("Nombre: %s\n", a3.nombre);
    printf("Carrera: %s\n", a3.carrera);
    printf("Promedio: %.2f\n", a3.promedio);
    printf("Celular: %s\n", a3.personales.celular);
    // printf("Correo: %s\n", a3.personales.correo); // también dará basura

    return 0;
}

void Lectura(alumno *a)
{
    printf("\nIngrese la matrícula: ");
    scanf("%d", &a->matricula);
    while(getchar() != '\n');

    printf("Ingrese el nombre: ");
    fgets(a->nombre, sizeof(a->nombre), stdin);
    a->nombre[strcspn(a->nombre, "\n")] = 0;

    printf("Ingrese la carrera: ");
    fgets(a->carrera, sizeof(a->carrera), stdin);
    a->carrera[strcspn(a->carrera, "\n")] = 0;

    printf("Ingrese el promedio: ");
    scanf("%f", &a->promedio);
    while(getchar() != '\n');

    printf("Ingrese el teléfono celular: ");
    fgets(a->personales.celular, sizeof(a->personales.celular), stdin);
    a->personales.celular[strcspn(a->personales.celular, "\n")] = 0;
}
