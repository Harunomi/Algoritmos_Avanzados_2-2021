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

int aux; // variable global

archivo leerArchivo(char nombreArchivo[30]);

void buscarSolucion(archivo a);

int estadoCorte(Estado entrada,int pMax);

Estado crearEstado(int filaActual,Array* recorrido,int pActual,int maximoActual,int id);

Estado *eliminarEstado(Estado *abiertos, int *size);

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);

void mostrarEstados(Estado * cerrados, int canCerrados);

int buscarEntero(Array *lista);

int verificarRecorrido(Array* lista,int buscar);

Array* agregarEntero(Array* lista, int numero);

int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\npor ejemplo knapPI_1_10_269.txt\n");
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
    Array* listaVacia =(Array*)malloc(sizeof(Array)*1);
    listaVacia[0].numero=0;
    listaVacia[0].largo=1;
    int canAbiertos = 0; 
	int canCerrados = 0;
    aux = 0;
    //int contador = 0; este contador lo usamos solo para tener feedback cuando probamos el codigo
    Estado estActual,estSiguiente;
    Estado * abiertos = (Estado*)malloc(sizeof(Estado)*canAbiertos);
	Estado * cerrados = (Estado*)malloc(sizeof(Estado)*canCerrados);
    //creamos y rellenamos el estado inicial de forma manual
    Estado inicial;
    inicial.id=0;
    inicial.filaActual=0;
    inicial.recorrido=listaVacia;
    inicial.pActual=0;
    inicial.maximoActual=0;

    printf("\nEspere un momento estamos generando la solucion\n"); 
    abiertos = agregarEstado(abiertos,&canAbiertos,inicial);
    int pActual,maximoActual;
    while (canAbiertos > 0){
        estActual = abiertos[0];//tomo el estado
        abiertos = eliminarEstado(abiertos,&canAbiertos);
        if (estadoCorte(estActual,a.pMax) == 1){//si no cumple lo desechamos
            continue;
        }else{//si cumple lo agregamos en cerrados y seguimos con el ciclo
            cerrados = agregarEstado(cerrados,&canCerrados,estActual);
            for (int i = 0; i < a.nFilas; i++){
                if (verificarRecorrido(estActual.recorrido,i) == 0){ // sino esta, lo generamos
                    pActual = estActual.pActual + a.matriz[i][1];
                    maximoActual = estActual.maximoActual + a.matriz[i][0];
                    estSiguiente = crearEstado(i,estActual.recorrido,pActual,maximoActual,estActual.id);
                    abiertos = agregarEstado(abiertos,&canAbiertos,estSiguiente);
                   //contador++; //este contador lo usamos solo para tener feedback cuando probamos el codigo
                    /*if(contador%10000 == 0){
                        printf("posibles soluciones  %d\n",contador);
                    }*/
                }
            }   
        }

    }
    mostrarEstados(cerrados,canCerrados);
    
}
int verificarRecorrido(Array* lista,int buscar){
    int i;
    for(i=0;i<lista[0].largo;i++){
        if(lista[i].numero==buscar){
            return 1;
        }
    }
    return 0;
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
    /*if(entrada.pActual == pMax){
        printf("id:%d\n",entrada.id);
        printf("maximoActual:%d\n",entrada.maximoActual);
    }*/
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
    int mayor,posicion,i;
    mayor=0;
    posicion=0;
    printf("Buscando la mejor solucion...\n");
    for (i = 0; i < canCerrados; i++){
        if(cerrados[i].maximoActual>mayor){
            posicion=i;
            mayor=cerrados[i].maximoActual;
        }
    }
    printf("\nSolucion encontrada\n\n");
    printf("ID: %d\n",cerrados[posicion].id);
    printf("ID ANTERIOR: %d\n",cerrados[posicion].idAnterior);
    printf("P ACTUAL: %d\n",cerrados[posicion].pActual);
    printf("MAXIMO ACTUAL: %d\n",cerrados[posicion].maximoActual);
    printf("\n\n");
}

int buscarEntero(Array *lista){

    return 0;
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

void buscarMayor(Estado* lista,int total){
    int mayorActual;

}