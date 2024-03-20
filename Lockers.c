#include "Lockers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEA 100


// Caberea: void carga_lockers( Locker ** )
// Precondicion:
// Postcondicion: Vuelca los datos del fichero en la estructura


void carga_lockers( Locker **lock ,int *n_lock){      // FUNCIONA

    int i;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";
    char n_comp_t[3]={0},n_comp_ocup[3]={0};
    char *ptr;

    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\Lockers.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_lock)++;

        }


        *lock = (Locker *)calloc(*n_lock, sizeof(Locker));
        if (*lock == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

       for ( i=0 ; i< *n_lock ; i++ ) {

           fgets(line,LINEA,f);

           strcpy((*lock)[i].id_locker, strtok(line, "-\n"));
           strcpy((*lock)[i].localidad, strtok(NULL, "-\n"));
           strcpy((*lock)[i].provincia, strtok(NULL, "-\n"));
           strcpy((*lock)[i].ubicacion, strtok(NULL, "-\n"));
           strcpy(n_comp_t, strtok(NULL, "-\n"));
           strcpy(n_comp_ocup, strtok(NULL, "-\n"));


           (*lock)[i].Num_compT = strtol(n_comp_t, &ptr, 10);
           (*lock)[i].Num_compOcup = strtol(n_comp_ocup, &ptr, 10);

           strcpy(n_comp_t,"00");
           strcpy(n_comp_ocup,"00");

        }

        rewind(f);
        fclose(f);

    }

}


void carga_compartimento_lockers( CompartimentoLocker **c_lock ,int *n_c_lock){      // FUNCIONA

    int i,j;
    char line[LINEA]="0";
    char contador_lineas[LINEA]="0";
    char estado[18]="\0",Num_compT[4]="\0";
    char *ptr;

    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\CompatimentoLockers.txt", "r")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        while(!feof(f)){

            fgets(contador_lineas,LINEA,f);
            (*n_c_lock)++;

        }


        *c_lock = (CompartimentoLocker *)calloc(*n_c_lock, sizeof(CompartimentoLocker));
        if (*c_lock == NULL) {
            printf("Error al crear la memoria para los lockers.\n");
            exit(1);
        }

        rewind(f);

        for ( i=0 ; i< *n_c_lock ; i++ ) {

            fgets(line,LINEA,f);

            strcpy((*c_lock)[i].id_locker, strtok(line, "-\n"));
            strcpy(Num_compT, strtok(NULL, "-\n"));

            (*c_lock)[i].Num_compT = strtol(Num_compT,&ptr,10);

            strcpy((*c_lock)[i].cod_locker, strtok(NULL, "-\n"));
            strcpy(estado, strtok(NULL, "-\n"));

            if ( strcmp( estado , "vacio") == 0 ){

                (*c_lock)[i].est_locker = vacio;

            }else if ( strcmp( estado , "ocupado") == 0 ){

                (*c_lock)[i].est_locker = ocupado;

                strcpy((*c_lock)[i].fecha_ocup, strtok(NULL, "-\n"));
                strcpy((*c_lock)[i].fecha_cad, strtok(NULL, "-\n"));


            }else{

                printf("Error con el estado del comp_locker");


            }


            for ( j=0 ; j<18 ; j++ ){

                estado[j] = '\0';

            }


        }

        rewind(f);
        fclose(f);

    }

}


void volcado_lockers ( Locker **l, int *n_lock ){

    int i;
    char line[LINEA]="\0",Num_compT[4]="\0",Num_compOcup[4]="\0";
    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\Lockers.txt", "w")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_lock ; i++ ){

            strcpy(line, (*l)[i].id_locker);
            strcat(line, "-");
            strcat(line, (*l)[i].localidad);
            strcat(line, "-");
            strcat(line, (*l)[i].provincia);
            strcat(line, "-");
            strcat(line, (*l)[i].ubicacion);
            strcat(line, "-");

            sprintf(Num_compT,"%i",(*l)[i].Num_compT);
            sprintf(Num_compOcup,"%i",(*l)[i].Num_compOcup);

            strcat(line, Num_compT);
            strcat(line, "-");
            strcat(line, Num_compOcup);

            if(i < *n_lock - 1) {
                strcat(line, "\n");
            }
            fprintf(f, "%s", line);


        }



    }


    fclose(f);

}



void volcado_comp_lockers ( CompartimentoLocker **c_l, int *n_c_lock ){

    int i;
    char line[LINEA]="\0",Num_compT[4]="\0";
    FILE *f;

    if ((f = fopen("C:\\Users\\migue\\Desktop\\CLASE\\AMAZON_MP\\Proyecto_MP\\Files\\CompatimentoLockers.txt", "w")) == NULL) {

        printf("Error al abrir el archivo");

    } else {

        for ( i=0 ; i<*n_c_lock ; i++ ){

            strcpy(line, (*c_l)[i].id_locker);
            strcat(line, "-");

            sprintf(Num_compT,"%i",(*c_l)[i].Num_compT);

            strcat(line, Num_compT);
            strcat(line, "-");
            strcat(line, (*c_l)[i].cod_locker);
            strcat(line, "-");

            if ( (*c_l)[i].est_locker == vacio ){

                strcat(line, "vacio");

            }else if ( (*c_l)[i].est_locker == ocupado ){

                strcat(line, "ocupado");
                strcat(line, "-");
                strcat(line, (*c_l)[i].fecha_ocup);
                strcat(line, "-");
                strcat(line, (*c_l)[i].fecha_cad);


            }else printf("Error con el esatdo del locker ( volcado )");


            if(i < *n_c_lock - 1) {
                strcat(line, "\n");
            }

            fprintf(f, "%s", line);


        }



    }


    fclose(f);

}










