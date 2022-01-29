#include "Stations.h"
#include "structuredonnees.h"
#ifndef verificateurT
#define verificateurT

class Verificateur

{
 private:
             Stations* m_stations;         // l'objet Stations
                  int  socket;             // Socket pour communiquer entre le taxi et le verificateur
                  int  tabParcours[9];     // Tableau contenant l'ordre de parcours des files d'attente     
             unsigned  NbrClientsRestant;  // Nombre de  clients restants à transporter
                  int  DebarquementTrain;  // Nombre des clients débarqués à destination par le train pendant l'itération   
                  int  DebarquementBus;    // Nombre des clients arrivés à destination par le bus pendant l'itération
             unsigned  argent;             // Compter l'argent pris pour le transfert vers les taxis
                  int  semaphore;          // Ensemble des semaphores privés utilisés par le verificateur. 
const static unsigned  semPVerificateur=0; // Numero du semaphore privé RDV du verificateur
const static unsigned  semPTrain=1;        // Numero du semaphore privé RDV du train 
const static unsigned  semPBus=2;          // Numero du semaphore privé RDV du bus 
   


 public:
                       Verificateur (Stations*,int,unsigned); //Le constructeur
                 void  mettre_ds_socket(client clt);      //Mettre le client ctl dans le pipe
                 void  lancerVerificateur();	               //Lancer le verificateur
                 void  rendezVousBus(int);		       //RDV du bus  				
                 void  rendezVousTrain(int);                   //RDV du train
                 bool  finiSimulation();                       //Esque la simulation est terminé?
             unsigned  renvoyerGain();                         //Gain pour le transfert vers les taxis pendant la simulation 


};
#endif
