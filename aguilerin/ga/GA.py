'''
Created on 08/06/2013

@author: aaguilera
'''
from random import sample
import Consts
import Population

class GA:
    def __init__(self):
        self.population_size    = Consts.POPULATION_SIZE
        self.genome_size        = Consts.GENOME_SIZE
        self.old_population     = Population.Population(self.population_size, self.genome_size)
        self.new_population     = None
        self.generations        = Consts.GENERATIONS
        self.mutation_prob      = Consts.MUTATION_PROB
        self.crossover_prob     = Consts.CROSSOVER_PROB
        self.tournamet_size     = Consts.TOURNAMENT_SIZE
        self.best_guy           = None
        
    def initialize(self):
        self.old_population.initialize()
    
    def best_fitness(self):
        if self.best_guy is None:
            self.best_guy = self.old_population.best_fitness()            
        return self.best_guy.__repr__()
    
    def __repr__(self):
        """
        ret =  "- GA\n"
        ret += "\tPopulation Size:\t %d\n" % (self.population_size,)
        ret += "\tGenerations:\t\t %d\n" % (self.generations,)
        ret += "\tMutation Rate:\t\t %.2f\n" % (self.mutation_prob,)
        ret += "\tCrossover Rate:\t\t %.2f\n" % (self.crossover_prob,)
        ret += "\t" + self.old_population.__repr__()
        ret += "\n"
        """
        ret = self.best_guy.__repr__()
        return ret
        
    def evaluate(self):
        if self.new_population == None:
            self.old_population.evaluate()
        else:
            self.new_population.evaluate()
        
    def swap_populations(self):
        self.old_population = self.new_population
        
    def crossover(self):
        self.new_population.crossover(self.crossover_prob)
        
    def mutation(self):
        self.new_population.mutate(self.mutation_prob)
        
    def tournament_selection(self):
        self.old_population.sort()
        self.best_guy = self.old_population.best_fitness()
        self.new_population = Population.Population(0, Consts.GENOME_SIZE)
        for i in xrange(self.population_size):
            sampl = sample(xrange(self.population_size), self.tournamet_size)
            self.new_population.append(self.old_population[min(sampl)])
    
    def elitism(self):
        if not self.new_population.find_individual(self.best_guy):
            self.new_population.sort()
            self.new_population[self.population_size-1] = self.best_guy

    def stop_condition(self, num_gen):
        cond1 = (num_gen == self.generations)
        num_gen_max_fitness = 0
        for i in xrange(self.population_size):
            if self.new_population.internal_pop[i].fitness == self.genome_size:
                num_gen_max_fitness += 1
        cond2 = (num_gen_max_fitness == self.population_size)
        return (cond1 or cond2)
