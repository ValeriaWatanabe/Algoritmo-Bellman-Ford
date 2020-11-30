/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: USER
 *
 * Created on 17 de octubre de 2020, 12:13 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/resource.h>
#include <time.h>
#define INFINITO 5000

//Función para la impresión de las rutas 
void ImprimirSolucion(int distancia[],int V, int S)
{
    printf("\nNodo\tDistancia desde nodo %d \n",S);
    for(int i=0; i<V; i++)
    {
        printf("%d\t%d\n",i,distancia[i]);
    }
    return;
}

void VectorDistancia(int V, int A, int S, int arcos[A][3])
{
    int f, d, peso;
    //arreglo que contendrá las distancias más cortas
    int distancia[V];
    //Inicializacion de distancias con un valor infinito
    for(int i=0; i<V; i++)
    {
        distancia[i] = INFINITO;    
    }
    distancia[S] = 0;//la distancia del valor fuente es 0
    //Relajación
    for(int i=1; i<V; i++)
    {
        for(int j=0; j<A; j++)
        {
            f = arcos[j][0]; 
            d = arcos[j][1]; 
            peso = arcos[j][2];
            
            if(distancia[f] + peso < distancia[d])
            {
                //actualizacion de la distancia en caso de que se encuentre una mejor
                distancia[d] = distancia[f] + peso;
                //Impresión de la actualización
                ImprimirSolucion(distancia, V, S);
            }
        }
    }    
    //Busqueda de ciclos negativos
    for(int k=0;k<A;k++)
    {
        f = arcos[k][0] , d = arcos[k][1] ; peso = arcos[k][2];
        if(distancia[f]+ peso < distancia[d])
        {
             printf("Existen ciclos de peso negativo");
        }       
    }
    //Impresión del resultado final
    printf("\nResultado final: ");
    ImprimirSolucion(distancia, V, S);
    return;
}

int main() 
{
    //estructura para calcular la cantidad de memoria que consume el programa
    struct rusage uso;
    //se lee el archivo el cual contiene la informacion del grafo
    //depende de que topología se analize, se lee un archivo diferente 
    FILE *archivo = fopen("C:\\Users\\USER\\Documents\\Redes Compu\\Trabajo Integrador\\simple.txt","r");
    //Cantidad de vertices, Cantidad de aristas, nodo fuente
    int V, A, S; 
    fscanf(archivo,"%d", &V);//lee el primer numero del archivo que se refiere a la cantidad de vértices
    fscanf(archivo,"%d", &A);//lee el segundo numero del archivo que se refiere a la cantidad de aristas
    fscanf(archivo,"%d", &S);//lee el tercer numero del archivo que se refiere al nodo fuente
    //matriz para almacenar el valor de las aristas, nodo de origen y nodo destino
    int arcos[A][3];
    //almacenamiento de datos en la matriz
    for(int i=0; i<A; i++)
    {
        fscanf(archivo,"%d", &arcos[i][0]);//nodo origen
        fscanf(archivo,"%d", &arcos[i][1]);//nodo destino
        fscanf(archivo,"%d", &arcos[i][2]);//valor arista
    }
    //se llama al algoritmo de bellman-ford
    VectorDistancia(V, A, S, arcos);
    fclose(archivo);
    //se obtiene el valor de la cantidad de memoria
    getrusage(RUSAGE_SELF, &uso);
    float t = 1.0*(long)uso.ru_maxrss/1000;
    //se imprime valor de memoria utilizada
    printf("Uso de memoria: %f MB\n", t);
    return (EXIT_SUCCESS);
}

