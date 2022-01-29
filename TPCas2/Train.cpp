#include <cstdlib>
#include <iostream>
#include "stdio.h"
#include "structuredonnees.h"
#include "Train.h"
#include "Stations.h"
#include "verificateur.h"

//______________Constructeur de la classe Train_________________//

 Train::Train(Stations* stations,Verificateur* verificateur)
{ 
     
     this->stations=stations; 
     this->fileActuelle=5; 
     this->argent=0;
     this->nbrClients=0;
     this->verificateur=verificateur;
     
 }

//________________________________________________________________//

//_____________________Le thread du train_________________________//

 void Train::lancertrain(){
  
  client c;
  int nbrClientArrive; //Pour sauvegarder le nbr de clients arrivés à destination dans la station actuelle

  
  while(!verificateur->finiSimulation())
  { 
     
     printf("[Train]: dans la station %u \n",this->stationActuelle());
     nbrClientArrive=0;//Initialiser le nombre de clients arrivés à destination dans la station actuelle
     
   //1- Debarquer les clients arrivés à déstination
     
       for(clients.initialiserIteration();!clients.finiIteration();clients.suivantIteration())
       { //explorer la liste des clients  
         
          c=clients.renvoyerEltIteration();//Recupérer un client du train
             
          if(this->fileActuelle==5 && c.station_fin>=0 && c.station_fin<=4 )
          {// Client allant station de train 5 vers les stations de bus  
              
             
              //Decrementer le nombre de clients,afficher le debarquement
              //Et compter l'argent pris pour le transport   
               this->nbrClients--;
               printf("[Train]: debarque le passager {%u} dans la station {%u} \n" ,c.id, this->stationActuelle()); 
               this->argent+=30;        
                                           
               if(c.transfert==true)//Verifier la condition du transfert
                {
                    if(c.station_fin!=0)
                    {
                     stations->debarquer(0,c); 
                    }else nbrClientArrive++;//Incrementer le nombre de clients arrivés à destination

                  printf("[Train]: transfert le passager {%u} vers la station {%u} \n",c.id,0);
                  this->argent+=10;  //Compter l'argent du transfert
                
                }else nbrClientArrive++; //Incrementer le nombre de clients arrivés à destination
            
           
             clients.supprimerEltIteration();//Enlever le client du train
             

        }else if(c.station_fin==this->stationActuelle()){//Client arrivés à destination

            //Decrementer le nombre de clients,afficher le debarquement
            //Compter l'argent pris pour le transport

            this->nbrClients--;
            printf("[Train]: debarque le passager {%u} dans la station {%u} \n" ,c.id, this->stationActuelle()); 
            this->argent+=30;
 
            clients.supprimerEltIteration();//Enlever le client du train 
            nbrClientArrive++; //Incrementer le nombre de clients arrivés à destination
         } 
       
       }

     
 
   //2- Embarquer les clients
      while(!this->atteintCapMaximal() && stations->embarquer(this->fileActuelle,&c))
      {//Tanque je n'ai pas atteint ma limite, et la station n'est pas vide

        nbrClients++;
        clients.emfiler(c);   //Mettre le client dans le train
        printf("[Train]: embarque le passager {%u} de la station{%u} \n" ,c.id,this->stationActuelle());
         
      }  
    
   //3- Envoyer le rendez-vous vers le validateur et l'informer du nombre de clients arrivés à destination
     verificateur->rendezVousTrain(nbrClientArrive); 
    
   //4- Avancer dans les stations
     avancer();
  
   }


 }
//______________Fonction pour avancer dans les stations______________//

 void Train::avancer()
 {
  switch (this->fileActuelle)
                               {
                                 case 5:
                                        this->fileActuelle=67;
                                        
                                        break;    
                                case 65:
                                        this->fileActuelle=5;
                                        break;
                                case 67:
                                        this->fileActuelle=7;
                                        break;
                                 case 7:
                                        this->fileActuelle=65;
                                        break;
                               }
}

//___________________________________________________________________//

//_Fonction vérifiant si on a atteint une capacité maximale pour le train_//

 bool Train::atteintCapMaximal()
 { 
  return (this->nbrClients==this->nbrClientsMaximal);
 }

//______________________________________________________________________//
 
//___Fonction retournant la station correspondante à la file actuelle___//
 unsigned Train::stationActuelle()
 {
  if(this->fileActuelle>7)
   return 6;
  else
   return this->fileActuelle;

 }
//_____________________________________________________________________//

//____________________Fonction qui renvoie le gain du train__________________//

unsigned Train::renvoyerGain()
{ 
 return (this->argent);
}

//___________________________________________________________________________//
  
