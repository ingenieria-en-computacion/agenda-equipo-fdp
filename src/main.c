#include <stdio.h>
#include "agenda.h"

// El nombre del archivo donde se guardan los datos
const char* NOMBRE_ARCHIVO = "mi_agenda.dat";

int main() {
    Agenda mi_agenda;
    int opcion, posicion;
    char busqueda[30];
    
    // 1. Cargar datos al iniciar
    cargar_contactos(NOMBRE_ARCHIVO, &mi_agenda);

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Agregar contacto\n");
        printf("2. Mostrar todos los contactos\n");
        printf("3. Buscar contacto por nombre\n");
        printf("4. Ordenar (A-Z)\n");
        printf("5. Salir (y Guardar)\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: { // Se usan llaves {} para declarar variables dentro de un case
                Contacto nuevo_contacto;
                leer_contacto(&nuevo_contacto); // Pide datos al usuario
                agregar_contacto(&mi_agenda, nuevo_contacto); // Agrega a la agenda
                printf("¡Contacto agregado!\n");
                break;
            }
            case 2:
                // Le pasamos la 'mi_agenda' 
                imprimir_agenda(mi_agenda);
                break;
            case 3:
                printf("Nombre a buscar: ");
                scanf("%29s", busqueda);
                posicion = buscar_contacto(&mi_agenda, busqueda);
                if (posicion != -1) {
                    printf("¡Contacto encontrado en la posicion %d!\n", posicion);
                    mostrar_contacto(mi_agenda.contactos[posicion]);
                } else {
                    printf("Contacto no encontrado.\n");
                }
                break;
            case 4:
                ordenar_contactos(&mi_agenda);
                printf("Agenda ordenada.\n");
                break;
            case 5:
                // Le pasamos la 'mi_agenda' para guardarla
                guardar_contactos(NOMBRE_ARCHIVO, mi_agenda);
                printf("Datos guardados. ¡Adios!\n");
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }

    } while(opcion != 5);

    return 0;
}
