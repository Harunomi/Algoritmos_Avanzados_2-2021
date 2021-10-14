# se asume que a este punto ya tenemos leido el archivo con los datos necesarios 
# archivo siendo una struct
# definimos como estado inicial la primera fila (fila 0).
# nuestra transicion sera pasar a la siguiente fila
# hasta que se llegue a la del inicio


def cola():

def algoritmo(archivo) :
    cantAbiertos = 0 # puntero /c
    cantCerrados = 0 # puntero /c
    abiertos = malloc() # c
    cerrados = malloc() # c
    estadoInicial = crearEstado(0) #creamos el estado inicial #c
    abiertos = agregarEstado(abiertos,estadoInicial,cantAbiertos) # agregamos el estado a la lista de abiertos (1)
    while (cantAbiertos > 0):
        estadoActual = abiertos[0]
        abiertos = eliminarEstado(abiertos,cantAbiertos) # O(n)
        cerrados = agregarEstado(cerrados,estadoActual,cantCerrados) # O(n)
        if (estadoActual->pActual > archivo->pMax) :
            continue
        else:
            abiertos = generarEstados(abiertos,estadoActual,cantAbiertos) # generarEstados O(n)
            
    buscarSolucion(cerrados,archivo->pMax)

'''
Calculo Complejidad
T(n)=C+m(n+n+cn)+n
=>C+mn+mn+mcn+n
=>C+2mn+mcn+n
por cota superior asumimos m=n
=>C+2n^2+Cn^2+n
=>C+3n^2+n 
nuevamente por cota superior dejamos todas las N como la de mayor grado 
=>C+4n^2 => K=4 , O(n^2)
'''
                




