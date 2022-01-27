#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct archivoALeer{
    int pMax;
    int nFilas;
    int **matriz;
}archivo;

typedef struct intArray{
    int numero; 
    int largo;
}Array;

typedef struct estadoStruct{
    int id;
    int idAnterior;
    int filaActual;
    Array* recorrido;
    int pActual;
    int maximoActual;
    // agregar mas
}Estado;

int aux;

archivo leerArchivo(char nombreArchivo[30]);
Estado crearEstado(int filaActual,Array* recorrido,int pActual,int maximoActual,int id);
Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);
Estado *eliminarEstado(Estado *abiertos, int *size);
void mostrarResultado(Estado * arreglo,int size);
Array* agregarEntero(Array* lista,int numero);
int estadoCorte(Estado entrada,int pMax);

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\npor ejemplo knapPI_1_10_269.txt\n");
    scanf("%s",nombreArchivo);
    archivo a = leerArchivo(nombreArchivo);

    ejecutarAlgoritmo(a);




    return 0;
}

void ejecutarAlgoritmo(archivo a){
    Array* listaVacia =(Array*)malloc(sizeof(Array)*1);
    listaVacia[0].numero=0;
    listaVacia[0].largo=1;
    int canAbiertos = 0; 
	int canCerrados = 0;
    aux = 0;
    Estado estActual,estSiguiente;
    Estado * abiertos = (Estado*)malloc(sizeof(Estado)*canAbiertos);
	Estado * cerrados = (Estado*)malloc(sizeof(Estado)*canCerrados);
    Estado inicial;
    inicial.id=0;
    inicial.filaActual = 0;
    inicial.recorrido = listaVacia;
    inicial.pActual = 0;
    inicial.maximoActual = 0;
    abiertos = agregarEstado(abiertos,&canAbiertos,inicial);

    printf("\n*--------------------Se procedera a buscar la solucion a continuacion:--------------------*\n");
    int pActual,maximoActual;

    while(canAbiertos>0){
        estActual = abiertos[0]; // tomamos el primer estado
        abiertos = eliminarEstado(abiertos,&canAbiertos); // lo eliminamos de la lista de abiertos
        cerrados = agregarEstado(cerrados,%canCerrados,estActual);
        if(estadoCorte(estActual,a.pMax) == 1){ // s
            mostrarResultado(cerrados,canCerrados-1);
            break;
        }else{
            if((estActual.pActual +a.matriz[estActual.filaActual+1][1]) <= a.pMax){
                pActual = estActual.pActual + a.matriz[estActual.filaActual+1][1];
                maximoActual = estActual.maximoActual + a.matriz[estActual.filaActual+1][0];
                estSiguiente = crearEstado(estActual.filaActual+1,listaVacia,pActual,maximoActual,estActual.id);
                abiertos = agregarEstado(abiertos,&canAbiertos,estSiguiente);
            }else{


            }
        }
    }




}

Estado crearEstado(int filaActual,Array* recorrido,int pActual,int maximoActual,int id){
    Estado nuevoEstado;
    Array* lista =agregarEntero(recorrido,filaActual);
    nuevoEstado.recorrido=lista;
    nuevoEstado.filaActual = filaActual;
    nuevoEstado.pActual = pActual;
    nuevoEstado.maximoActual = maximoActual;
    nuevoEstado.id = aux;
    aux++;
    nuevoEstado.idAnterior = id;
    return nuevoEstado;

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

// modificado para eliminar al final
Estado *eliminarEstado(Estado *abiertos, int *size){
	Estado * listaNueva = (Estado*)malloc(sizeof(Estado)*(*size-1));
	for (int i = 0; i < *size-1; ++i){
		listaNueva[i] = abiertos[i];
	}
	*size = *size - 1;
	free(abiertos);
	return listaNueva;
}

void mostrarResultado(Estado * arreglo,int size){
	printf("Los pasos que se hicieron para llegar a la solucion fueron:\n\n");
	while (arreglo[size].id != 0){
		printf("%s\n\n", arreglo[size].transicion);
		size = arreglo[size].idAnterior;
	}
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

Array* agregarEntero(Array* lista,int numero){
    Array* listaNueva = (Array*)malloc(sizeof(Array)*(lista[0].largo+1));
    for (int i = 0; i < lista[0].largo; i++){
        listaNueva[i].numero = lista[i].numero;
        listaNueva[i].largo = lista[i].largo+1;

    }
    listaNueva[lista[0].largo].numero = numero;
    listaNueva[lista[0].largo].largo = lista[0].largo+1;

    return listaNueva;
    

}

int estadoCorte(Estado entrada,int pMax){
    if (entrada.pActual > pMax){
        return 1;
    }
    /*if(entrada.pActual == pMax){
        printf("id:%d\n",entrada.id);
        printf("maximoActual:%d\n",entrada.maximoActual);
    }*/
    return 0;

}