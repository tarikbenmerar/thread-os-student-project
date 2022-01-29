#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "structuredonnees.h"
#include "verificateur.h"
#include "Stations.h"
#include "semaphore.h"


/*__________________________Constructeur de la classe Verificateur ____________________________*/

Verificateur::Verificateur(Stations *stations,int *tube,unsigned NbrClient,unsigned nbrBus) 
{
  //Initialisation du pipe, des stations ,du nombre des clients restants, du nombre des bus
  // et du gain

   m_stations=stations ;
   m_pipe=tube;
   NbrClientsRestant=NbrClient;
   this->nbrBus=nbrBus;
   argent=0;

  //Initialisation du tableau de parcours
   tabParcours[0]=0;
   tabParcours[1]=1;
   tabParcours[2]=2;
   tabParcours[3]=3;
   tabParcours[4]=4;
   tabParcours[5]=5;
   tabParcours[6]=65;
   tabParcours[7]=67;	
   tabParcours[8]=7;         

 //Allocation des tableaux DebarquementBus en fonction du nombre des bus
   DebarquementBus=(int*)malloc(nbrBus*sizeof(int));
      

 //Initialisation de l'ensemble des semaphores privés 
   semaphore=sem_create(2+nbrBus, 0);
   
}

/*___________________ mettre le passager dans le pipe_________________________*/

void Verificateur::mettre_ds_mem_partage(client clt)
{

   write(m_pipe[1],&clt,sizeof(client));
                                           
}

/*___________________ lancer le verificateur _____________________________________________________*/
void Verificateur::lancerVerificateur()
{ 
 Liste* file;//Utilisé pour le parcours des différents files d'attente
 client c;//Utilisé pour mettre a jour le temps d'attente des client
 
 while(!this->finiSimulation())
 {
   
   //Attendre le rendez vous du train 
     P(semaphore,semPTrain);

   //Attendre le rendez vous des bus 
    for(int i=0;i<nbrBus;i++) 
      P(semaphore,semPBus+i);
  
   //Calculer le nombre de clients restants
     for(int i=0;i<nbrBus;i++) 
       NbrClientsRestant-=DebarquementBus[i];
    
     NbrClientsRestant-=DebarquementTrain;
   
   for(int i=0;i<9;i++)
   {
     file=m_stations->retourner_station(tabParcours[i]);//Selectionner une station à parcourir
      
     //Parcourir la station selectionnée
     for(file->initialiserIteration();!file->finiIteration();file->suivantIteration())
     {

     //Renvoyer un client de la file de la station et incrémenter son temps d'attente
      c=file->renvoyerEltIteration();
      c.tmp_att++;
     
      if(c.tmp_att<=c.tmp_max)//s'il a atteint son temps maximal d'attente
      {
        file->modifierEltIteration(c);//modifier le client actuel avec une nouvelle valeur de tmp_att
      }else{

        //Sinon supprimer le client et mettre dans le pipe et mise à jour du nbr des clients restants.
         file->supprimerEltIteration();
         mettre_ds_mem_partage(c);
         NbrClientsRestant--;

        //Calculer le gain pour le transfert vers les taxis
          argent+=300;      
      }
 
     }
   }
   printf("--------------------------------------------------------------------------------------\n");
    sleep(5);//Simuler l'attente dans les stations
  
    //Libérer le train et les bus
     for(int i=0;i<nbrBus+1;i++) 
      V(semaphore,semPVerificateur); 
 }

 //Fin de la simulation

  //Envoyer dans la mémoire partagé 3 clients avec id=-1 
  //pour signaler la fin de la simulation 
   c.id=-1;
   mettre_ds_mem_partage(c);
   mettre_ds_mem_partage(c);
   mettre_ds_mem_partage(c);

  //Suppression de l'ensemble des semaphores
   sem_delete(semaphore);
}							
//_______________________________________________________________________________________________________//

//_________________________________Fonction de rendezVous pour le bus____________________________________//

 void Verificateur::rendezVousBus(unsigned DebarquementBus,unsigned numBus)
{
  this->DebarquementBus[numBus]=DebarquementBus;
  V(semaphore,semPBus+numBus);
  P(semaphore,semPVerificateur);//Attendre la fin du parcours du verificateur
}

//_______________________________________________________________________________________________________//

//_________________________________Fonction de rendezVous pour le train____________________________________//

void Verificateur::rendezVousTrain(unsigned DebarquementTrain)
{
 this->DebarquementTrain=DebarquementTrain;
 V(semaphore,semPTrain);
 P(semaphore,semPVerificateur);//Attendre la fin du parcours du verificateur
}

//______________________________________________________________________________________________________//

//____________________________Fonction verifiant si la simulation est fini______________________________//

bool Verificateur::finiSimulation()
{
 return(NbrClientsRestant==0);
}

//_____________________________________________________________________________________________________//

//____________________Fonction qui renvoie le gain du verificateur__________________//

unsigned Verificateur::renvoyerGain()
{ 
 return (this->argent);
}

//_______________________________________________________________________________//

