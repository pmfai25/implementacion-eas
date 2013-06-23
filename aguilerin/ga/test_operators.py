'''
Created on 08/06/2013

@author: aaguilera
'''
import BinaryString
#import Consts
import Crossovers
#import Mutators
import time

if __name__ == "__main__":
    size = 100
    cross_max_iters = 100000
    #mut_max_iters = 1000000
    pmut = 0.02
    dad = BinaryString.BinaryString(size)
    mom = BinaryString.BinaryString(size)
    #print dad
    #print mom
    
    start = time.time()
    for i in xrange(1, cross_max_iters):
        (son1, son2) = Crossovers.single_point_crossover(dad, mom)    
    end = time.time()
    print "single_point_crossover time:", ((end-start)*1000) / cross_max_iters, "ms"
    
    #print son1
    #print son2

    start = time.time()
    for i in xrange(1, cross_max_iters):
        (son1, son2) = Crossovers.two_point_crossover(dad, mom)    
    end = time.time()
    print "two_point_crossover time:", ((end-start)*1000) / cross_max_iters, "ms"

    start = time.time()
    for i in xrange(1, cross_max_iters):
        (son1, son2) = Crossovers.uniform_crossover(dad, mom)    
    end = time.time()
    print "uniform_crossover time:", ((end-start)*1000) / cross_max_iters, "ms"
    """
    start = time.time()
    for i in xrange(1, mut_max_iters):
        mut = Mutators.swap_mutator(dad, Consts.MUTATION_PROB)    
    end = time.time()
    print "swap_mutator time:", ((end-start)*1000) / mut_max_iters, "ms"
    
    start = time.time()
    for i in xrange(1, mut_max_iters):
        mut = Mutators.flip_mutator(dad, Consts.MUTATION_PROB)    
    end = time.time()
    print "flip_mutator time:", ((end-start)*1000) / mut_max_iters, "ms"
    """