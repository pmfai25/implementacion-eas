# Apuntes de Clase #

## Día 11/04/2012 ##

### Primera Parte ###

  * Hablamos sobre **que** es software libre y sus **ventajas**.
  * También sobre el problema y la multa que ha sufrido la universidad por no usar software libre
  * Con el software libre podemos ver el código fuente, para cuando lo necesitemos
  * Tenemos libertad de uso para **modificar** el código.
  * Podemos **copiarlo**, reutilizarlo, dárselo a nuestros amigos, etc...
  * Hemos estado hablando de como las empresas pueden sacar dinero a partir de software libre: Personalización, adecuacion de base de datos, uso, software in house (haces software para un banco, por ejemplo), soporte técnico.
  * El software libre **no** es gratis, ya que aunque el software sea libre, hay que pagar a los informáticos para que lo hagan, por lo que libre no es gratis.
  * Hemos visto las **10 principales características** de usar software libre.
  * Hablamos sobre un parser que creó la UGR, y vemos en un articulo y sobre un cerebro artifical para robots.
  * Hablamos sobre los distintos tipos de licencias que hay, con sus limitaciones y ventajas. Para obtener una licencia podemos ir a www.openfoundry.org
  * Para licenciar un proyecto, tienes que tener un fichero de texto que te descargas de la web de tu licencia y meterla dentro de tu proyecto, y ademas crear un fichero de copyright.

### Segunda Parte ###

  * Empezamos a hablar sobre que es GIT (sirve para trabajar en grupo).
  * Git permite historicos
  * Nos ha pedido que nos descarguemos git desde http://git-scm.com/download
  * Primero creamos el repositorio con este comando:
git clone https://code.google.com/p/implementacion-eas
  * Una vez clonado en nuestra maquina el proyecto:
> Creamos una carpeta y un archivo con la orden:
> mkdir minombreusuario, cd minombredeusuario; git add nuevofichero.txt

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
