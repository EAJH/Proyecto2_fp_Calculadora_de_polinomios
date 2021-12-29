#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funciones.h"

//--------FUNCION BURBUJA---------
/**
 * @brief Función que representa el algoritmo burbuja
 * @param pRes polinomio resultante a ordenar
 * @return Nada, debido a que es una función de tipo void
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 7 diciembre 2021
 */
void burbuja(POLINOMIO pRes)
{
    MONOMIO aux;
    for (int i = 0; i < sizeof(pRes.nTerm); i++)
    {
        // Con -i ya no evaluamos números que ya están acomodados
        // El -1 es para que, a la hora de hacer las comparaciones, no llegue al ultimo y compare con el siguiente y se de cuenta que no hay siguiente
        for (int j = 0; j < sizeof(pRes.nTerm) - i - 1; j++)
        {
            if (pRes.term[j].exp < pRes.term[j + 1].exp)
            {
                // Intercambio de exponentes para ordenar el polinomio drecientemente
                aux = pRes.term[j];
                pRes.term[j] = pRes.term[j + 1];
                pRes.term[j + 1] = aux;
            }
        }
    }
}

//--------FUNCIONES RELACIONADAS CON OPERACIONES ENTRE POLINOMIOS---------

/**
 * @brief Función que realiza la división de un polinomio entre un binomio mediante el método de división sintética
 * @param p1 polinomio ingresado
 * @param bino binomio ingresado
 * @return POLINOMIO lo que retorna es un apuntador de tipo POLINOMIO con el polinomio resultante
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 28 diciembre 2021
 */

POLINOMIO div_binomio(POLINOMIO p1)//POLINOMIO div_binomio(POLINOMIO p1, POLINOMIO bino)
{
    
    POLINOMIO bino;
    POLINOMIO pRes;
    int k;
    int i = 0;

    k=p1.nTerm;

    //Reserva de memoria
    pRes.term = (MONOMIO *)malloc(sizeof(MONOMIO) * p1.nTerm);
    bino.term = (MONOMIO *)malloc(2 * sizeof(MONOMIO));
    p1.term = (MONOMIO *)malloc(p1.nTerm * sizeof(MONOMIO));
    
    for (int g = 0; g < p1.nTerm; g++)
    {
        printf("Ingrese el termino %d del polinomio 1:\n", g);
        scanf("%f\t%d", &p1.term[g].coef, &p1.term[g].exp);
    }

    //Lectura del binomio
    for(int j=0; j<2; j++)
    {
        printf("Ingrese el termino %d del binomio divisor: \n", j+1);
        scanf("%f\t%d", &bino.term[j].coef, &bino.term[j].exp);
    }

    //EN DIV SINTÉTICA UTILIZAMOS SOLAMENTE LOS COEFICIENTES

    bino.term[1].coef = bino.term[1].coef * -1;
    pRes.term[0].coef = p1.term[0].coef;// Primer valor del polinomio resultante
    pRes.term[0].exp = p1.term[0].exp - 1;// Exponente del primer valor del polinomio resultante

    // División sintética
    for (i=1; i < p1.nTerm; i++)
    {
        pRes.term[i].coef = (bino.term[1].coef * pRes.term[i - 1].coef) + p1.term[i].coef;
        pRes.term[i].exp = p1.term[i].exp - 1;
    }

    pRes.grado = p1.term[0].exp - bino.term[0].exp;
    pRes.nTerm = (p1.nTerm-1);
    pRes.term = (MONOMIO *)realloc(pRes.term, (p1.nTerm-1) * (sizeof(MONOMIO)));

    printf("El grado del polinomio resultante es: %d\n",pRes.grado);

    //Imprimimos el polinomio
    for(int g=0; g<(k-1);g++)
    {
        printf("%.3f\t%d\t", pRes.term[g].coef, pRes.term[g].exp);
    }

    //Residuo
    printf("\nEl residuo del polinomio es: %f\t0", pRes.term[k-1].coef);

    if(pRes.term[k-1].coef == 0)
    {
        printf("\nAdemás, x = %f\t%d es una raiz del polinomio.\n",bino.term[1].coef , bino.term[1].exp);
        //bin.term[1].coef no se multiplica por -1 porque eso ya se hizo desde antes
    }
    return pRes;
}

/**
 * @brief Función que realiza la suma entre dos polinomios
 * @param p1 primer polinomio ingresado
 * @param p2 segundo polinomio ingresado
 * @return POLINOMIO lo que retorna es un apuntador de tipo POLINOMIO con el polinomio resultante
 * @programador: Jasso Vázquez Sara, Juárez Herrera Erick Adrián, Pérez Ortiz Sofia
 * @ÚltimaModificación: 28 diciembre 2021
 */
POLINOMIO suma(POLINOMIO p1, POLINOMIO p2)
{
    POLINOMIO pRes;
    MONOMIO t, t2;

    int i = 0, j = 0, k = 0, h = 0;
    //int grado, nTerm;

    p1.term = (MONOMIO *)malloc(p1.nTerm * sizeof(MONOMIO));
    p2.term = (MONOMIO *)malloc(p2.nTerm * sizeof(MONOMIO));
    pRes.term = (MONOMIO *)malloc((p1.nTerm + p2.nTerm) * sizeof(MONOMIO));

    for (int g = 0; g < p1.nTerm; g++)
    {
        printf("Ingrese el termino %d del polinomio 1:\n", g);
        scanf("%f\t%d", &p1.term[g].coef, &p1.term[g].exp);
    }

    for (int o = 0; o < p2.nTerm; o++)
    {
        printf("Ingrese el termino %d del polinomio 2:\n", o);
        scanf("%f\t%d", &p2.term[o].coef, &p2.term[o].exp);
    }

//Comparacion

int gradomayor;

    while (i < p1.nTerm)
    {
        while (j < p2.nTerm)
        {
            t = p1.term[i];
            t2 = p2.term[j];
            if (t.exp == t2.exp)
            {
                pRes.term[k].coef = t.coef + t2.coef;
                pRes.term[k].exp = t.exp;
                k++;
                i++;
                j++;
            }
            else if (t.exp > t2.exp)
            {
                pRes.term[k].coef = t.coef;
                pRes.term[k].exp = t.exp;
                k++;
                i++;
            }
            else if (t.exp < t2.exp)
            {
                pRes.term[k].coef = t2.coef;
                pRes.term[k].exp = t2.exp;
                k++;
                j++;
            } 
        } 
    }

    pRes.nTerm = k;
    pRes.term = (MONOMIO*)realloc(pRes.term, (k)*sizeof(MONOMIO));
    
    burbuja(pRes);
    
    printf("Resultados:\n");

    //Imprime el grado (Primera impresión en pantalla)
   if (p1.grado > p2.grado)
    {
        pRes.grado = p1.grado;
        
    }
    else if(p1.grado < p2.grado)
    {
        pRes.grado = p2.grado;
       
    } else{
        pRes.grado = p1.grado;
    
    }

    gradomayor = pRes.grado;
    printf(" El grado del polinommio resultante es: %d\n", gradomayor);

    //Imprimir resultado
    for(; h<k; h++)
    {
        printf("%.3f\t%d\t", pRes.term[h].coef, pRes.term[h].exp);
    }
    return pRes;
}

/**
 * @brief Función que realiza la resta entre dos polinomios
 * @param p1 primer polinomio ingresado
 * @param p2 segundo polinomio ingresado
 * @return POLINOMIO lo que retorna es un apuntador de tipo POLINOMIO con el polinomio resultante
 * @programador: Jasso Vázquez Sara, Juárez Herrera Erick Adrián, Pérez Ortiz Sofia
 * @ÚltimaModificación: 28 diciembre 2021
 */
POLINOMIO resta(POLINOMIO p1, POLINOMIO p2)
{
    POLINOMIO pRes;
    MONOMIO t, t2;

    int i = 0, j = 0, k = 0, h = 0;
    //int grado, nTerm;

    p1.term = (MONOMIO *)malloc(p1.nTerm * sizeof(MONOMIO));
    p2.term = (MONOMIO *)malloc(p2.nTerm * sizeof(MONOMIO));
    pRes.term = (MONOMIO *)malloc((p1.nTerm + p2.nTerm) * sizeof(MONOMIO));

    for (int g = 0; g < p1.nTerm; g++)
    {
        printf("Ingrese el termino %d del polinomio 1:\n", g);
        scanf("%f\t%d", &p1.term[g].coef, &p1.term[g].exp);
    }

    for (int o = 0; o < p2.nTerm; o++)
    {
        printf("Ingrese el termino %d del polinomio 2:\n", o);
        scanf("%f\t%d", &p2.term[o].coef, &p2.term[o].exp);
    }

//Comparacion

int gradomayor;

    while (i < p1.nTerm)
    {
        while (j < p2.nTerm)
        {
            t = p1.term[i];
            t2 = p2.term[j];
            if (t.exp == t2.exp)
            {
                pRes.term[k].coef = t.coef - t2.coef;
                pRes.term[k].exp = t.exp;
                k++;
                i++;
                j++;
            }
            else if (t.exp > t2.exp)
            {
                pRes.term[k].coef = t.coef;
                pRes.term[k].exp = t.exp;
                k++;
                i++;
            }
            else if (t.exp < t2.exp)
            {
                pRes.term[k].coef = t2.coef;
                pRes.term[k].exp = t2.exp;
                k++;
                j++;
            } 
        } 
    }

    pRes.nTerm = k;
    pRes.term = (MONOMIO*)realloc(pRes.term, (k)*sizeof(MONOMIO));
    
    burbuja(pRes);
    
    printf("Resultados:\n");

    //Imprime el grado (Primera impresión en pantalla)
   if (p1.grado > p2.grado)
    {
        pRes.grado = p1.grado;
        
    }
    else if(p1.grado < p2.grado)
    {
        pRes.grado = p2.grado;
       
    } else{
        pRes.grado = p1.grado;
    
    }

    gradomayor = pRes.grado;
    printf(" El grado del polinommio resultante es: %d\n", gradomayor);

    //Imprimir resultado
    for(; h<k; h++)
    {
        printf("%.3f\t%d\t", pRes.term[h].coef, pRes.term[h].exp);
    }
    return pRes;
}



/**
 * @brief Función que realiza la multiplicación entre un polinomio ingresado y un escalar ingresado
 * @param p1 polinomio ingresado
 * @param n escalar ingresado
 * @return POLINOMIO lo que retorna es un apuntador de tipo POLINOMIO con el polinomio resultante
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 28 diciembre 2021
 */
POLINOMIO multEsc(POLINOMIO p1)
{
    POLINOMIO pRes;
    int k,n1;
    float escalar=0;

    //Reserva de memoria
    p1.term = (MONOMIO*)malloc(k*sizeof(MONOMIO));
    pRes.term =  (MONOMIO*)malloc(p1.nTerm*sizeof(MONOMIO));//Tiene el mismo tamaño que el polinomio ingresado

    for (int g = 0; g < p1.nTerm; g++)
    {
        printf("Ingrese el termino %d del polinomio 1:\n", g);
        scanf("%f\t%d", &p1.term[g].coef, &p1.term[g].exp);
    }


    printf("Ingresa el escalar a multiplicar:\n");
    scanf("%f",&escalar);

    for (int i = 0; i < p1.nTerm; i++)
    {
        pRes.term[i].coef = p1.term[i].coef * escalar;
        pRes.term[i].exp = p1.term[i].exp;
    }
    pRes.grado = p1.grado;
    pRes.nTerm = p1.nTerm;
    pRes.term = (MONOMIO*)realloc(pRes.term, (p1.nTerm)*sizeof(MONOMIO));
    printf("Grado del polinomio resultante: %d\n", pRes.grado);

    //Imprimir resultado
    for(int j=0;j<p1.nTerm;j++)
    {
        printf("%.3f\t%d\t", pRes.term[j].coef, pRes.term[j].exp);
    }

    return pRes;
}

/**
 * @brief Función que realiza la multiplicación entre dos polinomios ingresados
 * @param p1 primer polinomio ingresado
 * @param p2 segundo polinomio ingresado
 * @return POLINOMIO lo que retorna es un apuntador de tipo POLINOMIO con el polinomio resultante
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 28 diciembre 2021
 */
POLINOMIO mult(POLINOMIO p1, POLINOMIO p2)
{
    POLINOMIO pRes;
    int h=0;
    p1.term = (MONOMIO *)malloc(p1.nTerm * sizeof(MONOMIO));
    p2.term = (MONOMIO *)malloc(p2.nTerm * sizeof(MONOMIO));
    pRes.term = (MONOMIO *)malloc((p1.nTerm + p2.nTerm) * sizeof(MONOMIO));

    for (int g = 0; g < p1.nTerm; g++)
    {
        printf("Ingrese el termino %d del polinomio 1:\n", g);
        scanf("%f\t%d", &p1.term[g].coef, &p1.term[g].exp);
    }

    for (int o = 0; o < p2.nTerm; o++)
    {
        printf("Ingrese el termino %d del polinomio 2:\n", o);
        scanf("%f\t%d", &p2.term[o].coef, &p2.term[o].exp);
    }

    if (p1.nTerm > p2.nTerm)
    {
        for (int i = 0; i < p1.nTerm; i++)
        {
            for (int j = 0; j < p2.nTerm; j++)
            {
                pRes.term[i].coef = p1.term[i].coef * p2.term[j].coef;
                pRes.term[i].exp = p1.term[i].exp + p2.term[j].exp;
            }
        }
    }
    else
    {
        if (p1.nTerm < p2.nTerm)
        {
            for (int i = 0; i < p1.nTerm; i++)
            {
                for (int j = 0; j < p2.nTerm; j++)
                {
                    pRes.term[i].coef = p2.term[i].coef * p1.term[j].coef;
                    pRes.term[i].exp = p2.term[i].exp + p1.term[j].exp;
                }
            }
        }
        else
        {
            for (int i = 0; i < p1.nTerm || i < p2.nTerm; i++)
            {
                pRes.term[i].coef = p1.term[i].coef * p2.term[i].coef;
                pRes.term[i].exp = p1.term[i].exp + p2.term[i].exp;
            }
        }
    }
    burbuja(pRes);
    printf("Resultados:\n");
    //Imprime el grado 
    pRes.grado = p1.term[0].exp + p2.term[0].exp;
    printf("Grado del polinomio resultante: %d\n", pRes.grado);

    //Imprimir resultado
    for(; h<pRes.nTerm; h++)
    {
        printf("%.3f\t%d\t", pRes.term[h].coef, pRes.term[h].exp);
    }
    return pRes;
    
}

/**
 * @brief Función que elabora la división de un polinomio entre un monomio
 * @param p1 polinomio ingresado
 * @param p2 monomio ingresado
 * @return POLINOMIO lo que retorna es un apuntador de tipo POLINOMIO con el polinomio resultante
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 28 diciembre 2021
 */

POLINOMIO divMon(POLINOMIO p1)
{
    POLINOMIO pRes;
    int i = 0;
    MONOMIO aux;
    MONOMIO p2;
    int  k;

    k = p1.nTerm;

    //Reserva de memoria
    p1.term = (MONOMIO*)malloc(k*sizeof(MONOMIO));
    pRes.term =  (MONOMIO*)malloc(k*sizeof(MONOMIO));//Tiene el mismo tamaño que el polinomio ingresado

    for (int g = 0; g < p1.nTerm; g++)
    {
        printf("Ingrese el termino %d del polinomio 1:\n", g);
        scanf("%f\t%d", &p1.term[g].coef, &p1.term[g].exp);
    }

    printf("Ingresa el monomio divisor: \n");
    scanf("%f\t%d", &p2.coef, &p2.exp);

    for (; i < p1.nTerm; i++)
    {
        pRes.term[i].coef = p1.term[i].coef / p2.coef;
        pRes.term[i].exp = p1.term[i].exp - p2.exp;
    }
    
    pRes.nTerm = k;
    pRes.term = (MONOMIO*)realloc(pRes.term, (k)*sizeof(MONOMIO));
    pRes.grado = p1.term[0].exp-p2.exp;
    printf("El grado del polinomioo resultante es: %d\n",pRes.grado);
    //Tiene el mismo numero de terminos que p1 el pRes
    
    //Imprimir resultado
    for(int g=0; g<k;g++)
    {
        printf("%.3f\t%d\t", pRes.term[g].coef, pRes.term[g].exp);
    }
    return pRes;
}

//--------FUNCIONES RELACIONADAS CON LOS ARCHIVOS---------

/**
 * @brief Función que abre el contenido de un archivo en modo lectura (r)
 * @param filename Nombre del archivo
 * @return Nada, debido a que es una función de tipo void
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 23 diciembre 2021
 */
void open_in_file(char *filename)
{
    in_file = fopen(filename, "r");
    if (!in_file)
    {
        printf("No tienes permisos suficientes para abrir %s\n", filename);
    }
}

/**
 * @brief Función que abre el contenido de un archivo en modo lectura/escritura (r+)
 * @param filename Nombre del archivo
 * @return Nada, debido a que es una función de tipo void
 * @programador: Juárez Herrera Erick Adrián
 * @ÚltimaModificación: 23 diciembre 2021
 */
void open_out_file(char *filename)
{
    out_file = fopen(filename, "r+");
    if (!out_file)
    {
        printf("No tienes permisos para abrir %s\n", filename);
    }
}


/**
 * @brief Función que se encarga de escribir en un archivo lo polinomios en memoria
 * @return Nada, debido a que es una función de tipo void
 * @programador: Pérez Ortiz Sofia
 * @ÚltimaModificación: 27 diciembre 2021
 */
void escribirEnArchivo()
{
    FILE *archivo; 
    archivo = fopen("polinomios1.txt", "w+"); 

    if (archivo != NULL) 
    { 
        printf("El archivo se abrio correctamente.\n"); 

        char pol[80];
        char coeficiente[5];
        char exponente[5];

        printf("countMemory archivo: %d", countMemory);

        for (int k = 1; k <= countMemory; k++)    
        {
            memset(pol, 0, 80); //Limpiamos cadena
            for (int j = 0; j < dynMemory[k].nTerm ; j++) 
            {  
                sprintf(pol, "%.3f", dynMemory[k].term[j].coef);    
                fputs (pol, archivo);
                fputs ("\t", archivo);
                sprintf(pol, "%d", dynMemory[k].term[j].exp);    
                fputs (pol, archivo);               
                fputs ("\t", archivo);
                
            }
            fputs("\n",archivo);
        }
        int res = fclose(archivo); 
        printf("fclose = %d\n", res); 
        printf("Se realizo la escritura con exito\n");
    } 
    else 
    { 
        printf("Error al abrir el archivo.\n"); 
        printf("El archivo no existe o no se tienen permisos de lectura.\n"); 
    }

}

/**
 * @brief Función que lee polinomios desde un archivo
 * @param nombre Cadena del nombre del archivo a leer
 * @return dynMemory, retorna los polinomoios guardados
 * @programador: Jasso Vázquez Sara, Juárez Herrera Erick Adrián, Pérez Ortiz Sofia 
 * @ÚltimaModificación: 28 diciembre 2021
 */
POLINOMIO *leerArchivo(char *nombre)
{
    in_file = fopen("polinomios1.txt", "r"); 

    if (in_file != NULL) 
    { 
        printf("El archivo se abrio correctamente.\n"); 

        char pol[80];
        char coeficiente[5];
        char exponente[5];

        printf("countMemory archivo: %d\n", countMemory);

        do{
            if(fgets(dynMemory,80, in_file))
            {
                printf("%s", dynMemory);
            }
        }while(!feof(nombre));

        int res = fclose(in_file); 
        printf("fclose = %d\n", res); 
        printf("Se realizo la lectura con exito\n");
    } 
    else 
    { 
        printf("Error al abrir el archivo.\n"); 
        printf("El archivo no existe o no se tienen permisos de lectura.\n"); 
    }
    return dynMemory;
}


//--------FUNCIONES RELACIONADAS CON LA MEMORIA---------


/**
 * @brief Función que va almacenando los polinomios ingresados en la memoria
 * @param p Polinomio ingresado
 * @return Nada, debido a que es una función de tipo void
 * @programador: Juárez Herrera Erick Adrián, Pérez Ortiz Sofia
 * @ÚltimaModificación: 28 diciembre 2021
 */
void memoryWrite(POLINOMIO p)
{
    countMemory++;
    printf("\tcountMemory write:%d\n",countMemory);
    dynMemory[countMemory] = p;
}


/**
 * @brief Función que imprime todos los polinomios almacenados en memoria
 * @return Nada, debido a que es una función de tipo void
 * @programador: Pérez Ortiz Sofia
 * @ÚltimaModificación: 27 diciembre 2021
 */
void polPrint()
{

    printf("Los polinomios almacenados son:\n");
    for (int k = 1; k <= countMemory; k++)    
    {
        for (int j = 0; j < dynMemory[k].nTerm ; j++)    
            printf("%.3f\t%d\t", dynMemory[k].term[j].coef, dynMemory[k].term[j].exp);
        printf("\n");
    }
}