#ifndef PRODUCTOS_H
#define PRODUCTOS_H
#define F_PRODUCTO "Productos.txt"
#define F_CATEGORIAS "Categorias.txt"
#include <stdio.h>
typedef struct {
    char descrip[51];
    char id_prod[8];
    char id_gestor[5];
    char id_categ[5];
    int stock,entrega,importe;
}producto;
typedef struct {
    char id_cat[5];
    char descrip[51];
}categoria;

//Cabecera: void alta_producto(producto p)
//Precondicion: usuario debe estar definido 
//Poscondicion: Lee toda los campos de producto por teclado excepto por producto.id_gestor y
//escribe en el fichero el nuevo producto, tomando como id la menor disponible.
void alta_producto(/*usuario*/);
//Cabecera: void baja producto(char*id)
//Precondicion: id debe pertenecer a un producto
//Poscondicion: Borra la informacion de un producto
void baja_producto(char *id);
//Cabecera: void alta_categoria
//Cabecera: void mod_prod(producto)
//Precondicion: producto.id_prod=id del producto a modificar
//Poscondicion: Cambia los datos del producto con id producto.id_prod
void mod_prod(producto);
//Cabecera: int buscar_id (FILE *f,char *n)
//Precondicion: f debe ser F_PRODUCTO o F_CATEGORIAS y estar abierto para lectura
//poscondicion: Devuelve la id de n dentro del fichero
int buscar_id(FILE **f,char *n);
//Cabecera: void Busqueda_prod_nombre(char *nombre)
//Precondicion: nombre debe seruna cadena ya definida
//Poscondicion: Escribe por pantalla todos los productos cuya descripcion coincida con nombre
void Busqueda_prod_nombre(char*n);
//cabecera: void Busqueda_prod_cat(char *id)
//Precondicion: id debe pertenecer a una categoria
//Poscondicion: Escribe por pantalla todos los productos 
//que pertenecen a la categoria con identificador id
void Busqueda_prod_cat(char *id);
//Cabecera: producto cargar_prod(char *id)
//Precondicion: id debe ser una id de un producto registrado
//Poscondicion: Devuelve todo la informacion del producto con identificador id
producto cargar_prod(char *id);
#endif