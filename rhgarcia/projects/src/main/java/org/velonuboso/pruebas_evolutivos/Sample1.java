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

    public static int MAX = 1000;
    public static int POOL_SIZE = 50;
    public static int ITERATIONS = 100000;
    
    
    public static void main (String[] args) {
    
        Random r = new Random(0);
        ByteArrayIndividual bestIndividual = new ByteArrayIndividual(MAX, r);
        int bestValue = 0;
        TunnedOperator op = (TunnedOperator) TunnedOperator.getInstance();
        
        // 1st step, first population
        ArrayList<ByteArrayIndividual> population = new ArrayList ();
        for (int i=0; i<POOL_SIZE; i++){
            ByteArrayIndividual ind = new ByteArrayIndividual(MAX, r);
            population.add(ind);
        }
        
        int iter = 0;
        while (iter<ITERATIONS || (bestValue == MAX)){
            
            System.out.println("Generation "+iter);
            
            ArrayList<ByteArrayIndividual> pool = new ArrayList ();
            for (int i=0; i<POOL_SIZE; i++){
                int p0 = r.nextInt(POOL_SIZE);
                int p1 = 0;
                do{
                    p1 = r.nextInt(POOL_SIZE);
                }while (p1 == p0);

                ByteArrayIndividual ind0 = population.get(p0);
                ByteArrayIndividual ind1 = population.get(p1);

                int n0 = op.count(ind0, true);
                int n1 = op.count(ind1, true);

                if (n0>n1){
                    pool.add(ind0);
                    if (n0>bestValue){
                        bestValue = n0;
                        bestIndividual = ind0;
                        System.out.println("Best value "+bestValue);
                    }
                }else{
                    pool.add(ind1);
                    if (n1>bestValue){
                        bestValue = n1;
                        bestIndividual = ind1;
                        System.out.println("Best value "+bestValue);
                    }
                }
            }

            population = new ArrayList<>();
            for (int i=0; i<POOL_SIZE; i+=2){
                ByteArrayIndividual ind0 = pool.get(i);
                ByteArrayIndividual ind1 = pool.get(i+1);

                Pair<Individual> a = op.crossover(ind0, ind1, r);
                ByteArrayIndividual b0 = (ByteArrayIndividual)a.getElement1();
                ByteArrayIndividual b1 = (ByteArrayIndividual)a.getElement2();

                b0 = (ByteArrayIndividual) op.mutate(b0, r);
                b1 = (ByteArrayIndividual) op.mutate(b1, r);

                population.add(b0);
                population.add(b1);
            }
            iter++;
        }
        System.out.println("END");
        System.out.println("Best individual "+ bestIndividual.toString());
        System.out.println("Best value "+bestValue);
        
    }
    
    
    /*
    public static void main(String[] args) throws NoSuchMethodException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException, IOException {

        ArrayList<Class> classesIndivisuals = new ArrayList<Class>();
        //classesIndivisuals.add(StringIndividual.class);
        classesIndivisuals.add(ByteArrayIndividual.class);
        
        ArrayList<Class> classesOperators = new ArrayList<Class>();
        //classesOperators.add(BasicOperator.class);
        classesOperators.add(TunnedOperator.class);
        
        
        HashMap<String,ArrayList<Long>> results = new HashMap<String, ArrayList<Long>>(); 
        
        for (Class o:classesOperators){
        
            Operator opInstance = (Operator) o.getMethod("getInstance").invoke(null);
            
            for (Class c:classesIndivisuals){
                Random r = new Random(0);

                long t0 = 0;

                t0 = System.currentTimeMillis();
                Individual i1 = (Individual) c.getDeclaredConstructor(int.class,Random.class).newInstance(MAX, r);
                long tCreation1 = System.currentTimeMillis();
                int count1 = opInstance.count(i1, true);
                long tCount1 = System.currentTimeMillis();

                Individual i2 = (Individual) c.getDeclaredConstructor(int.class,Random.class).newInstance(MAX, r);
                long tCreation2 = System.currentTimeMillis();
                int count2 = opInstance.count(i2, true);
                long tCount2 = System.currentTimeMillis();

                Individual i3 = opInstance.mutate(i1, r);
                long tMutation = System.currentTimeMillis();
                Pair<Individual> p = opInstance.crossover(i2, i3, r);
                long tCrossover = System.currentTimeMillis();
                int count3 = opInstance.count(p.getElement1(), true);
                long tCount3 = System.currentTimeMillis();


                String ret = new String();
                ret += "Operator: "+o.getSimpleName()+"\n";
                ret += "Individual: "+c.getSimpleName()+"\n\n";

                ret += "First individual:\n";
                ret += "creation time: "+(tCreation1-t0)+" ms\n";
                ret += "count time: "+(tCount1-tCreation1)+" ms\n";
                ret += "number of ones: "+count1+"\n\n";

                ret += "Second individual:\n";
                ret += "creation time: "+(tCreation2-tCount1)+" ms\n";
                ret += "count time: "+(tCount2-tCreation2)+" ms\n";
                ret += "number of ones: "+count2+"\n\n";

                ret += "mutation time: "+(tMutation-tCount2)+" ms\n";
                ret += "crossover time: "+(tCrossover-tMutation)+" ms\n";

                ret += "Last individual:\n";
                ret += "count time: "+(tCount3-tCrossover)+" ms\n";
                ret += "number of ones: "+count3+"\n\n";

                System.out.println(ret);
                
                ArrayList<Long> values = new ArrayList<Long>();
                results.put(o.getSimpleName()+"_"+c.getSimpleName(), values);
                
                values.add(tCreation1-t0);
                values.add(tCount1-tCreation1);
                //values.add((long)count1);

                values.add(tCreation2-tCount1);
                values.add(tCount2-tCreation2);
                //values.add((long)count2);
                values.add(tMutation-tCount2);
                values.add(tCrossover-tMutation);

                values.add(tCount3-tCrossover);
                //values.add((long)count3);
                
            }
        }
        
        printToHtml("results.html", results);
    }
    */

    private static void printToHtml(String name, HashMap<String, ArrayList<Long>> results) throws IOException {
        String ret = "<table border=\"1\" cellpadding=\"10px\">\n";
        for (String key: results.keySet()){
            ret+="<tr>\n<td>"+key+"</td>";
            
            for (Long l:results.get(key)){
                ret+="<td>"+l+"</td>";
            }
            ret+="\n</tr>\n";
        }
        ret += "</table>";
        
        FileUtils.write(new File(name), ret);
    }

    public Sample1() {
    }

    private int countOnesV1(Random r, int size) {
        // First test
        long d1 = System.currentTimeMillis();
        // generating a random string
        String str = newRandomString(r, size);

        // counting
        int countOnes = 0;
        for (int i = 0; i < size; i++) {
            if (str.charAt(i) == '1') {
                countOnes++;
            }
        }
        long duration = System.currentTimeMillis() - d1;
        System.out.println("Count = " + countOnes);
        System.out.println("Duration = " + duration);
        return countOnes;
    }

    private int countOnesV2(Random r, int sizeM) {
        // Second test
        long d1 = System.currentTimeMillis();
        // generating a random string
        int size = sizeM / 8;
        byte buffer[] = newRandomBuffer(r, sizeM);

        // counting
        int countOnes = 0;
        for (int i = 0; i < size; i++) {
            int b = buffer[i];
            for (int x = 0; x < 8; x++) {
                if ((b & (1L << x)) != 0) {
                    countOnes++;
                }
            }
        }
        long duration = System.currentTimeMillis() - d1;
        System.out.println("Count = " + countOnes);
        System.out.println("Duration = " + duration);

        return countOnes;
    }

    private String[] crossoverV1(String[] source, Random r) {

        long d1 = System.currentTimeMillis();

        String ret[] = new String[source.length];
        ret[0] = new String();
        ret[1] = new String();

        int from = r.nextInt(source[0].length()-1);
        int to = from + r.nextInt(source[0].length()-from);
        

        ret[0] = source[0].substring(0, from);
        ret[1] = source[1].substring(0, from);

        ret[0] = source[1].substring(from, to);
        ret[1] = source[0].substring(from, to);

        ret[0] = source[0].substring(to);
        ret[1] = source[1].substring(to);

        long duration = System.currentTimeMillis() - d1;
        System.out.println("Duration = " + duration);

        return ret;
    }

    private byte[][] crossoverV2(byte[][] source, Random r) {
        
        long d1 = System.currentTimeMillis();

        byte ret[][] = new byte[source.length][];
        ret[0] = new byte[source[0].length];
        ret[1] = new byte[source[0].length];

        int from = r.nextInt(source[0].length-1);
        int to = from + r.nextInt(source[0].length-from);
        
        int counter = 0;

        while (counter < from) {
            ret[0][counter] = source[0][counter];
            ret[1][counter] = source[1][counter];
        }

        while (counter < to) {
            ret[0][counter] = source[1][counter];
            ret[1][counter] = source[0][counter];
        }

        while (counter < source[0].length) {
            ret[0][counter] = source[0][counter];
            ret[1][counter] = source[1][counter];
        }

        long duration = System.currentTimeMillis() - d1;
        System.out.println("Duration = " + duration);

        return ret;
    }

    private String mutateV1(String s1, Random r) {
        long d1 = System.currentTimeMillis();


        int pos = r.nextInt(s1.length());
        String ret = new String(s1.substring(0, pos));
        
        ret += s1.charAt(pos) == '0' ? '1' : '0';

        if (pos < s1.length()) {
            ret += s1.substring(pos + 1, s1.length());
        }

        long duration = System.currentTimeMillis() - d1;
        System.out.println("Duration = " + duration);

        return ret;
    }

    private byte[] mutateV2(byte[] s1, Random r) {
        long d1 = System.currentTimeMillis();
        byte[] ret = new byte[s1.length];
        int pos = r.nextInt(s1.length);
        
        int counter = 0;
        while (counter < pos) {
            ret[counter] = s1[counter];
        }
        ret[counter] = s1[counter] == (byte)0L ? (byte)1L : (byte)0L;

        counter++;
        while (counter < pos) {
            ret[counter] = s1[counter];
        }
        
        long duration = System.currentTimeMillis() - d1;
        System.out.println("Duration = " + duration);

        return ret;
        
    }

    private byte[] newRandomBuffer(Random r, int sizeM) {
        byte buffer[] = new byte[sizeM];
        for (int i = 0; i < sizeM; i++) {
            buffer[i] = (byte) r.nextInt(256);
        }
        return buffer;
    }

    private String newRandomString(Random r, int size) {
        StringBuffer stb = new StringBuffer();
        stb.append("");
        for (int i = 0; i < size; i++) {
            stb.append(String.valueOf(r.nextInt(2)));
        }
        String str = stb.toString();
        return str;
    }
}
