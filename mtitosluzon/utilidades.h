/**
 * @file utilidades.h Fichero que contiene todas las utilidades necesarias para la práctica comunes a los métodos:
 *   operaciones de números aleatorios, 
 *   imprimir los resultados en un fichero, 
 *   método K-NN
 *   ...
 * @author Manuel Marcelino Titos Luzón
*/

#ifndef __utilidades_h__
#define __utilidades_h__

#include<vector>
#include<set>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<string.h>
using namespace std;

//habia 20000 evaluaciones

#define K 3
#define N_SEMILLAS 5
#define EVALUACIONES 4000
#define POBLACIONGENETICOS 50
#define PROBABLIDADMUTARGENERACIONAL 0.1
#define PROBABILIDADCRUCEGENERACIONAL 1
#define PROBABLIDADMUTARESTACIONARIO 0.1
#define PROBABILIDADCRUCEESTACIONARIO 0.7

double semillas[N_SEMILLAS] = {12345678, 23456781, 34567812, 45678123, 56781234};

// ******************** Funciones para la generación de los números aleatorios ********************

unsigned long Seed = 0L;

#define MASK 2147483647
#define PRIME 65539
#define SCALE 0.4656612875e-9

/**
 * @brief Inicializa la semilla al valor x
 * @param x Valor de la semilla
 * 
 * Inicializa la semilla a un valor, sólo debe llamarse a esta funcion una vez en todo el programa
*/
void Set_random (unsigned long x)
{
    Seed = (unsigned long) x;
}

/**
 * @brief Devuelve el valor actual de la semilla
 * @return Valor de la semilla
 * 
 * Devuelve la semilla
*/
unsigned long Get_random ()
{
    return Seed;
}

/**
 * @brief Genera un número aleatorio real en el intervalo [0,1[ (incluyendo el 0 pero sin incluir el 1)
 * @return Número aleatorio
*/
double Rand()
{
    return (( Seed = ( (Seed * PRIME) & MASK) ) * SCALE );
}

/**
 * @brief Genera un número aleatorio en {low,...,high}
 * @param low Límite inferior
 * @param high Límite superior
 * @return Número aleatorio
 * 
 * Genera un número aleatorio entero en {low,...,high}
*/
int Randint(int low, int high)
{
    return (int) (low + (high-(low)+1) * Rand());
}

/**
 * @brief Genera un número aleatorio real en el intervalo [low,...,high[ (incluyendo 'low' pero sin incluir 'high')
 * @param low Límite inferior
 * @param high Límite superior
 * @return Número aleatorio
 * 
 * Genera un número aleatorio en coma flotante en {low,...,high}
*/
float Randfloat(float low, float high)
{
    return (low + (high-(low))*Rand());
}

// ************************************************************************************************

/**
 * @brief Genera una solución aleatoria para el problema
 * @param tamasolucion Tamaño de la solución
 * @see Randint
 * @return Vector que contiene la solución
 * 
 * Genera una solución aleatoria para el problema
*/
vector<bool> generarSolucionAleatoria(unsigned int tamasolucion)
{
	vector<bool> solucionaleatoria;
	
	for(unsigned int i = 0; i < tamasolucion; i++)
		solucionaleatoria.push_back(Randint(0, 1));
	
	return solucionaleatoria;
}

// ******************** Funciones para el clasificador K-NN ********************

/**
 * @brief Calcula la distancia euclídea de dos filas
 * @param atributos Atributos para comparar
 * @param vectordato Vector base
 * @param vectoracomparar Vector para comparar
 * @return Distancia euclídea de las dos filas
 * 
 * Calcula y devuelve la distancia euclídea de las dos filas con los atributos especificados
 * La fórmula de la distancia euclídea es: 
*/
double distanciaEuclidea(vector<bool> &atributos, vector<double> &vectordato, vector<double> &vectoracomparar)
{
	double suma = 0.0;
	
	for(unsigned int i = 0; i < atributos.size(); i++)
		if( atributos[i] )
			suma += ((vectordato[i]-vectoracomparar[i])*(vectordato[i]-vectoracomparar[i]));
		
	return sqrt(suma);
}

/**
 * @brief Calcula los k mejores elementos de un vector de distancias euclídeas
 * @param k Número de mejores elementos a encontrar, esta K es la misma que la del clasificador KNN
 * @param distanciaseuclideas Vector de las distancias euclídeas
 * @param clases Vector de las clases de las distancias euclídeas
 * @return Cojunto de los k mejores elementos
 * 
 * Calcula los k mejores elementos de un conjunto de distancias euclídeas y lo devuelve con el siguiente formato:
 * { [distanciaeuclidea, clase], ..... }
*/
vector<pair<double, string> > kmejores(unsigned int k, vector<double> &distanciaseuclideas, vector<string> &clases)
{	
	vector<pair<double, string> > mejores;
	set<int> posicioneselegidas;
	pair<double, string> aux;
	int posicionmejor = 0;
	
	while( mejores.size() < k )
	{
		double mejor = distanciaseuclideas[0];
		string clasemejor = clases[0];
		for(unsigned int i = 1; i < distanciaseuclideas.size(); i++)
			if( distanciaseuclideas[i] < mejor && posicioneselegidas.find(i) == posicioneselegidas.end() )
			{
				mejor = distanciaseuclideas[i];
				clasemejor = clases[i];
				posicionmejor = i;
			}
		aux.first = mejor;
		aux.second = clasemejor;
		mejores.push_back(aux);
		posicioneselegidas.insert(posicionmejor);
	}
	
	return mejores;
}

/**
 * @brief Calcula la clase que mas se repite en un cojunto de instancias
 * @param mejoresInstancias Instancias de la siguiente forma: first = distanciaeuclidea, second = clase
 * @param clases Todas las clases
 * @return Clase que mas se repite
 * 
 * Calcula la clase que mas se repite en un cojunto de instancias y la devuelve
 * La clase que mas se repite será la clase que buscamos en el clasificador KNN 
*/
string clasePredominante(vector<pair<double, string> > &mejoresInstancias, vector<string> &clases)
{
	string mejorclase;
	vector<pair<string, double> > clasesconfrecuencia, clasespredominantes;
	set<string> clasessinrepetir;
	
	// Como aquí tengo el vector con las clases de las columnas las meto en un conjunto y así obtengo las clases en general sin repetir
	for(unsigned int i = 0; i < clases.size(); i++)
		clasessinrepetir.insert(clases[i]);
	
	for(set<string>::iterator i = clasessinrepetir.begin(); i != clasessinrepetir.end(); i++) // relleno el vector de las clases con una frecuencia igual a 0
	{
		pair<string, double> aux;
		aux.first = *i;
		aux.second = 0;
		clasesconfrecuencia.push_back(aux);
	}

	for(unsigned int i = 0; i < clasesconfrecuencia.size(); i++) // relleno las frecuencias de las clases que han aparecido en las mejores
		for(unsigned int j = 0; j < mejoresInstancias.size(); j++)
			if( clasesconfrecuencia[i].first == mejoresInstancias[j].second )
				clasesconfrecuencia[i].second++;
	
	double frecuencia = clasesconfrecuencia[0].second;
	mejorclase = clasesconfrecuencia[0].first;
	for(unsigned int i = 1; i < clasesconfrecuencia.size(); i++) // busco la que mas se repite que se supone que es la del elemento
		if( clasesconfrecuencia[i].second > frecuencia )
		{
			frecuencia = clasesconfrecuencia[i].second;
			mejorclase = clasesconfrecuencia[i].first;
		}
	
	return mejorclase;
}

/**
 * @brief Clasificador KNN
 * @param k Valor de la k del clasificador, si k = 3 el clasificador será un 3NN
 * @param tipo Indica si es ENTRENAMIENTO o TEST
 * @param posicion Posición de la fila en caso de que sea modo entrenamiento
 * @param datos Matriz de datos
 * @param atributos Vector de 0 y 1 que indican los atributos elegidos
 * @param vectoraprobar Instancia a la que le vamos a pasar el clasficador KNN
 * @param clases Vector donde se encuentran las clases de los atributos
 * @see distanciaEuclidea
 * @see kmejores
 * @see clasePredominante
 * @return Clase a la que el clasificador estima que pertenece el vector
 * 
 * Clasificador general KNN que estima la clase a la que pertenece la instancia dada sobre el conjunto de datos dado también 
*/
string clasificadorKNN(unsigned int k, string tipo, unsigned int posicion, vector<vector<double> > &datos, vector<bool> &atributos, vector<double> &vectoraprobar, vector<string> &clases)
{
	vector<double> distancias;
	
	if( tipo == "ENTRENAMIENTO" )
	{
		for(unsigned int i = 0; i < datos.size(); i++)
			if( i != posicion ) // con esto aplico el método de dejar uno fuera
				distancias.push_back(distanciaEuclidea(atributos, datos[i], vectoraprobar));
	}
	else
	{
		for(unsigned int i = 0; i < datos.size(); i++)
			distancias.push_back(distanciaEuclidea(atributos, datos[i], vectoraprobar));
	}
	
	vector<pair<double, string> > mejores = kmejores(k, distancias, clases); // calculo las k mejores, en este caso las 3 mejores
	
	return clasePredominante(mejores, clases); // saco la clase que mas se repite, que supuestamente es la clase de la instancia
}

// *****************************************************************************

/**
 * @brief Calcula el porcentaje de aciertos de un conjunto de atributos
 * @param tipo Indica si es ENTRENAMIENTO o TEST
 * @param datosentrenamiento Matriz de datos de entrenamiento
 * @param datostest Matriz de datos de test
 * @param atributos Atributos elegidos
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * @see clasificadorKNN
 * @return Porcentaje de aciertos
 * 
 * Calcula el porcentaje de aciertos que tienen los atributos pasados sobre el conjunto de datos 
*/
double porcentajeAciertos(string tipo, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<bool> &atributos, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	double aciertos = 0.0;
	double media;
	
	if( tipo == "ENTRENAMIENTO" )
	{
		for(unsigned int i = 0; i < datosentrenamiento.size(); i++)
			if( clasificadorKNN(K, tipo, i, datosentrenamiento, atributos, datosentrenamiento[i], clasesentrenamiento) == clasesentrenamiento[i] )
				aciertos++;
		media = 100*(aciertos/datosentrenamiento.size());
	}
	else
	{
		for(unsigned int i = 0; i < datostest.size(); i++)
			if( clasificadorKNN(K, tipo, i, datosentrenamiento, atributos, datostest[i], clasesentrenamiento) == clasestest[i] )
				aciertos++;
		media = 100*(aciertos/datostest.size());
	}
	
	return media;
}

/**
 * @brief Calcula el porcentaje de reducción de atributos de un vector
 * @param nuevo Vector de atributos
 * @return Porcentaje de reducción de atributos
 * 
 * Calcula el porcentaje de reducción de atributos de 'nuevo' sobre un vector con todos los atributos seleccionados
*/
double calcularReduccion(const vector<bool> &nuevo)
{
	double atributos = 0;
	
	for(unsigned int i = 0; i < nuevo.size(); i++)
		if( nuevo[i] )
			atributos++;
	
	return 100-((atributos/nuevo.size())*100);
}

// ******************** Funciones para tratamiento de ficheros ********************

/**
 * @brief Carga los datos y las clases
 * @param fichero Fichero de donde se van a cargar los datos
 * @param datos Matriz donde se van a guardar los datos
 * @param clasesdatos Vector donde se van a guardar las clases de los datos
 * 
 * Carga los datos y las clases desde un fichero que ya debe estar normalizado previamente
*/
void cargarDatosFichero(const char* fichero, vector<vector<double> > &datos, vector<string> &clasesdatos)
{
	ifstream ficheroentrada(fichero);
	if( ficheroentrada )
	{
		int numeroatributos, totalfilas;
		vector<double> fila;
		string basura, clase;
		double datoleido;
		if( strcmp(fichero, "bd/normalizada/ozone.tra") == 0 )
			{
				numeroatributos = 73;
				totalfilas = 148;
			}
			else
				if( strcmp(fichero, "bd/normalizada/ozone.tst") == 0 )
				{
					numeroatributos = 73;
					totalfilas = 37;
				} 
				else
					if( strcmp(fichero, "bd/normalizada/sonar.tra") == 0 )
					{
						numeroatributos = 61;
						totalfilas = 165;
					}
					else
						if( strcmp(fichero, "bd/normalizada/sonar.tst") == 0 )
						{
							numeroatributos = 61;
							totalfilas = 41;
						}
						else
							if( strcmp(fichero, "bd/normalizada/spambase.tra") == 0 )
							{
								numeroatributos = 58;
								totalfilas = 368;
							}
							else
								if( strcmp(fichero, "bd/normalizada/spambase.tst") == 0 )
								{
									numeroatributos = 58;
									totalfilas = 91;
								}
		// ***** Leo los datos *****
		for(int filasleidas = 0; filasleidas < totalfilas; filasleidas++)
		{
			for(int j = 0; j < numeroatributos; j++)
			{
				if( j < numeroatributos-1 ) // Leo un dato
				{
					ficheroentrada >> datoleido; // Leo el dato
					ficheroentrada >> basura; // Leo la coma
					fila.push_back(datoleido);
				}
				else // Leo una clase
				{
					ficheroentrada >> clase;
					clasesdatos.push_back(clase);
				}
			}
			datos.push_back(fila);
			fila.clear();
		}
		// *************************
	}
	else
		cerr << "\tError abriendo el fichero '" << ficheroentrada << "' ." << endl;
	ficheroentrada.close();
}

/**
 * @brief Guarda los datos obtenidos en un fichero
 * @param bd Base de datos que se está tratando
 * @param fichero Fichero para guardar los datos
 * @param porcentajesentrenamiento Vector con los mejores porcentajes de entrenamiento
 * @param porcentajestest Vector con los mejores porcentajes de test
 * @param reduccionatributos Vector con las reducciones de los atributos
 * 
 * Guarda en un fichero los mejores datos de porcentajes de entrenamiento y test y las reducciones de los atributos de cada semilla.
 * Para cada semilla guardará el mejor % de reducción de atributos, el mejor % de entrenamiento y el mejor % de test, luego mostrará
 * el mejor, la media, el peor y la desviación típica de los datos de cada semilla.
*/
void guardarResultadosFichero(const char* bd, const char* fichero, const vector<double> &porcentajesentrenamiento, const vector<double> &porcentajestest, const vector<double> &reduccionatributos, const vector <vector<bool> > &solucion)
{	
	ofstream ficheroresultados(fichero, ios::app);
	if( ficheroresultados )
	{
		double mejorPorEnt = porcentajesentrenamiento[0], peorPorEnt = porcentajesentrenamiento[0], sumaPorEnt = 0, mediaPorEnt, desvTipPorEnt = 0;
		double mejorPorTes = porcentajestest[0], peorPorTes = porcentajestest[0], sumaPorTes = 0, mediaPorTes, desvTipPorTes = 0;
		double mejorRed = reduccionatributos[0], peorRed = reduccionatributos[0], sumaRed = 0, mediaRed, desvTipRed = 0;
		
		ficheroresultados << bd << endl;
		for(unsigned int i = 0; i < porcentajesentrenamiento.size(); i++)
		{
			ficheroresultados << "Semilla " << i << " (reduccion, entrenamiento, test): \t\t" << reduccionatributos[i] << "\t\t" << porcentajesentrenamiento[i] << "\t\t" << porcentajestest[i] << endl;

			ficheroresultados <<"Solucion: "<<endl;
			for(unsigned int j=0;j<solucion[i].size();j++){
				ficheroresultados << solucion[i][j];
			}
			ficheroresultados << endl;
			if( reduccionatributos[i] > mejorRed )
				mejorRed = reduccionatributos[i];
			if( reduccionatributos[i] < peorRed )
				peorRed = reduccionatributos[i];
			if( porcentajesentrenamiento[i] > mejorPorEnt )
				mejorPorEnt = porcentajesentrenamiento[i];
			if( porcentajesentrenamiento[i] < peorPorEnt )
				peorPorEnt = porcentajesentrenamiento[i];
			if( porcentajestest[i] > mejorPorTes )
				mejorPorTes = porcentajestest[i];
			if( porcentajestest[i] < peorPorTes )
				peorPorTes = porcentajestest[i];
			sumaPorEnt += porcentajesentrenamiento[i];
			sumaPorTes += porcentajestest[i];
			sumaRed += reduccionatributos[i];
		}
		mediaRed = sumaRed/reduccionatributos.size();
		mediaPorEnt = sumaPorEnt/porcentajesentrenamiento.size();
		mediaPorTes = sumaPorTes/porcentajestest.size();
		ficheroresultados << endl;
		ficheroresultados << "Mejores (reduccion, entrenamiento, test): \t\t" << mejorRed << "\t\t" << mejorPorEnt << "\t\t" << mejorPorTes << endl;
		ficheroresultados << "Medias (reduccion, entrenamiento, test): \t\t" << mediaRed << "\t\t" << mediaPorEnt << "\t\t" << mediaPorTes << endl;
		ficheroresultados << "Peores (reduccion, entrenamiento, test): \t\t" << peorRed << "\t\t" << peorPorEnt << "\t\t" << peorPorTes << endl;
		
		for(unsigned int i = 0; i < porcentajesentrenamiento.size(); i++)
		{
			desvTipRed += ((reduccionatributos[i]-mediaRed)*(reduccionatributos[i]-mediaRed));
			desvTipPorEnt += ((porcentajesentrenamiento[i]-mediaPorEnt)*(porcentajesentrenamiento[i]-mediaPorEnt));
			desvTipPorTes += ((porcentajestest[i]-mediaPorTes)*(porcentajestest[i]-mediaPorTes));
		}
		desvTipRed /= reduccionatributos.size();
		desvTipPorEnt /= porcentajesentrenamiento.size();
		desvTipPorTes /= porcentajestest.size();
		
		ficheroresultados << "Desv. Tip. (reduccion, entrenamiento, test): \t\t" << sqrt(desvTipRed) << "\t\t" << sqrt(desvTipPorEnt) << "\t\t" << sqrt(desvTipPorTes) << endl;
		ficheroresultados << endl;
		
	}
	else
		cerr << "Error creando el fichero '" << fichero << "' ." << endl;
	ficheroresultados.close();
}


/**
 * @brief Guarda los datos obtenidos en un fichero estructura
 * @param bd Base de datos que se está tratando
 * @param fichero Fichero para guardar los datos
 * @param porcentajesentrenamiento Vector con los mejores porcentajes de entrenamiento
 * @param porcentajestest Vector con los mejores porcentajes de test
 * @param reduccionatributos Vector con las reducciones de los atributos
 * 
 * Guarda en un fichero estructurado los mejores datos de porcentajes de entrenamiento y test y las reducciones de los atributos de     *cada semilla. Para cada semilla guardará el mejor % de reducción de atributos, el mejor % de entrenamiento y el mejor % de test, luego mostrará el mejor, la media, el peor y la desviación típica de los datos de cada semilla.
*/
void guardarResultadosFicheroEstructurado(const char* bd, const char* fichero, const vector<double> &porcentajesentrenamiento, const vector<double> &porcentajestest, const vector<double> &reduccionatributos, const vector <vector<bool> > &solucion)
{	
	ofstream ficheroresultados(fichero, ios::app);
	if( ficheroresultados )
	{
		double mejorPorEnt = porcentajesentrenamiento[0], peorPorEnt = porcentajesentrenamiento[0], sumaPorEnt = 0, mediaPorEnt, desvTipPorEnt = 0;
		double mejorPorTes = porcentajestest[0], peorPorTes = porcentajestest[0], sumaPorTes = 0, mediaPorTes, desvTipPorTes = 0;
		double mejorRed = reduccionatributos[0], peorRed = reduccionatributos[0], sumaRed = 0, mediaRed, desvTipRed = 0;
		ficheroresultados << "BaseDatos,Semilla,Reducción,Entrenamiento,Test,Solución" << endl;
		//ficheroresultados << bd << endl;
		for(unsigned int i = 0; i < porcentajesentrenamiento.size(); i++)
		{
			ficheroresultados << bd << "," << i << ","<< reduccionatributos[i]<< ","<< porcentajesentrenamiento[i] << "," << porcentajestest[i] << ",";

			//ficheroresultados <<"Solucion: "<<endl;
			for(unsigned int j=0;j<solucion[i].size();j++){
				ficheroresultados << solucion[i][j];
			}
			ficheroresultados << endl;
			if( reduccionatributos[i] > mejorRed )
				mejorRed = reduccionatributos[i];
			if( reduccionatributos[i] < peorRed )
				peorRed = reduccionatributos[i];
			if( porcentajesentrenamiento[i] > mejorPorEnt )
				mejorPorEnt = porcentajesentrenamiento[i];
			if( porcentajesentrenamiento[i] < peorPorEnt )
				peorPorEnt = porcentajesentrenamiento[i];
			if( porcentajestest[i] > mejorPorTes )
				mejorPorTes = porcentajestest[i];
			if( porcentajestest[i] < peorPorTes )
				peorPorTes = porcentajestest[i];
			sumaPorEnt += porcentajesentrenamiento[i];
			sumaPorTes += porcentajestest[i];
			sumaRed += reduccionatributos[i];
		}
		mediaRed = sumaRed/reduccionatributos.size();
		mediaPorEnt = sumaPorEnt/porcentajesentrenamiento.size();
		mediaPorTes = sumaPorTes/porcentajestest.size();
		//ficheroresultados << endl;
		//ficheroresultados << "Mejores (reduccion, entrenamiento, test): \t\t" << mejorRed << "\t\t" << mejorPorEnt << "\t\t" << mejorPorTes << endl;
		//ficheroresultados << "Medias (reduccion, entrenamiento, test): \t\t" << mediaRed << "\t\t" << mediaPorEnt << "\t\t" << mediaPorTes << endl;
		//ficheroresultados << "Peores (reduccion, entrenamiento, test): \t\t" << peorRed << "\t\t" << peorPorEnt << "\t\t" << peorPorTes << endl;
		
		for(unsigned int i = 0; i < porcentajesentrenamiento.size(); i++)
		{
			desvTipRed += ((reduccionatributos[i]-mediaRed)*(reduccionatributos[i]-mediaRed));
			desvTipPorEnt += ((porcentajesentrenamiento[i]-mediaPorEnt)*(porcentajesentrenamiento[i]-mediaPorEnt));
			desvTipPorTes += ((porcentajestest[i]-mediaPorTes)*(porcentajestest[i]-mediaPorTes));
		}
		desvTipRed /= reduccionatributos.size();
		desvTipPorEnt /= porcentajesentrenamiento.size();
		desvTipPorTes /= porcentajestest.size();
		
		//ficheroresultados << "Desv. Tip. (reduccion, entrenamiento, test): \t\t" << sqrt(desvTipRed) << "\t\t" << sqrt(desvTipPorEnt) << "\t\t" << sqrt(desvTipPorTes) << endl;
		//ficheroresultados << endl;
		
	}
	else
		cerr << "Error creando el fichero '" << fichero << "' ." << endl;
	ficheroresultados.close();
}

/**
 * @brief Guarda los datos obtenidos en un fichero estructurado
 * @param bd Base de datos que se está tratando
 * @param fichero Fichero para guardar los datos
 * @param selecciones_generacionales Vector que almacena los individuos seleccionados para cruzar en cada iteración
 * 
 * Guarda en un fichero estructurado los mejores datos cromosomas seleccionados en cada iteracion para el cruce
*/

void guardarResultadosFicheroEstructuradoSelecciones(const char* bd, const char* fichero, const vector <pair<pair<vector<bool>, double>,pair<vector<bool>,double> > >&soluciones_seleccionadas,const vector <pair<int,int> >&generaciones)
{	
	ofstream ficheroresultados(fichero, ios::app);
	if( ficheroresultados )
	{
		if(generaciones.size()!=soluciones_seleccionadas.size()) ficheroresultados << "Los size difieren"<< endl;		
		ficheroresultados << "Semilla,BaseDatos,Generacion,individuo,fitness" << endl;
		for (int i=0;i< soluciones_seleccionadas.size(); i++){
			ficheroresultados <<generaciones[i].first <<","<< bd << ","<<generaciones[i].second<<",";
			//Obtengo valores del individuo
			for(int j=0;j<soluciones_seleccionadas[i].first.first.size();j++){
				ficheroresultados <<soluciones_seleccionadas[i].first.first[j];
			}
			ficheroresultados<<","<<soluciones_seleccionadas[i].first.second<< endl;
			//escribo individuo 2
			ficheroresultados <<generaciones[i].first<< "," << bd << ","<<generaciones[i].second<<",";
			for(int l=0;l<soluciones_seleccionadas[i].second.first.size();l++)
				ficheroresultados <<soluciones_seleccionadas[i].second.first[l];
			ficheroresultados<<","<<soluciones_seleccionadas[i].second.second<< endl;
				
		}
		
	}
	else
		cerr << "Error creando el fichero '" << fichero << "' ." << endl;
	ficheroresultados.close();
}




// ********************************************************************************

// ******************** Funciones para la búsqueda local ********************

/**
 * @brief Genera un vecino de un vector de atributos
 * @param atributos Vector para generar el vecino
 * @param vecinosgenerados Vecinos ya generados para no volver a repetirlos
 * @param solucionesnovalidas Soluciones ya generadas anteriormente que han sido mejoradas, así no se vuelven a generar
 * @see Randint
 * @return Vecino válido al vector que se le pasa
 * 
 * Calcula y devuelve un vecino para el vector de atributos que se le pasa, un vecino será válido cuando no se haya generado antes
 * ni haya sido mejorado, si no se encuentra ningún vecino que cumpla estas condiciones se devolverá el mismo vector de atributos 
*/
vector<bool> generarVecino(vector<bool> atributos, set<int> &vecinosgenerados, set<vector<bool> > &solucionesnovalidas)
{
	bool seguirbuscando = true;
	int vecinonuevo;
	
	while( seguirbuscando )
	{
		vecinonuevo = Randint(0, atributos.size()-1);
		while( vecinosgenerados.find(vecinonuevo) != vecinosgenerados.end() && vecinosgenerados.size() < atributos.size() ) // mientras ya haya generado ese vecino
			vecinonuevo = Randint(0, atributos.size()-1);
		
		if( vecinosgenerados.size() < atributos.size() ) // si no he generado todos los posibles vecinos ya
		{
			vecinosgenerados.insert(vecinonuevo);
			atributos[vecinonuevo] = !atributos[vecinonuevo];
			if( solucionesnovalidas.find(atributos) != solucionesnovalidas.end() ) // si la solucion ya la he generado anteriormente
				atributos[vecinonuevo] = !atributos[vecinonuevo];
			else
				seguirbuscando = false;
		}
		else
			seguirbuscando = false;
	}
		
	return atributos;
}

/**
 * @brief Aplica la búsqueda local a un vector posible solución
 * @param evaluaciones Evaluaciones a la función objetivo
 * @param inicial Vector solución para aplicar la búsqueda local
 * @param datosentrenamiento Datos de entrenamiento
 * @param datostest Datos de test
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * @see generarVecino
 * @return Vector solución después de aplicar la búsqueda local
 * 
 * Aplica la búsqueda local a un vector posible solución y devuelve el resultado de habersela aplicado
*/
vector<bool> busquedaLocal(unsigned int &evaluaciones, vector<bool> inicial, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	set<vector<bool> > solucionesnovalidas; // aquí voy a ir guardando las soluciones que han sido mejoradas por otras para no repetirlas
	set<int> vecinosgenerados;
	vector<bool> solucion = inicial, solucion2, solucionfinal;
	double mejorporcentajeentrenamiento = -1, porcentajeentrenamiento = 0;
	
	while( solucion != solucion2 ) // En este bucle es donde genero todos los vecinos y busco
	{
		solucion2 = generarVecino(solucion, vecinosgenerados, solucionesnovalidas);
		porcentajeentrenamiento = porcentajeAciertos("ENTRENAMIENTO", datosentrenamiento, datostest, solucion2, clasesentrenamiento, clasestest);
		if( porcentajeentrenamiento > mejorporcentajeentrenamiento )
		{
			cout << "\t\t\tHe encontrado una solucion mejor" << endl;
			mejorporcentajeentrenamiento = porcentajeentrenamiento; // actualizo el porcentaje de entrenamiento
			solucionfinal = solucion2; // actualizo la solución al vecino
			solucionesnovalidas.insert(solucion); // meto la solución anterior en el vector de soluciones ya mejoradas para que no se repita
			vecinosgenerados.clear(); // vacío los vecinos que generé para empezar de nuevo a generar en la solución nueva
			solucion = solucion2; // actualizo solucion para generar los nuevos vecinos a partir de la nueva
			solucion2.clear();
		}
		evaluaciones++;
	}
	
	return solucionfinal;
}

// **************************************************************************

// ******************** Funciones para algoritmos genéticos ********************

class cromosoma
{
	private:
		vector<bool> caracteristicas;
		double aciertosEntrenamiento;
	
	public:
		/**
		 * @brief Constructor por defecto
		*/
		cromosoma()
		{
			aciertosEntrenamiento = -1;
		}
		
		/**
		 * @brief Destructor
		*/
		~cromosoma() {}
		
		/**
		 * @brief Inicia un cromosoma
		 * @param tama Tamaño del cromosoma
		 * @param datosentrenamiento Datos de entrenamiento
		 * @param datostest Datos de test
		 * @param clasesentrenamiento Clases de entrenamiento
		 * @param clasestest Clases de test 
		 * @see generarSolucionAleatoria
		 * @see aciertosEnEntrenamiento
		 * 
		 * Inicia un cromosoma
		*/
		void iniciarCromosoma(unsigned int tama, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
		{
			caracteristicas = generarSolucionAleatoria(tama);
			aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
		}
		
		/**
		 * @brief Calcula los aciertos en entrenamiento de un cromosoma
		 * @param datosentrenamiento Datos de entrenamiento
		 * @param datostest Datos de test
		 * @param clasesentrenamiento Clases de entrenamiento
		 * @param clasestest Clases de test 
		 * @see porcentajeAciertos
		 * 
		 * Calcula los aciertos en entrenamiento de un cromosoma
		*/
		void aciertosEnEntrenamiento(vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
		{
			aciertosEntrenamiento = porcentajeAciertos("ENTRENAMIENTO", datosentrenamiento, datostest, caracteristicas, clasesentrenamiento, clasestest);
		}
		
		/**
		 * @brief Devuelve los aciertos en entrenamiento de un cromosoma
		 * @return Aciertos en entrenamiento
		 * 
		 * Devuelve los aciertos en entrenamiento de un cromosoma 
		*/
		double getAciertosEntrenamiento() const
		{
			return aciertosEntrenamiento;
		}
		
		/**
		 * @brief Devuelve los aciertos en test de un cromosoma
		 * @param datosentrenamiento Datos de entrenamiento
		 * @param datostest Datos de test
		 * @param clasesentrenamiento Clases de entrenamiento
		 * @param clasestest Clases de test 
		 * @see porcentajeAciertos
		 * 
		 * Calcula y devuelve los aciertos en test de un cromosoma
		*/
		double getAciertosTest(vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
		{
			 return porcentajeAciertos("TEST", datosentrenamiento, datostest, caracteristicas, clasesentrenamiento, clasestest);
		}
		
		/**
		 * @brief Devuelve la reducción de atributos de un cromosoma
		 * @see calcularReduccion
		 * @return Reducción de atributos
		 * 
		 * Devuelve la reducción de atributos de un cromosoma
		*/
		double getReduccion() const
		{
			return calcularReduccion(caracteristicas);
		}
		
		/**
		 * @brief Indica si un cromosoma está vacío
		 * @return True si el cromosoma está vacío, false en caso contrario
		 * 
		 * Indica si un cromosoma está vacío 
		*/
		bool vacio() const
		{
			return caracteristicas.empty();
		}
		
		/**
		 * @brief Devuelve el tamaño de un cromosoma
		 * @return Tamaño de un cromosoma
		 * 
		 * Devuelve el tamaño de un cromosoma
		*/
		unsigned int size() const
		{
			return caracteristicas.size();
		}
	
		/**
		 * @brief Inserta un elemento en un cromosoma
		 * @param elemento Elemento a insertar
		 * 
		 * Inserta un elemento en un cromosoma
		*/
		void insertarElemento(bool elemento)
		{
			caracteristicas.push_back(elemento);
		}
		
		/**
		 * @brief Devuelve un elemento de un cromosoma
		 * @param posicion Posición del elemento a devolver
		 * @return Elemento del cromosoma
		 * 
		 * Devuelve un elemento en concreto de un cromosoma
		*/
		bool getElemento(unsigned int posicion) const
		{
			return caracteristicas[posicion];
		}
		
		/**
		 * @brief Modifica un elemento de un cromsoma
		 * @param posicion Posicion del elemento a modificar
		 * @param nuevo Nuevo elemento
		 * 
		 * Modifica un elemento de un cromosoma
		*/
		void setElemento(unsigned int posicion, bool nuevo)
		{
			caracteristicas[posicion] = nuevo;
		}
		
		/**
		 * @brief Aplica una búsqueda local a un cromosoma
		 * @param evaluaciones Evaluaciones a la función objetivo
		 * @param datosentrenamiento Datos de entrenamiento
		 * @param datostest Datos de test
		 * @param clasesentrenamiento Clases de entrenamiento
		 * @param clasestest Clases de test
		 * @see busquedaLocal
		 * @see aciertosEnEntrenamiento
		 * 
		 * Aplica la búsqueda local a un cromosoma 
		*/
		void aplicarBusquedaLocal(unsigned int &evaluaciones, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
		{
			busquedaLocal(evaluaciones, caracteristicas, datosentrenamiento, datostest, clasesentrenamiento, clasestest);
			aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
		}
		
		/**
		 * @brief Muta un cromosoma
		 * @param datosentrenamiento Datos de entrenamiento
		 * @param datostest Datos de test
		 * @param clasesentrenamiento Clases de entrenamiento
		 * @param clasestest Clases de test
		 * @see Randint
		 * @see setElemento
		 * @see getElemento
		 * @see aciertosEnEntrenamiento
		 * 
		 * Muta un cromosoma
		*/
		void mutar(vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
		{
			unsigned int atributosamutar = 0.1 * size();
			set<int> atributos;
			while( atributos.size() < atributosamutar )
			{
				int atributo = Randint(0, size()-1);
				while( atributos.find(atributo) != atributos.end() )
					atributo = Randint(0, size()-1);
				atributos.insert(atributo);
			}
			for(set<int>::iterator i = atributos.begin(); i != atributos.end(); i++)
				setElemento(*i, !getElemento(*i)); // muto el atributo			
			aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
		}
		
		/**
		 * @brief operator==
		 * @param c Cromosoma para comparar
		 * @return True si los cromosomas son iguales, falso en caso contrario
		 * 
		 * Comprueba si dos cromosomas son iguales
		*/
		bool operator==(const cromosoma &c)
		{
			bool son_iguales = false;
			
			if(this == &c)
				son_iguales = true;
			else
				if( caracteristicas == c.caracteristicas )
					son_iguales = true;
			
			return son_iguales;
		}
		
		/**
		 * @brief operator!=
		 * @param c Cromosoma para comparar
		 * @see operator==
		 * @return True si los cromosomas son distintos, false en caso contario
		 * 
		 * Comprueba si dos cromosomas son distintos 
		*/
		bool operator!=(const cromosoma &c)
		{
			return !(*this == c);
		}
		
		/**
		 * operator=
		 * @param c Cromosoma para igualar
		 * @return Cromosoma
		 * 
		 * Iguala dos cromosomas 
		*/
		cromosoma& operator=(const cromosoma &c)
		{
			if(this != &c)
			{
				caracteristicas = c.caracteristicas;
				aciertosEntrenamiento = c.aciertosEntrenamiento;
			}
			return *this;
		}
		
		/**
		 * @brief operator<<
		 * @param os Flujo de salida
		 * @param c Cromosoma
		 * @see getElemento
		 * @return Flujo de salida 
		 * 
		 * Muestra por pantalla un cromosoma
		*/
		friend ostream& operator<<(ostream &os, cromosoma &c)
		{
			for(unsigned int i = 0; i < c.size(); i++)
					os << c.getElemento(i);
			return os;
		}
};

/**
 * @brief Operador de cruce 
 * @param padre Padre para heredar
 * @param madre Madre para heredar
 * @param descendiente1 Descendiente número 1 que va a salir de la herencia
 * @param descendiente2 Descendiente número 2 que va a salir de la herencia
 * @param datosentrenamiento Datos de entrenamiento
 * @param datostest Datos de test
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * @see Randint
 * 
 * Operador de cruce para algoritmos genéticos
*/
void cruce(const cromosoma &padre, const cromosoma &madre, cromosoma &descendiente1, cromosoma &descendiente2, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	unsigned int puntoCorte1 = Randint(0, padre.size()-1);
	unsigned int puntoCorte2 = Randint(0, padre.size()-1);
	
	if(puntoCorte2 < puntoCorte1)
	{
		int corteAux = puntoCorte1;
		puntoCorte1 = puntoCorte2;
		puntoCorte2 = corteAux;
	}
	
	// Herencia de padres a hijos
	for(unsigned int i = 0; i < puntoCorte1; i++)
	{
		descendiente1.insertarElemento(padre.getElemento(i));
		descendiente2.insertarElemento(madre.getElemento(i));
	}
	for(unsigned int i = puntoCorte1; i < puntoCorte2; i++)
	{
		descendiente1.insertarElemento(madre.getElemento(i));
		descendiente2.insertarElemento(padre.getElemento(i));
	}
	//padre.size()-1
	for(unsigned int i = puntoCorte2; i < padre.size(); i++)
	{
		descendiente1.insertarElemento(padre.getElemento(i));
		descendiente2.insertarElemento(madre.getElemento(i));
	}
	
	descendiente1.aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
	descendiente2.aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
}

/**
 * @brief Operador de cruce 
 * @param padre Padre para heredar
 * @param madre Madre para heredar
 * @param descendiente1 Descendiente número 1 que va a salir de la herencia
 * @param descendiente2 Descendiente número 2 que va a salir de la herencia
 * @param datosentrenamiento Datos de entrenamiento
 * @param datostest Datos de test
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * @see Randint
 * 
 * Operador de cruce para algoritmos genéticos
*/
void cruceUnPunto(const cromosoma &padre, const cromosoma &madre, cromosoma &descendiente1, cromosoma &descendiente2, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	
	unsigned int puntoCorte1 = Randint(0, padre.size()-1);
	//unsigned int puntoCorte2 = Randint(0, padre.size()-1);
	
	/*if(puntoCorte2 < puntoCorte1)
	{
		int corteAux = puntoCorte1;
		puntoCorte1 = puntoCorte2;
		puntoCorte2 = corteAux;
	}*/
	
	// Herencia de padres a hijos
	for(unsigned int i = 0; i <puntoCorte1; i++)
	{
		descendiente1.insertarElemento(padre.getElemento(i));
		descendiente2.insertarElemento(madre.getElemento(i));
	}
	/*for(unsigned int i = puntoCorte1; i < puntoCorte2; i++)
	{
		descendiente1.insertarElemento(madre.getElemento(i));
		descendiente2.insertarElemento(padre.getElemento(i));
	}*/
	for(unsigned int i = puntoCorte1; i < padre.size(); i++)
	{
		descendiente1.insertarElemento(madre.getElemento(i));
		descendiente2.insertarElemento(padre.getElemento(i));
	}
	
	descendiente1.aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
	descendiente2.aciertosEnEntrenamiento(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
}

/**
 * @brief Devuelve un elemento de un conjunto de enteros
 * @param conjunto Conjunto donde se va a buscar
 * @param posicion Posicion del elemento que se quiere obtener
 * @return Elemento de la posición 'posicion' del conjunto
 * 
 * Devuelve un elemento de un conjunto de enteros, la posición ha de ser válida. 
*/
int getElemento(set<int> &conjunto, int posicion)
{
	set<int>::iterator i = conjunto.begin();
	
	for(int pos = 0; pos < posicion; pos++)
		i++;
	
	return *i;
}

/**
 * @brief Torneo estacionario
 * @param padre Cromosoma que va a ser el padre
 * @param madre Cromosoma que va a ser la madre
 * @param poblacion Población de cromosomas
 * @param datosentrenamiento Datos de entrenamiento
 * @param datostest Datos de test
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * @see Randint
 * @see porcentajeAciertos
 * @see getElemento
 * 
 * Torneo estacionario para ver qué 2 cromosomas son los que se reproducen
*/
void seleccionEstacionario(cromosoma &padre, cromosoma &madre, vector<cromosoma> &poblacion, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	set<int> participantes;
	
	while(participantes.size() < 4) // genero los cromosomas que van a luchar a sangre fría y sin remordimientos
		participantes.insert(Randint(0, poblacion.size()-1));
	
	// Calculo los resultados de cada participante
	vector<double> resultados;
	for(set<int>::iterator i = participantes.begin(); i != participantes.end(); i++)
		resultados.push_back(poblacion[*i].getAciertosEntrenamiento());
		
	// Torneo 1: cromosoma 0 VS cromosoma 1 - Luchando por ser el padre
	if( resultados[0] > resultados[1] )
		padre = poblacion[ getElemento(participantes, 0) ];
	else
		padre = poblacion[ getElemento(participantes, 1) ];
	
	// Torneo 2: cromosoma 2 VS cromosoma 3 - Luchando por ser la madre
	if( resultados[2] > resultados[3] )
		madre = poblacion[ getElemento(participantes, 2) ];
	else
		madre = poblacion[ getElemento(participantes, 3) ];
}

/**
 * @brief Método estacionario de reemplazamiento de cromosomas
 * @param descendiente1 Descendiente número 1 de los cromosomas padre y madre
 * @param descendiente2 Descendiente número 2 de los cromosomas padre y madre
 * @param poblacion Población de cromosomas
 * 
 * Método estacionario para reemplazar cromosomas
*/
void reemplazarCromosomasEstacionario(cromosoma &descendiente1, cromosoma &descendiente2, vector<cromosoma> &poblacion)
{
	unsigned int peorCromosoma = 0, penultimoCromosoma = 0;
	// Busco el peor cromosoma
	for(unsigned int i = 1; i < poblacion.size(); i++)
		if( poblacion[i].getAciertosEntrenamiento() < poblacion[peorCromosoma].getAciertosEntrenamiento() )
			peorCromosoma = i;
	// Busco el penúltimo peor cromosoma
	for(unsigned int i = 1; i < poblacion.size(); i++)
		if( i != peorCromosoma && (poblacion[i].getAciertosEntrenamiento() < poblacion[penultimoCromosoma].getAciertosEntrenamiento()) )
			penultimoCromosoma = i;
	
	// Miro si mis descendientes son mejores que los peores cromosomas
	if( poblacion[peorCromosoma].getAciertosEntrenamiento() < descendiente1.getAciertosEntrenamiento() )
		poblacion[peorCromosoma] = descendiente1;
	if( poblacion[penultimoCromosoma].getAciertosEntrenamiento() < descendiente2.getAciertosEntrenamiento() )
		poblacion[penultimoCromosoma] = descendiente2;
}

/**
 * @brief Torneo generacional
 * @param padre Padre para el cruce
 * @param madre Madre para el cruce
 * @param posicionPadre Posición del cromosoma que actuó como padre
 * @param posicionMadre Posición del cromosoma que actuó como madre
 * @param poblacion Población de cromosomas
 * @param datosentrenamiento Datos de entrenamiento
 * @param datostest Datos de test
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * @see Randint
 * @see porcentajeAciertos
 * 
 * Torneo generacional para ver qué 2 cromosomas son los que se reproducen
*/
void seleccionGeneracional(cromosoma &padre, cromosoma &madre, unsigned int &posicionPadre, unsigned int &posicionMadre, vector<cromosoma> &poblacion, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	unsigned int numeroParticipantes = poblacion.size();
	vector<bool> participantes;
	vector<int> luchadores;
	
	for(unsigned int i = 0; i < numeroParticipantes; i++)
		participantes.push_back(true); // al principio participan todos
	
	while( numeroParticipantes > 2 )
	{
		luchadores.clear();
		// Elijo el orden de los luchadores
		while(luchadores.size() < numeroParticipantes)
		{
			int candidato = Randint(0, poblacion.size()-1);
			while( !participantes[candidato] ) // miro si el candidato para la pareja está eliminado de antes
				candidato = Randint(0, poblacion.size()-1);
			bool yaesluchador = false;
			for(unsigned int j = 0; !yaesluchador && j < luchadores.size(); j++)
				if( luchadores[j] == candidato )
					yaesluchador = true;
			if( !yaesluchador )
				luchadores.push_back(candidato);
		}
		
		unsigned int topeLucha = numeroParticipantes;
		if( numeroParticipantes % 2 != 0 )
			topeLucha--;
		
		for(unsigned int j = 0; j < topeLucha; j+=2) // ¡¡¡PELEAS!!!
		{
			if( poblacion[luchadores[j]].getAciertosEntrenamiento() > poblacion[luchadores[j+1]].getAciertosEntrenamiento() ) // elimino al perdedor
				participantes[luchadores[j+1]] = false;
			else
				participantes[luchadores[j]] = false;
		}
		
		// Paso a la siguiente fase del torneo
		// Reduzco el número de participantes
		if( numeroParticipantes % 2 == 0 )
			numeroParticipantes /= 2;
		else
			numeroParticipantes = (numeroParticipantes / 2) + 1;
		if( numeroParticipantes == 2 ) // si quedan 2 son los ganadores, el padre y la madre
		{
			//cout << "\t\tFin del torneo, han ganado: ";
			for(unsigned int k = 0; k < participantes.size(); k++)
				if( participantes[k] )
					cout << k << ", ";
			cout << endl;
			for(unsigned int k = 0; k < participantes.size(); k++)
			{
				if( padre.vacio() && participantes[k] )
				{
					padre = poblacion[k];
					posicionPadre = k;
				}
				if( !padre.vacio() && participantes[k] )
				{
					madre = poblacion[k];
					posicionMadre = k;
				}
			}
		}
	}
}

/**
 * @brief Método generacional de reemplazamiento de cromosomas
 * @param descendiente1 Descendiente número 1 de los cromosomas padre y madre
 * @param descendiente2 Descendiente número 2 de los cromosomas padre y madre
 * @param posicionPadre Posición del cromosoma que actuó como padre
 * @param posicionMadre Posición del cromosoma que actuó como madre
 * @param cromosomas Población de cromosomas
 * @param datosentrenamiento Datos de entrenamiento
 * @param datostest Datos de test
 * @param clasesentrenamiento Clases de entrenamiento
 * @param clasestest Clases de test
 * 
 * Método generacional para reemplazar cromosomas
*/
void reemplazarCromosomasGeneracional(cromosoma &descendiente1, cromosoma &descendiente2, unsigned int &posicionPadre, unsigned int &posicionMadre, vector<cromosoma> &poblacion, vector<vector<double> > &datosentrenamiento, vector<vector<double> > &datostest, vector<string> &clasesentrenamiento, vector<string> &clasestest)
{
	// Primeramente busco la mejor y la peor solución dentro de mi población
	double mejor = poblacion[0].getAciertosEntrenamiento();
	double peor = mejor;
	unsigned int mejorCromosoma = 0, peorCromosoma = 0;
	for(unsigned int i = 1; i < poblacion.size(); i++)
	{
		if( mejor > poblacion[i].getAciertosEntrenamiento() )
		{
			mejor = poblacion[i].getAciertosEntrenamiento();
			mejorCromosoma = i;
		}
		else
		{
			if( peor < poblacion[i].getAciertosEntrenamiento() )
			{
				peor = poblacion[i].getAciertosEntrenamiento();
				peorCromosoma = i;
			}
		}
	}
	// Para conservar el etilismo, si el padre o la madre son la mejor solución de toda la población, reemplazo por la posición peor
	// En caso contrario reemplazo por el padre o la madre
	if( posicionPadre == mejorCromosoma )
	{
		poblacion[peorCromosoma] = descendiente1;
		poblacion[posicionMadre] = descendiente2;
	}
	else
		if( posicionMadre == mejorCromosoma )
		{
			poblacion[posicionPadre] = descendiente1;
			poblacion[peorCromosoma] = descendiente2;
		}
		else
		{
			poblacion[posicionPadre] = descendiente1;
			poblacion[posicionMadre] = descendiente2;
		}
}

// *****************************************************************************

#endif
