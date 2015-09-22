#Apuntes de la asignatura

# Introduction #
## Apuntes tomados primera sesión (11 Abril) ##
### Implementación algoritmos evolutivos usando software libre ###
El uso de sotfware libre aporta diferentes características a la comunidad informática:

  * Libertad de ejecutar software sin licencias de uso.
  * Código fuente visible por cualquier usuario lo que permite su modificación.
  * Libertad de copia.
  * Libertad de mejora, la cual contribuye a distribuir cambios.
  * Software libre no quiere decir que sea gratuito, implica que el software pasa a ser propiedad del cliente, el cual paga por el desarrollo,mantenimiento,etc del mismo.

Además de estas características se han descrito diez aportaciones del software libre a la cuminidad científica y por tanto a la propia sociedad.

Existen varios tipos de licencias en software, entre otras GPL, EUPL, MIT, etc

**Git**

  * Sistema para despliegue de aplicaciones ya que facilita la sincronizzación de grupos de trabajo.
  * Basado en línea de órdenes.
  * Sistema de control de fuentes distribuido.

Se han realizado varias funciones con el cliente git para la comprensión del mismo.
En las transparencias de clase estan alojadas las órdenes que hemos llebado a cabo.


## Clase 18 Abril 2013 ##

Se ha realizado una pequeña introducción del funcionamiento de los algoritmos evolutivos,
en las que se ha hablado de las estructuras de datos posibles para implementar dichos algoritmos
así como algunos operadores de cruce, mutación existentes para llevar a cabo la evolución de la población.

Realizar un programa que cuente el número de unos que existen en una cadena de caracteres de dos formas diferentes y medir la diferencia de tiempos.

Se han explicado las partes más importantes de un algoritmo génetico, como son la población, fitness, mutación,etc.

La mutación puede ser un cambio aleatorio e individual, y de los cuales no se puede abusar, en cambio en cruce de individuos es algo mucho más frecuente y facctible.

En los algoritmos genéticos se producen dos funciones exploración(mutación) y la explotación, lo que consigue un comportamiento mucho más eficiente que otros algoritmos.

Se estuvo explicando algunas implementaciones de algoritmos genéticos implementados en LUA y probados en cámaras de vídeo comerciales.

Se va implementar una función de mutación y otra de crossover. Una vez creadas dichas funciones, se han probado y se han comentado posibles mejoras.

Se han explicado para que sirven los profiler y se ha instalado y ejecutado uno.He realizado una captura de pantalla con el resultado del profiler que lo podeis encontrar en la zona de descargas.

Para ejecutar el profiler se usaron los siguientes comandos:

g++ funciones\_evolutivas.cpp -o funciones -p

gprof funciones




## Clase 25 Abril 2013 ##

Hemos comenzado la clase haciendo un resumen de los visto en la clase anterior. Además hemos subido a la plataforma de la asignatura algunas capturas de los tiempos obtenidos por el profiler y seguidamente hemos explicado que ocurre en esos tiempos, es decir, donde el tiempo el algoritmo.

Se ha ejecutado la función time la cual introduce los tiempos emplados por el sistema operativo en realizar los cálculos del programa.

También se han introducido algunas medidas para tener en cuenta a la hora de evaluar un algoritmo genético.

Hemos programado un algoritmo genético completo y lo hemos evaluado.
Se han comentado algunas pautas para crear archivos estructurados de cara a la creacion de resultados.


# Proyecto Asignatura #
## Selección de Caracteristicas ##

### Breve descripción del Problema: ###

El problema de la selección de características es un típico problema de
clasificación. Para abordar este problema primero debemos describirlo:

Dada una base de datos compuesta por elementos descritos por sus  características,se desea realizar una búsqueda sobre estas características de
manera que podamos clasificar de forma inequívoca cualquier elemento de la
base de datos sin necesidad de estudiar todas sus características.
Una vez descrito el problema,diremos que la selección de características
tiene como objetivo obtener un subconjunto del conjunto de características de
los elementos de la base de datos de forma que la tasa de clasificación de los
elementos dentro de la base de datos sea lo más alta posible,entendiendo por
tasa de clasificación el porcentaje de acierto cuando clasificamos nuestros
elementos. Este porcentaje de acierto vendrá dado por la relación de elementos
bien clasificados y elementos totales clasificados. A la hora de tener en cuenta
la clasificación de los elementos trabajaremos con el clasificador 3­NN,el cual se
describirá mas adelante. Para llevar a cabo el estudio del problema
realizaremos diferentes algoritmos y realizaremos también un estudio de los
resultados obtenidos al aplicar los mismos con el fin de obtener la mejor
solución para nuestro problema.

### Breve descripción de  la aplicación de los algoritmos : ###

Para el desarrollo de la práctica voy a realizar una serie de algoritmos
para los cuales algunas características estarán relacionadas:

­Generación de la solución inicial: La solución inicial para todos los
algoritmos será una solución aleatoria,a partir de esta solución cada algoritmo
trabajará de manera independiente.

­Representación de la solución: La solución vendrá dada en forma de
vector,cuyo rango de valores serán 0(false) si la característica no esta en la solución y 1(true) si la característica se encuentra en ella. El tamaño del vector será el número  de características que posean los elementos a clasificar dentro de la base de datos en la que estemos trabajando.

­
­Función Objetivo: La función objetivo del problema,es la maximización
del porcentaje de clasificación en función del clasificador el cual en este caso es
3­NN. Para llevar a cabo este porcentaje se hace uso de la siguiente fórmula,la
cual indica el porcentaje de aciertos de nuestro clasificador:

F (S) = tasa\_clas = 100 x nº de instancias bien clasificadas de T/nº de instancias en T.

El cambio más significativo de esta práctica es la introducción del concepto de población, donde ahora en vez de tener una solución simple existirán varias soluciones que irán transformándose a lo largo del tiempo.
El esquema de las poblaciones será un vector de cromosomas, donde he definido
una clase cromosoma con todas sus respectivas operaciones para facilitar la
implementación.
Es importante citar la aparición de dos operadores nuevos, el de cruce y el de mutación.

El operador de cruce consiste en obtener descendencia a partir de dos individuos previamente seleccionados (usando algún criterio de selección).Este criterio de selección se basa en la obtención de cuatro individuos de la población inicial, de entre estos cuatro individuos se seleccionan los dos mejores como Padre y Madre de los futuros descendientes.Para crear descendientes se usa un pequeño filtro, en el cual se cruzan los cromosomas siempre y cuando se cumpla una determinada situación, para evitar así cruzar en todas las generaciones. Para poder realizar un estudio más detallado de la potencialidad de estos algoritmos, he tenido en cuenta dos operadores de cruce diferentes, el multipunto y el monopunto. A continuación  se detalla su funcionamiento:
### Operador de Cruce Multipunto ###
Se eligen aleatoriamente dos puntos de corte que determinen en
los procreadores tres cadenas, y cada hijo heredará una cadena central de un
predecesor y las dos exteriores del otro predecesor.
### Operador de Cruce Monopunto ###
Se elige aleatoriamente un punto de corte. Cada uno de los descientes heredará la cadena inicial hasta el punto del corte del padre, y la cadena final desde el punto de corte de la madre y viceversa.

**Algunas Aclaraciones del algoritmo y su funcionamiento**

El operador de mutación recorre toda la población y muta tantos cromosomas como cumplan una determinada condición de probalidad de mutación.La mutación recorre las características del cromosoma y cambia o no el estado de pertenencia de esa característica en función de si se encuentra o no en el conjunto
de características mutables calculado previamente.

Para la facilitación del tratado de los datos he creado un fichero llamado utilidades.h en el que he introducido las funciones que son utilizadas por todos los algoritmos, como por ejemplo el manejo de números aleatorios, generación de soluciones aleatorias, clasificador KNN, búsqueda local, guardado de datos en fichero, etc.

He creado un programa para normalizar las bases de datos, al cual se le pasa el nombre de la base de datos y crea los ficheros de datos normalizados necesarios para ejecutar los algoritmos, con esto gano que con una vez que normalice la base de datos puedo lanzar los algoritmos sin problemas.

Como algoritmos propuestos, he implementado dos versiones diferentes de algoritmos genéticos, una versión es el modelo generacional y la otra el modelo estacionario. Además, para cada una de estas versiones he utilizado las dos versiones de operadores de cruce implementados, obteniendo  así dos versiones de algoritmos genéticos estacionarios y generacionales, cada una con un operador de
cruce diferente.

Para comprobar la potencialidad de cada una de las versiones implementadas, se realizará una tabla informativa con los porcentajes de acierto en cada una de las bases de datos disponibles (tanto para entrenamiento como para test), así como un porcentaje de reducción, el cual no es más que el número de características seleccionadas del total de características disponibles para cada elemento, obteniendo así un ratio informativo de las características más utiles a la hora de hacer la clasificación.

Como he citado anteriormente, para cada uno de los algoritmos genéticos implementados (estacionario, generacional) he utilizado una versión diferente de operador de cruce, obteniendo así poblaciones de individuos mucho más distantes en
cuanto a cromosomas, lo cual implica una mayor diversidad en la población. Las pruebas llevadas a cabo trabajan sobre tres bases de datos diferentes, en las cuales el número de características de los elementos cambia, al igual que el número de clases o elementos diferentes disponibles a la hora de clasificar.

A continuación se expone una tabla explicativa en la que cada columna informa de la base de datos en la que se ha  trabajado, y cada fila informa del tipo de algoritmo ejecutado y los porcentajes de acierto en clasificación obtenidos tanto en el conjunto de entrenamiento como en el conjunto de test.Para una información más detallada de los resultados se pueden consultar los archivos extensión "csv" adjuntados dentro del directorio resultados, en los cuales se puede observar el resultado de la solución obtenida para cada semilla. Estos archivos representan la evolución de los cruces realizados a lo largo de las generaciones, viéndose claramente como va en aumento el rendimiento de las soluciones .Al hablar de semillas, me refiero a que se han usado cinco semillas diferentes a la hora de crear las poblaciones iniciales, con el fin de obtener una mayor diversidad en las soluciones obtenidas. Estos archivos están compuestos por el nombre de la base de datos en la que se está trabajando, la semilla aleatoria con la que se crean las soluciones iniciales de la población, la generación en la que se encuentra, el cromosoma del indivíduo seleccionado y su fitnees. Encontramos por tanto en cada generación dos indivíduos, correspondientes al padre y a la madre. Si el cruce de estos indivíduos mejora la solución hasta el momento se introducirán en la población y entrarán a formar parte de la selección en las próximas generaciones, asegurándonos así una divergencia hacia una solución óptima.

Los nombres de los algoritmos han sido sustituidos para minimizar el tamaño de la tabla, pero sus significados sonlos siguientes:

AGE: ALGORITMO GENÉTICO ESTACIONARIO MONOPUNTO (operador de cruce monopunto).

AGG: ALGORITMO GENÉTICO GENERACION MONOPUNTO (operador de cruce monopunto).

AGEM: ALGORITMO GENÉTICO ESTACIONARIO MULTIPUNTO (operador de cruce multipunto).

AGGM: ALGORITMO GENÉTICO GENERACIONAL MULTIPUNTO (operador de cruce multipunto).


**Tabla Informativa**

Base de datos Ozone

AGEM --->Entrenamiento:99.324% , Test:100% ;

AGGM --->Entrenamiento:97.297% , Test:97.297% ;

AGE --->Entrenamiento:97.324% , Test:100% ;

AGG --->Entrenamiento:97.297% , Test:97.297% ;


Base de datos Sonar

AGEM --->Entrenamiento:98.181% , Test:85.365% ;

AGGM --->Entrenamiento:90.909% , Test:82.926% ;

AGE --->Entrenamiento:96.969% ,  Test:70.731% ;

AGG --->Entrenamiento:92.727% ,  Test:85.365% ;

**Resultados obtenidos:**

Como se puede apreciar en la anterior tabla, los algoritmos que emplean el operador de cruce multipunto y que por tanto  diversifican un poco más la población, obtienen un mayor rendimiento en el conjunto de test, que es realmente donde se centra  nuestro interés. Además, cabe mencionar que todos los resultados obtenidos, independientemente de si pertenece al conjunto de  entrenamiento o de test son bastente buenos, es decir, la tasa de clasificación es elevada o muy elevada, lo cual desde mi punto de vista se debe a que este tipo de algoritmos,al estar basado en  poblaciones realiza un estudio del dominio basándose generalmente
en la evolución de las soluciones obtenidas por dicha población. Al trabajar sobre dicha población e ir reemplazando las soluciones,el algoritmo va dando forma a soluciones bastantes buenas desde el punto de vista de la clasificación ya que cruza y muta soluciones buenas obteniendo así soluciones mejores. Con el paso de las generaciones de la población actual el algoritmo obtiene individuos
destacados por su fitness,es decir ,por su optimalidad en cuanto a la función objetivo se refiere,obteniendo así una población de individuos mejor dotados que sus antecesores, lo cual queda reflejado en los resultados obtenidos.

**Profiler:**

Como se comentó en clase, se hará uso de un profiler para ver los cuellos de botella o funciones donde el algoritmo invierte más tiempo de cómputo, lo cual nos puede ayudar a optimizar dicha función o funciones y conseguir mejores tiempos de cómputo globales. Dada la complejidad del trabajo realizado, y dado que el lenguaje utilizado ha sido C++, el uso del profiler, obtiene como resultado un archivo sumamente largo ya que muestra en detalle cada una de las funciones y procedimientos usados. Al observar detenidamente el archivo se extrae que las funciones donde el algoritmo dedica la mayor pate del tiempo son aquellas en las que se realiza un recorrido a lo largo del vector solución, es decir, al calcular el porcentaje de aciertos o función fitness, al clasificar la solución y al mutar la solución, ya que en todas ellas o bien se correo el vector , se realiza algún cambio, o bien se recorre toda la población intentando obtener el vecino más cercano y clasificarlo según la clase del mismo. En el apartado de resultados del proyecto se observa el archivo "Profiler.txt" donde se aprecian dichas conclusiones.

**Time:**

Para reflejar la magnitud del problema, se ha usado la orden time de los sistemas Linux, para obtener el tiempo de ejecución de los algoritmos. Como se ha citado a lo largo del presente texto, se trata de un problema de selección de características bastante complejo, lo cual sumado a un procesor con algunos años hace que la ejecución de los algoritmos sea bastante lenta. Para reflejar los tiempos se hará uso de una tabla informativa:


AGEM---> Ozone: 447 minutos, Sonar:471 minutos

AGGM---> Ozone: 457 minutos,Sonar: 475 minutos

AGE----> Ozone: 461 minutos,Sonar:480 minutos

AGG----> Ozone: 471 minutos,Sonar:477 minutos


**Conclusiones Finales:**

Para realizar el proyecto final de la asignatura he intentado solventar un problema complejo y de bastante actualidad,basándome en computación evolutiva. La decisión de optar por un proyecto tan complejo ha sido porque lo conocía bastante bien y he podido aprovechar parte del código, ya que en asignaturas que he cursado a lo largo de la carrera he hecho cosas parecidas. En este caso he introducido diferentes operadores de cruce, así como otro tipo de algoritmo genético, el generacional, ya que antes sólo usaba el estacionario, dando así una mayor dimensión al proyecto. Además he cambiado de lenguaje de programación, ya que las anteriores soluciones estaban resueltas en C, con lo que no se podía hacer uso del paradigma orientado a objetos. Como conclusión final, diré que la puesta en marcha de varias soluciones de algoritmos genéticos en un problema tan complejo y de tanta dimensión no ha sido nada fácil, pero al final si bastante satisfactorio, ya que comparando las soluciones obtenidas con algoritmos más resultadistas como búsqueda local, el porcentaje de aciertos en clasificación de elementos es casi el doble.