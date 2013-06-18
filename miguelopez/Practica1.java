package ags2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Practica1 {

    private static int num_elementos = 256;
    private static int max_poblacion = 100;
    private static float tabla_con_funcion[][] = new float[num_elementos][3];
    private static float poblacion[][] = new float[max_poblacion][4];
    private static String binarios_tabla[] = new String[num_elementos];
    private static String binarios_poblacion[] = new String[max_poblacion];
    private static String poblacionesSiguientes[] = new String[max_poblacion];
    public static String XML_total = "";

    public static String convertirABinario(int a) {
        int i = 0;

        int bin[] = new int[8];
        while (a >= 1) {
            if ((a % 2) == 0) {
                bin[i] = 0;
            } else {
                bin[i] = 1;
            }
            a = a / 2;
            i++;
        }
        int k = bin.length - 1;
        String cad = "";
        while (k >= 0) {
            cad += bin[k];
            k--;
        }
        int lon = cad.length();
        String cad2 = "";
        for (int l = 1; l <= 7 - lon; l++) {
            cad2 += "0";
        }
        cad2 += cad;
        return cad2;

    }

    /**
     * aki evaluaremos nuestra función a utilizar en este caso fue:
     * 36-((6*x-3)^2-3)^2
     */
    public static void construirTablaInicial() {
        int totalNums = num_elementos;
        for (int i = 0; i < totalNums; i++) {
            tabla_con_funcion[i][0] = i;
            binarios_tabla[i] = convertirABinario(i);
            float aux = (float) (i * 0.00390625);
            tabla_con_funcion[i][1] = aux;
            float aux11 = (float) (i * 0.00390625);
            float aux1 = (6 * aux11) - 3;
            float pot = (float) aux1 * aux1;
            float aux2 = pot - 3;
            float pot2 = (float) aux2 * aux2;
            float aux3 = 36 - pot2;
            tabla_con_funcion[i][2] = aux3;
        }
    }

    public static void generarPoblacionInicial() {
        float calificacionTotal = 0;

        for (int i = 0; i < max_poblacion; i++) {
            int temp = (int) (Math.random() * 256);
            binarios_poblacion[i] = convertirABinario(temp);
            poblacion[i][0] = temp;
            poblacion[i][1] = tabla_con_funcion[temp][1];//asignamos calificación
            calificacionTotal = calificacionTotal + poblacion[i][1];
            poblacion[i][3] = calificacionTotal;
        }

        for (int j = 0; j < max_poblacion; j++) {
            float probabilidadSeleccion = poblacion[j][1] / calificacionTotal;
            poblacion[j][2] = probabilidadSeleccion;
        }
    }

    public static void cruzar() {

        for (int m = 0; m < poblacionesSiguientes.length; m += 2) {


            String subStrA = poblacionesSiguientes[m].substring(0, 4);
            String subStrB = poblacionesSiguientes[m + 1].substring(4, 8);

            String subStrA2 = poblacionesSiguientes[m].substring(4, 8);
            String subStrB2 = poblacionesSiguientes[m + 1].substring(0, 4);

            poblacionesSiguientes[m] = subStrA + subStrB;/*concatenamos*/
            poblacionesSiguientes[m + 1] = subStrA2 + subStrB2;

            //else System.out.println("es mayor");
        }//end for
    }

    /**
     * Ahora creamos la siguiente Generación eligiendo a los mejores (comparados
     * con el valor de la funcion del ultimo)
     */
    public static void crearGeneracionSiguiente() {
        int k = 0;
        while (k < max_poblacion) {
            double valor_maxi_aux = poblacion[99][3] * Math.random() * 2;
            float calificacion = 0;
            int i = 0;
            boolean parar = true;
            while (parar) {
                calificacion = calificacion + poblacion[i][1];
                if (calificacion > valor_maxi_aux) {
                    poblacionesSiguientes[k] = binarios_poblacion[i];
                    parar = false;
                } else {
                    i++;
                }
                if (i == 99) {
                    i = 0;
                }
            }
            k++;
        }

        //for (int i=0; i<poblacionesSiguientes.length; i++){
        //System.out.println(poblacionesSiguientes[i]);
        //}
        //System.out.println("");
    }

    private static int calcularFitness(String individuo, String max) {
        int cont = 0;

        for (int i = 0; i < 8; i++) {
            if (individuo.charAt(i) == max.charAt(i)) {
                cont++;
            }
        }

        return cont;
    }

    /**
     * Código de mutación 1
     */
    public static void mutar(String max) {
        int max_cuantos_llegan_al_fitness = 7;
        int cuantos_llegan_al_fitness = 0;
        for (int i = 0; i < max_poblacion; i++) {
            String individuo = poblacionesSiguientes[i];
            cuantos_llegan_al_fitness = calcularFitness(individuo, max);
            if (cuantos_llegan_al_fitness < max_cuantos_llegan_al_fitness) {
                String nuevo_individuo = "";
                if (individuo.charAt(3) == '0') {
                    nuevo_individuo = individuo.substring(0, 3) + "1" + individuo.substring(4);
                } else {
                    nuevo_individuo = individuo.substring(0, 3) + "0" + individuo.substring(4);
                }
                poblacionesSiguientes[i] = nuevo_individuo;
            }
        }
    }

    /**
     * Obtenemos cual es nuestro punto máximo en nuestra función
     */
    public static int obtenerMayor() {
        float x = 0;
        int pos = 0;
        for (int i = 0; i < num_elementos; i++) {
            if (tabla_con_funcion[i][2] > x) {
                x = tabla_con_funcion[i][2];
                pos = i;
            }
        }
        System.out.println("El maximo de nuestra funcion esta en la pos: " + tabla_con_funcion[pos][0]);
        return pos;
    }

    /**
     * Evalua la población y nos dice cuantos individuos son iguales que el
     * mayor. (Cuanto más mejor, y si lleva al numero que buscamos, hemos
     * terminado)
     */
    public static int cuantos_llegan_al_fitness(int max, int generacion) {
        String optimo = binarios_tabla[max];
        int encontrados = 0;

        for (int i = 0; i < max_poblacion; i++) {
            if (poblacionesSiguientes[i].equalsIgnoreCase(optimo)) {
                if (encontrados == 0) {
                    XML_total += "      <gen n=\"" + generacion + "\">\n";
                }
                String aux = poblacionesSiguientes[i];
                XML_total += "         <individuo id=\"" + i + "\">\n";
                XML_total += "            " + aux + "\n";
                XML_total += "         </individuo>\n";

                encontrados++;
            }
        }
        if (encontrados > 0) {
            XML_total += "      </gen>\n";
        }
        return encontrados;
    }

    public static void main(String ar[]) {


        long tiempo_promedio = 0;
        int cuantas_iteraciones = 15;
        int num_maximo_iteraciones = -1;
        int poblacion_a_optimizar = 4;
        XML_total += "<?xml version=\"1.0\" ?>\n<resultados>\n";

        for (int i = 0; i < cuantas_iteraciones; i++) {
            long tiempoInicio1 = System.currentTimeMillis();
            XML_total += "   <ag id=\"" + i + "\">\n";


            int x = 0;
            int cont = 0;

            construirTablaInicial();
            int max = obtenerMayor();

            generarPoblacionInicial();

            while (x <= poblacion_a_optimizar || cont < num_maximo_iteraciones) {
                crearGeneracionSiguiente();
                //cruzar(convertirABinario(max));
                cruzar();
                mutar(convertirABinario(max));
                x = cuantos_llegan_al_fitness(max, cont);

                if (x > (poblacion_a_optimizar - 1)) {
                    System.out.println("Generacion optima en:--> " + cont);
                    break;
                }
                cont++;
                if (cont == num_maximo_iteraciones) {
                    System.out.println("\nNo encontrada población que optimize la funcion en: " + poblacion_a_optimizar + " individuos");
                    break;
                }
            }

            long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
            System.out.println("Tiempo para " + cont + " veces " + totalTiempo1 + " milisegundos\n");
            tiempo_promedio += totalTiempo1;
            XML_total += "   </ag>\n";

        }
        XML_total += "</resultados>";
        System.out.println("Tiempo total= " + tiempo_promedio + "milisegundos");
        System.out.println("Tiempo promedio/iteración= " + tiempo_promedio / cuantas_iteraciones + "milisegundos");

        escribirXML();

    }

    public static void escribirXML() {

        File f;
        f = new File("xml_practica1.xml");
        try {
            FileWriter w = new FileWriter(f);
            BufferedWriter bw = new BufferedWriter(w);
            PrintWriter wr = new PrintWriter(bw);
            wr.write(XML_total);//escribimos en el archivo
            wr.close();
            bw.close();
        } catch (IOException e) {
        };
    }
}
