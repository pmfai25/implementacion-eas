'''
Created on 08/06/2013

@author: aaguilera
'''
from random import choice
import Util

class BinaryString:    
    def __init__(self, length=10):
        self.fitness = 0.0        
        self.genome_size = length
        self.genome_list = [ choice((0,1)) for i in xrange(self.genome_size) ]
        self.needs_eval = True
        
    def __iadd__(self, item):
        self.genome_list.append(item)
        return self

    def __eq__(self, other):
        cond1 = (self.genome_size == other.genome_size)
        cond2 = (self.genome_list == other.genome_list)
        return (cond1 and cond2)
    
    def __contains__(self, value):
        return value in self.genome_list
    
    def __getslice__(self, a, b):
        return self.genome_list[a:b]
    
    def __setslice__(self, a, b, val):
        self.genome_list[a:b] = val
    
    def __getitem__(self, key):
        return self.genome_list[key]
    
    def __setitem__(self, key, value):
        if value not in (0, 1):
            Util.raise_exception("El valor debe ser cero (0) o uno (1), en lugar de %s" % value, ValueError)
        self.genome_list[key] = value
    
    def __iter__(self):
        return iter(self.genome_list)
    
    def __len__(self):
        return self.genome_size
    
    def get_list_size(self):
        return self.genome_size    
    
    def copy(self, g):
        g.fitness = self.fitness
        g.genome_size = self.genome_size
        g.genome_list = self.genome_list[:]
    
    def get_fitness_score(self):
        return self.fitness
    
    def get_ones(self):
        return bin(self.get_decimal()).count('1')
    
    def __repr__(self):
        #ret = ""
        #ret = "- BinaryString\n"
        #ret += "\tString length:\t %s\n" % (self.get_list_size(),)
        #ret += "\tString: %s" % (self.get_binary(),)
        #ret += "\tDecimal value:\t %s\n" % (self.get_decimal(),)
        #ret += "\tOnes:\t %s\n" % (self.get_ones(),)
        #ret += "\tFitness: %s" % (self.fitness,) # %.6f
        ret = ",%s,%s" % (self.get_binary(), self.fitness,) #csv
        
        return ret
    
    def get_decimal(self):
        return int(self.get_binary(), 2)
    
    def get_binary(self):
        return "" . join(map(str, self))
    
    def clone(self):
        newcopy = BinaryString(self.get_list_size())
        self.copy(newcopy)
        return newcopy
    
    def evaluate(self):
        if self.needs_eval:
            self.fitness = self.get_ones()
            self.needs_eval = False
