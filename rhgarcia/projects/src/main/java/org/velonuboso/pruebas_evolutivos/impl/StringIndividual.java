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


/**
 * @author Rubén Héctor García Ortega <raiben@gmail.com>
 */

public class StringIndividual implements Individual{

    private int size;
    private String s;

    public StringIndividual(int size, Random r) {
        this.size = size;
        StringBuffer sb = new StringBuffer();
        for (int i=0; i<size; i++){
            sb.append(String.valueOf(r.nextInt(2)));
        }
        s = sb.toString();
    }

    public StringIndividual(String s) {
        this.size = s.length();
        this.s = new String(s);
    }
    
    public StringIndividual(byte[] s) {
        StringBuffer sb = new StringBuffer();
        
        for (int i=0; i<s.length; i++){
            String s2 = new String("00000000");
            for (int bit = 0; bit < 8; bit++) {
                if (((s[i] >> bit) & 1) > 0) {
                    sb.setCharAt(7 - bit, '1');
                }
            }
            sb.append(s2);
        }
        
        this.s = sb.toString();
        this.size = this.s.length();
    }
    
    
    public int getSize() {
        return size;
    }

    public byte[] asByteArray() {
        byte[] ret = new byte[size/8];
        
        for (int i=0; i<s.length(); i++){
            ret[i/8] = Byte.parseByte(s.substring(i, i+1), 2);
        }
        
        return ret;
    }

    public byte getByte(int position) {
        return (byte)Integer.parseInt(s.substring(position, position+8), 2);
    }

    public boolean getValue(int position) {
        return s.charAt(position)=='1';
    }

    public void setValue(boolean b, int position) {
        StringBuilder aux = new StringBuilder(s);
        aux.setCharAt(position, b?'1':'0');
        s = aux.toString();
    }

    public Individual copyClass() {
        return new StringIndividual(s);
    }

    public Individual copy() {
        return new StringIndividual(s);
    }
    
}
