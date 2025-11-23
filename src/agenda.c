#include <stdio.h>
#include "agenda.h"

/**
 * Arreglos de cadenas para "traducir" los enums a texto legible.
 * Son 'static' para que solo sean visibles dentro de este archivo.
 */


static const char* NOMBRES_MESES[] = {
    "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};

static const char* NOMBRES_TIPO_TEL[] = {
    "Casa", "Movil", "Oficina", "Otro"
};


//La siguiente función inicializa la agenda poniendo el numero de contactos a 0
void iniciar_agenda(Agenda* agenda) {
    //se establece el contador interno de la agenda en 0
    agenda->num_contactos = 0;//variable que lleva la cuenta de cuantos contactos hay en la agenda
}

/**
 * Esta función agrega un nuevo contacto a la agenda.
 * Nota: Esta funcion recibe el contacto ya lleno
 */
void agregar_contacto(Agenda *agenda, Contacto c){
    //1. Verificar si hay espacio en la agenda
    if (agenda->num_contactos >= MAX_CONTACTS) {
        printf("Error: La agenda esta llena. No se pudo agregar a %s.\n", c.nombre);
        return; //Salimos de la función
    }

    //2. Si hay especio, copiar el contacto "c" en la suguiente posicion libre del arreglo.
    agenda->contactos[agenda->num_contactos] = c;

    //3. Incrementar el contador de contactos
    agenda->num_contactos++;
}

/**
 * Esta función sirve para buscar un contacto por nombre en la agenda 
 * y retorna la posición del contacto si exisite
 * En caso contrario retorna -1
 */
int buscar_contacto(Agenda *agenda, char *nombre){
    //Recorremos el arreglo de contactos SÓLO hasta el número de contactos existentes
    for (int i = 0; i < agenda->num_contactos; i++){
        // strcmp es una función que compara dos cadenas de caracteres
        // strcmo devuelve un 0 si las cadenas son iguales
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0){
            return i; //Retornamos la posición del contacto encontrado
        }
    }

    //Si el bucle for termina, significa que no se encontró el contacto
    return -1;
}

/**
 * Esta función  sirve para buscar un contacto por su número de telefono en la agenda
 * Retorna la posicion de es este si lo encuentra, o -1 si no
 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    for (int i = 0; i < agenda->num_contactos; i++){
        if (strcmp(agenda->contactos[i].telefono, telefono) == 0){
            return i; //Retornamos la posición del contacto encontrado
        }
    }
    return -1; //No se encontró el contacto
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma ascendente
 */
void ordenar_contactos(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre)>0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma descendente
 */
void ordenar_contactos_inv(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre)<0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Funcion auxiliar para imprimir solo UN contacto
 */
void mostrar_contacto(Contacto c){
    //Hacemos uso de los arreglos NOMBRES_MESES y NOMBRES_TIPO_TEL 
    //para mostrar los enums como texto legible y no como números
    printf("    Nombre: %s %s\n", c.nombre, c.apellido);
    printf("    Nacimiento: %d de %s\n", c.dia_nacimiento, NOMBRES_MESES[c.mes_nacimiento]);
    printf("    Telefono: %s (%s)\n", c.telefono, NOMBRES_TIPO_TEL[c.tip_num]);
    printf("--------------------------\n");
}


/**
 * Funcion auxiliar para leer un contacto 
 */
void leer_contacto(Contacto *c){
    int mes_temp, tipo_temp;

    printf("---Nuevo Contacto---\n");
    printf("Nombre: ");
    scanf("%29s", c->nombre); //Limitar la entrada a 29 caracteres para evitar psarnos del char[30]

    printf("Apellido: ");
    scanf("%29s", c->apellido);

    printf("Dia de nacimiento (1-31): ");
    scanf("%d", &c->dia_nacimiento);

    printf("Mes de nacimiento (1-12): ");
    scanf("%d", &mes_temp);
    //Convertimos de (1-12) a (0-11) para el enum
    c->mes_nacimiento = mes_temp - 1;

    printf("Telefono: ");
    scanf("%14s", &c->telefono); //Limitar la entrada a 14 caracteres para evitar pasarnos del char[15]

    printf("Tipo de telefono (1=Casa, 2=Movil, 3=Oficina, 4=Otro): ");
    scanf("%d", &tipo_temp);
    //Convertimos de (1-4) a (0-3) para el enum
    c->tip_num = tipo_temp - 1;
    printf("-------------------\n");
}

/**
 * Función que imprime todos los contactos de la agenda en pantalla
 */
void imprimir_agenda(Agenda agenda){
    printf("\n======= Agenda de Contactos (%d) =======\n", agenda.num_contactos);
    
    if (agenda.num_contactos == 0){
        printf("La agenda esta vacia.\n");
        return;
    } 

    //Recorremos la agenda y usamos la funcion auxiliar 
    //"mostrar_contacto" para cada uno de los contactos
    for (int i = 0; i<agenda.num_contactos; i++){
        mostrar_contacto(agenda.contactos[i]);
    }
    printf("=====================================\n");
}

/**
 * Función que sirve para cargar contactos escritos en un archivo a la agenda
 * Usando un formato como el siguiente: Ana|Perez|...|1
 */
void cargar_contactos(const char *filename, Agenda *agenda){
    FILE *archivo = fopen(filename, "r"); //"r" = read (leer)

    if (archivo == NULL){
        printf("Archivo '%s' no encontrado. Iniciando agenda vacia.\n", filename);
        iniciar_agenda(agenda);
        return;
    }

    //Si el archivo existe, borramos la agenda actual
    iniciar_agenda(agenda); //Esta es la funcion para iniciar la agenda desde 0

    Contacto temp; //Contacto temporal para ir leyendo los datos

    //Leemos linea por linea con el fomato de ejemplo antes mencionado "|"
    //el fscanf duevuelve 6 si pudo leer los 6 campos necesarios para un contacto
    while (agenda->num_contactos < MAX_CONTACTS &&
        fscanf(archivo, "%29[^|]|%29[^|]|%d|%d|%14[^|]|%d\n",
                temp.nombre,
                temp.apellido,
                &temp.dia_nacimiento,
                &temp.mes_nacimiento, //Se lee como int (0-11)
                temp.telefono,
                &temp.tip_num) == 6)  //Se lee como int (0-3)
    {
        //Si la lectura fue exitosa, agregamos el contacto a la agenda
        agregar_contacto(agenda, temp);
    }

    fclose(archivo); //Cerramos el archivo
    printf("Se cargaron %d contactos desde '%s'.\n", agenda->num_contactos, filename);
}

/**
 * Función que sirve para guardar todos los contactos de la agenda en un archivo
 */
void guardar_contactos(const char *filename, Agenda agenda){
    FILE *archivo = fopen(filename, "w"); //"w" = write (sobreescribir)

    if(archivo == NULL){
        printf("Error: No se pudo abrir/crear el archivo '%s'.\n", filename);
        return;
    }

    //Recorremos la agenda
    for (int i = 0; i < agenda.num_contactos; i++){
        Contacto c = agenda.contactos[i];

        // Escribimos en el archivo con formato de tubería '|'
        // Guardamos los enums como números (0-11 y 0-3)
        fprintf(archivo, "%s|%s|%d|%d|%s|%d\n",
                c.nombre,
                c.apellido,
                c.dia_nacimiento,
                c.mes_nacimiento,
                c.telefono,
                c.tip_num);
    }

    fclose(archivo);
    printf("Agenda guardada en '%s'.\n", filename);
}
