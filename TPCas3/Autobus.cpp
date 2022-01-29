#include <cstdlib>
#include <iostream>
#include "stdio.h"
#include "structuredonnees.h"
#include "Autobus.h"
#include "Stations.h"
#include "verificateur.h"

//______________Constructeur de la classe Autobus_________________//

 Autobus::Autobus(Stations* stations, Verificateur* verificateur, unsigned stationDebut)
 { 
     
     this->stations=stations;
    
   //Mettre le bus dans la station spécifiée
     if(stationDebut<5) 
      this->stationActuelle=stationDebut;
     else
      this->stationActuelle=0;
 
     this->argent=0;
     this->nbrClients=0;
     this->verificateur=verificateur;
     
  }

//________________________________________________________________//

//_______________________Le thread du bus_________________________//

 void Autobus::lancerautobus()
 {
  client c;
  int nbrClientArrive; //Sauvegarder le nbr de clients arrivés à destination dans la station actuelle

  while(!verificateur->finiSimulation())//Tanque le simulation n'est pas terminée
   {
      printf("[Bus]: dans la station %u \n",this->stationActuelle);
      nbrClientArrive=0;//Initialiser le nombre de clients arrivés à destination dans la station actuelle
   
     //1- Debarquer les clients arrivés à déstination
       for(clients.initialiserIteration();!clients.finiIteration();clients.suivantIteration())
        {//explorer la liste des clients 
         
         c=clients.renvoyerEltIteration();//Recupérer un client du bus
       
         if(this->stationActuelle==0 && (c.station_fin>=5 && c.station_fin<=7) )
         { // Client allant de la station de bus 0 vers les stations de train  
              
             
            //Decrementer le nombre de clients,afficher le debarquement et compter l'argent pris pour le transport 
             this->nbrClients--;
             printf("[Bus]: debarque le passager {%u} dans la station {0} \n" ,c.id); 
             this->argent+=30;
       
            
               if(c.transfert==true)//Verifier la condition du transfert
                {
                    if(c.station_fin!=5)
                    {
                     stations->debarquer(5,c); 
                    }else nbrClientArrive++; //Incrementer le nombre de clients arrivés à destination
                  
                  printf("[Bus]: transfert le passager {%u} vers la station {5} \n",c.id);
                  this->argent+=10;  //Compter l'argent du transfert

                }else nbrClientArrive++; //Incrementer le nombre de clients arrivés à destination
            
             
             clients.supprimerEltIteration();//Enlever le client du bus
            
                      
           }else if(c.station_fin==this->stationActuelle ){//Client arrivé à destination

            //Decrementer le nombre de clients,afficher le debarquement
            //Compter l'argent pris pour le transport
            this->nbrClients--;
            printf("[Bus]: debarque le passager {%u} dans la station {%u} \n" ,c.id, this->stationActuelle); 
            this->argent+=30;

            clients.supprimerEltIteration();//Enlever le client du bus 
            nbrClientArrive++; //Incrementer le nombre de clients arrivés à destination
            
           }
          
        }
 
       
      //2- Embarquer les clients
        while(!this->atteintCapMaximal() && stations->embarquer(this->stationActuelle,&c))
        {//Tanque je n'ai pas atteint ma limite, et la station n'est pas vide
  
         this->nbrClients++;   
         clients.emfiler(c);   //Mettre le client en attente dans le bus
         printf("[Bus]: embarque le passager {%u} de la station {%u} \n" ,c.id, this->stationActuelle); 
         
        }   
    
   
       
     //3- Envoyer le rendez-vous vers le verificateur et l'informer du nombre de clients arrivés à destination
      verificateur->rendezVousBus(nbrClientArrive); 
     
     //4- Avancer dans les stations
      this->avancer();
  
  }
 }

//____________________________________________________________________//


//______________Fonction pour avancer dans les stations______________//
 
 void Autobus::avancer()
 {
  this->stationActuelle=(this->stationActuelle+1)%5;
 }

//___________________________________________________________________//

//_Fonction vérifiant si on a atteint une capacité maximale pour le bus_//

bool Autobus::atteintCapMaximal()
{ 
 return (this->nbrClients==this->nbrClientsMaximal);
}

//_______________________________________________________________________//

//____________________Fonction qui renvoie le gain du bus__________________//

unsigned Autobus::renvoyerGain()
{ 
 return (this->argent);
}

//_______________________________________________________________________//

  
