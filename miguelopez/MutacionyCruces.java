/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package mutacionycruces;

import java.util.ArrayList;

/**
 *
 * @author Miguel
 */
public class MutacionyCruces {

    static ArrayList<Integer> mutar(ArrayList<Integer> vec) {
        int pos=(int) (Math.random()*vec.size());
        int numero= vec.get(pos);
        
        vec.set(pos, ((numero+1)%2));
      
        return vec;

    }

    static ArrayList<Integer> cruzar(ArrayList<Integer> vec1,ArrayList<Integer> vec2) {
       
        ArrayList aux1= new ArrayList();
        ArrayList aux2= new ArrayList();
        ArrayList hijo= new ArrayList();
        
        for (int i=0; i<vec1.size()/2; i++){
            aux1.add(vec1.get(i));
        }
        
        for (int i=vec2.size()/2; i<vec2.size(); i++){
            aux2.add(vec2.get(i));
        }
        
        hijo.add(aux1);
        hijo.add(aux2);
        
       return hijo;

    }
    
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        int tamano=10;
///////////////////////
        ArrayList vector1 = new ArrayList();
       
        for (int i = 0; i < tamano; i++) {
            vector1.add(0);

        }
        
         System.out.println("\nMutar");
        System.out.println("Vector original: "+ vector1);
        System.out.println("Vector Mutado: " + mutar(vector1));
        
        
        ArrayList Padre = new ArrayList();
         ArrayList Madre = new ArrayList();
         for (int i = 0; i < tamano; i++) {
            Padre.add(0);
             Madre.add(1);

        }

        System.out.println("\nCruzar");
         System.out.println("Vector padre: "+ Padre);
          System.out.println("Vector madre: "+ Madre);
           System.out.println("Vector Hijo: "+ cruzar(Padre,Madre));
     

    }
}
