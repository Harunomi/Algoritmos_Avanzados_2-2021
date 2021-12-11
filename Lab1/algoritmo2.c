#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct archivoALeer{
    int pMax;//mejor valor posible
    int nTamanio; //tamanio NxN del grafo
    int **grafo;
}archivo;

typedef struct estadoStruct{
    int id;
    int idAnterior;
    int posicionActual;
    int recorrido;
    int tamanioRecorrido;
    int pActual;
}Estado;

int aux;//variable para las IDs

archivo leerArchivo(char nombreArchivo[30]);

Estado crearEstado();

Estado *eliminarEstado(Estado *abiertos, int *size);

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);


int verificarRecorrido(int* lista,int buscar);

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\npor ejemplo RT_4_30.txt\n");
    scanf("%s",nombreArchivo);

    archivo A=leerArchivo(nombreArchivo);
    //buscarSolucion(a);
   

    return 0;
}
Estado crearEstado(){

}

Estado *eliminarEstado(Estado *abiertos, int *size){

}

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar){

}

int verificarRecorrido(int* lista,int buscar){

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