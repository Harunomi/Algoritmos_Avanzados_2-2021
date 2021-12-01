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
    char *recorrido;
    int lenRecorrido;
    int pActual;
    int maximoActual;
    // agregar mas
}Estado;

int aux; // variable global

archivo leerArchivo(char nombreArchivo[30]);

void buscarSolucion(archivo a);

int *append(int *entrada,int lenRecorrido,int valorAgregar );

int estadoCorte(Estado entrada,int pMax);

int verificarRecorrido(int *recorrido,int lenRecorrido,int valor);

Estado crearEstado(int filaActual,int *recorrido,int lenRecorrido,int pActual,int maximoActual,int id);

Estado *eliminarEstado(Estado *abiertos, int *size);

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);

void mostrarEstados(Estado * cerrados, int canCerrados);

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\n knapPI_1_10_269.txt\n");
    scanf("%s",nombreArchivo);

    archivo a = leerArchivo(nombreArchivo);
    /* //mostrar matriz
    printf("mostrare la matriz\n");
    for (int i = 0; i < a.nFilas; i++){
        printf("%d %d\n",a.matriz[i][0],a.matriz[i][1]);
       
    }
    */
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
    char *recorridoAux = (char*)malloc(sizeof(char)*1);
    int canAbiertos = 0; 
	int canCerrados = 0;
    aux = 0;
    Estado estActual,estSiguiente;
    Estado * abiertos = (Estado*)malloc(sizeof(Estado)*canAbiertos);
	Estado * cerrados = (Estado*)malloc(sizeof(Estado)*canCerrados);
    Estado inicial = crearEstado(0,recorridoAux,0,a.matriz[0][1],a.matriz[0][0],aux);
    printf("\ncreado estado inicial\n");
    abiertos = agregarEstado(abiertos,&canAbiertos,inicial);
    while (canAbiertos > 0){
        estActual = abiertos[0];
        abiertos = eliminarEstado(abiertos,&canAbiertos);
        cerrados = agregarEstado(cerrados,&canCerrados,estActual);
        int pActual,maximoActual;

        if (estadoCorte(estActual,a.pMax) == 1){
        }else{
            for (int i = 0; i < a.nFilas; i++){
                if (verificarRecorrido(estActual.recorrido,estActual.lenRecorrido,i) == 0){ // sino esta, lo generamos
                    pActual = estActual.pActual + a.matriz[i][1];
                    maximoActual = estActual.maximoActual + a.matriz[i][0];
                    estSiguiente = crearEstado(i,estActual.recorrido,estActual.lenRecorrido,pActual,maximoActual,estActual.id);
                    abiertos = agregarEstado(abiertos,&canAbiertos,estSiguiente);
                }
            }   
        }

    }
    mostrarEstados(cerrados,canCerrados);
    
}


int verificarRecorrido(int *recorrido,int lenRecorrido,int valor){
    for (int i = 0; i < lenRecorrido; i++){
        if (recorrido[i] == valor){
            return 1;
        }
    }
    return 0;
}

int *append(int *entrada,int lenRecorrido,int valorAgregar ){
    int * listaNueva = (int*)malloc(sizeof(int)*(lenRecorrido+1));
    int i;
    for (i = 0; i < lenRecorrido; i++){
        listaNueva[i] = entrada[i];
    }
    listaNueva[i+1] = valorAgregar;
    return listaNueva;
    
}

Estado crearEstado(int filaActual,char *recorrido,int lenRecorrido,int pActual,int maximoActual,int id){
    Estado nuevoEstado;
    nuevoEstado.filaActual = filaActual;
    char *recorridoNuevo;// append(recorrido,lenRecorrido,filaActual);
    nuevoEstado.recorrido = recorridoNuevo;
    nuevoEstado.pActual = pActual;
    nuevoEstado.maximoActual = maximoActual;
    nuevoEstado.lenRecorrido = lenRecorrido+1;
    nuevoEstado.id = aux;
    aux++;
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
// si se paso del pMax retorna 1
int estadoCorte(Estado entrada,int pMax){
    if (entrada.pActual > pMax){
        return 1;
    }
    if(entrada.pActual == pMax){
        printf("id:%d\n",entrada.id);
        printf("maximoActual:%d\n",entrada.maximoActual);
    }
    return 0;
    
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

void mostrarEstados(Estado * cerrados, int canCerrados){
    for (int i = 0; i < canCerrados; i++){
        printf("ID: %d\n",cerrados[i].id);
        printf("ID ANTERIOR: %d\n",cerrados[i].idAnterior);
        printf("P ACTUAL: %d\n",cerrados[i].pActual);
        printf("MAXIMO ACTUAL: %d\n",cerrados[i].maximoActual);
        printf("RECORRIDO ACTUAL: ");
        for (int j = 0; j < cerrados[i].lenRecorrido; j++){
            printf("%d ",cerrados[i].recorrido[j]);
        }
        printf("\n\n");
    }
    
}
