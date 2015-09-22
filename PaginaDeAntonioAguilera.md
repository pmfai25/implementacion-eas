# Sesion11042013 #

## Contenido ##

En esta primera sesión vamos a tratar los siguientes temas:
  * Mecánica de la asignatura
  * Wikis
  * Introducción al software libre
  * Introducción a los sistemas de gestión de fuentes: Git

## Mecánica de la asignatura ##

Se utilizará Google Code, que proporciona un entorno libre de desarrollo colaborativo de proyectos de código abierto. Cada proyecto tiene su propio repositorio Git, seguimiento de incidencias, páginas wiki y sección de descargas.

Puede obtenerse más información sobre Google Code [aquí](http://code.google.com/p/support/wiki/GettingStarted?tm=6)

Para la evaluación se tiene en cuenta:
  * la asistencia y participación en clase
  * la confección de un wiki en el que se recojan las notas tomadas en clase
  * un trabajo final, que se entregará como máximo a principios del mes de julio

## Wikis ##

Un **wiki** es una página web configurable, es decir, que permite a cada usuario introducir la información que desee organizándola mediante páginas, enlaces o etiquetas. Esto supone una forma totalmente flexible, sencilla y versatil de compartir información entre usuarios.

Puede obtenerse más información [aquí](http://es.wikipedia.org/wiki/Wiki)

La sintaxis de los wikis para los proyectos de Google Code puede consultarse en [esta página](http://code.google.com/p/support/wiki/WikiSyntax)

## Introducción al software libre ##

### Libertades del software libre ###

Se enumeran las libertades del software libre. Ver [Libertades del software libre](http://es.wikipedia.org/wiki/Software_libre#Libertades_del_software_libre)

  1. Libertad de ejecutar: usar el programa, con cualquier propósito.
  1. Libertad de estudiar: estudiar cómo funciona el programa y modificarlo, adaptándolo a tus necesidades.
  1. Libertad de copiar: distribuir copias del programa, con lo cual puedes ayudar a tu prójimo.
  1. Libertad de mejorar: mejorar el programa y hacer públicas esas mejoras a los demás, de modo que toda la comunidad se beneficie.

### Beneficios del software libre ###

  1. El software libre implica independencia tecnológica.
  1. El software libre es un vehículo de transmisión de conocimiento.
  1. La ciencia no lo es si no es reproducible: liberar el software permite a cualquiera obtener los mismos resultados.
  1. Fomenta buenas prácticas en el desarrollo de software.
  1. Crea comunidad alrededor de un grupo, y aumenta el interés en la ciencia.
  1. Acerca la ciencia al público, a la sociedad, y mejora la percepción de la universidad.
  1. Hace público y patente para empresas y otros grupos el conocimiento y experiencia de los autores.
  1. Crea otro canal para la difusión de la investigación y el trabajo propios.
  1. Devuelve a la sociedad lo que la sociedad ha invertido en la creación del software.
  1. Fomenta la colaboración interdisciplinar.
  1. Aumenta la calidad de la investigación o proyecto resultante, al posibilitar la colaboración espontánea (y altruista).

Se comentan las excusas que suelen ponerse para no liberar el software.

Se explica cómo liberar software:
  1. Poner de acuerdo a las partes relacionadas.
  1. Elegir una licencia (GPL, EUPL, MIT, Academic Free License, Apache BSD,...)
  1. Solicitar la liberación a la UGR.
  1. Publicar los fuentes.
  1. Usar una forja para continuar el desarrollo y atraer comunidad.

## Introducción a los sistemas de gestión de fuentes: Git ##

Se sigue la presentación "Introducción al uso de Git y Github para trabajo colaborativo" disponible en [slideshare](http://www.slideshare.net/jjmerelo/introduccin-al-uso-git-y-github-para-trabajo-colaborativo)

Github puede considerarse una red social para programadores: [github.com](https://github.com/)

Git está disponible para cualquier plataforma. Para ubuntu, por ejemplo, puede instalarse ejecutando: `sudo apt-get -y install git`

Un proyecto se aloja en un repositorio. El de la asignatura puede descargarse ejecutando: `git clone https://code.google.com/p/implementacion-eas/ `

La primera vez que se utiliza git es conveniente registrar nuestro nombre y correo, que aparecerán cada vez que realicemos algún cambio en el repositorio. Para ello, ejecutamos:
`git config --global user.name "<nuestro nombre>"`
`git config --global user.email "<nuestra direccion de correo>"`

Para añadir nuevos ficheros se utiliza: `git add <fichero>`

Para establecer un punto de control se utiliza: `git commit -a -m "Mensaje descriptivo del cambio"`

Para enviar nuestros cambios al repositorio, hacemos: `git push origin master`. Para poder hacer push, es necesario estar autenticado con nuestra Google Account. Si queremos que no se nos solicite el password de googlecode.com cada vez, podemos crear un fichero .netrc cuyo contenido sea: `machine code.google.com login <direccion de correo> password <password de googlecode.com>`

Para descargar la última versión disponible en el repositorio, ejecutamos: `git pull origin master` (Git pull es git fetch + git merge [diferencia entre pull y fetch](http://stackoverflow.com/questions/292357/whats-the-difference-between-git-pull-and-git-fetch)
)

Pueden producirse conflictos cuando dos o más usuarios han modificado el mismo grupo de líneas de algún fichero. Se puede producir tanto en el pull como en el push, siempre que haya habido una divergencia. Se corrige con commit + push.

# Sesion18042013 #

## Contenido ##

En esta segunda sesión vamos a tratar los siguientes temas:
  * Operadores genéticos
  * Profiling
  * Otros operadores
  * La población
  * Operadores de selección
  * Operadores de terminación

Los **[algoritmos genéticos](https://es.wikipedia.org/wiki/Algoritmo_gen%C3%A9tico)** son algoritmos de búsqueda inspirados en la selección natural.
El proceso consiste en evolucionar la población, eliminando los peores y quedándose con los mejores, que a su vez van reproduciéndose...

Presentan las siguientes características:
  * Están basados en población (siempre se tiene una solución en cada iteración), inspirados en la teoría de selección natural (Darwin): los hijos proceden de los padres + mutaciones
  * Se trabaja con una codificacion (representacion) de la solucion (codificacion binaria o en nºs reales): arrays, listas, mapas (no hay elementos repetidos)... (en funcion de como se va a acceder a los elementos)
  * Representacion de cromosoma: cadena, vector de bits, vector, lista...
  * **Fitness**: cantidad de descendencia (el mas fuerte/sano tiene mayor descendencia), coste de una solución (unidades en que se mide una solución)

## Operadores genéticos ##

  * **Mutacion**: introducir una modificacion en (la representacion de) el individuo. Cambio aleatorio e individual. No se debe abusar.
  * **Crossover** (entrecruzamiento): cruce de 2 individuos para generar uno (o varios) nuevos individuos. Hay que garantizar que los hijos sean diferentes de los padres.
  * **[Functor](http://es.wikipedia.org/wiki/Funtor)**: de manera informal se puede considerar como un objeto que actúa como una función.
  * Otros operadores: utilidades para realizar modificaciones sobre los cromosomas (poner a 0, cambiar tamaño...)

## [Profiling](http://es.wikipedia.org/wiki/An%C3%A1lisis_de_rendimiento_de_software) ##

Un **profiler** es un programa que analiza cuáles son las líneas de programa utilizadas, cuánto tiempo ha tardado en esa línea y cuántas veces se ha llamado a esa línea.

## Otros operadores ##

  * Operadores de población: transforman la población y la intentan mejorar. Eligen quienes pasan a la siguiente generación. Se suelen basar en el fitness (cuanto mayor sea el fitness, más probabilidad tienen de estar en la siguiente generación).
  * Operadores sobre otros tipos de cromosomas (programación genética)

## La **población** ##

Es el conjunto de todas las entidades que representan las soluciones al problema.

Lo más habitual es que la población inicial se genere aleatoriamente.

La población va mejorando progresivamente, ya que las soluciones más adecuadas tienen mayor probabilidad de persistir.

## Operadores de selección ##

  * Se extrae una parte de la poblacion, que es la que se va a reproducir (los que tengan menor coste o mayor fitness)
  * A los mas aptos se les da mayor probabilidad de reproducirse
  * Se tiene que saber cuantos individuos se quiere tener en la nueva población
  * Ejemplos:
    * **Ruleta**: a cada individuo se asigna una probabilidad de ser seleccionado, proporcional a su fitness, que corresponderá a un intervalo entre 0 y 1. Se lanza un aleatorio y se escoge el individuo cuyo intervalo comprenda al aleatorio.
    * **Torneo**: coge individuos aleatorios y se queda con el que tenga mejor fitness. Se va repitiendo hasta completar la nueva población. (Si el tamaño del torneo es 7, por ejemplo, es muy poco probable que pasen los de poco fitness)

Si se sustituye el torneo por ordenar los elementos, se ahorran muchas comparaciones.

## Operadores de terminación ##

  * Número de generaciones: forma más simple. Para comparar algoritmos, se comparan los fitness. Siempre repetir muchas veces las ejecuciones (30 veces es lo mínimo estadísticamente significativo, pero siempre 10 como mínimo).
  * Encontrar el óptimo (en caso de conocerlo de antemano)
  * Generaciones sin cambio: contar el número de generaciones seguidas con el mismo fitness

# Sesion25042013 #

## Contenido ##

En esta tercera sesión vamos a tratar los siguientes temas:
  * Midiendo tiempos en el ordenador
  * Instrucciones para el trabajo final y fechas
  * Miscelánea

## Midiendo tiempos en el ordenador ##

Órden [time](http://ss64.com/bash/time.html) UNIX

## Instrucciones para el trabajo final y fechas ##

  * Guardar los resultados de nuestro algoritmo genético en un fichero con un formato que pueda ser procesado por otro programa (por ejemplo, JSON).
  * Programar el algoritmo genético completo, en el lenguaje que queramos, para resolver cualquier problema (por ejemplo, el problema de la mochila)
  * Medir tiempos
  * Demostrar que hemos probado varias alternativas de implementación para mutación, cruce,...
  * Profiler
  * Subir con git
  * Wiki explicando el trabajo

La fecha de entrega límite será el **1 de julio**, y habrá que mandar un correo al profesor avisando que ya se ha entregado.

## Miscelánea ##

### Control de cambios y trabajos ###

Uso de **tags**: útil para trabajos cientificos. Puede pasar tiempo entre entrega del trabajo y presentacion (6-7 meses o hasta 2 años), y es dificil reproducir los resultados, ya que el código puede haber ido cambiando.

### Algoritmo genético canónico ###

Utiliza ruleta, mutación y cruce para todos los individuos. Es no elitista.

### Registro de experimentos y análisis de los mismos ###

**Cuaderno de bitacora** (fecha, autor, por qué he hecho el cambio, en qué consiste,...)

Los resultados se van a procesar estadisticamente, por tanto, conviene que tengan el formato adecuado:
  * CSV (primera línea de cabeceras)
  * XML
  * YAML
  * **JSON**

Consejo: couts en json [cadena: valor, cadena2: valor2...]

# Proyecto Final #

## Contenido ##

  * Introducción
  * Algoritmo de cuenta de unos
  * Operador de cruce
  * Operador de mutación
  * Algoritmo genético
  * Análisis de rendimiento (profiling)

## Introducción ##

Basándonos en el algoritmo para la cuenta de unos en una cadena desarrollado en la sesión 2 (18/04/2013), mi proyecto final consistirá en un algoritmo genético para maximizar el número de unos en una cadena.

Para ello, se desarrollarán 2 versiones del algoritmo de cuenta de unos, 2 operadores de cruce y 2 operadores de mutación. Se compararán entre sí midiendo sus tiempos de ejecución y se elegirá el mejor en cada caso, pasando a formar parte de la implementación del algoritmo genético.

Para la implementación he elegido el lenguaje de programación **Python**.

## Algoritmo de cuenta de unos ##

He considerado estas implementaciones:
  * [count\_bits](http://stackoverflow.com/q/9829578): Este algoritmo obtiene la representación binaria del número, y cuenta el número de unos mediante el uso del método [count](http://docs.python.org/2/tutorial/datastructures.html#more-on-lists)
  * [count\_bits\_2](http://stackoverflow.com/a/407674): Esta versión se distingue en que recorre la representación binaria del número mediante un bucle for.

La implementación de ambos métodos puede consultarse en el fichero [count\_bits.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/count_bits/count_bits.py)

Los tiempos de ejecución obtenidos son:
  * count\_bits: 0.0369548797607 ms
  * count\_bits\_2: 0.648975372314 ms

Esto indica que **la primera versión es 17.56 veces más rápida**. Por tanto, será esta la implementación que utilizaremos en el algoritmo genético.

## Operador de cruce ##

Para la implementación tanto de los operadores como el algoritmo genético nos basaremos en el proyecto [Pyevolve](http://pyevolve.sourceforge.net/).

He considerado 3 implementaciones distintas:
  * **single\_point\_crossover**: Se selecciona un único punto de cruce de ambos padres. Todos los datos más allá de ese punto, se intercambian entre los dos individuos. Los organismos resultantes son los hijos. Ver [One-point\_crossover](http://en.wikipedia.org/wiki/Crossover_%28genetic_algorithm%29#One-point_crossover)
  * **two\_point\_crossover**: Se seleccionan 2 puntos de cruce en ambos padres. Se copian los datos entre el principio y el primer punto de cruce del primer padre, los datos entre el primer y segundo punto de cruce del segundo padre, y los datos entre el segundo punto de cruce y el final del primer padre. Para obtener un segundo hijo, se repite la operación intercambiando el orden de los padres. Ver [Two-point\_crossover](http://en.wikipedia.org/wiki/Crossover_%28genetic_algorithm%29#Two-point_crossover)
  * **uniform\_crossover**: Se mezclan los genes de los padres con una probabilidad uniforme de 0.5 para cada gen. Estadísticamente, cada hijo tiene la mitad de los genes de cada padre. Ver [Uniform\_crossover](http://en.wikipedia.org/wiki/Crossover_%28genetic_algorithm%29#Uniform_Crossover_and_Half_Uniform_Crossover)

El código fuente está disponible en [Crossovers.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/Crossovers.py)

Para evaluar las distintas versiones se utilizará [test\_operators.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/test_operators.py)

Los tiempos de ejecución obtenidos son:
  * single\_point\_crossover: 0.339749388695 ms
  * two\_point\_crossover: 0.342302830219 ms
  * uniform\_crossover: 0.596703228951 ms

El mejor tiempo se obtiene para la versión **single\_point\_crossover**.

## Operador de mutación ##

He considerado 2 implementaciones distintas:
  * **swap\_mutator**: intercambia genes en el cromosoma, proporcionalmente a la probabilidad de mutación.
  * **flip\_mutator**: invierte el valor de los genes seleccionados para mutar, es decir, si tenían el valor 0, pasan a tener 1, y viceversa.

El código fuente está disponible en [Mutators.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/Mutators.py)

Para evaluar las distintas versiones se utilizará de nuevo [test\_operators.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/test_operators.py), intercambiando el código comentado.

Los tiempos de ejecución obtenidos son:
  * swap\_mutator: 0.0262715060711 ms
  * flip\_mutator: 0.0163337860107 ms

Utilizaremos por tanto la versión **flip\_mutator**.

## Algoritmo genético ##

Aunque no se ha comentado antes, se deduce que la **representación** de los individuos es una cadena de 0s y 1s. La implementación se realiza mediante la clase [BinaryString](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/BinaryString.py).

Por comodidad, los objetos de esta clase tendrán los siguientes atributos:
  * genome\_list: lista de genes. Puede entenderse como un vector de 0s y 1s
  * genome\_size: tamaño del cromosoma, número de genes
  * fitness: resultado de aplicar la función objetivo al cromosoma
  * needs\_eval: booleano para indicar si el cromosoma necesita ser evaluado para calcular su fitness

El algoritmo genético en sí, es decir, el proceso de evolución está implementado en [main.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/main.py). Como se puede observar, consiste en:
  * Generar la **población inicial** aleatoriamente. Para ello se hace uso del método [choice](http://docs.python.org/2/library/random.html#random.choice). Ver [BinaryString.init](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/BinaryString.py)
  * **Evaluación** de la población: se evalua el fitness de cada individuo de la población. Para ello se aplica el método **count\_ones** descrito anteriormente a cada cromosoma. Ver [BinaryString.get\_ones](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/BinaryString.py)
  * **Selección por torneo**. Ver [GA.tournament\_selection](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/GA.py)
    1. Se ordena la población por orden descendente de fitness
    1. Se guarda el mejor individuo
    1. Se construye la nueva población, eligiendo el mejor de entre un número de individuos determinado por el tamaño del torneo, seleccionados aleatoriamente. Se hace uso de la función [sample](http://docs.python.org/2/library/random.html#random.sample) de Python
  * **Cruce**: se aplica el operador de cruce **single\_point\_crossover** para generar 2 cromosomas hijos para cada par de cromosomas padres. Ver [Population.crossover](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/Population.py)
  * **Mutación**: se aplica el operador de mutación **flip\_mutator** a cada individuo de la población. Ver [Population.mutate](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/Population.py)
  * **Elitismo**: se incorpora en la nueva población el mejor individuo de la población actual (guardado en la selección por torneo), si no está ya presente. Ver [GA.elitism](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/GA.py)
  * **Condición de parada**: el algoritmo genético sigue generando nuevas poblaciones de individuos mientras no se cumpla alguna de las siguientes condiciones. Ver [GA.stop\_condition](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/GA.py)
    1. Se genera un número determinado de poblaciones. Ver parámetro **GENERATIONS**
    1. Todos los individuos de la población tienen el fitness óptimo

El algoritmo genético utiliza diversos parámetros que determinan su funcionamiento. Estos parámetros están definidos en [Consts.py](http://code.google.com/p/implementacion-eas/source/browse/aguilerin/ga/Consts.py):
  * CROSSOVER\_PROB  = 0.9 (Probabilidad de cruce: 90%)
  * GENERATIONS     = 100 (Número de generaciones, utilizado como condición de parada)
  * GENOME\_SIZE     = 50  (Tamaño del cromosoma: número de genes)
  * MUTATION\_PROB   = 0.02  (Probabilidad de mutación de un gen: 2%)
  * POPULATION\_SIZE = 80  (Tamaño de la población: número de cromosomas)
  * TOURNAMENT\_SIZE = 2   (Tamaño del torneo: número de individuos que compiten)
  * UNIFORM\_PROB    = 0.5   (Probabilidad uniforme: 50%)

El algorimo genético muestra para cada generación el mejor individuo de la población. Se utiliza **CSV** para facilitar un posterior procesamiento de los resultados. El formato de cada línea es:
  * Número de generación
  * Representación del mejor individuo
  * Fitness del mejor individuo

Como ejemplo de ejecución del algoritmo, se obtiene el siguiente resultado:

```
0,01010111010100110011001111011011111111110001011010,31
1,01010111010100110011001111011011111111110001011010,31
2,10010110100110111010101111011011111111110011011010,33
3,11010111101010110101101101111111110110111110010100,34
4,10111101011000111011101111011011111111101011111100,36
5,11100010111111111010101001011111110011111011111101,36
6,01111011011110001010101111011111111111101011111111,38
7,01111011011110001010101111011111111111101011111111,38
8,10111101011000101111101111011011111101111111111111,39
9,11111010110110111110111101111111111111101010111101,40
10,11100110111111111110101101111111111101111011111111,42
11,11111010110110111110111101111111111111101011111111,42
12,11101011111101111110101001111111111101111111111111,42
13,11111011111111111101110111111111110111111011111101,44
14,11111111111111111101110111111111110111111011111101,45
15,11111110111110111110111111111111110011111011111111,44
16,11111111110111111101110111111111110111111101001111,43
17,10111110111111111101110111111111111111111111111101,45
18,10111110111111111101110111111111111001111111111111,44
19,11111011111011011111111111111111110111111111111101,45
20,11111011111001011111111111111111111111111111111110,45
21,11111111111111111111111101111111111111111111111111,49
22,11111111011111110111111111111111111111111111111111,48
23,11111111111111110111111111111111111111111111101111,48
24,11111111111111110111111111111111111111111111101101,47
25,11111111111111111110111111111111111111111111101111,48
26,11111111111111111111111101110111111111111111111111,48
27,01111110111111111111111111111111111111111111111111,48
28,11111111111111111111111111111111111110111111111101,48
29,11111111111111111111111111111111111111111101111101,48
30,11111111111010111111111111111110111111111111111111,47
31,11111011111111111111111111111110111111111111111111,48
32,11110111111111111111111111111110111111111111111111,48
33,11111111111111111111111111111110111111111111011111,48
34,11111111111111111111111111111111111111111111111101,49
35,11111111111111111111111111111111111111111111111110,49
36,11111111111111111111111111111111111111111111111111,50
37,11111111111101111011111111111111111111111111111111,48
38,11111111111111111111111111101111111111111111111111,49
39,11111111111111111111110111111111111111111110111111,48
40,11111111111111111111111111111111111111111111111110,49
41,11111111111111111111111111111111111111111011111111,49
42,01111111111111111111111111111111111111111111111111,49
43,10111111111011111111111111111111111111111111111111,48
44,01111111111111111111111111111111111111111111111111,49
45,11111111101111111111111011111111111111111111111111,48
46,11111111111111101111111110111111111111111111111111,48
47,11111111111111111110111111101111111111111111111111,48
48,11111111011111101111111111111111111111111111111110,47
49,11111111111111111110111111111011110111111111111111,47
50,11111111011111101111111111011111111111111111111111,47
51,11111111011111111111111111011111111111111111111111,48
52,11111111111111111111111111111111111111111111111101,49
53,11111111111011111111111111111111111111111111111111,49
54,11111111111111101110111111111111111111111111111111,48
55,11111111111111101111111111111111111111111111111111,49
56,11110111111110111111111111111111111111111111111111,48
57,11111111111111111111111111011111011111111111111011,47
58,11011111111111111111111111111111101111111111110111,47
59,11011111111111111111111111011111101111111111111111,47
60,11011101111111111111111111111111111111111111111101,47
61,11111111110111111111111111111110111111111111111110,47
62,11111111111111111111111011111111111111111111111110,48
63,11011111111111111111111111110111111111111111111111,48
64,11011111111111111111111111110011111111111111111111,47
65,11111111111111111111100111011111111111111111111111,47
66,11111111111111111111011111111011111111111111111111,48
67,11111111111111111111111111011111111111111111111111,49
68,11111111111111111111111111111111111111111111111101,49
69,11111111111111111111111111111111111111101111111011,48
70,11111111111101111111111111111111111011111111111111,48
71,11111111111111111111111111111110111011111111111110,47
72,11111111111011111111101111111111111111111111111111,48
73,11111110111111111111111111111111111111111111111111,49
74,11111111111111011111111111111111111011111111111111,48
75,11111111111111101111111111111111110111111111111111,48
76,11111111111111111111111111111111110110111111111111,48
77,11111111111111111111110111111111111011110111111111,47
78,11011111111111111110111111111111111111111111111111,48
79,11111111011110111111111111111111111111111111111111,48
80,11111111111101111111111111111111111111011111111111,48
81,11111111111111111111111111110111111111111111111111,49
82,11111111111111111111110111111111111111111111111111,49
83,11111111111111111111111111110111111111111111111111,49
84,11111111111111111111011111111110111111111111111111,48
85,11111111111111111111111111101111111111111111111111,49
86,11101111111111111111111111111111111111111111111111,49
87,11111101111111111111111111111111101111111111111111,48
88,11111111111111111111111111111111111111111111111101,49
89,11111111111111111110111111111111101111111111111111,48
90,01111111111111111111111111111111101111111111111111,48
91,11111111111111111111111111111111111111111111011111,49
92,11111111111111111111111111101111011111111111111111,48
93,11111111110111111111111111111111111111111111101111,48
94,10111111111111111111111111111101111111111111111111,48
95,11111111101011101111111111111111111111111111111111,47
96,11111111110111111111111011111011111111111111111111,47
97,11111111111111011111111111111111111111111111110111,48
98,11111111111111111101111111111111111111111111111111,49
99,11110111111111111111111111111111111111111111111111,49
```

El valor óptimo del fitness es 50 en este caso (el tamaño del cromosoma). Como se puede apreciar, el mejor fitness obtenido en el conjunto de generaciones es 49.

## Análisis de rendimiento (profiling) ##

Se utiliza **[RunSnakeRun](http://www.vrplumber.com/programming/runsnakerun/)**. Se trata de una GUI que muestra los resultados de **[cProfile](http://docs.python.org/2/library/profile.html)**, profiler de Python.

He seguido las indicaciones para instalarlo en Ubuntu descritas en la [página](http://www.vrplumber.com/programming/runsnakerun/) anterior.

Para capturar los datos necesarios de nuestro algoritmo, ejecutamos:

`python -m cProfile -o resultados main.py`

Para visualizar los resultados de la ejecución, escribimos:

`runsnake resultados`

Los resultados se muestran en la siguiente imagen:

![https://implementacion-eas.googlecode.com/git/aguilerin/ga/profiler.png](https://implementacion-eas.googlecode.com/git/aguilerin/ga/profiler.png)

En la imagen aparecen a la izquierda los métodos ordenados decrecientemente según el porcentaje de tiempo empleado (columna Local).

Como se puede apreciar, el método que más porcentaje de tiempo consume es **choice**, que se utiliza para generar la población inicial aleatoriamente. Se llama por cada individuo de la población y gen de cada individuo, es decir, 80 x 50 = 4000 veces. Supone un 34.87% del tiempo total.

Si quisiéramos mejorar el rendimiento de nuestro algoritmo, deberíamos pensar en sustituir este método por otro más eficiente.