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
    int pActual;
    int maximoActual;
}Estado;
int aux;
archivo leerArchivo(char nombreArchivo[30]);

void intercambiar(fila* a, fila* b) {
  fila temporal = *a;
  *a = *b;
  *b = temporal;
}
int particion(fila* arreglo, int izquierda, int derecha) {
  float pivote = arreglo[izquierda].ponderacion;
  while (1) {
    while (arreglo[derecha].ponderacion < pivote) {
      derecha--;
    }
    while (arreglo[izquierda].ponderacion > pivote) {
      izquierda++;
    }
    if (izquierda >= derecha) {
      return derecha;
    }else{
      intercambiar(&arreglo[izquierda], &arreglo[derecha]);
      izquierda++;
      derecha--;
    }
    }
}
void quicksort(fila* arreglo, int izquierda, int derecha) {
  if (izquierda < derecha) {
    int indiceParticion = particion(arreglo, izquierda, derecha);
    quicksort(arreglo, izquierda, indiceParticion);
    quicksort(arreglo, indiceParticion + 1, derecha);
  }
}

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\npor ejemplo knapPI_1_10_269.txt\n");
    scanf("%s",nombreArchivo);
    aux=0;
    Estado solucion;
    archivo a = leerArchivo(nombreArchivo);
    solucion.pActual=0;
    solucion.maximoActual=0;
    int i=0;
    while((i<=a.nFilas) && (solucion.pActual<a.pMax)){
        if(solucion.pActual+a.lista[i].p<=a.pMax){
            solucion.pActual = solucion.pActual+a.lista[i].p;
            solucion.maximoActual=solucion.maximoActual+a.lista[i].v;
        }
        i = i + 1;
    }
    printf("el valor encontrado fue %d\nutilizando el criterio de maximizar el resultado de valor/ponderacion",solucion.pActual);
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
    quicksort(lista,0,salida.nFilas);
    
    salida.lista=lista;
    printf("\n");
    fclose(fp);
    return salida;
}
