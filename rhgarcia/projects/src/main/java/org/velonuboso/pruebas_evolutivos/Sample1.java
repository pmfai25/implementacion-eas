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
package org.velonuboso.pruebas_evolutivos;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;
import org.apache.commons.io.FileUtils;
import org.velonuboso.pruebas_evolutivos.impl.BasicOperator;
import org.velonuboso.pruebas_evolutivos.impl.ByteArrayIndividual;
import org.velonuboso.pruebas_evolutivos.impl.StringIndividual;
import org.velonuboso.pruebas_evolutivos.impl.TunnedOperator;
import org.velonuboso.pruebas_evolutivos.interfaces.Individual;
import org.velonuboso.pruebas_evolutivos.interfaces.Operator;
import org.velonuboso.pruebas_evolutivos.interfaces.Pair;

/**
 * @author Rubén Héctor García Ortega <raiben@gmail.com>
 */
public class Sample1 {

    public static int MAX = 160;
    public static int POOL_SIZE = 160;
    public static int ITERATIONS = 1000000;
    public static int EXECUTIONS = 100;

    public static void main(String[] args) {

        long[] valuesTime = new long[EXECUTIONS];
        long[] valuesIteration = new long[EXECUTIONS];


        for (int execution = 0; execution < EXECUTIONS; execution++) {

            long t0 = System.currentTimeMillis();

            Random r = new Random();
            ByteArrayIndividual bestIndividual = new ByteArrayIndividual(MAX, r);
            int bestValue = 0;
            TunnedOperator op = (TunnedOperator) TunnedOperator.getInstance();

            // 1st step, first population
            ArrayList<ByteArrayIndividual> population = new ArrayList();
            for (int i = 0; i < POOL_SIZE; i++) {
                ByteArrayIndividual ind = new ByteArrayIndividual(MAX, r);
                population.add(ind);
            }

            int iter = 0;
            while (iter < ITERATIONS && (bestValue < MAX)) {

                System.out.println("Generation " + iter);

                ArrayList<ByteArrayIndividual> pool = new ArrayList();
                for (int i = 0; i < POOL_SIZE; i++) {
                    int p0 = r.nextInt(POOL_SIZE);
                    int p1 = 0;
                    do {
                        p1 = r.nextInt(POOL_SIZE);
                    } while (p1 == p0);

                    ByteArrayIndividual ind0 = population.get(p0);
                    ByteArrayIndividual ind1 = population.get(p1);

                    int n0 = op.count(ind0, true);
                    int n1 = op.count(ind1, true);

                    if (n0 > n1) {
                        pool.add(ind0);
                        if (n0 > bestValue) {
                            bestValue = n0;
                            bestIndividual = ind0;
                            System.out.println("Best value " + bestValue);
                        }
                    } else {
                        pool.add(ind1);
                        if (n1 > bestValue) {
                            bestValue = n1;
                            bestIndividual = ind1;
                            System.out.println("Best value " + bestValue);
                        }
                    }
                }

                population = new ArrayList<>();
                for (int i = 0; i < POOL_SIZE; i += 2) {
                    ByteArrayIndividual ind0 = pool.get(i);
                    ByteArrayIndividual ind1 = pool.get(i + 1);

                    Pair<Individual> a = op.crossover(ind0, ind1, r);
                    ByteArrayIndividual b0 = (ByteArrayIndividual) a.
                            getElement1();
                    ByteArrayIndividual b1 = (ByteArrayIndividual) a.
                            getElement2();

                    b0 = (ByteArrayIndividual) op.mutate(b0, r);
                    b1 = (ByteArrayIndividual) op.mutate(b1, r);

                    population.add(b0);
                    population.add(b1);
                }
                iter++;
            }
            System.out.println("END");
            System.out.println("Best individual " + bestIndividual.toString());
            System.out.println("Best value " + bestValue);

            valuesTime[execution] = System.currentTimeMillis() - t0;
            valuesIteration[execution] = iter - 1;
        }

        long averageTime = 0;
        String str = "";
        for (long l : valuesTime) {
            averageTime += l;
            str += l + ", ";
        }
        averageTime /= EXECUTIONS;


        long averageIteration = 0;
        String str2 = "";
        for (long l : valuesIteration) {
            averageIteration += l;
            str2 += l + ", ";
        }
        averageIteration /= EXECUTIONS;


        System.out.println("Number of executions = " + EXECUTIONS);
        System.out.println("Time per execution: [" + str + "]");
        System.out.println("Average time : " + averageTime + " ms");
        System.out.println("Generations per execution: " + str2);
        System.out.println("Average generations: " + averageIteration
                + " iterations");
    }
}
