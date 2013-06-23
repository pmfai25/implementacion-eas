'''
Created on 08/06/2013

@author: aaguilera
'''
import GA

if __name__ == '__main__':
    num_gen = 0    
    # generacion de la poblacion inicial
    ga = GA.GA()
    ga.initialize()
    # evaluacion de la poblacion
    ga.evaluate()
    # mostrar informacion
    print str(num_gen) + ga.best_fitness()
    
    num_gen += 1
    
    #print ga.old_population.__repr__()
    
    while True:
        #print "num_gen:", num_gen
        #print ga.old_population.__repr__()
        # seleccion por torneo
        ga.tournament_selection()
        # cruce
        ga.crossover()
        # mutacion
        ga.mutation()
        # evaluacion de la poblacion
        ga.evaluate()
        # seleccion elitista
        ga.elitism()
        # intercambio de poblacion
        ga.swap_populations()
        # mostrar informacion
        print str(num_gen) + str(ga)
        # comprobar condicion de parada
        num_gen += 1
        if ga.stop_condition(num_gen):
            break
    
    #print "-------------------------------------------------"
    #print "num_gen:", num_gen
    #print ga.new_population.__repr__()
