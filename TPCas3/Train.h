#include "Stations.h"
#include "verificateur.h"

class Train
{  
 private :
          unsigned fileActuelle;      //File actuelle du train
          Stations *stations;         //Pour Embarquer/Debarquer dans les stations
          Verificateur* verificateur; //Pour faire le RDV avec le verificateur 
          Liste clients;              //Liste  des clients à bord
          unsigned nbrClients;        //Nombre de clients à bord
          static unsigned const nbrClientsMaximal=8; //Capacité du train
          unsigned argent;            //Compter l'argent du transport     
          
 public :
                  Train(Stations*,Verificateur*);
             void avancer();           //Avancer dans la station suivante
             void lancertrain();       //Thread du train
             bool atteintCapMaximal(); //Esque le train est plein?
         unsigned stationActuelle();   //Renvoyer la station actuelle correspondante à la file actuelle
         unsigned renvoyerGain();      //Gain du train pendant la simulation 
};   
