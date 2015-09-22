# Introduction #

Apuntes del primer dia 11/04/2013

# Contenido #

## Libertades del software libre ##

  1. Libertad de ejecutar
  1. Libertad de estudiar
  1. Libertad de copiar
  1. Libertad de mejorar

## las 10 principales características de usar software libre ##

  1. El software libre implica independencia tecnológica.
  1. El software libre es un vehículo de transmisión de conocimiento.
  1. La ciencia no lo es si no es reproducible: liberar el software permite a cualquiera obtener los mismos resultados.
  1. Fomenta buenas prácticas en el desarrollo de software.
  1. Crea comunidad alrededor de un grupo, y aumenta el interés en la ciencia.
  1. Acerca la ciencia al público, a la sociedad, y mejora la percepción de la universidad.
  1. Hace público y patente para empresas y otros grupos el conocimiento y experiencia de los autores.
  1. Crea otro canal para la difusión de la investigación y el trabajo propios.
  1. Devuelve a la sociedad lo que la sociedad ha invertido en la creación del software.
  1. Fomenta la colaboración interdisciplinar.
  1. Aumenta la calidad de la investigación o proyecto resultante, al posibilitar la colaboración espontánea (y altruista).

  * cómo liberar software.

  1. Poner de acuerdo a las partes relacionadas.
  1. Elegir una licencia (GPL, EUPL, MIT, Academic Free License, Apache BSD,...)
  1. Solicitar la liberación a la UGR.
  1. Publicar los fuentes.
  1. Usar una forja para continuar el desarrollo y atraer comunidad.

> ## Git ##

**Empezamos a hablar sobre que es GIT (sirve para trabajar en grupo).
  * Git permite historicos
  * Nos ha pedido que nos descarguemos git desde http://git-scm.com/download
  * Primero creamos el repositorio con este comando:
git clone https://code.google.com/p/implementacion-eas
  * Una vez clonado en nuestra maquina el proyecto:
> Creamos una carpeta y un archivo con la orden:
> mkdir minombreusuario, cd minombredeusuario; git add nuevofichero.txt**

Ahora hacemos el commit con git commit -a -m "Esto es un cambio" y nos salta un aviso para configurar el correo.

Esto lo hacemos con "git config --global user.email miguel.euroinnova@gmail.com" y
git config --global user.name "Miguel"

ahora si podemos hacer el commit

Luego con git push origin master empujamos los cambios: ahora nos pedirá una contraseña, que no es la clave de gmail, sino una generada que tenemos que obtener.

Lo he intentado hacer desde windows y hemos tenido problemas:
Investigando por internet, he descubierto la solucion, que es la siguiente:

  1. Ejecuta el CMD  (windows + R)
  1. escribe set HOME=%HOMEPATH% y presiona enter para que cree la variable de entorno.
  1. Crea un archivo llamado _netrc (en windows es_ y en linux .), y ahí escribes: machine code.google.com login yourEmail@gmail.com password

Ahora ya no te pedirá mas el pass




Apuntes del segondo dia 18/04/2013

# Contenido #