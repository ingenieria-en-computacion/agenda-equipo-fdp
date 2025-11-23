#ifndef __AGENDA_H__
#define __AGENDA_H__

#include <stdio.h>
#include <string.h>

//Definir el numero maximo de contactos que seran 100 en nuestro caso
#define MAX_CONTACTS 100

enum TipoTelefono {CASA, MOVIL, OFICINA, OTRO}; 
enum Mes {ENERO, FEBRERO, MARZO, ABRIL, MAYO, JUNIO, JULIO, AGOSTO, SEPTIEMBRE, OCTUBRE, NOVIEMBRE, DICIEMBRE};

struct Persona{
    char nombre[30];    // Nombre de la persona
    char apellido[30];  // Apellido de la persona
    enum Mes mes_nacimiento;    // Mes de nacimiento
    int dia_nacimiento;         // Dia de nacimiento
    char telefono[15];      // Numero de telefono sin importar el tipo
    enum TipoTelefono tip_num;        // Tipo de telefono ())
};

typedef struct Persona Contacto;  //

typedef struct Agenda{
    Contacto contactos[MAX_CONTACTS];   // Arreglo para almacenar los contactos
    int num_contactos;                  // Lleva la cuenta de cuantos contactos están en la agenda 
} Agenda;

//Funciones para manejar la agenda
void iniciar_agenda(Agenda* agenda); //funcion para poner el contador de contactos en 0
void agregar_contacto(Agenda *agenda, Contacto c); //funcion para que el usuario agregue los datos de un nuevo contacto
void imprimir_contacto(const Agenda *agenda); //funcion para imrimir el contacto en la pantalla
int buscar_contacto(Agenda *agenda, char *nombre); //funcion para buscar un contacto por nombre
int buscar_contacto_x_telefono (Agenda *agenda, char telefono[]); //funcion para buscar un contacto por su número de telefono 
void ordenar_contactos(Agenda *agenda); //funcion para ordenar los contactos alfabeticamente por nombre
void mostrar_contactos(Contacto c); //funcion para mostrar todos los contactos de la agenda que se tienen
void leer_contacto  (Contacto *c); //funcion auxiliar para leer un contacto 
void cargar_contactos(const char *filename, Agenda *agenda);
void guardar_contactos(const char *filename, Agenda agenda);

// Prototipo para imprimir TODA la agenda
void imprimir_agenda(Agenda agenda);

// Prototipo para imprimir UN SOLO contacto
void mostrar_contacto(Contacto c);

#endif // __AGENDA_H__
