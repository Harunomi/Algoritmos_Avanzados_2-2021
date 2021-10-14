#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct archivoALeer{
    int pMax;
    int nFilas;
    int **matriz;
}archivo;


typedef struct estadoStruct{
    int id;
    int idAnterior;
    int filaActual;
    int *recorrido;
    int lenRecorrido;
    int pActual;
    int maximoActual;
    // agregar mas
}Estado;

int aux; // variable global

archivo leerArchivo(char nombreArchivo[30]);

void buscarSolucion(archivo a);


Estado *eliminarEstado(Estado *abiertos, int *size);

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);


int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\n");
    scanf("%s",nombreArchivo);
    archivo a = leerArchivo(nombreArchivo);
    buscarSolucion(a);
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
    int n,p;
    salida.matriz = (int**)malloc(sizeof(int*)*salida.nFilas);
    for (int i = 0; i < salida.nFilas; i++){
        
        salida.matriz[i] = (int*)malloc(sizeof(int)*2);
        fscanf(fp,"%d %d\n", &n,&p);
        salida.matriz[i][0] = n;
        salida.matriz[i][1] = p;
    }
    fclose(fp);
    return salida;
    
    

    
}


void buscarSolucion(archivo a){
    int *recorridoAux = (int*)malloc(sizeof(int)*0);
    int canAbiertos = 0; 
	int canCerrados = 0;
    Estado * abiertos = (Estado*)malloc(sizeof(Estado)*canAbiertos);
	Estado * cerrados = (Estado*)malloc(sizeof(Estado)*canCerrados);
}

int *append(int *entrada,int lenRecorrido,int valorAgregar ){
    int * listaNueva = (int*)malloc(sizeof(int)*(lenRecorrido+1));
    for (int i = 0; i < lenRecorrido; i++){
        listaNueva[i] = entrada[i];
    }
    listaNueva[lenRecorrido+1] = valorAgregar;
    return listaNueva;
    
}

Estado crearEstado(int filaActual,int *recorrido,int lenRecorrido,int pActual,int maximoActual,int id){
    Estado nuevoEstado;
    nuevoEstado.filaActual = filaActual;
    int *recorridoNuevo = append(recorrido,lenRecorrido,filaActual);
    nuevoEstado.recorrido = recorridoNuevo;
    nuevoEstado.pActual = pActual;
    nuevoEstado.maximoActual = maximoActual;
    nuevoEstado.lenRecorrido = lenRecorrido+1;
    nuevoEstado.id = aux;
    nuevoEstado.idAnterior = id;
    return nuevoEstado;

}

Estado *eliminarEstado(Estado *abiertos, int *size){
	Estado * listaNueva = (Estado*)malloc(sizeof(Estado)*(*size-1));
	for (int i = 1; i < *size; ++i){
		listaNueva[i-1] = abiertos[i];
	}
	*size = *size - 1;
	free(abiertos);
	return listaNueva;
}

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar){
	Estado * listaNueva = (Estado*)malloc(sizeof(Estado)*(*size+1));
	for (int i = 0; i < *size; ++i){
		listaNueva[i] = abiertos[i];
	}
	listaNueva[*size] = paraAgregar;
	*size = *size + 1;
	free(abiertos);
	return listaNueva;
}
