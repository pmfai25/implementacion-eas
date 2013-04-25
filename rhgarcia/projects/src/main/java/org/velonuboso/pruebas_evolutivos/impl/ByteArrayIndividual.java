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

import java.util.Arrays;
import java.util.Random;
import org.velonuboso.pruebas_evolutivos.interfaces.Individual;

/**
 * @author Rubén Héctor García Ortega <raiben@gmail.com>
 */
public class ByteArrayIndividual implements Individual {

    private int size;
    private int bsize;
    private byte[] s;

    public ByteArrayIndividual(int size, Random r) {
        this.size = size;
        this.bsize = size / 8;

        this.s = new byte[bsize];
        for (int i = 0; i < bsize; i++) {
            this.s[i] = (byte) r.nextInt(256);
        }
    }

    public ByteArrayIndividual(String s) {
        this.size = s.length();
        this.bsize = size / 8;
        StringBuilder sb = new StringBuilder(s);
        for (int i = 0; i < bsize; i++) {
            this.s[i] = Byte.parseByte(sb.substring(i * 8), 2);
        }
    }

    public ByteArrayIndividual(byte[] s) {
        this.size = s.length * 8;
        this.bsize = s.length / 8;
        this.s = Arrays.copyOf(s, s.length);
    }

    public int getSize() {
        return size;
    }

    public byte[] asByteArray() {
        return Arrays.copyOf(s, s.length);
    }

    public byte getByte(int position) {
        return s[position];
    }

    public boolean getValue(int position) {
        try{
            byte b = s[position / 8];
            int bitIndex = position % 8;
            return ((b & (1L << bitIndex)) != 0);
        }catch(Exception e){
            throw e;
        }
    }

    public void setValue(boolean b, int position) {
        int bitIndex = position % 8;
        if (b) {
            s[position / 8] |= (1 << bitIndex); // set a bit to 1
        } else {
            s[position / 8] &= ~(1 << bitIndex); // set a bit to 0
        }
    }

    public Individual copyClass() {
        return new ByteArrayIndividual(s);
    }

    public Individual copy() {
        return new ByteArrayIndividual(s);
    }
    
}
