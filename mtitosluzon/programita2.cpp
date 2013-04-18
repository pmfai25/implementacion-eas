#include <iostream>
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
    startC = clock();
    ftime(&startT);
    srand(time(NULL));
    for (unsigned int i=0; i<elements; i++)
    {
        valor=rand()%2;
        if(valor>0)
		num_unos++;
    }

    finishC = clock();
    ftime(&finishT);
    seconds = finishT.time - startT.time - 1;
    milliseconds = (1000 - startT.millitm) + finishT.millitm;
    cout << "Time (clock): "    << (finishC - startC)/CLOCKS_PER_SEC << endl;
    cout << "Numero de unos: " << num_unos<< endl;    
   return 0;

}
