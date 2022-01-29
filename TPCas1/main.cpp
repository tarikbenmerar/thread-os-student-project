#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#include "structuredonnees.h"
#include "Stations.h"
#include "Autobus.h"
#include "verificateur.h"
#include "taxis.h"
#include "Train.h"
using namespace std;


int main(int argc, char *argv[])
{
   int Pipe[2];//Le pipe
   
   //Les threads et leurs fonction associées
    pthread_t threadbus,threadtrain, threadverificateur;  
    void* lancerautobus(void*);
    void* lancertrain(void*);
    void* lancerverificateur(void*);
   
   //1- Verifier l'existence du fichier d'entrée
    if(argc==1)
    {
     printf("\n[Processus principal]:Nom de fichier manquant: Veuillez mentionner un nom de fichier \n");
     return 1;
    }

   //2- Ouvrir le fichier d'entrée
    ifstream fichier(argv[1], ios::in);
    if(!fichier)
    {
      printf("\n[Processus principal]:impossible d'ouvrir le fichier '%s' \n",argv[1]);
       return 1;    
    }
   
   //3- Création des classes requises et du pipe pour la simulation
    Stations s;
    printf("\n[Processus principal]:récuperation du fichier d'entrée\n");
    Verificateur verificateur(&s,Pipe,s.remplirStations(&fichier));//Remplir les stations et récuperer le nombre des clients
    Autobus bus(&s,&verificateur,0);//Mettre l'autobus dans la station 0
    Train train(&s,&verificateur);
    Taxis taxis(Pipe); 
    pipe(Pipe);//Créer le pipe
   
    printf("[Processus principal]:Début de la simulation\n");
    printf("--------------------------------------------------------------------------------------\n");
    
   //4- Lancer le processus fils
    if(fork()==0)   
    {
     taxis.lancer_taxi();
    }else{
    
    //5- Creer les trois threads
     pthread_create( &threadverificateur, NULL,lancerverificateur,&verificateur); 
     pthread_create( &threadbus, NULL,lancerautobus, &bus);
     pthread_create( &threadtrain, NULL,lancertrain, &train);
  
    //6- Attendre les trois threads
     pthread_join( threadbus, NULL);
     pthread_join( threadtrain, NULL);   
     pthread_join( threadverificateur, NULL);

    //7- Attendre le processus fils
     wait(NULL);

     printf("[Processus principal]:Simulation terminée.\n");
     printf("[Processus principal]:Gain total=%u D.A\n",bus.renvoyerGain()+train.renvoyerGain()+verificateur.renvoyerGain());
    
   } 
   
 return 0;
}

//________Thread Bus_________//

void* lancerautobus(void* b)
{
 Autobus* bus=(Autobus*)b;
 bus->lancerautobus();
}

//_________________________//

//______Thread Train______//

void* lancertrain(void* t)
{
  Train* train=(Train*)t;
  train->lancertrain();
}

//_______________________//

//______Thread Verificateur______//

void* lancerverificateur(void* v)
{
  Verificateur* verificateur=(Verificateur*)v;
  verificateur->lancerVerificateur();
}

//______________________________//


