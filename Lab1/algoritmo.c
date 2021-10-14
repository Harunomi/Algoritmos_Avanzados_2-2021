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
    int pActual;
    int maximoActual;
    // agregar mas
}estado;

archivo leerArchivo(char nombreArchivo[30]);

void buscarSolucion(archivo a);


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
    int pActual;
    int maximo = 0;
    int i = 0;
    int j = 0;
    int maximoActual;
    printf("     %d\n",a.pMax);
    while (i <=a.nFilas){
        // reiniciamos los valores de las variables
        maximoActual = 0;
        pActual = 0;
        j = i;
        // valores de i = 7
        while(pActual < a.pMax){
            //valores j = 7,
            if(j>a.nFilas+1){
                j = 0;
            }
            pActual = pActual + a.matriz[j][1];
            if (pActual>a.pMax){
                break;
            }
            maximoActual = maximoActual + a.matriz[j][0];
            if (maximoActual >= maximo){
                maximo = maximoActual;
                printf("valor de i: %d\n",i);
                printf("maximo = %d\n",maximo);

            }
            j = j + 1;
            
            
        }
        i++; // avanzamos al siguiente numero
    }
    printf("El valor obtenido es: %d",maximo);
}

