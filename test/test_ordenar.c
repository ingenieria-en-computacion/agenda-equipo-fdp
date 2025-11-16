#include "../src/agenda.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
    Agenda a;
    inicializar_agenda(&a);
    Contacto contacto1 = {"Ana", "Perez", 11, ENERO, "5555555555", CASA};
    Contacto contacto2 = {"Helena", "Rodriguez", 12, SEPTIEMBRE, "5555555556", MOVIL};
    Contacto contacto3 = {"Carlos", "Rodriguez", 12, SEPTIEMBRE, "5555555556", MOVIL};
    agregar_contacto(&a, contacto1);
    agregar_contacto(&a, contacto2);
    agregar_contacto(&a, contacto3);

    ordenar_contactos_inv(&a);

    assert(strcmp(a.contactos[0].nombre, "Carlos") == 0);
    assert(strcmp(a.contactos[1].nombre, "Helena") == 0);
    assert(strcmp(a.contactos[2].nombre, "Ana") == 0);

    printf("✅ test_ordenar: OK\n");
    return 0;
}
