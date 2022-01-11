#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct archivoALeer{
    int pMax;//mejor valor posible
    int nTamanio; //tamanio NxN del grafo
    int **grafo;
}archivo;

typedef struct estadoStruct{
    int posicionInicial;
    int posicionActual;
    int* recorrido;
    int pActual;
}Estado;


archivo leerArchivo(char nombreArchivo[30]);



int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\n");
    printf("RT_4_30.txt\nRT_6_78.txt\n");

    scanf("%s",nombreArchivo);
    printf("\n");

    archivo a=leerArchivo(nombreArchivo); //generar grafo
    //ahora que ya tenemos el grafo leido, comenzamos con greedy
    //nuestro criterio sera tomar el camino demenos peso
    //no podemos ir a un nodo que ya fue visitado, tampoco podemos tomar los caminos con valor -1
    //ya que estos representan el nodo en el que nos encontramos actualmente
    int i,j,pos;
    pos=0;

    for(i=0;i<a.nTamanio;i++){//recorrer columna1 (el nodo)
        for(j=0;j<a.nTamanio;j++){//recorrer la filaN en la que estamos( para seleccionar camino mas corto)
            //buscar el mas corto que no sea -1 y que no hayamos pasado por ahi 
            //aqui designamos tambien el siguiente valor de pos
        }
        //hacer el movimineto una vez revisada toda la fila
        //pos seria el nodo que visitamos(inicia en 0)

    }
    
    return 0;
}

archivo leerArchivo(char nombreArchivo[30]){
    FILE *fp = fopen(nombreArchivo,"r");
    archivo salida;
    char separacion[2] = "_";
    char separacion2[2] = ".";
    char *pedacito;
    pedacito = strtok(nombreArchivo,separacion); //no sirve
    pedacito = strtok(NULL,separacion);//tamanio grafo
    //con el tamanio del grafo, asignamos memoria para este
    salida.nTamanio=atoi(pedacito);
    salida.grafo=(int**)malloc(sizeof(int)*salida.nTamanio);
    int i,j;
    for(i = 0; i <salida.nTamanio;i++){
        salida.grafo[i]=(int*)malloc(sizeof(int)*salida.nTamanio);
    }
    pedacito = strtok(NULL,separacion2);//valor minimo
    salida.pMax=atoi(pedacito);//guardamos el valor del recorrido minimo

    pedacito = strtok(NULL,separacion2);//este no sirve ya que es el txt
    int valor;
    //rellenar el grafo
    for(i=0;i<salida.nTamanio;i++){
        for(j=0;j<salida.nTamanio;j++){
            //ahora leemos el grafo
            fscanf(fp,"%d", &valor);
            salida.grafo[i][j]=valor;
            printf("%d ",valor);
        }
        printf("\n");
    }
    fclose(fp);
    return salida;
}
