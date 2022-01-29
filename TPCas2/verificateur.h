#include "Stations.h"
#include "structuredonnees.h"

#ifndef verificateurT
#define verificateurT

class Verificateur

{
 private:
            Stations* m_stations;        // l'objet Stations
                 int* m_pipe;            // Pipe entre le taxi et le verificateur
                 int  tabParcours[9];    // Ensemble des semaphores privés utilisés par le verificateur.      
            unsigned  nbrBus;            // Nombre de bus pendant la simulation
            unsigned  NbrClientsRestant; // Nombre de client restant à débarquer
                 int  DebarquementTrain; // Nombre des clients débarqués à destination pour le train pendant l'itération   
                 int* DebarquementBus;   // Nombre des clients débarqués à destination pour chaque bus pendant l'itération 
             unsigned argent;            // Compter l'argent pris pour le transfert vers les taxis
                  int semaphore;         // Ensemble des semaphores privés utilisés par le verificateur. 
const static unsigned semPVerificateur=0;// Numero de semaphore privé RDV du verificateur
const static unsigned semPTrain=1;       // Numero de semaphore privé RDV du train 
const static unsigned semPBus=2;         // Numero de semaphore privé RDV du premier bus 

 public:
             Verificateur (Stations*,int*,unsigned,unsigned); //Le constructeur
        void mettre_ds_mem_partage(client clt);               //Mettre le client ctl dans le pipe
        void lancerVerificateur();	                      //Lancer le verificateur
        void rendezVousBus(unsigned, unsigned);		      //RDV des bus	  			
        void rendezVousTrain(unsigned);                       //RDV du train
        bool finiSimulation();                                //Esque la simulation s'est terminé?
    unsigned  renvoyerGain();                                 //Gain pour le transfert vers les taxis pendant la simulation 

};
#endif
