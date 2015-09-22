# Proyecto Fin Asignatura #

Para la realización de este proyecto, vamos a hacer un algoritmo evolutivo extraido del libro:

Algoritmos Genéticos” de Ángel Kuri Morales y José Galaviz Casas

que lo podemos encontrar en:

  * ttp://www.goodreads.com/author/show/4720235._ngel\_Kuri\_Morales_

  * ttp://biblioteca.universia.net/html\_bura/ficha/params/title/rese%C3%B1a-algoritmos-geneticos-kuri-angel-galaviz-jose/id/54591568.html

y cual el problema es el siguiente:

Se tiene la función 36-((6\*x-3)<sup>2-3)</sup>2 y se quiere maximizar el número de individuos de una población que sea igual
al punto maximo que tome esta función (es el tipico problema de maximizar una función).

La función inicial estará compuesta de 256 elementos (cada elemento es binario y compuesto de 8 bits por lo que se puede generar
hasta 256 elementos distintos) y le asignaremos un rango de 0 a 1.

Con esta función lo que haremos es crear (seleccionandolos de la función inicial) una población inicial de 100 individuos.

Este bucle se repetirá hasta que haya al menos 4 individuos que maximicen la función (es decir que su valor sea igual que el maximo de la función inicial) sin limite
de generaciones, es decir, dejaré el algoritmo hasta que se encuentren.

## Historial del versionado (Memoria) ##

### Creación de la tabla inicial ###

Lo primero que voy ha hacer es crear la tabla inicial de los valores de la función
esta es: construirTablaInicial()

Una vez ejecutada esta función tendremos una tabla[hasta256](hasta256.md)[0,1,2] donde tendremos
Para cada i, [0](0.md) un número hasta 256, [1](1.md) su calificación, [2](2.md) su f(x).

He hecho una primera implementación que se llama construirTablaInicial() que llama a la función convertirABinario().

Esta función ejecutada simplemente en un bucle de 100000 veces nos da este tiempo:

> long tiempoInicio1 = System.currentTimeMillis();

> for (int i = 0; i < 100000; i++) {
> > construirTablaInicial();

> }

> long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
> System.out.println("Tiempo para 100000 veces " + totalTiempo1);

Tiempo para 100000 veces 7538 milisegundos

Ahora voy a hacer otra implementación a la que he llamado 	construirTablaInicial2() y que llama a la función 	convertirABinario2().

> long tiempoInicio1 = System.currentTimeMillis();

> for (int i = 0; i < 100000; i++) {
> > construirTablaInicial2();

> }

> long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
> System.out.println("Tiempo para 100000 veces " + totalTiempo1 + " milisegundos");

Tiempo para 100000 veces 2816 milisegundos

En la cual vemos como se reduce el tiempo de creación de la tabla de casi 8 segundos a casi 3.

### Construcción de la población ###

Ahora a partir de esa tabla de 256 elementos voy a construir aleatoriamente, la población inicial de 100 individuos.

A esta función la llamaré generarPoblacionInicial();

Esta función necesita convertir a binario el numero random para construir el vector binario\_poblacion.

Ejecutada esta función en el bucle para convertirABinario y para convertirABinario2, tenemos los siguientes tiempos.

  * funcion convertirABinario  -> Tiempo para 100000 veces 6018 milisegundos
  * funcion convertirABinario2 -> Tiempo para 100000 veces 3814 milisegundos

Por lo que se pone de manifiesto la ganancia mejorarndo esta función de convertir un numero entero a binario de 8 digitos para esta función tambien.

### Creación de las proximas generaciones ###

Ahora lo que voy a hacer es crear a la siguiente generación, esto lo haré con la función: crearGeneracionSiguiente().

El funcionamiento es el siguiente:
1) se elige el valor de la función del ultimo individuo y se multiplica por un numero entre 0 y 2.
2) vamos recorriendo la poblacion antigua y sumando las calificaciones hasta que se supera a ese valor, entonces ese individuo se almacena en la siguiente generación.
3) este bucle se repite hasta que tenemos otros 100 nuevos individuos (se supone que mejores).

Una vez tengamos a los "elegidos para la siguiente generacion", tendremos que cruzarlos y mutarlos para obtener finalemente la nueva generación.

### Implementación de los operadores de Cruce ###

Haré dos versiones del operador de cruce:

#### Primera Implementación Operador Cruce ####

El primero simpre seleccionará a todos los individuos de la población para cruzar.
Para cada elegido y su siguiente, se cruzarán obteniendo dos nuevos individuos que seran:
Para el elegido-> los 4 primeros digitos de su gen + los 4 ultimos del siguiente.
Para el siguiente-> los 4 ultimos digitos de su gen + los 4 primeros de su anterior.

Por lo que estos dos nuevos se introducirán en la población y se eliminarán los anteriores.

#### Segunda Implementación Operador Cruce ####

En mi segunda versión:

Se calcularán dos numeros aleatorios que elegirán si la población (de dos en dos) debe de cruzarse. (Se hará un bucle para poder cruzar a toda la población)

Si se debieran cruzar (control con el primer numero aleatorio en la cual se mutan aquellos en la que la probabilidad hubiera salido a 0.4),

  * el hijo1 será el primer caracter del padre + los X ultimos de la madre (Siendo X un numero aleatorio base 7)
  * el hijo2 será el primero de la madre + los X ultimos del padre

He creado esta versión ya que el profesor me dijo que era muy poco cruzar solo a pocos individuos en cada generación (veremos la mejora de tiempo más adelante), asi que en esta se pueden llegar a cruzar todos ellos (Si las variable aleatorias lo favorecen).

Con estas dos implementaciones de cruzar, he realizado dos comprobaciones de tiempo, para ver cual es mejor.

Lo he ejecutado 10 veces y he calculado el tiempo total para cada iteración.

Para la implementación del primer cruce tengo: Tiempo total= 131048 milisegundos (más de 2 minutos)
Para la implementación del segundo cruce tengo: Tiempo total= 37159 milisegundos (37 segundos)

Como vemos, es cierto que hay que cruzar a muchos individuos a la vez para que vaya fluido.

A partir de ahora, elegiré esta segunda implementación de cruce para continuar con las pruebas.

### Implementación operadores de Mutación ###

#### Primera Implementación Operador Mutación ####

En esta primera versión de mutar lo que haré será mutar a los indiviuos de la población que esten debajo de un umbral de fitness (semejanza con el valor a buscar).
Si no son lo suficiente parecidos, su gen numero 3, mutará.
Para ello hago uso de mi función fitness que devuelve un valor (de 0 a 8) dependiendo de lo que se parezca al valor a buscar.

He creado esta función porque recuerdo que en clase se habló de que no era bueno mutar en exceso.
Mi intención era modificar el parametro de los individuos que se mutan, para ver mediante esta implementación, como varía la solución.

Para ello, he ejecutado el programa 50 veces (ya que en clase se habló de que para "evaluar" un algoritmo genetico había que hacerlo muchas veces y calcular su promedio)
y calculado el tiempo medio en encontrar la solución para:

(como uso windows y no unix no puedo utilizar la orden time, por lo que ejecuto el main X veces y lo controlo mediante los contadores de tiempo de java)

> #### Mutan aquellos que su fitness sea menor que 1 ####

Tiempo para 0 veces 371 milisegundos

Tiempo para 1 veces 64 milisegundos

Tiempo para 2 veces 9279 milisegundos

Tiempo para 3 veces 115 milisegundos

Tiempo para 4 veces 667 milisegundos

Tiempo para 5 veces 16332 milisegundos

Tiempo para 6 veces 3 milisegundos

Tiempo para 7 veces 81 milisegundos

Tiempo para 8 veces 75 milisegundos

Tiempo para 9 veces 1234 milisegundos

Tiempo para 10 veces 711 milisegundos

Tiempo para 11 veces 497 milisegundos

Tiempo para 12 veces 10 milisegundos

Tiempo para 13 veces 11292 milisegundos

Tiempo para 14 veces 14 milisegundos

Tiempo para 15 veces 241 milisegundos

Tiempo para 16 veces 81 milisegundos

Tiempo para 17 veces 2792 milisegundos

Tiempo para 18 veces 74 milisegundos

Tiempo para 19 veces 117 milisegundos

Tiempo para 20 veces 704 milisegundos

Tiempo para 21 veces 4194 milisegundos

Tiempo para 22 veces 131 milisegundos

Tiempo para 23 veces 326 milisegundos

Tiempo para 24 veces 2280 milisegundos

Tiempo para 25 veces 8 milisegundos

Tiempo para 26 veces 2472 milisegundos

Tiempo para 27 veces 116 milisegundos

Tiempo para 28 veces 496 milisegundos

Tiempo para 29 veces 23 milisegundos

Tiempo para 30 veces 45 milisegundos

Tiempo para 31 veces 599 milisegundos

Tiempo para 32 veces 319 milisegundos

Tiempo para 33 veces 1762 milisegundos

Tiempo para 34 veces 2880 milisegundos

Tiempo para 35 veces 979 milisegundos

Tiempo para 36 veces 144 milisegundos

Tiempo para 37 veces 538 milisegundos

Tiempo para 38 veces 112 milisegundos

Tiempo para 39 veces 105 milisegundos

Tiempo para 40 veces 3 milisegundos

Tiempo para 41 veces 1460 milisegundos

Tiempo para 42 veces 610 milisegundos

Tiempo para 43 veces 117 milisegundos

Tiempo para 44 veces 677 milisegundos

Tiempo para 45 veces 1060 milisegundos

Tiempo para 46 veces 213 milisegundos

Tiempo para 47 veces 2098 milisegundos

Tiempo para 48 veces 16599 milisegundos

Tiempo para 49 veces 425 milisegundos


Tiempo Promedio= 1710 milisegundos/iteración.


> #### Mutan aquellos que su fitness sea menor que 2 ####

Tiempo Promedio= 1416  milisegundos/iteración.


> #### Mutan aquellos que su fitness sea menor que 3 ####

Tiempo Promedio= 1259 milisegundos/iteración.


  * Mutan aquellos que su fitness sea menor que 4 ====

Tiempo Promedio= 1611 milisegundos/iteración.


> #### Mutan aquellos que su fitness sea menor que 5 ####

Tiempo Promedio= 1982 milisegundos/iteración.


> #### Mutan aquellos que su fitness sea menor que 6 ####

Tiempo Promedio= 1997 milisegundos/iteración.


> #### Mutan aquellos que su fitness sea menor que 7 ####

Tiempo Promedio= 4331 milisegundos/iteración.


Por lo que se ve un punto de inflexión fijando el valor  max\_fitness a 3, a partir de este valor es peor mutarlos;


#### Segunda Implementación Operador Mutación ####

En la segunda versión de esta implementación de mutar haré lo siguiente.

Iré recorriendo toda la población siguiente, generaré un valor aleatorio para cada gen y lo comprobaré con un umbral establecido, si fuese menor,
ese gen de ese individuo será intercambiado por 1 si es 0, o 0 si es uno.

Es decir, es posible que pueda mutar toda la población (es muy aleatorio).

## Tiempos Finales ##

Una vez terminado, para ver la diferencia de tiempos entre la version sin mejorar (sin ninguna mejora en optimización de codigo + optimización de cruces/mutaciones)
y la segunda version mejorada (optimizado codigo + operador cruce/mutacion) ejecutaré los programas 15 veces quedandome con la media de las iteraciones.

#### Version sin optimizar (practica1.java) ####

Para la versión sin optimizar (practica1.java), el tiempo obtenido para 15 veces (luego hago el tiempo promedio para cada iteración), fijando el maximo de iteraciones de prueba en -1 (num\_maximo\_iteraciones, es decir, dejar el bucle hasta que encuentre la solucion, tarde lo que tarde)
e intentado optimizar a 4 individuos en la población (poblacion\_a\_optimizar = 4) es:


Generacion optima en:--> 788
Tiempo para 788 veces 191 milisegundos

Generacion optima en:--> 11576
Tiempo para 11576 veces 2159 milisegundos

Generacion optima en:--> 2533
Tiempo para 2533 veces 1041 milisegundos

Generacion optima en:--> 8160
Tiempo para 8160 veces 4933 milisegundos

Generacion optima en:--> 19257
Tiempo para 19257 veces 14804 milisegundos

Generacion optima en:--> 25549
Tiempo para 25549 veces 39509 milisegundos

Generacion optima en:--> 36620
Tiempo para 36620 veces 58834 milisegundos

Generacion optima en:--> 15924
Tiempo para 15924 veces 42260 milisegundos

Generacion optima en:--> 248
Tiempo para 248 veces 1814 milisegundos

Generacion optima en:--> 10408
Tiempo para 10408 veces 29985 milisegundos

Generacion optima en:--> 10148
Tiempo para 10148 veces 37651 milisegundos

Generacion optima en:--> 3337
Tiempo para 3337 veces 9756 milisegundos

Generacion optima en:--> 98815
Tiempo para 98815 veces 301374 milisegundos

Generacion optima en:--> 121706
Tiempo para 121706 veces 428606 milisegundos

Generacion optima en:--> 1646
Tiempo para 1646 veces 10217 milisegundos

Tiempo total= 983134milisegundos
Tiempo promedio/iteración= 65542milisegundos

BUILD SUCCESSFUL (total time: 16 minutes 23 seconds)


#### Version optimizada (practica1\_Opt.java) ####

Para la versión optimizada (practica1\_Opt) el tiempo obtenido para 15 veces con las mismas condiciones que en la anterior, es:


Generacion optima en:--> 3951
Tiempo para 3951 veces 882 milisegundos

Generacion optima en:--> 852
Tiempo para 852 veces 251 milisegundos

Generacion optima en:--> 4242
Tiempo para 4242 veces 2082 milisegundos

Generacion optima en:--> 1144
Tiempo para 1144 veces 858 milisegundos

Generacion optima en:--> 1829
Tiempo para 1829 veces 1326 milisegundos

Generacion optima en:--> 1816
Tiempo para 1816 veces 1458 milisegundos

Generacion optima en:--> 2668
Tiempo para 2668 veces 2549 milisegundos

Generacion optima en:--> 1400
Tiempo para 1400 veces 1584 milisegundos

Generacion optima en:--> 2541
Tiempo para 2541 veces 3135 milisegundos

Generacion optima en:--> 227
Tiempo para 227 veces 316 milisegundos

Generacion optima en:--> 696
Tiempo para 696 veces 1033 milisegundos

Generacion optima en:--> 1014
Tiempo para 1014 veces 1534 milisegundos

Generacion optima en:--> 22
Tiempo para 22 veces 16 milisegundos

Generacion optima en:--> 3466
Tiempo para 3466 veces 5090 milisegundos

Generacion optima en:--> 1012
Tiempo para 1012 veces 1706 milisegundos

Tiempo total= 23820milisegundos
Tiempo promedio/iteración= 1588milisegundos

BUILD SUCCESSFUL (total time: 24 seconds)


Por lo que podemos ver la mejora considerable de tiempo entre una versión optimizada con operadores de cruce/mutación distintos (más potentes), tal y como se vio
en clase.

### Utilizando un profiler de Java ###

Una vez hecho esto, pasaré a dar los tiempos del debugger propio de netbeans (en wikis anteriores explico detalladamente como y cual ejecuto), en donde veremos el tiempo que está tardando cada uno de los algoritmos, en cada una
de las funciones, para darnos cuenta de cuales son los cuellos de botella de nuestro programa.

Estas vienen en las imagenes adjuntas, debug\_practica1.png y debug\_practica1\_Opt.png

Donde vemos el tiempo utilizado para cada una de las funciones, así como cada una de las invocaciones a cada funcion.

Tengo que decir que todos estos calculos han sido realizados en un MacBook Air del 2011, con 2 nucleos a 1.7Ghz con 4Gb Ram

### Exportando los datos a XML ###

Ahora, implementaré la opción para poder exportar en XML siguiendo el formato visto en clase:




&lt;resultado&gt;


> 

&lt;ag id="1"&gt;

 (esto indica cada iteración del algoritmo distinta)
> > 

&lt;gen n="37"&gt;

	(esto indica que generación se está tratando)
> > > 

&lt;individuo id="100"&gt;

 	(Esto indica que individuo maximiza la función, es decir, su fitness es 100 ya que es exactamente igual que el maximo de la función)
> > > > 0101010101			(Los genes del individuo)

> > > 

&lt;/individuo&gt;



> > 

&lt;gen&gt;



> 

Unknown end tag for &lt;/ag&gt;





Unknown end tag for &lt;/resultado&gt;



Por tanto, obtendremos un fichero xml con tantos AG como iteraciones haya, y en donde aparecerán solo las generaciones en las que hay individuos que maximizen
la funcion.
Si estos individuos fuese igual que el numero que quisiesemos buscar, terminaría. Tal y como podemos ver en el fichero XML.


Para ello he realizado una sería de inserciones de código en los dos codigos para que se pueda generar un String ocn la información necesaria y más tarde escribirla en un fichero.

> public static void escribirXML() {

> File f;
> f = new File("nombreFichero.xml");
> try {
> > FileWriter w = new FileWriter(f);
> > BufferedWriter bw = new BufferedWriter(w);
> > PrintWriter wr = new PrintWriter(bw);
> > wr.write(XML\_total);//escribimos en el archivo
> > wr.close();
> > bw.close();

> } catch (IOException e) {
> };
> }

Podemos ver el resultado en el fichero xml\_practica1.xml y fichero\_practica2.xml para 15 iteraciones del algoritmo.

Además para comprobar si los XML están bien formados, he utilizado la web http://www.xmlvalidation.com/
En la cual como podemos ver, se generan los XML bien formados.

## Notas a tener en cuenta ##

Por tanto, RESUMEN (para la evaluación):

Tal y como pidió el profesor el último día en clase

  1. He programado un algoritmo Genético completo
  1. En lenguaje Java
  1. He medido tiempos para todo lo que he hecho
  1. He utilizado varias alternativas para codificación e implementaciones de codigo.
  1. He implementado distintas alternativas para cada función y para las mutaciones/cruces
  1. He utilizado el profiler de java para ver las funciones cuello de botella de cada una de las funciones
  1. Los datos se almacenan de forma estrucutrada siguiendo el protocolo XML (y además son válidos).
  1. He subido a la wiki, una memoria de la práctica mientras realizaba este trabajo.
  1. He subido los fuentes a la wiki al igual que las imagenes correspondientes.
  1. He comentado cada uno de los puntos fuertes en mi algoritmo explicando la relación con lo que el profesor dijo en clase en vista a los resultados practicos.
  1. He ido todas los dias a clase
  1. He tomado apuntes en clase durante todos los dias y los he estado subiendo de manera continua
  1. He subido a la plataforma cada uno de los mini-ejercicios que ha pedido el profesor.
  1. He entregado todo, antes de la fecha limite (1 de Julio)

Por lo que espero poder tener buena nota en la asignatura, ya que me nivel de dedicación ha sido constante y aprendido bastante sobre algoritmos geneticos (que era el objetivo).