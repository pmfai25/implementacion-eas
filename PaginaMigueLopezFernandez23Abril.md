Hemos empezado a contar que hicimos en la clase el día anterior.
Ha resumido Ruben y luego yo.

Luego he vuelto a hacer la captura de pantalla del profiler que se me olvido poner el otro dia.
La he subido, pero al enseñarlo al profesor me ha dicho que me descargue un algoritmo genetico de internet en vez de utilizarla con mi algoritmo
y le haga una captura al profiler.

Lo he hecho, me he bajado un ejemplo de esta pagina:

http://www.alevsk.com/2012/03/algoritmo-genetico-hecho-en-java/

lo he ejectuado y hecho una captura de pantalla, que he subido en mis descargas.

Ruben está comentando los resultados de su profiler.

Hemos hablado del comando time para linux, que cuenta el tiempo de ejecución de un algoritmo.
He buscado en Internet una página en donde explica (y tiene ejemplos) de como usarlo:
http://www.thegeekstuff.com/2012/01/time-command-examples/

Hemos comentado que un algoritmo genético hay que ejecutarlo mas de 10 veces para comprobar los resultados.

Nos hemos tirado una hora haciendo un algoritmo evolutivo que al final he terminado subiendo y explicando.

Como podemos ver, en este algoritmo tenemos una población de 100 individuos, con 100 cromosomas cada individuo.

Explicación del algoritmo....

Le he comentado al profesor que tenía que irme sobre las 19:30 y ha explicado por tanto la ultima explicación de la asignatura que era que deberíamos de sacar los datos de nuestro algoritmo en algun formato válido (json, xml, csv..).

El aspecto de un fichero de salida .xml tendría la siguiente forma.



&lt;resultado&gt;


> 

&lt;ag&gt;


> > 

&lt;gen n=37&gt;


> > > 

&lt;individuo fitness=88&gt;


> > > > 0101010101

> > > 

&lt;/individuo&gt;



> > 

&lt;gen&gt;



> 

Unknown end tag for &lt;/ag&gt;




Unknown end tag for &lt;/resultado&gt;




El aspecto de un fichero de salida .csv tendría la siguiente forma.

Generacion;individuo;Fitness
0;10101010101; 88
1;1010101010; 11

Además ha dado las instrucciones para realizar el trabajo final de la asignatura.
Los pasos que hay que cumplir son los siguientes:

  * Programar un algotimo genetico completo, el que queramos.
  * Lenguaje que queramos
  * Lo importante es:

  1. medir tiempos
  1. varias alternativas para codificacion, profiler, varias implementaciones, y ademas se almacenen de forma estructurada (xml,csv,json...)

  * Subirlo, al wiki (explicación en la wiki, no en word) y subido el fuente a source.

La nota total de la asignatura se dividirá en:

  * nota proyecto : 60%
  * notas de wiki + trabajillos: 40%

La fecha límite de entrega es: 1 Julio