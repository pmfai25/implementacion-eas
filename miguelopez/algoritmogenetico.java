/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package seleccion;

import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author Miguel
 */
public class Seleccion {

    static ArrayList<Integer> mutar(ArrayList<Integer> vec) {

        ArrayList<Integer> aux = new ArrayList<Integer>();
        aux = vec;
        int cuanto = vec.size();
        int pos = (int) (Math.random() * vec.size());

        int numero = aux.get(pos);

        aux.set(pos, ((numero + 1) % 2));

        return aux;

    }

    static ArrayList<Integer> cruzar(ArrayList<Integer> vec1, ArrayList<Integer> vec2) {

        ArrayList aux1 = new ArrayList();
        ArrayList aux2 = new ArrayList();
        ArrayList hijo = new ArrayList();

        for (int i = 0; i < vec1.size() / 2; i++) {
            aux1.add(vec1.get(i));
        }

        for (int i = vec2.size() / 2; i < vec2.size(); i++) {
            aux2.add(vec2.get(i));
        }

        for (int i = 0; i < aux1.size(); i++) {
            hijo.add(aux1.get(i));
        }

        for (int i = 0; i < aux2.size(); i++) {
            hijo.add(aux2.get(i));
        }

        return hijo;

    }

    public static ArrayList<ArrayList<Integer>> crearPoblacionInicial() {

        ArrayList<ArrayList<Integer>> inicial = new ArrayList<>();

        for (int j = 0; j < 100; j++) {

            ArrayList<Integer> aux = new ArrayList<Integer>();
            for (int i = 0; i < 100; i++) {
                aux.add((Math.random() < 0.5) ? 0 : 1);
            }
            inicial.add(aux);

        }



        return inicial;
    }

    public static ArrayList<Integer> elegirDePoblación(ArrayList<ArrayList<Integer>> inicial) {

        ArrayList<Integer> elegido = new ArrayList<Integer>();

        int aleatorio = (int) (Math.random() * 25 + 1);

        elegido = inicial.get(aleatorio);
        return elegido;

    }

    public static int fitness(ArrayList<Integer> individuo) {
        int cont = 0;
        for (int i = 0; i < individuo.size(); i++) {
            if (individuo.get(i) == 1) {
                cont++;
            }
        }

        return cont;
    }

    public static void comprobarMenores(ArrayList<ArrayList<Integer>> poblacion, ArrayList<Integer> hijo1, ArrayList<Integer> hijo2) {

        int fit1 = fitness(hijo1);
        int fit2 = fitness(hijo2);

        for (int i = 0; i < poblacion.size(); i++) {
            int fit_aux = fitness(poblacion.get(i));

            if (fit_aux < fit1) {
                poblacion.remove(poblacion.get(i));
                poblacion.add(hijo1);
                break;
            }

        }

        for (int i = 0; i < poblacion.size(); i++) {
            int fit_aux = fitness(poblacion.get(i));

            if (fit_aux < fit2) {
                poblacion.remove(poblacion.get(i));
                poblacion.add(hijo2);
                break;
            }

        }

    }

    public static boolean ha_terminado(ArrayList<ArrayList<Integer>> poblacion) {
        boolean que = true;

        for (int i = 0; i < poblacion.size(); i++) {
            for (int j = 0; j < poblacion.get(i).size(); j++) {
                if (poblacion.get(i).get(j) == 0) {
                    que = false;
                }
            }
        }


        return que;

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {




        long tiempoInicio1 = System.currentTimeMillis();


        for (int i = 0; i < 30; i++) {

            ArrayList<ArrayList<Integer>> inicial = crearPoblacionInicial();

            while (!ha_terminado(inicial)) {

                ArrayList<Integer> padre1 = elegirDePoblación(inicial);
                ArrayList<Integer> padre2 = elegirDePoblación(inicial);

                ArrayList<Integer> hijo1 = cruzar(padre1, padre2);
                ArrayList<Integer> hijo2 = cruzar(padre1, padre2);

                hijo1 = mutar(hijo1);
                hijo2 = mutar(hijo2);
                comprobarMenores(inicial, hijo1, hijo2);
             
            }
            
            System.out.println("fin: "+ (i+1));
        }
        long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
        System.out.println("Tiempo 30 veces algoritmo: " + totalTiempo1);

        System.out.println("ele");
    }
}
