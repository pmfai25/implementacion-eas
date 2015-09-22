Algoritmos evolutivos:

  * Basados en población de soluciones:
No se trabaja en uns solución que se contruye poco a poco, como sucede en los greddy. Crea una población de posibles recorridos y la evoluciona
  * Se evoluciona el genotipo, no el fenotipo. Uno no trabaja directamente con la solución, sino con una codificación de la solución.

La primera decisión de implementación es la codificación de la población:
  * Array, lista, conjunto, mapa

Representación de un cromosoma:
  * Cadena, binaria, lista, etc

Fitness:
  * Cantidad de descendencia de un indivíduo
  * Coste o adecuación de una solución
  * Siempre es necesario que se puedan comparar dos indivíduos (da igual si es numérico o no lo es)
  * La implementación es fundamental

Selección proporcional al fitness

Rueda de la ruleta:
  * si tenemos un conjunto de fitness: 4, 3 y 1, se saca un número al azar entre [0-1].
    * Si Sale entre 0 y 1/2, se reproduce el primero
    * Si Sale entre 1/2 y 7/8, se reproduce el segundo
    * Si Sale entre 7/8 y 1, se reproduce el tercero

Torneo
  * Se cogen X elementos al azar y se reproduce el mayor. Se repite N veces.

Equilibrio entre exploración y explotación.
  * El torne es más voraz

La reproducción:
  * Consiste en dos operadores: Mutación y entrecruzamiento

Mutación cambia valores en los cromosomas: Cambio aleatorio e individual
  * Si es binario cambia un 1 por un 0 y viceversa
  * Si es un caracter, cambia el carácter
  * Las mutaciones en la naturaleza son raras

Functor
  * Abstracción del operador genético
  * Aridad: Número de cromosomas que acepta

Otras operaciones
  * Son interesantes los métodos para trabajar con los cromosomas: poner a 0, duplicar tamaño, etc

Importancia del profiling

Ejemplo de profiling del proyecto subido a git:

https://plus.google.com/photos/112276417139397063494/albums/5870804132415879825?authkey=CKLa3tKdp527qAE

Aquí algunos tiempos medidos con el programa presente en git:

| TunnedOperator\_ByteArrayIndividual | 1 | 4 | 0 | 3 | 0 | 16 | 1 |
|:------------------------------------|:--|:--|:--|:--|:--|:---|:--|
| TunnedOperator\_StringIndividual    | 5 | 29 | 6 | 2 | 0 | 14345 | 1 |
| BasicOperator\_ByteArrayIndividual  | 1 | 9 | 1 | 1 | 0 | 37 | 1 |
| BasicOperator\_StringIndividual     | 73 | 23 | 6 | 0 | 0 | 15298 | 0 |