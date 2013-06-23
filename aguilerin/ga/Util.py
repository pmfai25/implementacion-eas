'''
Created on 08/06/2013

@author: aaguilera
'''
from random import random

def random_coin(p):
    """ Returns True with the p probability """
    if p == 1.0:
        return True
    if p == 0.0:
        return False
    if random() <= p:
        return True
    else:
        return False

def swap_list_element(xlist, index_a, index_b):
    """ Swaps elements A and B in a list """
    temp = xlist[index_a]
    xlist[index_a] = xlist[index_b]
    xlist[index_b] = temp

def raise_exception(message, expt=None):
    if expt is None:
        raise Exception(message)
    else:
        raise expt, message

def cmp_individual(a, b):
    if a.fitness < b.fitness:
        return -1
    if a.fitness > b.fitness:
        return 1
    return 0
