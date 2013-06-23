'''
Created on 08/06/2013

@author: aaguilera
'''
from random import random
import BinaryString
import Crossovers
import Mutators
import Util

class Population:    
    def __init__(self, pop_size, gen_size):
        self.pop_size       = pop_size
        self.gen_size       = gen_size
        self.internal_pop   = []
        self.sorted         = False
    
    def initialize(self):
        self.internal_pop = [ BinaryString.BinaryString(self.gen_size) for i in xrange(self.pop_size) ]
    
    def append(self, genome):
        self.internal_pop.append(genome)
        self.pop_size += 1
    
    def __repr__(self):
        ret = ""
        #ret =  "- Population\n"
        ret += "\tPopulation Size:\t %d\n" % (self.pop_size,)
        ret += "\tGenome Size:\t %d\n" % (self.gen_size,)
        for gen in self.internal_pop:
            ret += "\t" + gen.__repr__() + "\n"
        #ret += self.stats.__repr__()
        return ret
    
    def __len__(self):
        return len(self.internal_pop)
    
    def __getitem__(self, key):
        return self.internal_pop[key]
    
    def __iter__(self):
        return iter(self.internal_pop)
    
    def __setitem__(self, key, value):
        self.internal_pop[key] = value
    
    def best_fitness(self, index=0):
        self.sort()
        return self.internal_pop[index]
    
    def sort(self):
        if self.sorted:
            return        
        self.internal_pop.sort(cmp=Util.cmp_individual, reverse=True)        
        self.sorted = True
        
    def find_individual(self, individual):
        for i in xrange(self.pop_size):
            if individual == self.internal_pop[i]:
                return True
        return False
            
    def evaluate(self):
        for i in xrange(self.pop_size):
            self.internal_pop[i].evaluate()
            
    def crossover(self, pcross):
        for i in xrange(0, self.pop_size, 2):
            if random() < pcross:
                (son1, son2) = Crossovers.single_point_crossover(self.internal_pop[i], self.internal_pop[i+1])
                self.internal_pop[i] = son1
                self.internal_pop[i].needs_eval = True
                self.internal_pop[i+1] = son2
                self.internal_pop[i+1].needs_eval = True
        
    def mutate(self, pmut):
        for i in xrange(self.pop_size):
            Mutators.flip_mutator(self.internal_pop[i], pmut)
    
    def copy(self, pop):
        pop.pop_size       = self.pop_size
        pop.gen_size       = self.gen_size
        pop.internal_pop   = self.internal_pop
        pop.sorted         = self.sorted
    
    def clear(self):
        del self.internal_pop[:]
    
    def clone(self):
        new_pop = Population(self.pop_size, self.gen_size)
        self.copy(new_pop)
        return new_pop
    
