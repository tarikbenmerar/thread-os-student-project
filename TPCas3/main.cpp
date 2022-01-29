#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "structuredonnees.h"
#include "Stations.h"
#include "Autobus.h"
#include "verificateur.h"
#include "Train.h"

int main(int argc, char *argv[])
{
  //Variables requises pour la connexion et la deconnexion avec le serveur Taxi
   int Socket;
   int len;
   struct sockaddr_in address;
   int result;
   client c; // Utilisé pour l'attente de la fin de la simulation
  
  //Les threadse et leurs fonctions associées
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

   
 
  //3- Etablissement de la connexion avec le serveur Taxi
   
    Socket = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);

    result = connect(Socket, (struct sockaddr *)&address, len);
    
    if(result == -1) {
      perror("[Processus principal]");
     return 1;
    }
   printf("[Processus principal]:Connexion établie avec le serveur de taxi.\n");
    
  //4- Création des classes requises pour la simulation
  
    Stations s;
    printf("\n[Processus principal]:récuperation du fichier d'entrée\n");
    Verificateur verificateur(&s,Socket,s.remplirStations(&fichier));
    Autobus bus(&s,&verificateur,0);
    Train  train(&s,&verificateur);
 
  //5- Creer les trois threads
    pthread_create( &threadverificateur, NULL,lancerverificateur,&verificateur); 
    pthread_create( &threadbus, NULL,lancerautobus, &bus);
    pthread_create( &threadtrain, NULL,lancertrain, &train);
  
  //6- Attendre les trois threads
    pthread_join( threadbus, NULL);
    pthread_join( threadtrain, NULL);   
    pthread_join( threadverificateur, NULL);

  //7- Attendre le processus Taxi
    printf("[Processus principal]:En attente du serveur Taxi pour la terminaison de la simulation.\n");
    read(Socket, &c, sizeof(client));
     
  //8- Afficher un résumé de la simulation 
    printf("[Processus principal]:Simulation terminée.\n");
    printf("[Processus principal]:Gain total=%u D.A\n",bus.renvoyerGain()+train.renvoyerGain()+verificateur.renvoyerGain());
    
  //9- Fermeture de la connexion entre le verificateur et le serveur taxi   
   close(Socket);
 
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


