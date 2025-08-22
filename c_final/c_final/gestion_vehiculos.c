/*
  gestion_vehiculos.c
  Sistema de gestión de vehiculos y cálculo de costo de viaje (terminal).
  - Persistencia simple: vehicles -> "vehicles.dat", general data -> "general.dat".
  - Estructuras y funciones modularizadas.
  - Lenguaje: C (C11).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PLACA_LEN 16
#define MAX_MARCA_LEN 64
#define MAX_MODELO_LEN 64
#define VEHICLE_DATA_FILE "vehicles.dat"
#define GENERAL_DATA_FILE "general.dat"

typedef enum { GASOLINA = 0, GASOIL = 1 } FuelType;

typedef struct {
    char placa[MAX_PLACA_LEN];
    char marca[MAX_MARCA_LEN];
    char modelo[MAX_MODELO_LEN];
    FuelType tipo_combustible;
    double km_x_galon_carretera;   // km per gallon highway
    double km_x_galon_ciudad;      // km per gallon city
    double costo_gomas;            // cost for a set of tires
    double km_gomas;               // km life of those tires
    double costo_seguro_12m;       // insurance cost per 12 months
    double costo_mantenimiento;    // cost per maintenance event
    double km_mantenimiento;       // interval km for maintenance
    double costo_vehiculo;         // purchase cost of vehicle
    double vida_util_anios;        // useful life in years
    double km_por_anio_promedio;   // average km per year
    // Nota: no almacenamos "depreciación" como dato fijo; se calcula dinámicamente
    bool used;                     // marca si el registro está ocupado
} Vehicle;

typedef struct {
    double precio_gasolina;
    double precio_gasoil;
} GeneralData;

/* ---------- Utilidades de entrada segura ---------- */

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void read_line(char *buf, size_t len) {
    if (fgets(buf, (int)len, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t l = strlen(buf);
    if (l > 0 && buf[l-1] == '\n') buf[l-1] = '\0';
}

/* Lee un double con validación simple */
static double read_double(const char *prompt, double min_allowed, double max_allowed) {
    double val;
    int rc;
    char line[128];
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            clear_stdin();
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }
        if (sscanf(line, "%lf", &val) != 1) {
            printf("Entrada invalida. Ingrese un numero.\n");
            continue;
        }
        if ((min_allowed != max_allowed) && (val < min_allowed || val > max_allowed)) {
            printf("Valor fuera de rango (%.2f - %.2f). Intente de nuevo.\n", min_allowed, max_allowed);
            continue;
        }
        return val;
    }
}

/* Lee un entero con validación */
static int read_int(const char *prompt, int min_allowed, int max_allowed) {
    int val;
    char line[128];
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) { clear_stdin(); continue; }
        if (sscanf(line, "%d", &val) != 1) {
            printf("Entrada invalida. Ingrese un entero.\n");
            continue;
        }
        if ((min_allowed != max_allowed) && (val < min_allowed || val > max_allowed)) {
            printf("Valor fuera de rango (%d - %d). Intente de nuevo.\n", min_allowed, max_allowed);
            continue;
        }
        return val;
    }
}

/* ---------- Persistencia (archivo) ---------- */

static Vehicle *vehicles = NULL;
static size_t vehicles_capacity = 0;
static size_t vehicles_count = 0;

static GeneralData general_data = { .precio_gasolina = 5.0, .precio_gasoil = 4.5 };

/* Carga vehiculos desde archivo (si existe) */
static void load_vehicles(void) {
    FILE *f = fopen(VEHICLE_DATA_FILE, "rb");
    if (!f) return; // no hay archivo aún
    // leer cantidad
    if (fread(&vehicles_count, sizeof(size_t), 1, f) != 1) { fclose(f); return; }
    vehicles_capacity = (vehicles_count > 0) ? vehicles_count : 1;
    vehicles = malloc(sizeof(Vehicle) * vehicles_capacity);
    if (!vehicles) { fclose(f); perror("malloc"); exit(EXIT_FAILURE); }
    if (fread(vehicles, sizeof(Vehicle), vehicles_count, f) != vehicles_count) {
        // si falla, reiniciar
        vehicles_count = 0;
        vehicles_capacity = 0;
        free(vehicles);
        vehicles = NULL;
    }
    fclose(f);
}

/* Guarda vehiculos a archivo */
static void save_vehicles(void) {
    FILE *f = fopen(VEHICLE_DATA_FILE, "wb");
    if (!f) { perror("No se pudo abrir archivo para guardar vehiculos"); return; }
    if (fwrite(&vehicles_count, sizeof(size_t), 1, f) != 1) { perror("fwrite"); fclose(f); return; }
    if (vehicles_count > 0) {
        if (fwrite(vehicles, sizeof(Vehicle), vehicles_count, f) != vehicles_count) {
            perror("fwrite");
        }
    }
    fclose(f);
}

/* Carga datos generales */
static void load_general_data(void) {
    FILE *f = fopen(GENERAL_DATA_FILE, "rb");
    if (!f) return;
    if (fread(&general_data, sizeof(GeneralData), 1, f) != 1) {
        // mantener valores por defecto
    }
    fclose(f);
}

/* Guarda datos generales */
static void save_general_data(void) {
    FILE *f = fopen(GENERAL_DATA_FILE, "wb");
    if (!f) { perror("No se pudo abrir archivo para guardar datos generales"); return; }
    if (fwrite(&general_data, sizeof(GeneralData), 1, f) != 1) {
        perror("fwrite");
    }
    fclose(f);
}

/* Asegura capacidad para n+1 vehiculos */
static void ensure_vehicle_capacity(void) {
    if (vehicles_capacity == 0) {
        vehicles_capacity = 8;
        vehicles = malloc(sizeof(Vehicle) * vehicles_capacity);
        if (!vehicles) { perror("malloc"); exit(EXIT_FAILURE); }
    } else if (vehicles_count >= vehicles_capacity) {
        vehicles_capacity *= 2;
        vehicles = realloc(vehicles, sizeof(Vehicle) * vehicles_capacity);
        if (!vehicles) { perror("realloc"); exit(EXIT_FAILURE); }
    }
}

/* Busca indice por placa (exacta) */
static int find_vehicle_index_by_placa(const char *placa) {
    for (size_t i = 0; i < vehicles_count; ++i) {
        if (vehicles[i].used && strcmp(vehicles[i].placa, placa) == 0) return (int)i;
    }
    return -1;
}

/* Lista vehiculos */
static void list_vehicles(void) {
    if (vehicles_count == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    printf("Lista de vehiculos:\n");
    printf("%-6s  %-12s  %-12s  %-8s  Km/gal(C)  Km/gal(U)\n",
           "Índice", "Placa", "Marca", "Comb.");
    for (size_t i = 0; i < vehicles_count; ++i) {
        if (!vehicles[i].used) continue;
        printf("%-6zu  %-12s  %-12s  %-8s  %-9.2f  %-9.2f\n",
               i,
               vehicles[i].placa,
               vehicles[i].marca,
               (vehicles[i].tipo_combustible == GASOLINA) ? "Gas." : "Gasoil",
               vehicles[i].km_x_galon_carretera,
               vehicles[i].km_x_galon_ciudad);
    }
}

/* Imprime datos completos de un vehiculo */
static void print_vehicle(const Vehicle *v) {
    if (!v) return;
    printf("Placa: %s\nMarca: %s\nModelo: %s\nTipo combustible: %s\n"
           "Km/galon (carretera): %.3f\nKm/galon (ciudad): %.3f\n"
           "Costo gomas (por set): %.2f | Vida gomas (km): %.2f\n"
           "Costo seguro (12m): %.2f\nCosto mantenimiento: %.2f | Cada: %.2f km\n"
           "Costo vehiculo: %.2f\nVida util (años): %.2f\nKm por año promedio: %.2f\n",
           v->placa,
           v->marca,
           v->modelo,
           (v->tipo_combustible == GASOLINA) ? "Gasolina" : "Gasoil",
           v->km_x_galon_carretera,
           v->km_x_galon_ciudad,
           v->costo_gomas,
           v->km_gomas,
           v->costo_seguro_12m,
           v->costo_mantenimiento,
           v->km_mantenimiento,
           v->costo_vehiculo,
           v->vida_util_anios,
           v->km_por_anio_promedio);
}

/* ---------- Operaciones CRUD de vehiculos ---------- */

static void create_vehicle(void) {
    Vehicle v;
    memset(&v, 0, sizeof(Vehicle));
    v.used = true;

    printf("Crear nuevo vehiculo\n");
    printf("Ingrese placa (sin espacios, max %d): ", MAX_PLACA_LEN-1);
    read_line(v.placa, sizeof(v.placa));

    if (strlen(v.placa) == 0) {
        printf("Placa no puede ser vacia.\n");
        return;
    }
    if (find_vehicle_index_by_placa(v.placa) != -1) {
        printf("Ya existe un vehiculo con esa placa.\n");
        return;
    }

    printf("Ingrese marca: ");
    read_line(v.marca, sizeof(v.marca));
    printf("Ingrese modelo: ");
    read_line(v.modelo, sizeof(v.modelo));

    int tipo = read_int("Tipo combustible (0=Gasolina, 1=Gasoil): ", 0, 1);
    v.tipo_combustible = (tipo == 0) ? GASOLINA : GASOIL;

    v.km_x_galon_carretera = read_double("Km por galon - Carretera: ", 0.1, 10000.0);
    v.km_x_galon_ciudad = read_double("Km por galon - Ciudad: ", 0.1, 10000.0);

    v.costo_gomas = read_double("Costo gomas (por set): ", 0.0, 1e12);
    v.km_gomas = read_double("Km de vida util de las gomas: ", 1.0, 1e9);

    v.costo_seguro_12m = read_double("Costo seguro (12 meses): ", 0.0, 1e12);

    v.costo_mantenimiento = read_double("Costo por evento de mantenimiento: ", 0.0, 1e12);
    v.km_mantenimiento = read_double("Km entre mantenimientos: ", 1.0, 1e9);

    v.costo_vehiculo = read_double("Costo vehiculo: ", 0.0, 1e12);
    v.vida_util_anios = read_double("Vida util (años): ", 0.1, 1000.0);
    v.km_por_anio_promedio = read_double("Km por año promedio: ", 1.0, 1e9);

    ensure_vehicle_capacity();
    vehicles[vehicles_count++] = v;
    save_vehicles();
    printf("vehiculo agregado correctamente.\n");
}

static void delete_vehicle(void) {
    list_vehicles();
    if (vehicles_count == 0) return;
    int idx = read_int("Ingrese indice del vehiculo a borrar: ", 0, (int)vehicles_count-1);
    if (idx < 0 || (size_t)idx >= vehicles_count || !vehicles[idx].used) {
        printf("Índice invalido o vehiculo no existe.\n");
        return;
    }
    printf("Vas a borrar:\n");
    print_vehicle(&vehicles[idx]);
    char resp[8];
    printf("Confirmar borrado (s/N): ");
    read_line(resp, sizeof(resp));
    if (resp[0]=='s' || resp[0]=='S') {
        // para simplicidad hacemos compactación: mover último al lugar
        vehicles[idx] = vehicles[--vehicles_count];
        printf("vehiculo borrado.\n");
        save_vehicles();
    } else {
        printf("Operacion cancelada.\n");
    }
}

static void modify_vehicle(void) {
    list_vehicles();
    if (vehicles_count == 0) return;
    int idx = read_int("Ingrese indice del vehiculo a modificar: ", 0, (int)vehicles_count-1);
    if (idx < 0 || (size_t)idx >= vehicles_count || !vehicles[idx].used) {
        printf("Índice invalido.\n");
        return;
    }
    Vehicle *v = &vehicles[idx];
    printf("Modificando vehiculo (dejar campo vacio para mantener valor).\n");
    printf("Placa (%s): ", v->placa);
    char tmp[128];
    read_line(tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(v->placa, tmp, MAX_PLACA_LEN);

    printf("Marca (%s): ", v->marca); read_line(tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(v->marca, tmp, MAX_MARCA_LEN);

    printf("Modelo (%s): ", v->modelo); read_line(tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(v->modelo, tmp, MAX_MODELO_LEN);

    printf("Tipo combustible (%s) 0=Gasolina,1=Gasoil (enter para mantener): ",
           (v->tipo_combustible==GASOLINA) ? "Gasolina" : "Gasoil");
    read_line(tmp, sizeof(tmp));
    if (strlen(tmp) > 0) {
        int t;
        if (sscanf(tmp, "%d", &t) == 1 && (t==0 || t==1)) v->tipo_combustible = (t==0?GASOLINA:GASOIL);
    }

    printf("Km/galon carretera (%.3f): ", v->km_x_galon_carretera); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->km_x_galon_carretera=x; }

    printf("Km/galon ciudad (%.3f): ", v->km_x_galon_ciudad); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->km_x_galon_ciudad=x; }

    printf("Costo gomas (%.2f): ", v->costo_gomas); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->costo_gomas=x; }

    printf("Km gomas (%.2f): ", v->km_gomas); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->km_gomas=x; }

    printf("Costo seguro 12m (%.2f): ", v->costo_seguro_12m); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->costo_seguro_12m=x; }

    printf("Costo mantenimiento (%.2f): ", v->costo_mantenimiento); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->costo_mantenimiento=x; }

    printf("Km mantenimiento (%.2f): ", v->km_mantenimiento); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->km_mantenimiento=x; }

    printf("Costo vehiculo (%.2f): ", v->costo_vehiculo); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->costo_vehiculo=x; }

    printf("Vida util años (%.2f): ", v->vida_util_anios); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->vida_util_anios=x; }

    printf("Km por año promedio (%.2f): ", v->km_por_anio_promedio); read_line(tmp, sizeof(tmp));
    if (strlen(tmp)>0) { double x; if (sscanf(tmp,"%lf",&x)==1) v->km_por_anio_promedio=x; }

    save_vehicles();
    printf("vehiculo modificado y guardado.\n");
}

/* ---------- Gestión datos generales ---------- */
static void manage_general_data(void) {
    printf("Datos generales actuales:\n");
    printf("Precio gasolina: %.3f\n", general_data.precio_gasolina);
    printf("Precio gasoil:   %.3f\n", general_data.precio_gasoil);
    char line[128];
    printf("Ingrese nuevo precio gasolina (enter para mantener): ");
    read_line(line, sizeof(line));
    if (strlen(line) > 0) {
        double x; if (sscanf(line, "%lf", &x) == 1) general_data.precio_gasolina = x;
    }
    printf("Ingrese nuevo precio gasoil (enter para mantener): ");
    read_line(line, sizeof(line));
    if (strlen(line) > 0) {
        double x; if (sscanf(line, "%lf", &x) == 1) general_data.precio_gasoil = x;
    }
    save_general_data();
    printf("Datos generales guardados.\n");
}

/* ---------- Cálculos de costos ---------- */

/*
  Estrategia de cálculo (por km):
  - Costo gomas por km = costo_gomas / km_gomas
  - Costo mantenimiento por km = costo_mantenimiento / km_mantenimiento
  - Costo seguro por km = costo_seguro_12m / km_por_anio_promedio  (suponemos seguro por 12m; lo prorrateamos por km/año)
  - Costo vehiculo por km = costo_vehiculo / (vida_util_anios * km_por_anio_promedio)
  - Combustible: calcular km en ciudad y carretera; obtener galones necesarios y multiplicar por precio del combustible (según tipo)
*/

/* Calcula y muestra desgloses y totales */
static void calcular_costo_viaje(void) {
    if (vehicles_count == 0) {
        printf("No hay vehiculos registrados. Cree uno primero.\n");
        return;
    }
    list_vehicles();
    int idx = read_int("Seleccione indice del vehiculo para calcular viaje: ", 0, (int)vehicles_count-1);
    if (idx < 0 || (size_t)idx >= vehicles_count || !vehicles[idx].used) {
        printf("Índice invalido.\n");
        return;
    }
    Vehicle *v = &vehicles[idx];

    double km_viaje = read_double("Ingrese kilometros totales del viaje: ", 0.1, 1e9);
    double pct_ciudad = read_double("Porcentaje de km en ciudad (0 - 100): ", 0.0, 100.0);

    double km_ciudad = km_viaje * (pct_ciudad / 100.0);
    double km_carretera = km_viaje - km_ciudad;

    // combustible necesario (galones)
    double gal_ciudad = 0.0, gal_carretera = 0.0;
    if (v->km_x_galon_ciudad <= 0.0 || v->km_x_galon_carretera <= 0.0) {
        printf("Valores de consumo invalidos en el vehiculo.\n");
        return;
    }
    gal_ciudad = km_ciudad / v->km_x_galon_ciudad;
    gal_carretera = km_carretera / v->km_x_galon_carretera;
    double gal_total = gal_ciudad + gal_carretera;

    double precio_combustible = (v->tipo_combustible == GASOLINA) ? general_data.precio_gasolina : general_data.precio_gasoil;
    double costo_combustible = gal_total * precio_combustible;

    // Costo gomas
    double costo_gomas_viaje = 0.0;
    if (v->km_gomas > 0.0) costo_gomas_viaje = (km_viaje / v->km_gomas) * v->costo_gomas;

    // Costo mantenimiento
    double costo_mantenimiento_viaje = 0.0;
    if (v->km_mantenimiento > 0.0) costo_mantenimiento_viaje = (km_viaje / v->km_mantenimiento) * v->costo_mantenimiento;

    // Costo seguro prorrateado por km; usamos km por año para convertir seguro 12m -> costo por km
    double costo_seguro_viaje = 0.0;
    if (v->km_por_anio_promedio > 0.0) {
        double costo_seguro_por_km = v->costo_seguro_12m / v->km_por_anio_promedio;
        costo_seguro_viaje = costo_seguro_por_km * km_viaje;
    }

    // Costo vehiculo (depreciación) prorrateado por km: costo / (vida_util_anios * km_por_anio_promedio)
    double costo_vehiculo_viaje = 0.0;
    if (v->vida_util_anios > 0.0 && v->km_por_anio_promedio > 0.0) {
        double km_vida_total = v->vida_util_anios * v->km_por_anio_promedio;
        if (km_vida_total > 0.0) {
            double costo_por_km = v->costo_vehiculo / km_vida_total;
            costo_vehiculo_viaje = costo_por_km * km_viaje;
        }
    }

    double costo_total = costo_combustible + costo_gomas_viaje + costo_mantenimiento_viaje + costo_seguro_viaje + costo_vehiculo_viaje;
    double costo_por_km = (km_viaje > 0.0) ? (costo_total / km_viaje) : 0.0;

    // Mostrar desglose
    printf("\n--- Resultado desglosado para el vehiculo %s (%s %s) ---\n",
           v->placa, v->marca, v->modelo);
    printf("Km totales: %.2f (Ciudad: %.2f | Carretera: %.2f | %%Ciudad: %.2f)\n",
           km_viaje, km_ciudad, km_carretera, pct_ciudad);
    printf("Galones necesarios: %.3f (Ciudad: %.3f | Carretera: %.3f)\n",
           gal_total, gal_ciudad, gal_carretera);
    printf("Precio combustible usado: %.3f (por unidad)\n", precio_combustible);
    printf("\nDesglose de costos:\n");
    printf("  3.4.1 Costo de gomas:       %.2f\n", costo_gomas_viaje);
    printf("  3.4.2 Costo de seguro:      %.2f\n", costo_seguro_viaje);
    printf("  3.4.3 Costo de combustible: %.2f\n", costo_combustible);
    printf("  3.4.4 Costo mantenimiento:  %.2f\n", costo_mantenimiento_viaje);
    printf("  3.4.5 Costo vehiculo:       %.2f\n", costo_vehiculo_viaje);
    printf("--------------------------------------\n");
    printf("Costo total viaje: %.2f\n", costo_total);
    printf("Costo por km: %.4f\n", costo_por_km);
    printf("--------------------------------------\n");
}

/* ---------- Menú principal ---------- */

static void show_main_menu(void) {
    printf("\n===== Sistema de Gestion de vehiculos =====\n");
    printf("1) Gestion de vehiculo - Crear\n");
    printf("2) Borrar vehiculo\n");
    printf("3) Modificar vehiculo\n");
    printf("4) Listar vehiculos\n");
    printf("5) Gestion de datos generales (combustible)\n");
    printf("6) Calculo costo viaje\n");
    printf("7) Ver detalles vehiculo (por indice)\n");
    printf("0) Salir\n");
    printf("Elija una opcion: ");
}

/* Inicialización (cargar datos) */
static void init_system(void) {
    load_general_data();
    load_vehicles();
}

/* Liberar recursos */
static void free_system(void) {
    if (vehicles) free(vehicles);
}

/* Acción: ver detalles vehiculo por indice */
static void show_vehicle_details(void) {
    list_vehicles();
    if (vehicles_count == 0) return;
    int idx = read_int("Ingrese indice para ver detalles: ", 0, (int)vehicles_count-1);
    if (idx < 0 || (size_t)idx >= vehicles_count || !vehicles[idx].used) {
        printf("Índice invalido.\n");
        return;
    }
    print_vehicle(&vehicles[idx]);
}

/* ---------- main ---------- */

int main(void) {
    init_system();
    while (1) {
        show_main_menu();
        int opt = read_int("", -1000, 1000); // lee la opcion
        switch (opt) {
            case 1: create_vehicle(); break;
            case 2: delete_vehicle(); break;
            case 3: modify_vehicle(); break;
            case 4: list_vehicles(); break;
            case 5: manage_general_data(); break;
            case 6: calcular_costo_viaje(); break;
            case 7: show_vehicle_details(); break;
            case 0:
                printf("Saliendo. Guardando datos...\n");
                save_vehicles();
                save_general_data();
                free_system();
                return 0;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    }
    return 0;
}
