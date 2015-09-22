## ¿Cuanto se tarda en ejecutar un algoritmo genético? ##

El problema es que la CPU no se dedica únicamente a su programa

Una buena idea es usar el comando time:

  * Real time (tiempo que tarda): Es interesante sólo cuando se trata de algoritmos paralelos
  * User time (es el importante)
  * System time (tiempo invertido en las llamadas al kernel)

Hasta cuando se ejecuta?

  * Normalmente un número de generaciones
  * En otras, un número de evaluaciones
  * En otras ocasiones, cuando el algoritmo no progresa un número específico de ejecuciones
  * O bien, si encuentra el óptimo (si se conoce)

> Importante: Repetir entre 10 y 30 veces. 30 veces es lo mínimo estadísticamente significativo

> Si se quiere comparar el algoritmo en dos máquinas diferentes,
    * Se compara el número de evaluaciones
    * o el número de evecs que se llega al óptimo

## Resultados ##

Tras implementar el algoritmo subido a GIT, obtengo los siguientes resultados:

  * Number of executions = 100
  * Time per execution: [123, 77, 69, 137, 112, 110, 155, 97, 40, 74, 70, 69, 49, 99, 184, 58, 75, 47, 50, 67, 189, 49, 54, 35, 76, 73, 42, 84, 109, 78, 47, 72, 118, 93, 237, 50, 38, 46, 40, 71, 111, 153, 110, 94, 47, 46, 53, 43, 63, 65, 127, 128, 42, 53, 173, 35, 119, 77, 95, 64, 138, 54, 74, 59, 92, 60, 117, 93, 56, 34, 44, 44, 55, 36, 26, 132, 46, 25, 65, 48, 100, 53, 49, 29, 34, 148, 102, 59, 47, 35, 36, 138, 37, 44, 40, 100, 74, 122, 63, 45, ]
  * Average time : 77 ms
  * Generations per execution: 149, 119, 94, 183, 295, 258, 379, 266, 113, 161, 197, 180, 126, 281, 455, 163, 170, 120, 132, 164, 400, 119, 155, 90, 207, 180, 125, 283, 301, 218, 149, 243, 362, 277, 640, 130, 101, 122, 108, 215, 330, 443, 332, 241, 118, 137, 135, 106, 177, 184, 391, 356, 115, 158, 570, 110, 329, 237, 266, 155, 398, 158, 213, 155, 262, 164, 305, 243, 137, 83, 126, 143, 141, 94, 64, 384, 137, 76, 186, 131, 255, 132, 138, 89, 102, 434, 305, 170, 125, 93, 91, 430, 102, 109, 131, 284, 196, 350, 192, 126,
  * Average generations: 207 generations