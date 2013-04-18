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
        Random r = new Random();

        System.out.println("Array length = " + MAX);


        // First test
        long d1 = System.currentTimeMillis();
        // generating a random string
        StringBuffer stb = new StringBuffer();
        stb.append("");
        for (int i = 0; i < MAX; i++) {
            stb.append(String.valueOf(r.nextInt(2)));
        }
        String str = stb.toString();
        // counting
        int countOnes = 0;
        for (int i = 0; i < MAX; i++) {
            if (str.charAt(i) == '1') {
                countOnes++;
            }
        }
        long duration = System.currentTimeMillis() - d1;
        System.out.println("Count = " + countOnes);
        System.out.println("Duration = " + duration);

        // Second test
        d1 = System.currentTimeMillis();
        // generating a random string
        int size = MAX / 8;
        byte buffer[] = new byte[size];
        for (int i = 0; i < size; i++) {
            buffer[i] = (byte) r.nextInt(256);
        }

        // counting
        countOnes = 0;
        for (int i = 0; i < size; i++) {
            int b = buffer[i];
            for (int x = 0; x < 8; x++) {
                if ((b & (1L << x)) != 0) {
                    countOnes++;
                }
            }
        }
        duration = System.currentTimeMillis() - d1;
        System.out.println("Count = " + countOnes);
        System.out.println("Duration = " + duration);

    }
}
