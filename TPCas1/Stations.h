#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include "structuredonnees.h"

using namespace std;
#ifndef stationC

  #define stationC

class Stations 
{ 

  private:


    //Les files d'attentes des differentes stations

           Liste  m_station0 ;
           Liste  m_station1 ;
           Liste  m_station2 ;
           Liste  m_station3 ;
           Liste  m_station4 ;
           Liste  m_station5 ;
           Liste  m_station65;
           Liste  m_station67;
           Liste  m_station7 ;        
           
             int  prochainChamps(string&);            // Retourner la valeur du prochain champs du fichier
   
  public:
  
             int  remplirStations (ifstream*);        //Remplir les files d'attente avec le fichier d'entrée    
            bool  embarquer(unsigned,client*);        //Embarquer un client 
            void  debarquer(unsigned, client);        //Debarquer un client
           Liste* retourner_station(int num_station); //Retourner une file d'attente 
        

         
};

#endif
