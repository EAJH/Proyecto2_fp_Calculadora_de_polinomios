#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "funciones.h"

//--------PROTOTIPOS--------
void menu();

int main(int argc, char **argv)
{
    //ARGV0   ARGV1   ARGV2    ARGV3   ARGV4
// ./polinomio -in entrada.txt -out salida.txt
// ./polinomio -out salida.txt -in entrada.txt
// ./polinomio -in entrada.txt
// ./polinomio -out salida.txt
// ./polinomio
if(argc==3)
    {
        if(strcmp(argv[1], "-in")==0)
        {
            open_in_file(argv[2]);
        }else if(strcmp(argv[1], "-out")==0){
            open_out_file(argv[2]);
        }
    }else if(argc==5){
        if(strcmp(argv[1], "-in")==0){
            open_in_file(argv[2]);
        }else if(strcmp(argv[1], "-out")==0){
            open_out_file(argv[2]);
        }
    }else if(strcmp(argv[3], "-in")==0){
        open_in_file(argv[4]);
    }else if(strcmp(argv[3], "-out")==0){
        open_out_file(argv[4]);
    } 

    int op;
    int n1;
    int n2;
    float escalar;
    POLINOMIO p, p1, p2;
    MONOMIO m;
    POLINOMIO bino;

    //Se define un maximo de 75 polinomios para almacenar en memoria
    dynMemory = (POLINOMIO*)malloc(75*sizeof(POLINOMIO));
    
    //Los términos se deben de ingresar en orden decreciente respecto al exponente

    while(true)
    {
        printf("\n---------------PROYECTO 2. CALCULADORA DE POLINOMIOS---------------\n");
        printf("\t\t\tUniversidad Nacional Autonoma de Mexico (UNAM)\n");
        printf("\t\t\tFacultad de Ingenieria\n");
        printf("\t\t\tMateria: Fundamentos de programacion (1122)\n");
        printf("\t\t\tProfesor: Mercado Martinez Adrian Ulises\n");
        printf("\t\t\tGrupo: 07\n");
        printf("\t\tBrigada 11\n");
        printf("Integrantes de la brigada:\n");
        printf("\t-Jasso Vazquez Sara.\n");
        printf("\t*Numero de lista: 28.\n");
        printf("\t-Juarez Herrera Erick Adrian.\n");
        printf("\t*Numero de lista: 30.\n");
        printf("\t-Perez Ortiz Sofia.\n");
        printf("\t*Numero de lista: 38.\n");
        printf("\t\t\tSemestre 2022-1\n");
        menu();
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                leerArchivo(argv[2]);
                memoryWrite(p);
            break;
            case 2:
                printf("Existen en memoria %d polinomios\n", countMemory);                
               
                printf("Ingrese el grado del polinomio 1:\n");
                scanf("%d", &p1.grado);

                printf("Ingrese el grado del polinomio 2:\n");
                scanf("%d", &p2.grado);

                printf("Ingrese el numero de terminos del polinomio 1:\n");
                scanf("%d", &p1.nTerm);
                printf("Ingrese el numero de terminos del polinomio 2:\n");
                scanf("%d", &p2.nTerm);
              
                p = suma(p1,p2);
                memoryWrite(p);
                polPrint(p);
            break;
            case 3:
                printf("Existen en memoria %d polinomios\n", countMemory);
               
                printf("Ingrese el grado del polinomio 1:\n");
                scanf("%d", &p1.grado);

                printf("Ingrese el grado del polinomio 2:\n");
                scanf("%d", &p2.grado);

                printf("Ingrese el numero de terminos del polinomio 1:\n");
                scanf("%d", &p1.nTerm);
                printf("Ingrese el numero de terminos del polinomio 2:\n");
                scanf("%d", &p2.nTerm);
              
                p = resta(p1,p2);
                memoryWrite(p);
                polPrint(p);
            break;
            case 4:
                printf("Existen en memoria %d polinomios\n", countMemory);
               
                printf("Ingrese el grado del polinomio 1:\n");
                scanf("%d", &p1.grado);
                printf("Ingrese el numero de terminos del polinomio 1:\n");
                scanf("%d", &p1.nTerm);
                p = multEsc(p1);
                memoryWrite(p);

                polPrint(p);
            break;
            case 5:
                printf("Existen en memoria %d polinomios\n", countMemory);
               
                printf("Ingrese el grado del polinomio 1:\n");
                scanf("%d", &p1.grado);

                printf("Ingrese el grado del polinomio 2:\n");
                scanf("%d", &p2.grado);

                printf("Ingrese el numero de terminos del polinomio 1:\n");
                scanf("%d", &p1.nTerm);
                printf("Ingrese el numero de terminos del polinomio 2:\n");
                scanf("%d", &p2.nTerm);
                p = mult(p1,p2);
                memoryWrite(p);
                polPrint(p);
            break;
            case 6:
                printf("Existen en memoria %d polinomios\n", countMemory);
               
                printf("Ingrese el grado del polinomio 1:\n");
                scanf("%d", &p1.grado);
                printf("Ingrese el numero de terminos del polinomio 1:\n");
                scanf("%d", &p1.nTerm);
    
                p = divMon(p1);
                memoryWrite(p);
                polPrint(p);
            break;
            case 7:
                printf("Existen en memoria %d polinomios\n", countMemory);
               
                printf("Ingrese el grado del polinomio 1:\n");
                scanf("%d", &p1.grado);

                printf("Ingrese el numero de terminos del polinomio 1:\n");
                scanf("%d", &p1.nTerm);

                p = div_binomio(p1);
                memoryWrite(p);
                polPrint(p);
            break;
            case 8:
                printf("Existen en memoria %d polinomios\n", countMemory); 
                polPrint();
            break;
            case 9:
                printf("Se realizara la escritura de los polinomios almacenados en memoria\n");
                escribirEnArchivo();
            break;
            case 10:
                printf("Para poder consultar el manual de usuario, consulte el siguiente link: \n");
                printf("https://drive.google.com/file/d/1qwHnzGB3dHe50UqcUaQL9N6B5wEmhUrR/view?usp=sharing");
            break;
            case 11:
                exit(EXIT_SUCCESS);
            break;
        }
    }
    return 0;
}

void menu()
{
    printf("\t\nCALCULADORA DE POLINOMIOS\t\n");
    printf("Selecciona una opcion a ejecutar: \n");
    printf("1. Leer polinomio(s) desde un archivo.\n");
    printf("2. Suma de polinomios.\n");
    printf("3. Resta de polinomios.\n");
    printf("4. Multiplicacion de un polinomio por un escalar.\n");
    printf("5. Multiplicacion de polinomios\n");
    printf("6. Division de un polinomio entre un monomio.\n");
    printf("7. Division de polinomio entre un binomio.\n");
    printf("8. Escribir en pantalla.\n" );
    printf("9. Escribir a un archivo.\n");
    printf("10. Manual de usuario.\n");
    printf("11. Salir.\n");
}














































