

"""Una avispa que come fruta se tira en una tablero rectangular.
Hay fruta en otra parte del tablero, por lo que el movimiento de la avispa
se determina por su codigo genetico. En cada generacion, mutaciones aleatorias se producen
en el código, y los mejores hijos (los que llegan más cerca de la fruta), se seleccionan.
Estos hijos tienen sus hijos propios (avispas hijas) hasta que al menos un hijo es capaz de alcanzar la fruta.

@author Francisco Estella, UGR
"""

import sys
import os
import time
import random


# Geometría del tablero y posicion de la fruta y de la avispa
default_tabl_size = (80,25)
default_fruta_position = (60,5)
default_avispa_position = (30,15)

code_elements = ["n", "s", "e", "w"]

# Vectores de movimiento
move_vectors = dict()
move_vectors[code_elements[0]] = (0,-1)
move_vectors[code_elements[1]] = (0,1)
move_vectors[code_elements[2]] = (1,0)
move_vectors[code_elements[3]] = (-1,0)

# La longitud del codigo será la distancia de la avispa a la fruta+ el offset
code_size_offset = 10

# avispas por generacion
avispa_pool_size = 2**5

# Probabilidad de mutación
mutation_probability = 0.1


default_fruta_char = "F"
default_avispa_char = "@"
default_tabl_char = "#"
default_space_char = "·"

## Comando para limpiar consola: cls = windows.
clear_function = "cls"

## Tiempo de espera entre pasos
wait_time_step = 0.05

## Tiempo de espera mientras anda la avispa, mientras se está en animación
wait_time_generation = 2



def print_tabl(fruta_pos_list, avispa_pos_list,
		size=default_tabl_size,
		fruta_char=default_fruta_char,
		avispa_char=default_avispa_char,
		tabl_char=default_tabl_char,
		space_char=default_space_char):
  """Dibuja el tablero con las avispas y la fruta en la posicion deseada"""
  print "Distancia =", manhattan_distance(fruta_pos_list[0], avispa_pos_list[0])

  # Primera fila
  for y in range(size[0] + 2):
    sys.stdout.write(tabl_char)
  print

  # filas del tablero
  for y in range(size[1]):
    sys.stdout.write(tabl_char)
    for x in range(size[0]):
      if (x,y) in fruta_pos_list:
	sys.stdout.write(fruta_char)
      elif (x,y) in avispa_pos_list:
	sys.stdout.write(avispa_char)
      else:
	sys.stdout.write(space_char)
    sys.stdout.write(tabl_char)
    print

  # Ultima fila
  for y in range(size[0] + 2):
    sys.stdout.write(tabl_char)
  print

def is_good_pos(position, tabl_size=default_tabl_size):
  """¿Posicion valida?"""
  if position[0] < 0 or position[1] < 0:
    return False
  if position[0] >= tabl_size[0] or position[1] >= tabl_size[1]:
    return False
  return True

def code_to_walk(origin, code, fruta_list=[default_fruta_position]):
  """Camina"""
  avispa_pos_list = [origin]
  for c in code:
    old_pos = avispa_pos_list[-1]
    move_vector = move_vectors[c]
    new_pos = (old_pos[0] + move_vector[0], old_pos[1] + move_vector[1])
    if is_good_pos(new_pos):
      avispa_pos_list.append(new_pos)
      
      # Parar si se obtiene la fruta!
      if new_pos in fruta_list:
	return avispa_pos_list

  return avispa_pos_list

def animate_walk(fruta_list, avispa_list):
  """animacion de la avispa avanzando"""
  for i in range(len(avispa_list)):
    time.sleep(wait_time_step)
    os.system(clear_function)
    print_tabl(fruta_pos_list=[default_fruta_position], avispa_pos_list=avispa_list[i:i+1])
  #print_tabl(fruta_pos_list=[default_fruta_position], avispa_pos_list=avispa_list)

def manhattan_distance(pos1, pos2):
  """Distancia"""
  return abs(pos1[0]-pos2[0]) + abs(pos1[1]-pos2[1])

def mutate_code(old_code, mutation_probability=mutation_probability):
  """Mutacion"""
  code = list(old_code)
  for position in range(len(code)):
    if random.random() <= mutation_probability:
      new_base = random.choice(code_elements)
      code[position] = new_base
  return code

def evolve_generation(pool, reproduction_factor):
  """Reproducir generacion"""
  next_generation = []
  for evaluation in pool:
    avispa = evaluation[0]
    for i in range(reproduction_factor):
      next_generation.append(mutate_code(avispa))
  return next_generation


############################################################################################
############################################################################################
############################################################################################

#                                 BEGIN executable part                                    #

############################################################################################
############################################################################################
############################################################################################

default_code_size = manhattan_distance(default_fruta_position, default_avispa_position) + code_size_offset

print_tabl(fruta_pos_list=[default_fruta_position], avispa_pos_list=[default_avispa_position])

original_codes = [[random.choice(code_elements) for j in range(default_code_size)] for i in range(avispa_pool_size)]

codes = original_codes
for generation in range(10000):
  # Fitness
  evaluated_codes = []
  for code in codes:
    # Camina
    walk = code_to_walk(default_avispa_position, code)
    # Distancia Final
    distance = manhattan_distance(default_fruta_position, walk[-1])
    
    evaluated_codes.append((code, distance))

  # Mejores avispas
  evaluated_codes.sort(key=lambda x: x[1])
  surviving_codes = evaluated_codes[:len(evaluated_codes)/4]
  best_fit = surviving_codes[0]
  os.system(clear_function)
  animate_walk([default_fruta_position], code_to_walk(default_avispa_position, surviving_codes[0][0]))
  print "Best fit for generation", generation, "=", best_fit[1]
  print "Best code for generation", generation, "=", "".join(best_fit[0])
  time.sleep(wait_time_generation)
  if best_fit[1] == 0:
    os.system("clear")
    animate_walk([default_fruta_position], code_to_walk(default_avispa_position, surviving_codes[0][0]))
    print_tabl([default_fruta_position], code_to_walk(default_avispa_position, surviving_codes[0][0]))
    print "Done in generation", generation, "!!!"
    print "Final code =", "".join(surviving_codes[0][0])
    exit(0)

  # Siguiente generación
  codes = evolve_generation(surviving_codes, 4)
