package ags2;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Practica1_Opt {

    private static int num_elementos = 256;
    private static int max_poblacion = 100;
    private static float tabla_con_funcion[][] = new float[num_elementos][3];
    private static float poblacion[][] = new float[max_poblacion][4];
    private static String binarios_tabla[] = new String[num_elementos];
    private static String binarios_poblacion[] = new String[max_poblacion];
    private static String poblacionesSiguientes[] = new String[max_poblacion];
    public static String XML_total = "";

    public static String convertirABinario2(int a) {

        String que = Integer.toBinaryString(a);
        int cuantos = que.length();

        while (cuantos < 8) {
            que = 0 + que;
            cuantos++;
        }

        return que;

    }

    public static void construirTablaInicial2() {
        int totalNums = num_elementos;
        for (int i = 0; i < totalNums; i++) {
            binarios_tabla[i] = convertirABinario2(i);
            tabla_con_funcion[i][0] = i;
            tabla_con_funcion[i][1] = (float) (i * 0.00390625);
            tabla_con_funcion[i][2] = 36 - (float) Math.pow((float) Math.pow((6 * (float) (i * 0.00390625)) - 3, 2) - 3, 2);
        }
    }

    public static void generarPoblacionInicial() {
        float calificacionTotal = 0;

        for (int i = 0; i < max_poblacion; i++) {
            int temp = (int) (Math.random() * 256);
            binarios_poblacion[i] = convertirABinario2(temp);
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

    /**
     * *********************************************************************
     */
    /**
     * Seleccionamos dos individuos para crear dos nuevos individuos
     */
    public static void cruzar() {

        for (int m = 0; m < poblacionesSiguientes.length; m += 2) {
            double Pc;
            do {
                Pc = Math.random();
            } while (Pc < 0.4);
            double d = Math.random();
            if (d < Pc) {
                //cruza
                int l;
                do {
                    l = (int) (Math.random() * 7);
                } while (l < 2);
                String subStrA = poblacionesSiguientes[m].substring(0, l);
                String subStrB = poblacionesSiguientes[m + 1].substring(l, 8);

                String subStrA2 = poblacionesSiguientes[m].substring(l, 8);
                String subStrB2 = poblacionesSiguientes[m + 1].substring(0, l);

                poblacionesSiguientes[m] = subStrA + subStrB;/*concatenamos*/
                poblacionesSiguientes[m + 1] = subStrA2 + subStrB2;

            }//end if
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
    }

    /**
     * Código de mutación 1
     */
    public static void mutar() {
        int aleatorio = 5;
        for (int i = 0; i < max_poblacion; i++) {
            String cad = "";
            for (int j = 0; j < 8; j++) {
                double q = Math.random() * aleatorio;
                char caracter = poblacionesSiguientes[i].charAt(j);
                if (q < (aleatorio / 2)) {
                    if (caracter == '0') {
                        cad += "1";
                    } else {
                        cad += "0";
                    }
                } else {
                    cad += caracter;
                }
            }
            poblacionesSiguientes[i] = cad;
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

    public static void main(String ar[]) throws IOException {


        long tiempo_promedio = 0;
        int cuantas_iteraciones = 15;
        int num_maximo_iteraciones = -1;
        int poblacion_a_optimizar = 4;
        XML_total += "<?xml version=\"1.0\" ?>\n<resultados>\n";

        for (int i = 0; i < cuantas_iteraciones; i++) {

            XML_total += "   <ag id=\"" + i + "\">\n";
            //String plantilla_aux;
            //plantilla_aux = plantilla1.replace("NUM", String.valueOf(i));

            long tiempoInicio1 = System.currentTimeMillis();

            int x = 0;
            int cont = 0;

            construirTablaInicial2();
            int max = obtenerMayor();

            generarPoblacionInicial();

            while (x <= poblacion_a_optimizar || cont < num_maximo_iteraciones) {
                crearGeneracionSiguiente();


                cruzar();
                mutar();
                x = cuantos_llegan_al_fitness(max, cont);
                //System.out.println("Esta generación tiene x=...." + x);
                if (x > (poblacion_a_optimizar - 1)) {
                    System.out.println("Generacion optima en:--> " + cont+"\n");
                    break;
                }
                cont++;
                //System.out.println("Generacion: " + cont + "->No");
                if (cont == num_maximo_iteraciones) {

                    break;
                }

            }

            long totalTiempo1 = System.currentTimeMillis() - tiempoInicio1;
            System.out.println("Tiempo para " + cont + " veces " + totalTiempo1 + " milisegundos");
            tiempo_promedio += totalTiempo1;

            XML_total += "   </ag>\n";
        }
        XML_total += "</resultados>";
        System.out.println("Tiempo total= " + tiempo_promedio + "milisegundos");
        System.out.println("Tiempo promedio/iteración= " + tiempo_promedio / cuantas_iteraciones + "milisegundos");
// Escribimos el fichero
        escribirXML();
///

    }

    public static void escribirXML() {

        File f;
        f = new File("xml_practica1_Opt.xml");
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
