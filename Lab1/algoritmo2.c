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
    int* recorrido;
    int tamanioRecorrido;
    int pActual;
}Estado;

int aux;//variable para las IDs

archivo leerArchivo(char nombreArchivo[30]);

Estado crearEstado(int posicionActual,int* recorrido,int tamanio,int pActual,int pTraslado,int id);

Estado *eliminarEstado(Estado *abiertos, int *size);

Estado *agregarEstado(Estado * abiertos,int * size, Estado paraAgregar);

int verificarRecorrido(int* lista,int buscar,int tamanio);

void mostrarEstado(Estado A);
int main(){
    char nombreArchivo[30];
    printf("Ingrese el nombre del archivo a leer (con su respectiva extension)\npor ejemplo RT_4_30.txt\n");
    scanf("%s",nombreArchivo);

    archivo A=leerArchivo(nombreArchivo); //generar grafo
    //prueba crear estado
    Estado inicial;
    int* L=(int*)malloc(sizeof(int)*2);
    L[0]=1;
    L[1]=2;
    inicial=crearEstado(1,L,2,0,8,0);
    mostrarEstado(inicial);
   

    return 0;
}
void mostrarEstado(Estado A){
    printf("\n\n");
    printf("id : %d\n",A.id);
    printf("pActual : %d\n",A.pActual);
    int i;
    printf("recorrido\n");
    for(i=0;i<A.tamanioRecorrido;i++){
        printf("%d ",A.recorrido[i]);
    }
    printf("\n\n");
}
Estado crearEstado(int posicionActual,int* recorrido,int tamanio,int pActual,int pTraslado,int id){
    Estado salida;

    int* nuevoRec = (int*)malloc(sizeof(int)*tamanio+1);
    int i;
    for(i=0;i<tamanio;i++){
        nuevoRec[i]=recorrido[i];
    }
    nuevoRec[tamanio+1]=posicionActual;
    //ahora relleno la struct
    salida.id=aux;
    aux++;
    salida.idAnterior=id;
    salida.posicionActual=posicionActual;
    salida.recorrido=nuevoRec;
    salida.tamanioRecorrido=tamanio+1;
    salida.pActual=pActual+pTraslado;

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
int verificarRecorrido(int* lista,int buscar,int tamanio){
    int i;
    //1 si esta, 0 si no esta
    for (int i = 0; i < tamanio; i++){
		if(lista[i]==buscar){
            return 1;
        }
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