def algoritmo(archivo):
    cantAbiertos = 0 # puntero /c
    cantCerrados = 0 # puntero /c
    abiertos = malloc() # c
    cerrados = malloc() # c
    abiertos = generarEstadosIniciales(abiertos,cantAbiertos,archivo->cantNodos) # agregamos el estado a la lista de abiertos (c)
    while (cantAbiertos>0):
        estadoActual = abiertos[0]
        abiertos = eliminarEstado(abiertos,cantAbiertos) # O(n)
        cerrados = agregarEstado(cerrados,estadoActual,cantCerrados) # O(n)
        abiertos = buscarSiguientePosicion(abiertos,estadoActual) # O(n)


    buscarOptimo(cerrados,archivo->rutaOptima) # O(n)    

 '''
segundo calculo
Calculo Complejidad
T(n)=C+n+M(c+n+n+n)+n
=>C+2n+mc+3mn
por cota superior m=n
=>C+2n+nc+3n^2
nuevamente asumimos el n de mayor grado
=>C+2n^2+cn^2+3n^2
dejamos cn^2 como n^2 y la constante es absorcida por C
=>C+6n^2
=>C+6n^2 => K=6 , O(n^2)
en el peor de los casos tendriamos un O(n^2).
'''