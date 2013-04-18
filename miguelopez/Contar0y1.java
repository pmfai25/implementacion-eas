/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package contar0y1;

import java.util.ArrayList;

/**
 *
 * @author Miguel
 */
public class Contar0y1 {

    static long funcion1(ArrayList vec) {
        
          long tiempoInicio1 = System.currentTimeMillis();
    
        int cont = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec.get(i) == 1) {
                cont++;
            }
        }
        long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
        System.out.println("Tiempo funcion1: " + totalTiempo1);
        return totalTiempo1;

    }

    static long funcion2(ArrayList<Integer> vec) {
        
          long tiempoInicio1 = System.currentTimeMillis();
          
        int cont = 0;
        for (int i = 0; i < vec.size(); i++) {
            cont += vec.get(i);
        }
        
            long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
        System.out.println("Tiempo funcion2: " + totalTiempo1);
        return totalTiempo1;

    }
    
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        int tamano=24567977;
///////////////////////
        ArrayList vectoraleatorio = new ArrayList();
       
        for (int i = 0; i < tamano; i++) {
            vectoraleatorio.add((Math.random() < 0.5) ? 0 : 1);

        }
        
        ///////////////////////////////
         ArrayList vectormas0 = new ArrayList();
         
        vectormas0.add(0);
        vectormas0.add(0);
        vectormas0.add(0);
        
        for (int i=0; i<tamano;i++){
            vectormas0.add(1);
        }
        //////////////////////////
        
        
           ArrayList fifty = new ArrayList();
        
           for (int i=0; i<tamano;i++){
               
               if(i%2==0) fifty.add(0);
               else fifty.add(1);
           }
        
        //////
        
        ArrayList vectormas1 = new ArrayList();
         
        vectormas1.add(1);
        vectormas1.add(1);
        vectormas1.add(1);
        
        for (int i=0; i<tamano;i++){
            vectormas1.add(0);
        }
        
        System.out.print("Vector Aleatorio: ");
        funcion1(vectoraleatorio);
        System.out.print("Vector mas 0:       ");
        funcion1(vectormas0);
        System.out.print("Vector mas 1:       ");
        funcion1(vectormas1);
        System.out.print("Vector fifty:       ");
         funcion1(fifty);
        
         System.out.print("\nVector Aleatorio: ");
        funcion2(vectoraleatorio);
         System.out.print("Vector mas 0:      ");
        funcion2(vectormas0);
        System.out.print("Vector mas 1:       ");
        funcion2(vectormas1);
        System.out.print("Vector fifty:       ");
         funcion2(fifty);

     

    }
}
