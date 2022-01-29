#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "semaphore.h"
#include "taxis.h"
#include "structuredonnees.h"

//____________________Le constructeur de la classe ________________________//

Taxis::Taxis(int socketClient) 
{
 this->socketClient=socketClient;//Récupérer le socket
}

//________________________________________________________________________//

//____________________________Processus fils taxi______________________________//

void Taxis::lancer_taxi()
{
  //Creation des trois threads de taxi
   pthread_create( &threadtaxi1, NULL,Taxi1, this); 
   pthread_create( &threadtaxi2, NULL,Taxi2, this); 
   pthread_create( &threadtaxi3, NULL,Taxi3, this); 
   
  //Attendre la terminaison des trois thread taxi
   pthread_join( threadtaxi1, NULL);
   pthread_join( threadtaxi2, NULL);
   pthread_join( threadtaxi3, NULL);  
}
//_______________________________________________________________________//

//__________________Methode de renvoie du socket client_________________//
int Taxis::renvoyerSocketC()
{
  return this->socketClient;
}
//______________________________________________________________________//

//____________________________Thread Taxi1______________________________//

void* Taxi1(void* T)
{ 
  client clt;
  int socketClient=((Taxis*)T)->renvoyerSocketC();
  do 
  {
    read(socketClient, &clt, sizeof(client));
    if(clt.id!=-1)//Lire du socket des clients à transporter
     {
      printf("[Verificateur]: Transfert du passager {%d} vers le Taxi{1} \n",clt.id);
      sleep(5);   
      printf("[Taxi{1}]: Passager {%d} est rendu vers la station {%u}\n",clt.id,clt.station_fin);
     }
  }while(clt.id!=-1);//Tanque la simulation n'est pas finie 
  
}

//____________________________________________________________________//

//___________________________Thread Taxi2_____________________________//

void* Taxi2(void* T)
{
  client clt;
  int socketClient=((Taxis*)T)->renvoyerSocketC();
  do
  {  read(socketClient, &clt, sizeof(client));   
     if(clt.id!=-1)//Lire du socket des clients à transporter
      {
       printf("[Verificateur]: Transfert du passager {%d} vers le Taxi{2} \n",clt.id);
       sleep(5);   
       printf("[Taxi{2}]: Passager {%d} est rendu vers la station {%u}\n",clt.id,clt.station_fin);
      }
  }while(clt.id!=-1);//Tanque la simulation n'est pas finie 
  
}

//__________________________________________________________________//

//___________________________Thread Taxi3___________________________//

void* Taxi3(void* T)
{ 
  client clt;
  int socketClient=((Taxis*)T)->renvoyerSocketC();
  do 
  {  read(socketClient, &clt, sizeof(client));
     if(clt.id!=-1)//Lire du socket des clients à transporter
     {
      printf("[Verificateur]: Transfert du passager {%d} vers le Taxi{3} \n",clt.id);
      sleep(5);   
      printf("[Taxi{3}]: Passager {%d} est rendu vers la station {%u}\n",clt.id,clt.station_fin);
     }
  }while(clt.id!=-1);//Tanque la simulation n'est pas finie 
 
}

//________________________________________________________________//
