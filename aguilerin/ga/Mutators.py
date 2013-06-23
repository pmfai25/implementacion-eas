'''
Created on 08/06/2013

@author: aaguilera
'''
from random import randint
import Util

def swap_mutator(genome, pmut):
    if pmut <= 0.0:
        return 0
    mutations = pmut * (genome.genome_size)
    
    if mutations < 1.0:
        mutations = 0
        for it in xrange(genome.genome_size):
            if Util.random_coin(pmut):
                Util.swap_list_element(genome, it, randint(0, genome.genome_size-1))
                mutations += 1
                genome.needs_eval = True  
    else:
        for it in xrange(int(round(mutations))):
            Util.swap_list_element(genome, randint(0, genome.genome_size-1), randint(0, genome.genome_size-1))
        genome.needs_eval = True
    
    return mutations

def flip_mutator(genome, pmut):
    if pmut <= 0.0:
        return 0
    mutations = pmut * (genome.genome_size)
    
    if mutations < 1.0:
        mutations = 0
        for it in xrange(genome.genome_size):
            if Util.random_coin(pmut):
                if genome[it] == 0:
                    genome[it] = 1
                else:
                    genome[it] = 0
                mutations += 1
                genome.needs_eval = True
    else:
        for it in xrange(int(round(mutations))):
            which = randint(0, genome.genome_size-1)
            if genome[which] == 0:
                genome[which] = 1
            else:
                genome[which] = 0
        genome.needs_eval = True
    
    return mutations
