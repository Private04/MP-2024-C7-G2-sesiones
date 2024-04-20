#ifndef PROYECTO_MP_CLIENTES_H
#define PROYECTO_MP_CLIENTES_H

typedef struct{

    char Id_cliente[8];
    char Nombr_cliente[21];
    char Dir_cliente[51];
    char Localidad[21];
    char Provincia[21];
    char email[31];
    char Contrasenna[16];
    char Cartera[7];

}Cliente;

void leer_string(char*cadena, int elem);
void siguiente_id(char*cad,int i);


void carga_cliente(Cliente **c,int *n_clien);
void volcado_cliente(Cliente **c,int *n_clien);
void nuevo_cliente(Cliente **c,int *n_cliente);

#endif //PROYECTO_MP_CLIENTES_H