## Día 18/04/2012 ##

Explicación de los algoritmos evolutivos.
Un breve resumen.

> _Los algoritmos evolutivos son métodos de optimización y búsqueda de soluciones basados en los postulados de la evolución biológica. En ellos se mantiene un conjunto de entidades que representan posibles soluciones, las cuales se mezclan, y compiten entre sí, de tal manera que las más aptas son capaces de prevalecer a lo largo del tiempo, evolucionando hacia mejores soluciones cada vez.
Los algoritmos evolutivos, y la computación evolutiva, son una rama de la inteligencia artificial. Son utilizados principalmente en problemas con espacios de búsqueda extensos y no lineales, en donde otros métodos no son capaces de encontrar soluciones en un tiempo razonable.
Siguiendo la terminología de la teoría de la evolución, las entidades que representan las soluciones al problema se denominan individuos o cromosomas, y el conjunto de éstos, población. Los individuos son modificados por operadores genéticos, principalmente el sobrecruzamiento, que consiste en la mezcla de la información de dos o más individuos; la mutación, que es un cambio aleatorio en los individuos; y la selección, consistente en la elección de los individuos que sobrevivirán y conformarán la siguiente generación. Dado que los individuos que representan las soluciones más adecuadas al problema tienen más posibilidades de sobrevivir, la población va mejorando gradualmente._

  1. clave, están basado en la evolución, población, etc..
> 2 clave, están basados en mutaciones y clonaciones.

Representación de cromosoma: Puede ser en principio una serie de 0 y 1, un vector, una lista...

El fitness lo usaremos como función de evaluación de cada uno de los individuos.
El fitness determina siempre los cromosomas que se van a reproducir, y aquellos que se van a eliminar, pero hay varias formas de considerarlo para seleccionar la población de la siguiente generación:

  * Usar el orden, o rango, y hacer depender la probabilidad de permanencia o evaluación de la posición en el orden.
  * Aplicar una operación al fitness para escalarlo; como por ejemplo el escalado sigma. En este esquema el fitness se escala
  * En algunos casos, el fitness no es una sola cantidad, sino diversos números, que tienen diferente consideración. Basta con que tal fitness forme un orden parcial, es decir, que se puedan comparar dos individuos y decir cuál de ellos es mejor. Esto suele suceder cuando se necesitan optimizar varios objetivos.

A veces el algoritmo evolutivo no depende en si del algoritmo sino del lenguaje de programación y la función fitness.

Ahora el profesor a pedido que implementemos un programa para contar 0 y 1 de un vector, cadena o lo que queramos pero con diferentes implementaciones de la función contar 1.

Hemos estado durante 25 minutos haciéndolo y lo he subido.

  * Mi primera función comprueba si es uno y si lo es, aumenta un contador, que al final devuelve.
  * El segundo algoritmo recorre la cadena y suma todos los 1 que encuentre, el resultado es el numero de unos.

Los vectores de prueba (poblacion) ha sido de 4 tipos:

  * Un vector donde el numero de 0 y 1 son aleatorios.
  * Un vector donde hay mas número de 0 que de 1.
  * Un vector donde hay mas número de 1 que de 0.
  * Un vector donde hay el mismo número de 1 que de 0.

El resultado es:

  * Vector Aleatorio:   Tiempo funcion1: 37 seg
  * Vector mas 0:       Tiempo funcion1: 45 seg
  * Vector mas 1:       Tiempo funcion1: 31 seg
  * Vector fifty:       Tiempo funcion1: 31 seg

  * Vector Aleatorio:   Tiempo funcion2: 31 seg
  * Vector mas 0:       Tiempo funcion2: 26 seg
  * Vector mas 1:       Tiempo funcion2: 22 seg
  * Vector fifty:       Tiempo funcion2: 31 seg

Por lo que el segundo algoritmo es más rápido para los 4 vectores definidos anteriormente.

Una vez evaluado el fitness, se tiene que crear la nueva población teniendo en cuenta que los buenos rasgos de los mejores se transmitan a esta. Para ello, hay que seleccionar a una serie de individuos encargados de tan ardua tarea. Y esta selección, y la consiguiente reproducción, se puede hacer de dos formas principales:

  * _Rueda de ruleta:_ se crea un pool genético formado por cromosomas de la generación actual, en una cantidad proporcional a su fitness. Si la proporción hace que un individuo domine la población, se le aplica alguna operación de escalado. Dentro de este pool, se cogen parejas aleatorias de cromosomas y se emparejan, sin importar incluso que sean del mismo progenitor (para eso están otros operadores, como la mutación). Hay otras variantes: por ejemplo, en la nueva generación se puede incluir el mejor representante de la generación actual. En este caso, se denomina método elitista.
  * _Selección de torneo:_ se escogen aleatoriamente un número T de individuos de la población, y el que tiene puntuación mayor se reproduce, sustituyendo su descendencia al que tiene menor puntuación.

Hemos hablado de que la ventaja de un algoritmo evolutivo es que no se queda en un mínimo local, ya que siempre luego pueden alcanzar el máximo.

Nos ha enseñado un powerpoint programado en visual basic de mutaciones y crossover que había realizado.

También nos ha enseñado un vídeo de como implementó un algoritmo genetico en una camara cannon.

Ahora hemos pasado a las transparencias donde se hablan de las operaciones básicas de los algoritmos evolutivos.

Dos tipos de operaciones.

  1. **MUTACION**

En una mutación es 1 individuo lo que va a cambiar. Es un cambio aleatorio e individual. No se debe abusar ya que puede ser letal.

Es cierto que es un mecanismo generador de diversidad, y, por tanto, la solución cuando un algoritmo genético está estancado, pero también es cierto que reduce el algoritmo genético a una búsqueda aleatoria. Siempre es más conveniente usar otros mecanismos de generación de diversidad, como aumentar el tamaño de la población, o garantizar la aleatoriedad de la población inicial.

Al individuo se le cambia un parte/partes de sus cromosomas para crear uno nuevo.

Tipos mas habituales de mutaciones: duplicación de cadenas o cambiar una base con otra base.

  1. **CRUZAMIENTO (Crossover)**
Combinación de individuos para dar uno, dos o varios individuos. Hay que asegurarse que entre dos cruces, el resultante no de el mismo.

Ahora el profesor nos ha pedido que implementemos una función de mutación y cruce sobre los vectores anteriores de 1 y 0.
Hemos dedicado 35 minutos y al final lo he subido a la plataforma.

El resultado es:

Mutar
Vector original: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
Vector Mutado: [0, 0, 0, 0, 1, 0, 0, 0, 0, 0]

Cruzar
Vector padre: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
Vector madre: [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
Vector Hijo: [[0, 0, 0, 0, 0], [1, 1, 1, 1, 1]]

Esto lo he subido, pero ahora lo volveré a subir haciendo que en vez de devolver un hijo, el cruce, devuelva dos (que es más normal que uno).

Al final de la clase hemos estado hablando sobre los profiler:
> _Es la investigación del comportamiento de un programa de computadora usando información reunida desde el análisis dinámico del mismo. El objetivo es averiguar el tiempo dedicado a la ejecución de diferentes partes del programa para detectar los puntos problemáticos y las áreas dónde sea posible llevar a cabo una optimización del rendimiento_

Hemos comentado el uso del profiler gprof para sistemas unix.
Dejo un tutorial de como usarlo en:
http://www.chuidiang.com/clinux/herramientas/profiler.php

Y por tanto, nos ha pedido utilizar un profiler para el lenguaje de programación para el que estemos trabajando y subir una captura de pantalla.

(No me ha dado tiempo a subirla y lo dejé en el escritorio)

Decir que he utilizado el profiler que viene por defecto instalado en el jre de java llamado VisualJM y que se situa en:
C:\Program Files\Java\jdk1.7.0\_13\bin\jvisualvm.exe

Dejo tambien un link de otro profiler de java para versiones anteriores:
http://omniumpotentior.wordpress.com/2009/08/23/profiling-de-java-en-netbeans/
Donde enseña a instalarlo y usarlo.