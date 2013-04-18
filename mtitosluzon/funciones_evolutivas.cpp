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
void Mutacion(int *c ,int valor){
	
	c[valor]=(c[valor] +1)%2;
}

int main(int argc, char** argv){
	
   
   int num_unos=0;
   clock_t startC, finishC;
   unsigned int seconds, milliseconds;
   struct timeb startT, finishT;
    unsigned int elements=10;
    int num,valor;
    int *a = new int[elements];
    int *b=new int[elements];
    int *c=new int[elements];


    startC = clock();
    ftime(&startT);
    srand(time(NULL));
    valor=rand()%11;
    //Introducimos el padre
    for(int i=0;i<10;i++){
	cin>>a[i];
    }
    //Introducimos la madre
    for(int j=0;j<10;j++){
	cin>>b[j];
    }
    MostrarVector(a,elements);
    MostrarVector(b,elements);  
    Crossover(a,b,c,valor,elements);
    MostrarVector(c,elements);
    valor=rand()%11;
    Mutacion(c,valor);
    MostrarVector(c,elements);	
    finishC = clock();
    ftime(&finishT);
    seconds = finishT.time - startT.time - 1;
    milliseconds = (1000 - startT.millitm) + finishT.millitm;
    cout << "Time (clock): "    << (finishC - startC)/CLOCKS_PER_SEC << endl;

    delete [] a;
    delete [] b;
    delete [] c;    
   return 0;

}
