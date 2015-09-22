# Introduction #

Proyecto Asignatura Computación Evolutiva


# Details #

Realización del Proyecto de computación Evolutiva. He realizado un algoritmo genético que se basa en un tablero en el que hay una fruta y una avispa que querría comérsela. He elegido este problema pese a tener partes más complejas ya que en trabajos pasados cree algo parecido y he podido reutilizar parte del código.

Se irán creando generaciones de hijos hasta que en una de estas generaciones, al menos un hijo alcance la fruta.

También he introducido mutaciones en el algoritmo y he ido variando su valor para comprobar los cambios en el tiempo consumido y la efectividad del sistema.

He usado la función time.time() para el cálculo del tiempo consumido de CPU en el desarrollo del problema.

He cambiado los tamaños de población de avispas creadas por generación para ver las diferencias en el rendimiento. También he variado el tamaño del tablero (más posibilidades de camino), y he ido comprobando como variaba.

Este es el código utilizado. (He utilizado Python como herramienta de creación de mi software libre).

"""Una avispa que come fruta se tira en una tablero rectangular. Hay fruta en otra parte del tablero, por lo que el movimiento de la avispa se determina por su codigo genetico. En cada generacion, mutaciones aleatorias se producen en el cÃ³digo, y los mejores hijos (los que llegan mÃ¡s cerca de la fruta), se seleccionan. Estos hijos tienen sus hijos propios (avispas hijas) hasta que al menos un hijo es capaz de alcanzar la fruta.

@author Francisco Estella, UGR """

import sys import os import time import random

t1=time.time()

# Geometria del tablero y posicion de la fruta y de la avispa default\_tabl\_size = (50,15) size=(50,15) default\_fruta\_position = (45,5) default\_avispa\_position = (10,14)

code\_elements = ["n", "s", "e", "w"]

# Vectores de movimiento move\_vectors = dict() move\_vectors[code\_elements0?] = (0,-1) move\_vectors[code\_elements1?] = (0,1) move\_vectors[code\_elements[2](2.md)] = (1,0) move\_vectors[code\_elements[3](3.md)] = (-1,0)

# La longitud del codigo sera la distancia de la avispa a la #fruta+ el offset code\_size\_offset = 10

# avispas por generacion avispa\_pool\_size = 25

# Probabilidad de mutacion mutation\_probability = 0.1

default\_fruta\_char = "F" default\_avispa\_char = "@" default\_tabl\_char = "#" default\_space\_char = "Â·"

## Comando para limpiar consola: cls = windows. clear\_function = "cls"

## Tiempo de espera entre pasos wait\_time\_step = 0.05

## Tiempo de espera mientras anda la avispa wait\_time\_generation = 2

def print\_tabl(fruta\_pos\_list, avispa\_pos\_list,

size=default\_tabl\_size, fruta\_char=default\_fruta\_char, avispa\_char=default\_avispa\_char, tabl\_char=default\_tabl\_char, space\_char=default\_space\_char):
#Dibuja el tablero con las avispas y la fruta en la posicion deseada print "Distancia =", manhattan\_distance(fruta\_pos\_list[0](0.md), avispa\_pos\_list[0](0.md))

# Primera fila

for y in range(size0? + 2):sys.stdout.write(tabl\_char)
print # filas del tablero for y in range(size1?):sys.stdout.write(tabl\_char) for x in range(size0?):
if(x,y) in fruta\_pos\_list:sys.stdout.write(fruta\_char)

if(x,y) in avispa\_pos\_list:sys.stdout.write(avispa\_char)
else:sys.stdout.write(space\_char) sys.stdout.write(tabl\_char) print

# Ultima fila for y in range(size[0](0.md)+ 2):sys.stdout.write(tabl\_char) print

def is\_good\_pos(position, tabl\_size=default\_tabl\_size):

#¿Posicion valida?

if position0? < 0 or position[1](1.md)<0:
return False
if position0? >= tabl\_size[0](0.md) or position1? >= tabl\_size1?:
return False
return True

def code\_to\_walk(origin, code, fruta\_list[default\_fruta\_position](default_fruta_position.md)): #Camina

avispa\_pos\_list = origin? for c in code:
old\_pos = avispa\_pos\_list[-1] move\_vector = move\_vectorsc? new\_pos = (old\_pos0? + move\_vector0?, old\_pos1? + move\_vector1?) if is\_good\_pos(new\_pos):
avispa\_pos\_list.append(new\_pos)
#Parar si se obtiene la fruta!

if new\_pos in fruta\_list:return avispa\_pos\_list


return avispa\_pos\_list

def animate\_walk(fruta\_list, avispa\_list):
#animacion de la avispa avanzando

for i in range(len(avispa\_list)):
time.sleep(wait\_time\_step) os.system(clear\_function) print\_tabl(fruta\_pos\_list=default\_fruta\_position?, avispa\_pos\_list=avispa\_list[i:i+1])


def manhattan\_distance(pos1, pos2):
#Distancia
return abs(pos10?-pos20?) + abs(pos11?-pos21?)


def mutate\_code(old\_code, mutation\_probability=mutation\_probability):

#Mutacion

code = list(old\_code) for position in range(len(code)):
if random.random() <= mutation\_probability:
new\_base = random.choice(code\_elements) codeposition? = new\_base
return code

def evolve\_generation(pool, reproduction\_factor):

#Reproducir generacion

next\_generation [.md](.md)
> for evaluation in pool:
avispa = evaluation[0](0.md)
> for i in range(reproduction\_factor):
next\_generation.append(mutate\_code(avispa))
return next\_generation

#Ejecucion default\_code\_size = manhattan\_distance(default\_fruta\_position, default\_avispa\_position) + code\_size\_offset

print\_tabl(fruta\_pos\_list=default\_fruta\_position?, avispa\_pos\_list=default\_avispa\_position?)

original\_codes = [[random.choice(code\_elements) for j in range(default\_code\_size)] for i in range(avispa\_pool\_size)]

codes = original\_codes for generation in range(10000):
#Fitness

evaluated\_codes =  for code in codes: 1.Camina

walk = code\_to\_walk(default\_avispa\_position, code)
#Distancia Final

distance = manhattan\_distance(default\_fruta\_position, walk[-1])

evaluated\_codes.append((code, distance))


# Mejores avispas evaluated\_codes.sort(key=lambda x: x1?) surviving\_codes = evaluated\_codes[:len(evaluated\_codes)/4] best\_fit = surviving\_codes0? os.system(clear\_function) animate\_walk(default\_fruta\_position?, code\_to\_walk(default\_avispa\_position, surviving\_codes0?0?)) print "Best fit for generation", generation, "=", best\_fit1? print "Best code for generation", generation, "=", "".join(best\_fit0?) time.sleep(wait\_time\_generation) if best\_fit1? == 0:

os.system("clear") animate\_walk(default\_fruta\_position?, code\_to\_walk(default\_avispa\_position, surviving\_codes0?0?))
print\_tabl(default\_fruta\_position?, code\_to\_walk(default\_avispa\_position, surviving\_codes0?0?)) print "Done in generation", generation, "!!!" print "Final code =", "".join(surviving\_codes0?0?) exit(0)

# Siguiente generacion codes = evolve\_generation(surviving\_codes, 4)

print(time.time() - t1)

Tiempos consumidos:

Tablero 40x10

Mutación 0.05 Tiempo consumido CPU: 1232 milisegundos

Mutación 0.1 Tiempo consumido CPU: 502 milisegundos

Tablero 50x15

Mutación 0.05 Tiempo consumido CPU: 2581 milisegundos

Mutación 0.1 Tiempo consumido CPU: 639 milisegundos

Profiller:

No he podido utilizar profiler ya que he intentado ejecutar RunSnakeRun para ver cuellos de botella y demás, pero continuamente aparecía un error al ejecutarlo. Imagino que será un problema de mi versión de Python. Sin embargo he intentado descargándome otras versiones y tampoco lo conseguí.  Pregunta: ¿Existe algún manual para intentar resolver este tipo de problemas? He buscado pero no he encontrado este problema aclarado.