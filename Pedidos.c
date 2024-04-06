#include "Pedidos.h"
#include <stdio.h>
#include "estado.h"
#include <stdlib.h>
#include <string.h>

#define LINEA 100

void carga_pedidos( Pedido **ped ,int *n_ped){     // FUNCIONA

    int i;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";

    FILE *f;

    if ((f = fopen("Files\\Pedidos.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_ped)++;

        }

        *ped = (Pedido *)calloc(*n_ped, sizeof(Pedido));
        if (*ped == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_ped; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*ped)[i].id_pedido, strtok(line, "-\n"));
            strcpy((*ped)[i].fecha_ped, strtok(NULL, "-\n"));
            strcpy((*ped)[i].id_cliente, strtok(NULL, "-\n"));
            strcpy((*ped)[i].lugar_entrega, strtok(NULL, "-\n"));

            if (strcmp( (*ped)[i].lugar_entrega, "domicilio") == 0 ){

                strcpy((*ped)[i].id_cod_prom, strtok(NULL, "-\n"));

            }else{

                strcpy((*ped)[i].id_locker, strtok(NULL, "-\n"));

            }



        }

        rewind(f);
        fclose(f);

    }

}


void carga_prod_pedido( ProductoPedido **pr_ped ,int *n_pr_ped){     // FUNCIONA

    int i,j;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";
    char estado[18]="\0";
    char *ptr;

    FILE *f;

    if ((f = fopen("Files\\ProductosPedidos.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_pr_ped)++;

        }


        *pr_ped = (ProductoPedido *)calloc(*n_pr_ped, sizeof(ProductoPedido));
        if (*pr_ped == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_pr_ped; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*pr_ped)[i].id_pedido, strtok(line, "-\n"));
            strcpy((*pr_ped)[i].id_prod, strtok(NULL, "-\n"));
            (*pr_ped)[i].unidades = strtol(strtok(NULL, "-\n"),&ptr,10);
            strcpy((*pr_ped)[i].fecha_entrega, strtok(NULL, "-\n"));
            (*pr_ped)[i].importe = strtol(strtok(NULL, "-\n"),&ptr,10);
            strcpy(estado, strtok(NULL, "-\n"));

            if ( strcmp(estado,"enPreparacion") == 0 ){

                (*pr_ped)[i].est_pedido = enPreparacion;

            }else if ( strcmp(estado,"entregado") == 0  ){

                (*pr_ped)[i].est_pedido = entregado;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].fecha_entr_dev, strtok(NULL, "-\n"));


            }else if ( strcmp(estado,"devuelto") == 0 ){

                (*pr_ped)[i].est_pedido = devuelto;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].fecha_entr_dev, strtok(NULL, "-\n"));

            }else if ( strcmp(estado,"enReparto") == 0 ){

                (*pr_ped)[i].est_pedido = enReparto;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));

            }else if ( strcmp(estado,"transportista") == 0 ){

                (*pr_ped)[i].est_pedido = trasnportista;

                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));

            }else if ( strcmp(estado,"enviado") == 0 ){

                (*pr_ped)[i].est_pedido = enviado;

            }else if ( strcmp(estado,"enLocker") == 0 ){

                (*pr_ped)[i].est_pedido = enLocker;


                strcpy((*pr_ped)[i].id_transp, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].id_locker, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].cod_locker, strtok(NULL, "-\n"));
                strcpy((*pr_ped)[i].fecha_entr_dev, strtok(NULL, "-\n"));

            }else{

                printf("Error al ver el estado del pedido");

            }


            for ( j=0 ; j<18 ; j++ ){

                estado[j] = '\0';

            }



        }

        rewind(f);
        fclose(f);

    }

}



void volcado_pedidos ( Pedido *p, int *n_ped ){

    int i,j;
    char line[LINEA]="\0";
    FILE *f;

    if ((f = fopen("Files\\Pedidos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_ped ; i++ ){

            strcpy(line, p[i].id_pedido);
            strcat(line, "-");
            strcat(line, p[i].fecha_ped);
            strcat(line, "-");
            strcat(line, p[i].id_cliente);
            strcat(line, "-");
            strcat(line, p[i].lugar_entrega);

            if (strcmp( p[i].lugar_entrega, "domicilio") == 0 ){

                if ( strcmp( p[i].id_cod_prom,"\0\0\0\0\0\0\0\0\0\0") != 0 ){

                    strcat(line, "-");
                    strcat(line, p[i].id_cod_prom);

                }


            }else if ( strcmp( p[i].lugar_entrega, "locker") == 0 ){

                strcat(line, "-");
                strcat(line, p[i].id_locker);

            }else printf("Error en el estado del pedido ( volcado )");


            if(i < *n_ped - 1) {
                strcat(line, "\n");
            }

            fprintf(f, "%s", line);

            for ( j=0 ; j<LINEA ; j++ ) line[j]='\0';

        }



    }


    fclose(f);

}




void volcado_prod_pedidos ( ProductoPedido *pr_p, int *n_pr_ped ){

    int i;
    char line[LINEA]="\0",unidades[6]="\0",importe[6]="\0";
    FILE *f;

    if ((f = fopen("Files\\ProductosPedidos.txt", "w+")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_pr_ped ; i++ ){

            strcpy(line, pr_p[i].id_pedido);
            strcat(line, "-");
            strcat(line, pr_p[i].id_prod);
            strcat(line, "-");

            sprintf(unidades,"%i",pr_p[i].unidades);
            strcat(line, unidades);

            strcat(line, "-");
            strcat(line, pr_p[i].fecha_entrega);
            strcat(line, "-");

            sprintf(importe,"%i",pr_p[i].importe);
            strcat(line, importe);
            strcat(line, "-");

            switch (pr_p[i].est_pedido) {

                case enPreparacion:

                    strcat(line, "enPreparacion");
                    break;
                case enviado:

                    strcat(line, "enviado");
                    break;
                case enReparto:

                    strcat(line, "enReparto");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    break;
                case enLocker:

                    strcat(line, "enLocker");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_locker);
                    strcat(line, "-");
                    strcat(line, pr_p[i].cod_locker);
                    strcat(line, "-");
                    strcat(line, pr_p[i].fecha_entr_dev);
                    break;
                case entregado:

                    strcat(line, "entregado");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    strcat(line, "-");
                    strcat(line, pr_p[i].fecha_entr_dev);
                    break;
                case devuelto:

                    strcat(line, "devuelto");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    strcat(line, "-");
                    strcat(line, pr_p[i].fecha_entr_dev);
                    break;
                case trasnportista:

                    strcat(line, "transportista");
                    strcat(line, "-");
                    strcat(line, pr_p[i].id_transp);
                    break;
                default:
                    printf("Error con el tipo de prod_pedido ( volcado )");
                    break;
            }

            if(i < *n_pr_ped - 1) {
                strcat(line, "\n");
            }

            fprintf(f, "%s", line);


        }



    }


    fclose(f);

}

void eliminar_pedido ( Pedido *ped, int indice_ped){

    char borrado[8]="#######";

    strcpy( ped[indice_ped].id_pedido , borrado );


}


void crear_siguiente_id ( int num_digitos, char vect_dest[num_digitos+1] , char vect_id[num_digitos+1]){

    int j,cifras=0,n,n_aux;
    char *aux,*nulo,*ptr;

    n= strtol(vect_id,&ptr,10);
    n++;
    n_aux = n;

    while ( n >= 1 ){

        n /= 10;
        cifras++;
    }

    aux = (char *)calloc(cifras+1,sizeof(char));
    nulo = (char *)calloc(num_digitos-cifras,sizeof(char));

    sprintf(aux,"%i",n_aux);

    for ( j=0 ; j<num_digitos-cifras ; j++ ){

        nulo[j]='0';

    }

    strcat(nulo,aux);
    strcpy(vect_dest,nulo);

}



void crear_pedido ( Pedido **ped, int *n_ped , char usu_act[8]){

    int i=0,j,n;
    char borrado[8]="#######",prueba_id_ped[8]="\0",prueba_fecha[11]="\0",prueba_id_cliente[8]="\0",prueba_lugar[10]="\0",prueba_id_lock[11]="\0",prueba_id_cod_prom[11]="\0";
    char id_sig[8]="\0";

    while ( i<*n_ped  && strcmp( (*ped)[i].id_pedido , borrado) != 0 ){

        i++;
    }


    if ( i >= *n_ped ){

        *ped = ( Pedido *)realloc(NULL, (*n_ped+1) * sizeof(Pedido));

        for ( j=0 ; j<10 ; j++ ) (*ped)[*n_ped].lugar_entrega[j] = '\0';

        crear_siguiente_id(7,id_sig,(*ped)[i-1].id_pedido);

        strcpy((*ped)[*n_ped].id_pedido,id_sig);

        system("cls");

        fflush(stdin);
        printf("Fecha_pedido: ");
        gets((*ped)[*n_ped].fecha_ped);

        strcpy( (*ped)[*n_ped].id_cliente , usu_act);
        fflush(stdin);
        printf("Lugar_entrega: ");
        gets((*ped)[*n_ped].lugar_entrega);
        fflush(stdin);

        if (strcmp((*ped)[*n_ped].lugar_entrega,"domicilio") == 0){

            printf("Id_cod_prom: ");
            fflush(stdin);
            gets((*ped)[*n_ped].id_cod_prom);

        }else if ( strcmp((*ped)[*n_ped].lugar_entrega,"locker") == 0 ){

            printf("Id_locker: ");
            fflush(stdin);
            gets((*ped)[*n_ped].id_locker);

        }else{

            printf("Error con el lugar de entrega de pedido en alta");
            exit(1);

        }

        strcpy(prueba_id_ped,(*ped)[*n_ped].id_pedido);
        strcpy(prueba_fecha,(*ped)[*n_ped].fecha_ped);
        strcpy(prueba_id_cliente,(*ped)[*n_ped].id_cliente);
        strcpy(prueba_lugar,(*ped)[*n_ped].lugar_entrega);
        strcpy(prueba_id_lock,(*ped)[*n_ped].id_locker);
        strcpy(prueba_id_cod_prom,(*ped)[*n_ped].id_cod_prom);

        (*n_ped)++;





    }else{

        if ( i == 0){

            strcpy( (*ped)[i].id_pedido , "0000001");

        }else{

            crear_siguiente_id(7,id_sig,(*ped)[i-1].id_pedido);

            strcpy( (*ped)[i].id_pedido,id_sig);

            system("cls");

            printf("Fecha_pedido: ");
            fflush(stdin);
            gets((*ped)[i].fecha_ped);
            strcpy( (*ped)[*n_ped].id_cliente , usu_act);
            printf("Lugar_entrega: ");
            fflush(stdin);
            gets((*ped)[i].lugar_entrega);

            if (strcmp((*ped)[i].lugar_entrega,"domicilio") == 0){

                printf("Id_cod_prom: ");
                fflush(stdin);
                gets((*ped)[i].id_cod_prom);

            }else if ( strcmp((*ped)[i].lugar_entrega,"locker") == 0 ){

                printf("Id_locker: ");
                fflush(stdin);
                gets((*ped)[i].id_locker);

            }else{

                printf("Error con el lugar de entrega de pedido en alta");
                exit(1);

            }

        }



    }


}


void modificar_pedido ( Pedido *ped , ProductoPedido *pr_ped ,int *n_ped , int *n_pr_ped, int indice ,usu tipo_usu, char usu_act[8]){

    int op,i,j=0;

    switch (tipo_usu) {

        case admin:

            printf("Fecha_pedido: ");
            fflush(stdin);
            gets(ped[indice].fecha_ped);
            printf("Id_cliente: ");
            fflush(stdin);
            gets(ped[indice].id_cliente);
            printf("Lugar_entrega: ");
            fflush(stdin);
            gets(ped[indice].lugar_entrega);

            if (strcmp(ped[indice].lugar_entrega,"domicilio") == 0){

                printf("Id_cod_prom: ");
                fflush(stdin);
                gets(ped[indice].id_cod_prom);

            }else if ( strcmp(ped[indice].lugar_entrega,"locker") == 0 ){

                printf("Id_locker: ");
                fflush(stdin);
                gets(ped[indice].id_locker);

            }else{

                printf("Error con el lugar de entrega de pedido en modificar");
                exit(1);

            }


            break;
        case proveedor:

            while ( strcmp(ped[indice].id_pedido,pr_ped[j].id_pedido)!=0) j++;

            switch (pr_ped[j].est_pedido) {

                case enPreparacion:

                    for (i=0 ; i<*n_pr_ped ; i++){

                        if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                            pr_ped[i].est_pedido = enviado;

                        }

                    }


                    break;
                case enviado:

                    for (i=0 ; i<*n_pr_ped ; i++){

                        if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                            pr_ped[i].est_pedido = enReparto;

                        }

                    }

                    break;
                case enReparto:

                    printf("--------- Nuevo estado del pedido -------\n");
                    printf("3.enLocker\n4.entregado\n");
                    scanf("%i",&op);


                    if ( op == 3){

                        for (i=0 ; i<*n_pr_ped ; i++){

                            if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                                pr_ped[i].est_pedido = enLocker;

                            }

                        }

                    }else if ( op == 4 ){

                        for (i=0 ; i<*n_pr_ped ; i++){

                            if ( strcmp(ped[indice].id_pedido,pr_ped[i].id_pedido)==0){

                                pr_ped[i].est_pedido = entregado;

                            }

                        }

                    }else{

                        printf("Error con el estado del pedido ( modificar estado pedido )");
                        exit(1);

                    }

                    break;
                default:
                    break;
            }

            break;

        default:
            break;
    }


}


void menu_prod_ped ( Pedido *ped, ProductoPedido *pr_p, int *n_ped,int *n_pr_ped , char id_ped[8] ,char id_cliente[8],usu tipo_usu){

    int i,cont=0,ind_prod_ped,error=0;
    char c,op,estado_ped_nuevo[]="\0";

    system("cls");

    printf("---------------- Productos asociados al pedido ----------------\n\n");

    for ( i=0 ; i< *n_pr_ped ; i++ ){

        if (strcmp( pr_p[i].id_pedido,id_ped)==0){

            printf("[%i].%s-%i\n",cont,pr_p[i].id_prod,pr_p[i].unidades);
            cont++;

        }

    }

    printf("----------------------------------\n");
    printf("Escriba el id del producto que desee ver: ");
    scanf("%i",&ind_prod_ped);
    fflush(stdin);

    ind_prod_ped--;

    system("cls");

    printf("------------------------- Producto %i --------------------------\n\n",ind_prod_ped+1);

    printf("Id_Ped: %s\nId_Prod: %s\nUnidades: %i\nFecha_prevista_entrega: %s\nImporte: %i\n",pr_p[ind_prod_ped].id_pedido,
                                                          pr_p[ind_prod_ped].id_prod,
                                                          pr_p[ind_prod_ped].unidades,
                                                          pr_p[ind_prod_ped].fecha_entrega,
                                                          pr_p[ind_prod_ped].importe);

    printf("Estado: ");
    switch (pr_p[ind_prod_ped].est_pedido) {

        case enPreparacion:

            printf("en Preparacion\n");

            break;
        case enviado:

            printf("enviado\n");

            break;
        case enReparto:

            printf("enReparto\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);

            break;
        case enLocker:

            printf("enLocker\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);
            printf("Id_locker: %s\n",pr_p[ind_prod_ped].id_locker);
            printf("Cod_locker: %s\n",pr_p[ind_prod_ped].cod_locker);
            printf("Fecha de entrega: %s\n",pr_p[ind_prod_ped].fecha_entr_dev);

            break;
        case entregado:

            printf("entregado\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);
            printf("Fecha de entrega: %s\n",pr_p[ind_prod_ped].fecha_entr_dev);

            break;
        case devuelto:

            printf("devuelto\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);
            printf("Fecha de entrega: %s\n",pr_p[ind_prod_ped].fecha_entr_dev);

            break;
        case trasnportista:

            printf("transportista\n");
            printf("Id_transportista: %s\n",pr_p[ind_prod_ped].id_transp);

            break;
        default:
            printf("Error con el estado del prod_ped ( menu prod ped )");
            exit(1);

    }

    system("pause");


    if ( tipo_usu == admin ){

        do{

            printf("\n Quiere modificar este producto? (s/n): ");
            scanf("%c",&c);

            system("cls");

            if ( c == 's' || c == 'S'){

                printf("Unidades: ");
                scanf("%i",&pr_p[ind_prod_ped].unidades);
                printf("Fecha_prev_entrega: ");
                fflush(stdin);
                gets(pr_p[ind_prod_ped].fecha_entrega);
                printf("Importe: ");
                scanf("%i",&pr_p[ind_prod_ped].importe);

                do{

                    printf("Estado_pedido: ");
                    fflush(stdin);
                    gets(estado_ped_nuevo);

                    if (strcmp(estado_ped_nuevo,"enPreparacion")==0){

                        pr_p[ind_prod_ped].est_pedido = enPreparacion;

                    }else if ( strcmp(estado_ped_nuevo,"enviado")==0 ){

                        pr_p[ind_prod_ped].est_pedido = enviado;

                    }else if ( strcmp(estado_ped_nuevo,"enReparto")==0 ){

                        pr_p[ind_prod_ped].est_pedido = enReparto;

                    }else if ( strcmp(estado_ped_nuevo,"enLocker")==0 ){

                        pr_p[ind_prod_ped].est_pedido = enLocker;

                    }else if ( strcmp(estado_ped_nuevo,"entregado")==0 ){

                        pr_p[ind_prod_ped].est_pedido = entregado;

                    }else if ( strcmp(estado_ped_nuevo,"devuelto")==0 ){

                        pr_p[ind_prod_ped].est_pedido = devuelto;

                    }else if ( strcmp(estado_ped_nuevo,"transportista")==0 ){

                        pr_p[ind_prod_ped].est_pedido = trasnportista;

                    }else{

                        printf("Escribe un estado valido.\n");
                        error=1;

                    }

                } while (error != 1);



            }else if ( c == 'n' || c == 'N'){


            }else printf("Escribe s o n");


        } while ( c != 's' && c != 'S' && c != 'n' && c != 'N');

    }




    if ( cont != 1){

        do{

            printf("---------------------------------------------\n");
            printf("Quiere ver otro producto? (s/n): ");
            fflush(stdin);
            scanf("%c",&op);

            printf("\n");
            system("cls");

            if ( op == 's' || op == 'S') menu_prod_ped(ped,pr_p,n_ped,n_pr_ped,id_ped,id_cliente,tipo_usu);
            else if ( op == 'n' || op == 'N' ){

                if ( tipo_usu == cliente ){

                    menu_pedidos_clientes(ped, pr_p, n_ped, n_pr_ped, id_cliente,cliente);

                }else if ( tipo_usu == admin ){


                    menu_pedidos_admin(ped, pr_p, n_ped, n_pr_ped,admin);

                }


            }else printf("Escribe s o n\n");

        }while ( op != 's' && op != 'S' && op != 'n' && op != 'N' );


    }else{

        printf("\n");
        system("cls");

        if ( tipo_usu == cliente ){

            menu_pedidos_clientes(ped, pr_p, n_ped, n_pr_ped, id_cliente,cliente);

        }else if ( tipo_usu == admin ){


            menu_pedidos_admin(ped, pr_p, n_ped, n_pr_ped,admin);

        }

    }

}




void menu_pedidos_clientes( Pedido *ped , ProductoPedido *prod_ped, int *n_pedidos,int *n_prod_ped, char id_cliente[8] , usu tipo_usu ){

    int i;
    int opcion;
    char c='a';

    printf("--------- Todos sus pedidos ---------\n\n");

    for (i=0 ; i<*n_pedidos ; i++ ){

        if ( strcmp( id_cliente , ped[i].id_cliente ) == 0){

            if (strcmp(ped[i].lugar_entrega, "domicilio") == 0) {

                printf("[%c].%s-%s-%s-%s-%s\n", c,
                       ped[i].id_pedido,
                       ped[i].fecha_ped,
                       ped[i].id_cliente,
                       ped[i].lugar_entrega,
                       ped[i].id_cod_prom);

            } else if (strcmp(ped[i].lugar_entrega, "locker") == 0) {

                printf("[%c].%s-%s-%s-%s-%s\n", c,
                       ped[i].id_pedido,
                       ped[i].fecha_ped,
                       ped[i].id_cliente,
                       ped[i].lugar_entrega,
                       ped[i].id_locker);

            } else {

                printf("Error con el lugar de entrega pedido");
                exit(1);

            }

            c++;
        }

    }

    printf("------------------------------------------------\n\n");

    do{

        printf("Escribe la id del pedido para ver los productos asociados a este:");
        scanf("%i",&opcion);


        if (strcmp(id_cliente,ped[opcion-1].id_cliente) != 0 ){

            printf("Introduzca un numeo vaido.\n");

        }

    }while( strcmp(id_cliente,ped[opcion-1].id_cliente) != 0);


    menu_prod_ped(ped,prod_ped,n_pedidos,n_prod_ped,ped[opcion-1].id_pedido,id_cliente,cliente);


}

/*

void asignar_transportista( Pedido *ped ,ProductoPedido *prod_ped,  int *n_pedidos , int *n_pr_ped , usu tipo_usu , int indice_p , char prov_cliente[21] ){

    int i,j,op,error=0;
    char c='a';

    system("cls");

    do{

        printf("---------------- Transportistas disponibles en %s -----------------\n\n",prov_cliente);

        for ( i=0 ; i< *n_pr_ped ; i++ ){

            if (strcmp(tranp[i].ciudad_rep,prov_cliente)==0){

                printf("[%c].%s\n",c,tranp[i].id_transp);
                c++;
            }

        }

        printf("Escribe el id de un transportista: ");
        scanf("%i",&op);

        if (strcmp(transp[op-1].ciudad_rep,prov_cliente)!=0){

            error = 1;
            printf("\nElije uno de los transportistas dados.");
            system("pause");
            system("cls");

        }

    }while ( error == 1 );


    for ( i=0 ; i< *n_pr_ped ; i++ ){

        if ( strcmp(ped[indice_p].id_pedido,prod_ped[i].id_pedido)==0){

            strcpy(prod_ped[i].id_transp,transp[op-1].id_transp);

        }

    }

}

*/

void menu_pedidos_admin( Pedido *ped ,ProductoPedido *prod_ped,  int *n_pedidos , int *n_pr_ped , usu tipo_usu) {

    int i, j,tipo_ped;
    char c = 'a', resp,resp_2;
    int op_ped,op_accion_pedido,existe=0;

    do {

        printf("Desea listar los pedidos segun su estado? (s/n):");
        fflush(stdin);
        scanf("%c", &resp);

        system("cls");

        if (resp == 's' || resp == 'S') {

            do{

                printf("1.enPreparacion\n2.enviado\n3.enReparto\n4.enLocker\n5.entregado\n6.devuelto\n7.transportista\n");
                printf("Elija el tipo de pedido (1-7):");
                scanf("%i", &tipo_ped);

                system("cls");

                switch (tipo_ped) {

                    case 1:

                        printf("--------- Pedidos en Preparacion ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enPreparacion){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en preparacion\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 2:

                        printf("--------- Pedidos enviados ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enReparto){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;

                                }


                            }else{

                                printf("No hay pedidos enviados\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;

                    case 3:

                        printf("--------- Pedidos en reparto ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enReparto){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en reparto\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 4:

                        printf("--------- Pedidos en locker ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != enLocker){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en locker\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 5:

                        printf("--------- Pedidos entregados ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != entregado){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos entregados\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 6:

                        printf("--------- Pedidos devueltos ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != devuelto ){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos devueltos\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    case 7:

                        printf("--------- Pedidos en transportista ---------\n\n");

                        i = 0;

                        while (i < *n_pedidos) {

                            j=0;

                            while ( j < *n_pr_ped && prod_ped[j].est_pedido != trasnportista){
                                j++;
                            }

                            if ( j < *n_pr_ped ) {


                                if ( strcmp(ped[i].id_pedido,prod_ped[j].id_pedido)==0 ){

                                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0 ) {

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_cod_prom);


                                    }else if (strcmp(ped[i].lugar_entrega, "locker") == 0){

                                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                                               ped[i].id_pedido,
                                               ped[i].fecha_ped,
                                               ped[i].id_cliente,
                                               ped[i].lugar_entrega,
                                               ped[i].id_locker);


                                    }

                                    c++;



                                }


                            }else{

                                printf("No hay pedidos en transportista\n");
                                system("pause");
                                system("cls");
                                menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                            }

                            i++;

                        }

                        break;
                    default:

                        printf("Escribe un numero del (1-7)");
                        system("cls");

                        break;

                }

            } while (tipo_ped != 1 && tipo_ped != 2 && tipo_ped != 3 && tipo_ped != 4 && tipo_ped != 5 && tipo_ped != 6 && tipo_ped != 7);


        }else if (resp == 'n' || resp == 'N') {

            system("cls");

            printf("--------- Todos los pedidos ---------\n\n");

            for (i = 0; i < *n_pedidos; i++) {

                if ( strcmp(ped[i].id_pedido, "#######") != 0 ){

                    if (strcmp(ped[i].lugar_entrega, "domicilio") == 0) {

                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                               ped[i].id_pedido,
                               ped[i].fecha_ped,
                               ped[i].id_cliente,
                               ped[i].lugar_entrega,
                               ped[i].id_cod_prom);

                    } else if (strcmp(ped[i].lugar_entrega, "locker") == 0) {

                        printf("[%c].%s-%s-%s-%s-%s\n", c,
                               ped[i].id_pedido,
                               ped[i].fecha_ped,
                               ped[i].id_cliente,
                               ped[i].lugar_entrega,
                               ped[i].id_locker);

                    } else {

                        printf("Error con el lugar de entrega pedido");
                        exit(1);

                    }

                    c++;

                }

            }


        } else printf("Introduce s o n\n");

    }while (resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');


        do{

            printf("\nElija una opcion:\n");
            printf("1.alta\n2.baja\n3.modificar\n4.ver productos asociados\n5.aignar transportista\n6.salir\n");
            scanf("%i", &op_ped);

            switch (op_ped) {

                case 1:

                    crear_pedido(&ped,n_pedidos,"0000004");

                    system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 2:

                    do{

                        printf("----------------------------\n\n");
                        printf("Escribe el id de pedido que quiera borrar: ");
                        scanf("%i",&op_accion_pedido);

                        eliminar_pedido( ped,op_accion_pedido-1);

                        printf("Quiere eliminar mas pedidos? (s/n): ");
                        fflush(stdin);
                        scanf("%c",&resp_2);

                    }while ( resp_2 != 'n' && resp_2 != 'N');

                        system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 3:

                    printf("----------------------------\n\n");
                    printf("Escribe el id de pedido que quiera modificar: ");
                    scanf("%i",&op_accion_pedido);

                    i=0;

                    modificar_pedido( ped , prod_ped,n_pedidos,n_pr_ped ,op_accion_pedido - 1 ,admin,"0000004");

                    system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 4:

                    printf("Escribe el id del pedido que quiera ver: ");
                    scanf("%i",&op_accion_pedido);

                    menu_prod_ped( ped,prod_ped, n_pedidos,n_pr_ped ,ped[op_accion_pedido-1].id_pedido ,NULL, admin);

                    system("cls");

                    menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                    break;
                case 5:

                    do{

                        printf("Escribe el id del pedido al que quiera asignar un transportista: ");
                        scanf("%i",&op_accion_pedido);

                        j=0;

                        while (  j<*n_pr_ped && strcmp(ped[op_accion_pedido].id_pedido,prod_ped[j].id_pedido)!=0  ){

                            if (prod_ped[j].est_pedido == enReparto || prod_ped[j].est_pedido == trasnportista ) existe=1;
                            j++;
                        }

                        if ( existe == 1 ){

                           // asignar_transportista(ped,prod_ped,n_pedidos,n_pr_ped,admin,op_accion_pedido--, usu[act].provincia);

                        }else{

                            printf("\nElije un pedido valido\n");
                            system("pause");
                            system("cls");
                            menu_pedidos_admin(ped, prod_ped, n_pedidos,n_pr_ped,admin);

                        }

                        printf("Quiere asignar otro transportista? (s/n): ");
                        fflush(stdin);
                        scanf("%c",&resp_2);

                    } while ( resp_2 != 'n' && resp_2 != 'N' );

                case 6:
                    exit(1);

                default:

                    printf("Elije un numero del 1 al 5\n\n");
                    break;
            }

        }while ( op_ped != 1 && op_ped != 2 && op_ped != 3 && op_ped != 4 && op_ped != 5);



    }




    void menu_pedidos_prov(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos, usu tipo_usu) {

    

    }

    void menu_pedidos_transp(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos , usu tipo_usu) {


    }


    void menu_pedidos(Pedido *ped, ProductoPedido *prod_ped, int *n_pedidos, int *n_prod_ped, usu tipo_usu) {

        int i;
        char id_cliente[8]="0000004";

        switch (tipo_usu) {


            case cliente:

                menu_pedidos_clientes(ped, prod_ped, n_pedidos, n_prod_ped, id_cliente,cliente);

                break;
            case admin:

                menu_pedidos_admin(ped, prod_ped, n_pedidos, n_prod_ped,admin);

                break;
            case proveedor:

                menu_pedidos_prov(ped, prod_ped, n_pedidos,proveedor);

                break;
            case transportista:

                menu_pedidos_transp(ped, prod_ped, n_pedidos,transportista);

                break;
            default:

                printf("Error con el tipo de ususario");
                exit(1);

        }

    }
