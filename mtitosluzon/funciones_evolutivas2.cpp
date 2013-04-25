#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/timeb.h>
using namespace std;



void MostrarVector(int *a,int elements){
            for(int p=0;p<elements;p++){
                cout << a[p];
        }
        cout << endl;
}

void fitness(int *vector,int elements){
	//Recorre el vector y cuenta numero de unos
	int unos=0;	
	for(int i=0;i<elements;i++){
		unos=vector[i]+unos;	
	}
	vector[elements]=unos;
}

void copioPoblacion(int **poblacion,int fila1,int* vector1){
	for(int i=0;i<11;i++){
		poblacion[fila1][i]=vector1[i];
	}
}
void Crossover(int *a, int *b,int *c,int valor,int elements){
 
    //Cruzo parte del padre
    for(int k=0;k<valor;k++){
        c[k]=a[k];
}
     //Cruzo la parte de la madre
    for(int l=valor+1;l<elements;l++){
        c[l]=b[l];
}

}
void generarPoblacion(int **poblacion){
	for(int i=0;i<100;i++){
		for(int j=0;j<10;j++){
		poblacion[i][j]=rand()%2;		
		}
	fitness(poblacion[i],10);	
	}
}
void eliminarPoblacion(int **poblacion){
	for(int i=0;i<100;i++){
		delete poblacion[i];	
	}
	delete [] poblacion;
}
void Mutacion(int *c ,int valor){
        
        c[valor]=(c[valor] +1)%2;
}

void comprobarNuevaPoblacion(int *vector1,int* vector2,int **poblacion){
	
	bool parar=false;
	for(int i=0;i<100 && !parar ;i++){
		if(vector1[10]>poblacion[i][10]){
			copioPoblacion(poblacion,i,vector1);
			parar=true;
		}
		else{
			if(vector2[10]>poblacion[i][10]){
				copioPoblacion(poblacion,i,vector2);
				parar=true;
			}

		}

	}
}

int NumeroUnos(int **poblacion){


	int maximo=0;
	for(int i=0;i<100;i++){
		if(maximo<=poblacion[i][10])
			maximo=poblacion[i][10];
	}
	return maximo;
}

int main(int argc, char** argv){
        
  bool para=false;
   clock_t startC, finishC;
   unsigned int seconds, milliseconds;
   struct timeb startT, finishT;
    unsigned int elements=10;
    int num,valor,valor2,padre,madre,unos_obtenidos=0;
    int *a;
    int *b;
    int *c=new int[11];
    int *d=new int [11];
    //creo poblacion
    int **poblacion=new int *[100];
    for(int i=0;i<100;i++){
    	poblacion[i]=new int[11];
    }
    startC = clock();
    ftime(&startT);
    srand(time(NULL));
    //valor=rand()%11;
    //MostrarVector(a,elements);
    //MostrarVector(b,elements);


    //genero poblacion inicial
    generarPoblacion(poblacion);

    while(para==false){


    //Escojo dos valores al hazar para realizar el cruce
    valor=rand()%10;
    valor2=rand()%10;
    
    //Escojo al padre y a la madre

    padre=rand()%101;
    madre=rand()%101;
    
    a=poblacion[padre];

    b=poblacion[madre];
    //Cruzo a,bas creando dos nuevos hijos
    
    Crossover(a,b,c,valor,elements);
    Crossover(a,b,d,valor2,elements);
    
    valor=rand()%11;
    valor2=rand()%11;

    //Muto ambos hijos
    Mutacion(c,valor);
    Mutacion(d,valor2);



    //Calculo fitness hijos nuevos
    fitness(c,10);
    fitness(d,10);

    comprobarNuevaPoblacion(c,d,poblacion);

    unos_obtenidos=NumeroUnos(poblacion);  
    if(unos_obtenidos==10) para=true; 	 	
    
 }

    finishC = clock();
    ftime(&finishT);
    seconds = finishT.time - startT.time - 1;
    milliseconds = (1000 - startT.millitm) + finishT.millitm;
    cout << "Time (clock): "    << (finishC - startC)/CLOCKS_PER_SEC << endl;


    cout << "El numero de unos es: "<< unos_obtenidos<<endl;
   eliminarPoblacion(poblacion);
   delete [] c;
   delete [] d;
   
   return 0;

}

