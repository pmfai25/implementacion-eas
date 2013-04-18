#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <sys/timeb.h>
using namespace std;


int main(int argc, char** argv){
	
   
   int num_unos=0;
   clock_t startC, finishC;
   unsigned int seconds, milliseconds;
   struct timeb startT, finishT;
    unsigned int elements=100000000;
    int num,c,valor;
    int *a = new int[elements];
    startC = clock();
    ftime(&startT);
    srand(time(NULL));
    for (unsigned int i=0; i<elements; i++)
    {
        valor=rand()%2;
		num_unos=num_unos+valor;
    }

    finishC = clock();
    ftime(&finishT);
    seconds = finishT.time - startT.time - 1;
    milliseconds = (1000 - startT.millitm) + finishT.millitm;
    delete [] a; 
    cout << "Time (clock): "    << (finishC - startC)/CLOCKS_PER_SEC << endl;
    cout << "Numero de unos: " << num_unos<< endl;    
   return 0;

}
