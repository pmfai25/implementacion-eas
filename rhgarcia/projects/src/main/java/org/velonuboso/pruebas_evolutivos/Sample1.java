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

import java.util.Random;

/**
 * @author Rubén Héctor García Ortega <raiben@gmail.com>
 */
public class Sample1 {

    public static int MAX = 1000000;

    public static void main(String[] args) {

        Sample1 s = new Sample1();

        Random r = new Random();

        System.out.println("Array length = " + MAX);

        int counter = s.countOnesV1(r, MAX);
        counter = s.countOnesV2(r, MAX);


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

        int from = r.nextInt(source.length);
        int to = r.nextInt(source.length);
        if (from < to) {
            int aux = from;
            from = to;
            to = aux;
        }

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

        int from = r.nextInt(source.length);
        int to = r.nextInt(source.length);
        if (from < to) {
            int aux = from;
            from = to;
            to = aux;
        }

        int counter = 0;

        while (counter < from) {
            ret[0][counter] = source[0][counter];
            ret[1][counter] = source[1][counter];
        }

        while (counter < from) {
            ret[0][counter] = source[1][counter];
            ret[1][counter] = source[0][counter];
        }

        while (counter < from) {
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
