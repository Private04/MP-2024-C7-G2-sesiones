#include "Transportistas.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE 150

// cabecera: void de_int_a_id_empresa(int i_id, char * s_id)
// precondicion: i_id es un numero de 4 digitos como máximo
// postcondicion: convierte el entero i_id en un string s_id
void de_int_a_id_empresa(int i_id, char* s_id)
{
    char cadena[5];
    int i, j = 0;

    strcpy(s_id, "0000");

    itoa(i_id, cadena, 10);

    for (i = 4 - strlen(cadena); i < 4; i++) {
        s_id[i] = cadena[j];
        j++;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////

void carga_transp(Transportista**t,int *n_trans){
    int i;
    char line[LINE]="\0",contador_lineas[LINE]="0";
    FILE *f;

    if((f=fopen("Files\\transportistas.txt","r"))==NULL){
        printf("Error al abrir el archivo\n");
    }

    while(!feof(f)){

        fgets(contador_lineas,LINE,f);
        (*n_trans)++;

    }

    *t = (Transportista *)calloc(*n_trans, sizeof(Transportista));
    if(*t==NULL){
        printf("Error al reservar memoria para los transportistas\n");
        exit(1);
    }else{
        rewind(f);
        for(i=0;i<*n_trans;i++){

            fgets(line,LINE,f);
            strcpy((*t)[i].Id_transp, strtok(line,"-"));
            strcpy((*t)[i].Nombre, strtok(NULL, "-\n"));  //cargamos los datos tipo char
            strcpy((*t)[i].email, strtok(NULL, "-\n"));
            strcpy((*t)[i].Contrasenna, strtok(NULL, "-\n"));
            strcpy((*t)[i].Nom_empre, strtok(NULL, "-\n"));
            strcpy((*t)[i].Ciudad, strtok(NULL, "-\n"));

        }
    }
    rewind(f);
    fclose(f);
}

void volcado_transp(Transportista **t,int *n_trans){
    int i,lim;
    char line[LINE]="\0";
    lim=*n_trans;
    FILE *f;
    if ((f = fopen("Files\\transportistas.txt", "w")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<lim ; i++ ){
            // strcpy(line,"\n");
            strcpy(line, (*t)[i].Id_transp);
            strcat(line, "-");
            strcat(line, (*t)[i].Nombre);
            strcat(line, "-");
            strcat(line, (*t)[i].email);
            strcat(line, "-");
            strcat(line, (*t)[i].Nom_empre);
            strcat(line, "-");
            strcat(line, (*t)[i].Contrasenna);
            strcat(line, "-");
            strcat(line, (*t)[i].Ciudad);

            if(i < *n_trans - 1) strcat(line, "\n");
            fprintf(f, "%s", line);
        }

    }

    fclose(f);

}


void nuevo_transportista(Transportista **t,int *n_transport, int *ind_usu_act){

    char Id[5];
    *ind_usu_act = *n_transport;
    (*n_transport)++;
    if((*t = (Transportista*)realloc(*t, *n_transport * sizeof(Transportista)))==NULL)
    {
        printf("Error al reservar memoria para los transportistas\n");
        exit(1);
    }else{

        if(*n_transport==1){
            de_int_a_id_empresa(*n_transport,Id);
        }else{
            strcpy(Id,(*t+(*n_transport-2))->Id_transp);
            siguiente_id(Id,4);
        }
        printf("\n Su Id de transportista es: ");
        puts(Id);
        strcpy((*t)[*n_transport-1].Id_transp,Id);

        printf("\nIntrozuca su nombre y apellidos(20 caracteres):\n");
        leer_string((*t)[*n_transport-1].Nombre,21);

        printf("\nIntroduzca su correco electrónico de empresa(31 caracteres):\n");
        leer_string((*t)[*n_transport-1].email,31);

        printf("\nIntroduzca el nombre de su empresa(21 caracteres):\n");
        leer_string((*t)[*n_transport-1].Nom_empre,21);

        printf("\nCree e introduzca una contraseña(hasta 15 dígitos):\n");
        leer_string((*t)[*n_transport-1].Contrasenna,16);

        printf("\nCree e introduzca su ciudad(hasta 15 dígitos):\n");
        leer_string((*t)[*n_transport-1].Ciudad,16);

    }
}


int indice_con_id_transp(Transportista**vector_transp,char *id_transp,int num_transp){
    int i=0,devolver;
    do{
        if(strcmp(id_transp,(*vector_transp)[i].Id_transp)==0){
            devolver=i;
        }
        i++;
    }while(i<=num_transp);
    return devolver;
}

void borrar_transp_con_id(Transportista**vector_transp,char *Id_trans, int *n_transp){
    int i,aux;
    aux=*n_transp;

    if(aux==1){
        free(vector_transp);
        *n_transp=0;
    }else{
        for(i=indice_con_id_transp(vector_transp,Id_trans,aux)+1;i<aux;i++)
            (*vector_transp)[i-1]=(*vector_transp)[i];
    }
    (*n_transp)=aux-1;
}


void listado_transportista ( Transportista *transp, int *n_transp ){

    int i=0,j;
    char c='a',resp,op[5];

    printf("--------------- Transportistas ------------------------------\n\n");

    for ( i=0 ; i<*n_transp ; i++ ){

        printf("[%c].%s-%s\n",c,transp[i].Id_transp,transp[i].Nombre);

        c++;
    }

    printf("\n\n-----------------------------------------------\n");

    system("pause");


    do{

        printf("\n Quiere modificar algun transportista? (s/n): ");
        fflush(stdin);
        scanf("%c",&resp);

        if ( resp == 's' || resp == 'S'){

            do{

                printf("Escribe el id del transportista a modificar: ");
                fflush(stdin);
                gets(op);

                j=0;
                while ( j<*n_transp && strcmp(op,transp[j].Id_transp) !=0) j++;

                if ( j >= *n_transp) printf("\nEscribe un id valido\n");

            }while ( j >= *n_transp);

            modificar_transp( transp, j );

        }


    }while( resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');


}



void modificar_transp ( Transportista *transp , int indice_transp ){

    system("cls");

    printf("Nombre: ");
    fflush(stdin);
    gets(transp[indice_transp].Nombre);

    printf("Email (30): ");
    fflush(stdin);
    gets(transp[indice_transp].email);

    printf("Contrasena (15): ");
    fflush(stdin);
    gets(transp[indice_transp].Contrasenna);

    printf("Nombre_empresa: ");
    fflush(stdin);
    gets(transp[indice_transp].Nom_empre);

    printf("Ciudad_reparto: ");
    fflush(stdin);
    gets(transp[indice_transp].Ciudad);

    system("cls");
    printf("\nHas modificado los datos corectamente.\n");
    system("pause");
    system("cls");




}


void datos_transportista ( Transportista *transp , int ind_transp ){

    char resp;

    system("cls");

    printf("------------------------------------------------------\n\n");
    printf("Nombre: %s\nEmail: %s\nContrasena: %s\nNombre_empresa: %s\nCiudad_reparto: %s\n\n",
           transp[ind_transp].Nombre,
           transp[ind_transp].email,
           transp[ind_transp].Contrasenna,
           transp[ind_transp].Nom_empre,
           transp[ind_transp].Ciudad);
    printf("------------------------------------------------------\n\n");

    do{

        printf("Quiere cambiar sus datos?(s/n): ");
        fflush(stdin);
        scanf("%c",&resp);

        system("cls");

        if ( resp == 's' || resp == 'S' ){

            modificar_transp(transp,ind_transp);

        }else if ( resp != 's' & resp != 'S' && resp != 'n' & resp != 'N' ) printf("\nEscribe s o n");

    } while (resp != 's' & resp != 'S' && resp != 'n' & resp != 'N');


}
