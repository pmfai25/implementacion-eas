/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

package org.velonuboso.pruebas_evolutivos.impl;

import java.util.Random;
import org.velonuboso.pruebas_evolutivos.interfaces.Individual;
import org.velonuboso.pruebas_evolutivos.interfaces.Operator;
import org.velonuboso.pruebas_evolutivos.interfaces.Pair;


/**
 * @author Rubén Héctor García Ortega <raiben@gmail.com>
 */

public class TunnedOperator implements Operator{

    private static Operator instance;

    private TunnedOperator() {
    }

    public static Operator getInstance() {
        if (instance == null){
            instance = new TunnedOperator();
        }
        return instance;
    }
    
    
    public Individual mutate(Individual i, Random r) {
        
        Individual ret = i.copy();
        int pos = r.nextInt(i.getSize());
        
        ret.setValue(!i.getValue(pos),pos);
        return ret;
    }

    public Pair<Individual> crossover(Individual i1, Individual i2, Random r) {

        int size = i1.getSize();
        
        Pair<Individual> ret = new Pair<Individual>(i1.copyClass(), i1.copyClass());
        
        int from = r.nextInt(size);
        int to = 0;
        do{
            to = r.nextInt(size);
        }while (to == from);
        
        int counter = from;

        while (counter != to) {
            ret.getElement1().setValue(i1.getValue(counter),counter);
            ret.getElement2().setValue(i2.getValue(counter),counter);
            counter = (counter + 1) % size;
        }

        while (counter != from) {
            ret.getElement1().setValue(i2.getValue(counter),counter);
            ret.getElement2().setValue(i1.getValue(counter),counter);
            counter = (counter + 1) % size;
        }

        return ret;
    }

    public int count(Individual i, boolean ones) {
        int count = 0;
        int s = i.getSize()/8;
        for (int it=0; it<s; it++){
            byte b = i.getByte(it);
            for (int x = 0; x < 8; x++) {
                if ((b & (1L << x)) != 0) {
                    count++;
                }
            }
        }
        return count;
    }
    
}
