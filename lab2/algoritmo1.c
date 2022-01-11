#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct fila{
    float v;
    float p;
    float ponderacion; // V - P - V/P
}fila;

typedef struct archivoALeer{
    int pMax;
    int nFilas;
    fila* lista;
}archivo;

typedef struct estadoStruct{
    int* recorrido;
    int pActual;
    int maximoActual;
}Estado;
int aux;
archivo leerArchivo(char nombreArchivo[30]);

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\npor ejemplo knapPI_1_10_269.txt\n");
    scanf("%s",nombreArchivo);
    aux=0;
    archivo a = leerArchivo(nombreArchivo);
    //ordenamos por mayor ponderacion v/p 
        //(quicksort)
    //greedy por mayor v/p
    /*int i=0;
    while((i<=a.nFilas) && (solucion.pActual<a.pMax)){
        if(solucion.pActual+a.matriz[i][1]<=a.pMax){
            solucion.pActual = solucion.pActual+a.matriz[i][1];
            solucion.maximoActual=solucion.maximoActual+a.matriz[i][0];
        }
        i = i + 1;
    }*/
    //entregamos solucion del greedy
        //la mejor solucion es mostrarsolucion(solucion)
    return 0;
}
archivo leerArchivo(char nombreArchivo[30]){
    FILE *fp = fopen(nombreArchivo,"r");
    archivo salida;
    char separacion[2] = "_";
    char separacion2[2] = ".";
    char *pedacito;
    pedacito = strtok(nombreArchivo,separacion); // no me sirve el nombre, por lo que no lo guardo en ninguna parte
    pedacito = strtok(NULL,separacion); // no me sirve el nombre, por lo que no lo guardo en ninguna parte
    pedacito = strtok(NULL,separacion);
    salida.nFilas = atoi(pedacito);
    pedacito = strtok(NULL,separacion2);
    salida.pMax = atoi(pedacito);
    fila datos;
    fila* lista=(fila*)malloc(sizeof(fila)*salida.nFilas);
    for (int i = 0; i <salida.nFilas; i++){
        
        fscanf(fp,"%f %f\n",&datos.v,&datos.p);
        datos.ponderacion= (datos.v/datos.p);
        lista[i]=datos;
    }
    salida.lista=lista;
    printf("leido\n\n");
    for (int i = 0; i < salida.nFilas; i++){
        printf("%f %f %f \n",lista[i].v,lista[i].p,lista[i].ponderacion); 
    }
    printf("\n");
    fclose(fp);
    return salida;
}
