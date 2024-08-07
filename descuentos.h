/* Fichero  en que irán las funciones del módulo descuentos que se necesiten en otros modulos*/

#include "Devoluciones.h"

typedef enum { 
    codpro, cheqreg, // tipos de descuentos
    activo, inactivo, //estados de los descuentos 
    todos, esizon, //Aplicabilidad de los descuentos en los productos
    si,no // Estado de descuentos clientes 
}opciones;

/*TIPO DESCUENTOS*/
typedef struct
{
    char Id_cod[11],Descrip[51], Importe[4];
    opciones Tipo, Estado, Aplicabilidad;
}Descuentos;

/*TIPO DESCUENTOS CLIENTES*/
typedef struct 
{
    char Id_cliente[8],Id_cod[11], f_asignacion[11], f_caducidad[11]; //por comodidad las fechas serán del tipo "00/00/0000\0" que posteriormente será pasada al tipo fecha
    opciones Estado; //si para aplicado y no en caso contrario
}Descuentos_clientes;
//cabecera: void crear_fichero_descuentos()
//precondición: ninguna
//postcondición:crea el fichero descuentos.txt sino existe e imprime un mensaje de error si es el caso
void crear_fichero_descuentos();

//cabecera: void crear_fichero_descuentos_clientes()
//precondición: ninguna
//postcondición:crea el fichero descuentos_clientes.txt sino existe e imprime un mensaje de error si es el caso
void crear_fichero_descuentos_clientes();


 //cabecera:void carga_descuentos(Descuentos **d )
 //precondición: recibe como doble puntero el vector de estructuras
 //postcondición: Carga del fichero descuentos.txt a un vector de estructuras del tipo indicado
void carga_descuentos(Descuentos **,int*);

 //cabecera:void carga_descuentos_clientes(Descuentos_clientes **dc)
 //precondición: recibe como doble puntero el vector de estructuras
 //postcondición:Carga del fichero descuentos_clientes.txt a un vector de estructuras del tipo indicado
void carga_descuentos_clientes(Descuentos_clientes **,int*);

 //cabecera: void volcado_descuentos(Descuentos **d)
 //precondición:  recibe como doble puntero el vector de estructuras, inicializado
 //postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos_clientes.txt
void volcado_descuentos(Descuentos**,int*);

 //cabecera: void volcado_descuentos_clientes(Descuentos_clientes **dc)
 //precondición:  recibe como doble puntero el vector de estructuras, inicializado
 //postcondición: Vuelca el contenido del vector de estructuras al fichero descuentos_clientes.txt
void volcado_descuentos_clientes(Descuentos_clientes **,int*);

//cabecera: void listar_descuentos(Descuentos *d,int *n_desc)
//precondición: *d inicializado
//postcondición: lista los descuentos actuales en el vector
void listar_descuentos(Descuentos*,int*);

//cabecera:void listar_descuentos_propios(char*Id_cliente)
//precondición:sea Id cliente un punteroa  char que apunta a la información en la estructura
//postcomdición: imprime por pantalla la lsita de descuentos asignados a esa ID de cliente 
void listar_descuentos_propios(Descuentos**,Descuentos_clientes**,char *,int*);

//cabecera: int comprobar_descuento(Descuentos_clientes**dc,char Id_cod[])
//precondición: **dc inicializado e Id_cod un código de descuento válido
//postcondición: devuelve: 0 si está en vigor y 1 si no es válido por cualquier otra razón, además imprime por pantalla el error producido
int comprobar_descuento(Descuentos_clientes**,char *);

 //cabecera:
 //precondición:
 //postcondición:

void nuevo_descuento(Descuentos **d,Descuentos_clientes **dc,Cliente *clt ,int *n_desc,int*n_desc_clien, int *n_cliente);

void menu_descuentos( Descuentos **desc , Descuentos_clientes **desc_cl, Cliente *clt , int *n_desc , int *n_desc_cl , int *n_clt );

void modificar_descuento(Descuentos**,Descuentos_clientes**,int*,int*,int*);

void asignar_cod_prom_cliente( Descuentos_clientes **desc_cl , int *n_desc_cl , char id_desc[11] );

//cabecera:void pasar_ids_desde_fich(char*cadena,int*num_linea);
//precondición: sea cadena* un puntero a char de 11 caracteres inicializado a 0, *num_linea un puntero a entero que contiene el número de la linea que se va a usar
// IMPORTANTE: Antes de usar la función, hacer un volcado a fichero para asegurarse que están todos los clientes
//postcondición: ninguna, ya que modifica la cadena introducida, poniendo la id del cliente de la línea seleccionada
void pasar_ids_desde_fich(char*,int*);
