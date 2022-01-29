#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <stdio.h>
#include "structuredonnees.h"
#include "Stations.h"

#ifndef StationS
  #define StationS
//Les mutexes pour l'accés aux stations O à 5 respectivements
 pthread_mutex_t mutexS0=PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutexS1=PTHREAD_MUTEX_INITIALIZER; 
 pthread_mutex_t mutexS2=PTHREAD_MUTEX_INITIALIZER; 
 pthread_mutex_t mutexS3=PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutexS4=PTHREAD_MUTEX_INITIALIZER;  
 pthread_mutex_t mutexS5=PTHREAD_MUTEX_INITIALIZER;    
 
//_________Fonction qui retourne le prochain champs du fichier_________//
 
 int Stations::prochainChamps(string &ligne)
 {
  ligne=ligne.substr(ligne.find_first_of(' ')+1);
  return atoi(ligne.c_str()); 
 }
 
//____________________________________________________________________//

//____Fonction qui mets les clients du fichiers dans les stations_____//

 int Stations::remplirStations (ifstream *fichier)
 {
    string ligne;
    int nbClient;
    client clt;
  
    getline(*fichier, ligne);
    nbClient=atoi(ligne.c_str()); //Récupérer le nombre des clients 
   
   for(int i=0; i<nbClient; i++) //Tant qu'il y'a des clients 
    {
         
        getline(*fichier,ligne); //Récupérer la ligne
     
      //Recuperation des différentes champs du client 
        clt.id=prochainChamps(ligne);
        clt.station_debut=prochainChamps(ligne);
        clt.station_fin=prochainChamps(ligne);
        clt.tmp_att=prochainChamps(ligne);
        clt.transfert=prochainChamps(ligne);
        clt.tmp_max=prochainChamps(ligne);
   
      //Mettre le client dans sa file d'attente appropriée   
        if(clt.station_debut!=6)
         retourner_station(clt.station_debut)->emfiler(clt);
        else if(clt.station_fin==7)
              retourner_station(67)->emfiler(clt);
             else
             retourner_station(65)->emfiler(clt);
    }
  return nbClient;     
 }

//___________________________________________________________________//

//_________Fonction pour embarquer un client d'une stations__________//

 bool Stations::embarquer(unsigned num_station, client *c)
 {          
               if(retourner_station(num_station)->listevide())  
                   return false; //Retourne faux s'il n'y aucun client à embarquer 
 
               else   switch  (num_station)
                                      {      
                                        case 0: 
                                                 pthread_mutex_lock( &mutexS0 );  
                                                         *c=m_station0.defiler();
                                                 pthread_mutex_unlock( &mutexS0 ); 
                                                 break;            
                                                 
                                        case 1:  pthread_mutex_lock( &mutexS1 );  
                                                        *c=m_station1.defiler();
                                                 pthread_mutex_unlock( &mutexS1 ); 
                                                 break;            
                                                 
                                        case 2:  pthread_mutex_lock( &mutexS2 );  
                                                         *c=m_station2.defiler();
                                                 pthread_mutex_unlock( &mutexS2); 
                                                 break;            
                                            
                                        case 3:  pthread_mutex_lock( &mutexS3 );  
                                                         *c=m_station3.defiler();
                                                 pthread_mutex_unlock( &mutexS3 ); 
                                                  
                                                 break;          
                                                
                                        case 4:  pthread_mutex_lock( &mutexS4 );  
                                                         *c=m_station4.defiler();
                                                 pthread_mutex_unlock( &mutexS4); 
                                                            
                                                 break;
                                        case 5:  
                                                 pthread_mutex_lock( &mutexS5 ); 
                                                     *c=m_station5.defiler();            
                                                 pthread_mutex_unlock( &mutexS5 ); 
                                                 break;
                                        
                                         case 7:  *c=m_station7.defiler();            break;
                                        case 67:
                                                {
                                                
                                                  *c=m_station67.defiler();
                                                
                                                }
                                                 break;
                                        case 65:{
                                                  *c=m_station65.defiler();
                                                }	
                                                 break;

                                      } 

                 return true; //Retourne vrai si on a embarqué un client
                   


 }

//___________________________________________________________________//

//________Fonction pour débarquer un client dans une station_________//

void Stations::debarquer(unsigned int idStation, client Client)
{
 switch(idStation)
 {
   case 0:
          pthread_mutex_lock( &mutexS0 ); 
           retourner_station(idStation)->emfiler(Client);
          pthread_mutex_unlock( &mutexS0 ); 
          break;

   case 1:
          pthread_mutex_lock( &mutexS1 ); 
           retourner_station(idStation)->emfiler(Client);
          pthread_mutex_unlock( &mutexS1 ); 
          break;

   case 2:
          pthread_mutex_lock(&mutexS2); 
           retourner_station(idStation)->emfiler(Client);
          pthread_mutex_unlock(&mutexS2); 
          break;

   case 3:
          pthread_mutex_lock(&mutexS3); 
           retourner_station(idStation)->emfiler(Client);
          pthread_mutex_unlock(&mutexS3); 
          break;

   case 4:
          pthread_mutex_lock(&mutexS4); 
           retourner_station(idStation)->emfiler(Client);
          pthread_mutex_unlock(&mutexS4); 
          break;

   case 5:
          pthread_mutex_lock(&mutexS5); 
           retourner_station(idStation)->emfiler(Client);
          pthread_mutex_unlock(&mutexS5); 
          break;

  default:
          retourner_station(idStation)->emfiler(Client);
 }

} 

//___________________________________________________________________//

//_____Fonction qui retourne un pointeur vers une station donnée_____//

Liste* Stations::retourner_station(int num_station) 
{

     switch(num_station){
                                                                case 0:  return &m_station0;       break;
                                                                case 1:  return &m_station1;       break;
                                                                case 2:  return &m_station2;       break;
                                                                case 3:  return &m_station3;       break;
                                                                case 4:  return &m_station4;       break;
                                                                case 5:  return &m_station5;       break;
                                                                
                                                                case 65:{
                                                 
                                                                         return &m_station65;     break;
                                                
                                                                         }
                                                                case 67:
                                                                         {
                                                 
                                                                         return &m_station67;     break;
                                                 
                                                                         }
                                                                case 7:  return &m_station7;       
               
                       }



}

//___________________________________________________________________//

#endif

