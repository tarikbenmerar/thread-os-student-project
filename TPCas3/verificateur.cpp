#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include "structuredonnees.h"
#include "verificateur.h"
#include "Stations.h"
#include "semaphore.h"

//___________________ Constructeur de la classe Verificateur_______________________//

Verificateur::Verificateur(Stations *stations,int socket,unsigned NbrClient) 
{
  //Initialisation des stations, du socket ,du nombre des clients restants, et du gain
   m_stations=stations ;
   NbrClientsRestant=NbrClient;
   argent=0;
   this->socket=socket;

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
 
 //Initialisation de l'ensemble des semaphores privés 
   semaphore= sem_create (3, 0);
 
}
//________________________________________________________________________________//

//___________________ mettre le passager dans le pipe_________________________//

void Verificateur::mettre_ds_socket(client clt)
{
 write(socket, &clt, sizeof(client));                                              
}
//___________________________________________________________________________//

//___________________ lancer le verificateur _____________________________________________________//

void Verificateur::lancerVerificateur()
{ 
 Liste* file;//Utilisé pour le parcours des différents files d'attente
 client c;//Utilisé pour mettre a jour le temps d'attente des client
 
 while(!this->finiSimulation())
 {
   //Attendre le rendez vous du train et du bus
     P(semaphore,semPTrain);
     P(semaphore,semPBus);
    
   
    NbrClientsRestant-=DebarquementBus+DebarquementTrain;//Calculer le nombre de clients restants
   
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
 
          //Sinon supprimer le client et le mettre dans le socket et mise à jour du nbr des clients restants
           file->supprimerEltIteration();
           mettre_ds_socket(c);
           NbrClientsRestant--;
       
          //Calculer le gain pour le transfert vers les taxis
           argent+=300;           
         }
  
      }
 
   }
   printf("--------------------------------------------------------------------------------------\n");
     
     sleep(5);//Simuler l'attente dans les stations

    //Libérer le train et le bus
     V(semaphore,semPVerificateur);
     V(semaphore,semPVerificateur); 
    
  }

 //Fin de la simulation
 
  //Envoyer dans la mémoire partagé 3 clients avec id=-1 pour signaler la fin de la simulation 
   c.id=-1;
   mettre_ds_socket(c);
   mettre_ds_socket(c);
   mettre_ds_socket(c);

  //Suppression de l'ensemble des semaphores
    sem_delete(semaphore);
   

}							
//_______________________________________________________________________________________________________//

//_________________________________Fonction de rendezVous pour le bus____________________________________//

void Verificateur::rendezVousBus(int DebarquementBus)
{
   this->DebarquementBus=DebarquementBus;
   V(semaphore,semPBus);
   P(semaphore,semPVerificateur);//Attendre la fin du parcours du verificateur

}

//_______________________________________________________________________________________________________//

//_________________________________Fonction de rendezVous pour le train__________________________________//

void Verificateur::rendezVousTrain(int DebarquementTrain)
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

