#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct archivoALeer{
    int pMax;//mejor valor posible
    int nTamanio; //tamanio NxN del grafo
    int **grafo;
}archivo;

typedef struct intArray{
    int numero; 
    int largo;
}Array;

typedef struct estadoStruct{
    int id;
    int idAnterior;
    int posicionInicial;
    int posicionActual;
    Array *recorrido;
    int pActual;
}Estado;

int aux;//variable para las IDs

archivo leerArchivo(char nombreArchivo[30]);

Estado crearEstado(int posicionActual,Array* recorrido,int pActual,int pTraslado,int id);

Estado crearEstadoInicial(int posicionActual,Array* recorrido);

Estado *eliminarEstado(Estado *abiertos, int *size);

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);

Array* agregarEntero(Array* lista,int numero);

int verificarRecorrido(Array* lista,int buscar);

int estadoCorte(Estado e,int pMax);

void buscarSolucion(archivo a);

void mostrarEstado(Estado A);




int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\n");
    printf("RT_4_30.txt\nRT_6_78.txt\n");

    scanf("%s",nombreArchivo);
    printf("\n");

    archivo a=leerArchivo(nombreArchivo); //generar grafo

    buscarSolucion(a);
    
    return 0;
}

void buscarSolucion(archivo a){
    
    int canAbiertos = 0; 
	int canCerrados = 0;
    aux = 0;
    //int contador = 0; este contador lo usamos solo para tener feedback cuando probamos el codigo
    Estado estActual, estSiguiente, inicial;
    Estado * abiertos = (Estado*)malloc(sizeof(Estado)*canAbiertos);
	Estado * cerrados = (Estado*)malloc(sizeof(Estado)*canCerrados);
    printf("GENERANDO LAS SOLUCIONES POSIBLES...\n\n");
    for (int i = 0; i < a.nTamanio; i++){
        Array* listaVacia =(Array*)malloc(sizeof(Array)*1);
        listaVacia[0].numero=i;
        listaVacia[0].largo=1;
        inicial = crearEstadoInicial(i,listaVacia);
        abiertos = agregarEstado(abiertos,&canAbiertos,inicial);

    }

    while(canAbiertos>0){
        estActual = abiertos[0];
        abiertos = eliminarEstado(abiertos,&canAbiertos);
        cerrados = agregarEstado(cerrados,&canCerrados,estActual);
        for (int i = 0; i < a.nTamanio; i++){
            if((a.grafo[estActual.posicionActual][i] != -1) && (verificarRecorrido(estActual.recorrido,i) == 0)){
                estSiguiente = crearEstado(i,estActual.recorrido,estActual.pActual,a.grafo[estActual.posicionActual][i],estActual.id);
                abiertos = agregarEstado(abiertos,&canAbiertos,estSiguiente);
            }
        }
    }

    
    for (int i = 0; i < canCerrados; i++){
        //mostrarEstado(cerrados[i]);
        int suma;
        int valorGrafo;
        int n,m;
        if(cerrados[i].recorrido[0].largo == a.nTamanio){
            estSiguiente = crearEstado(cerrados[i].recorrido[0].numero,cerrados[i].recorrido,cerrados[i].pActual,a.grafo[cerrados[i].posicionActual][cerrados[i].recorrido[0].numero],cerrados[i].id);
            if (estadoCorte(estSiguiente,a.pMax) == 1){
                printf("Encontrada la siguiente Solucion\n\n");
                mostrarEstado(estSiguiente);
                break;
            }
        }

    }   
}



void mostrarEstado(Estado e){
    printf("id: %d      idAnterior: %d\n",e.id,e.idAnterior);
    printf("posicionActual: %d      pActual: %d\n",e.posicionActual,e.pActual);
    printf("Recorrido: ");
    for (int i = 0; i < e.recorrido[0].largo; i++){
        printf("%d ",e.recorrido[i].numero);
    }
    printf("\n\n");
}

Estado crearEstadoInicial(int posicionActual,Array* recorrido){
    Estado nuevo; 
    nuevo.posicionActual = posicionActual;
    nuevo.posicionInicial = posicionActual;
    nuevo.recorrido = recorrido;
    nuevo.id = aux;
    aux++;
    nuevo.pActual = 0;
    nuevo.idAnterior = -1;
    return nuevo; 
    
}

Estado crearEstado(int posicionActual,Array* recorrido,int pActual,int pTraslado,int id){
    Estado salida;
    Array* nuevoRec = agregarEntero(recorrido,posicionActual);
    //ahora relleno la struct
    salida.id = aux;
    aux++;
    salida.idAnterior = id;
    salida.posicionActual = posicionActual;
    salida.recorrido = nuevoRec;
    salida.pActual = pActual + pTraslado;
    return salida;

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

int verificarRecorrido(Array* lista,int buscar){
    int i;
    //1 si esta, 0 si no esta
    for(int i = 0; i < lista[0].largo; i++){
		if(lista[i].numero==buscar){
            return 1;
        }
	}
    return 0;
}

int estadoCorte(Estado e,int pMax){
    if(e.pActual == pMax){
        return 1;
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
        }
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