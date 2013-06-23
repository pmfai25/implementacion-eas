'''
Created on 08/06/2013

@author: aaguilera
'''
from random import randint
import Consts
import Util

def single_point_crossover(dad, mom):    
    if len(dad) == 1:
        Util.raise_exception("La longitud del cromosoma debe ser > 1", TypeError)
    
    cut = randint(1, len(dad)-1)
    #print "punto de corte:", cut

    brother = dad.clone()
    brother[cut:] = mom[cut:]
    
    sister = mom.clone()
    sister[cut:] = dad[cut:]
    
    return (brother, sister)

def two_point_crossover(dad, mom):    
    if len(dad) == 1:
        Util.raise_exception("La longitud del cromosoma debe ser > 1", TypeError)

    cuts = [randint(1, len(dad)-1), randint(1, len(dad)-1)]
    
    if cuts[0] > cuts[1]:
        Util.swap_list_element(cuts, 0, 1)
    
    brother = dad.clone()
    brother[cuts[0]:cuts[1]] = mom[cuts[0]:cuts[1]]
    
    sister = mom.clone()
    sister[cuts[0]:cuts[1]] = dad[cuts[0]:cuts[1]]
    
    return (brother, sister)

def uniform_crossover(dad, mom):    
    brother = dad.clone()
    sister = mom.clone()
    
    for i in xrange(len(dad)):
        if Util.random_coin(Consts.UNIFORM_PROB):
            temp = brother[i]
            brother[i] = sister[i]
            sister[i] = temp
    
    return (brother, sister)
