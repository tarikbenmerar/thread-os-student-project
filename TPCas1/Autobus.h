#include "Stations.h"
#include "verificateur.h"

#ifndef autobusT
 #define autobusT

class Autobus
{  
 private :  
          unsigned int stationActuelle; //Station actuelle du bus
          Stations *stations;           //Pour Embarquer/Debarquer dans les stations
          Verificateur *verificateur;   //Pour faire le RDV avec le verificateur 
          Liste clients;                //Liste des clients à bord
          unsigned nbrClients;          //Nombre de clients à bord
          static unsigned const nbrClientsMaximal=5; //Capacité du bus
          unsigned argent;              //Compter l'argent du transport             

 public :
         Autobus(Stations*,Verificateur*,unsigned);//Le constructeur
         void avancer();           //Avancer dans la station suivante
         void lancerautobus();     //Thread du bus
         bool atteintCapMaximal(); //Esque le bus est plein?
     unsigned renvoyerGain();      //Gain du bus pendant la simulation 
};
   
#endif
