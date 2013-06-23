/**
 * @file gEstacionario.cpp Fichero de implementación del método del algoritmo genético estacionario
 * @author Manuel Marcelino Titos Luzón
*/

#include<iostream>
#include"utilidades.h"
using namespace std;

#define ficheroResultados "resultados/resultadosGeneticoEstacionario.txt"
#define ficheroResultados2 "resultados/resultadosGE_evoluciones.csv"

int main(int args, char* argv[])
{
	if( args == 2 )
	{
		string ficheroentrenamiento, ficherotest;
		vector<string> clasesentrenamiento, clasestest;
		vector<vector<double> > datosentrenamiento, datostest;
		vector<double> datosfinalesentrenamiento, datosfinalestest, datosfinalesreduccion;
		vector<vector<bool> >solucionesfinales;
		vector<bool> lasolucion;
		vector <pair<pair<vector<bool>, double>,pair<vector<bool>,double> > > soluciones_generadas;
		vector<bool> auxilar_copia;
		vector <pair<int,int> >generaciones_cruzadas;
		pair<vector<bool>, double> par1;
		pair<vector<bool>, double> par2;
		pair<int,int> par3;
		pair<pair<vector<bool>, double>,pair<vector<bool>,double> > parfinal;
		cromosoma mutado;
	
		if(strcmp(argv[1], "ozone") == 0)
		{
			ficheroentrenamiento = "bd/normalizada/ozone.tra";
			ficherotest = "bd/normalizada/ozone.tst";
		}
		else
			if(strcmp(argv[1], "sonar") == 0)
			{
				ficheroentrenamiento = "bd/normalizada/sonar.tra";
				ficherotest = "bd/normalizada/sonar.tst";
			}
			else
				if(strcmp(argv[1], "spambase") == 0)
				{
					ficheroentrenamiento = "bd/normalizada/spambase.tra";
					ficherotest = "bd/normalizada/spambase.tst";
				}
		
		cargarDatosFichero(ficheroentrenamiento.c_str(), datosentrenamiento, clasesentrenamiento);
		cargarDatosFichero(ficherotest.c_str(), datostest, clasestest);
	
		// ***** Ejecución del algoritmo *****
		for(unsigned int i = 0; i < N_SEMILLAS; i++)
		{
			Set_random(semillas[i]);
			vector<cromosoma> poblacion;
			cout << "\tINFORMACION: Creando poblacion de cromosomas de la semilla " << i+1 << " de la base de datos " << argv[1] << endl;
			for(unsigned int j = 0; j < POBLACIONGENETICOS; j++) // me creo mi población de cromosomas
			{
				cromosoma individuoNuevo;
				individuoNuevo.iniciarCromosoma(datosentrenamiento[0].size(), datosentrenamiento, datostest, clasesentrenamiento, clasestest);
				poblacion.push_back(individuoNuevo);
			}
			int j;
			for(j = 0; j < EVALUACIONES; j++)
			{
				//cout << "\tINFORMACION: Estoy en la evaluacion " << j << " de " << EVALUACIONES << " de la semilla " << i+1 << " de la base de datos " << argv[1] << endl;
				cromosoma padre, madre, descendiente1, descendiente2;
				//cout << "\tINFORMACION: Comienza el torneo estacionario" << endl;
				seleccionEstacionario(padre, madre, poblacion, datosentrenamiento, datostest, clasesentrenamiento, clasestest);
				
				if( Randfloat(0, 1) <= PROBABILIDADCRUCEESTACIONARIO )
				{
					//cout << "\tINFORMACION: cruzo" << endl;
					//Al decidir cruzar guardo elementos para ver su fitnes y realizar el archivo
					//Guardo los fitness de los padres
					par1.second=padre.getAciertosEntrenamiento();
					//cout<< "El fitness del padre es: "<< padre.getAciertosEntrenamiento()<< endl;
					//cout<< "El fitness de la madre es: "<< madre.getAciertosEntrenamiento()<< endl;
					par2.second=madre.getAciertosEntrenamiento();
					//Almaceno las caracteristicas de cada cromosoma
					for(int indice=0;indice<padre.size();indice++){
						par1.first.push_back(padre.getElemento(indice));
						par2.first.push_back(madre.getElemento(indice));
					}
					parfinal.first=par1;
					parfinal.second=par2;
					soluciones_generadas.push_back(parfinal);
					//Inicializo de nuevo los pares
					par1.first.clear();
					par2.first.clear();
					//Guardo la generacion en que cruce y la semilla
					par3.first=i;// semilla
					par3.second=j;//generacion					
					generaciones_cruzadas.push_back(par3);
					cruce(padre, madre, descendiente1, descendiente2, datosentrenamiento, datostest, clasesentrenamiento, clasestest);
					//j += 2;
				}
				//cout << "\tINFORMACION: reemplazo" << endl;
				reemplazarCromosomasEstacionario(descendiente1, descendiente2, poblacion);
				// Muto la población
				for(unsigned int k = 0; k < poblacion.size(); k++)
				{
					// Probablidad de mutar
					if( Randfloat(0, 1) <= PROBABLIDADMUTARESTACIONARIO )
					{
						//Compruebo que al mutar no baje el rendimiento
						mutado=poblacion[k];
						mutado.mutar(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
						// si el rendimiento mejora o iguala muto  
						if(mutado.getAciertosEntrenamiento() >= poblacion[k].getAciertosEntrenamiento())
							poblacion[k]=mutado;		
						//poblacion[k].mutar(datosentrenamiento, datostest, clasesentrenamiento, clasestest);
						//j++;
					}
				}
				
			}
			// Me quedo con el mejor cromosoma
			double mejorporcentajeentrenamiento = poblacion[0].getAciertosEntrenamiento();
			int posicionMejor = 0;
			for(unsigned int k = 1; k < poblacion.size(); k++)
			{
				if( mejorporcentajeentrenamiento < poblacion[k].getAciertosEntrenamiento() )
				{
					mejorporcentajeentrenamiento = poblacion[k].getAciertosEntrenamiento();
					posicionMejor = k;
				}
			}
			// Guardo los resultados para la semilla i
			datosfinalesentrenamiento.push_back(mejorporcentajeentrenamiento);
			datosfinalestest.push_back(poblacion[posicionMejor].getAciertosTest(datosentrenamiento, datostest, clasesentrenamiento, clasestest));
			datosfinalesreduccion.push_back(poblacion[posicionMejor].getReduccion());
			for(unsigned int i=0;i<poblacion[posicionMejor].size();i++){
				lasolucion.push_back(poblacion[posicionMejor].getElemento(i)); 			
			}
			solucionesfinales.push_back(lasolucion);
			poblacion.clear();
			lasolucion.clear();
			
		}
		// ***********************************
		
		guardarResultadosFicheroEstructurado(argv[1], ficheroResultados, datosfinalesentrenamiento, datosfinalestest, datosfinalesreduccion,solucionesfinales);
		guardarResultadosFicheroEstructuradoSelecciones(argv[1], ficheroResultados2,soluciones_generadas,generaciones_cruzadas);
	}
	else
	{
		cerr << "\tError. Introduzca la base de datos: ozone, sonar, spambase" << endl;
		cerr << "\t\tbin/gEstacionario ozone" << endl;
		cerr << "\t\tbin/gEstacionario sonar" << endl;
		cerr << "\t\tbin/gEstacionario spambase" << endl;
	}
}
