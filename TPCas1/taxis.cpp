#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include "semaphore.h"
#include "taxis.h"
#include"structuredonnees.h"

//____________________Le constructeur de la classe ________________________//

Taxis::Taxis(int *tube) 
{
 m_pipe=tube;//Récupérer l'@ du pipe
}

//________________________________________________________________________//

//____________________________Processus fils taxi______________________________//

void Taxis::lancer_taxi()
{
  client clt;

  //Creation des trois threads de taxi
   pthread_create( &threadtaxi1, NULL,Taxi1, m_pipe); 
   pthread_create( &threadtaxi2, NULL,Taxi2, m_pipe); 
   pthread_create( &threadtaxi3, NULL,Taxi3, m_pipe); 
  
  //Attendre la terminaison des trois thread taxi
   pthread_join( threadtaxi1, NULL);
   pthread_join( threadtaxi2, NULL);
   pthread_join( threadtaxi3, NULL);  
}
//_______________________________________________________________________//


//____________________________Thread Taxi1______________________________//

void* Taxi1(void* P)
{ client clt;
  int* Pipe=(int*)P; 
  while(clt.id!=-1)//Tanque la simulation n'est pas finie
  {
    if(read(Pipe[0],&clt,sizeof(clt)) && clt.id!=-1)//Lire du pipe des clients à transporter
    {
     printf("[Verificateur]: Transfert du passager {%d} vers le Taxi{1} \n",clt.id);
      sleep(5);   
     printf("[Taxi{1}]: Passager {%d} est rendu vers la station {%u}\n",clt.id,clt.station_fin);
    }
  } 
}

//____________________________________________________________________//

//___________________________Thread Taxi2_____________________________//

void* Taxi2(void* P)
{ client clt;
  int* Pipe=(int*)P; 
  while(clt.id!=-1)//Tanque la simulation n'est pas finie
  {     
     if(read(Pipe[0],&clt,sizeof(clt)) && clt.id!=-1)//Lire du pipe des clients à transporter
    {
     printf("[Verificateur]: Transfert du passager {%d} vers le Taxi{2} \n",clt.id);
      sleep(5);   
     printf("[Taxi{2}]: Passager {%d} est rendu vers la station {%u}\n",clt.id,clt.station_fin);
    }
  } 
}

//__________________________________________________________________//

//___________________________Thread Taxi3___________________________//

void* Taxi3(void* P)
{ client clt;
  int* Pipe=(int*)P; 
  while(clt.id!=-1)//Tanque la simulation n'est pas finie
  {
     if(read(Pipe[0],&clt,sizeof(clt)) && clt.id!=-1)//Lire du pipe des clients à transporter
    {
     printf("[Verificateur]: Transfert du passager {%d} vers le Taxi{3} \n",clt.id);
      sleep(5);   
     printf("[Taxi{3}]: Passager {%d} est rendu vers la station {%u}\n",clt.id,clt.station_fin);
    }
  } 
}

//________________________________________________________________//
