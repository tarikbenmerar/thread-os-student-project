#ifndef taxisC
#define taxisC
#include"structuredonnees.h"

class Taxis
{
 private:
  
  //le socket entre le verificateur et les taxis
   int socketClient; 
  
  //Les threads taxi
   pthread_t threadtaxi1;
   pthread_t threadtaxi2;
   pthread_t threadtaxi3;

 public:
        Taxis(int);         //Constructeur
  void  lancer_taxi();      //Processus Taxi
  int   renvoyerSocketC();
};

 //Les trois threads Taxi
   void* Taxi1(void*);
   void* Taxi2(void*);
   void* Taxi3(void*);
 

#endif
