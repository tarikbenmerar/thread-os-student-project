
/*_________Structure de données du TP System________*/

/*________________Structure client__________________*/

#ifndef clientC
 #define clientC
 struct client{
                     int id;
                unsigned station_fin; 
                unsigned station_debut; 
                    bool transfert;
                unsigned tmp_att;  
                unsigned tmp_max;                          
              };

#endif

/*________________________________________________*/

/*________________Structure liste_________________*/

#ifndef listClient
 #define listClient
  struct list
             { 
                client Client;
                list *svt;
                list *prc; 
             };

#endif

/*________________________________________________*/

/*___________________Classe Liste_________________*/
#ifndef ListClient
 #define ListClient
 class Liste 
 {
   //Les attributs
   private:        
           list* tete; // La tete de la liste
           list* queue; // la queue de la liste
           list* iterateur;//Utilisé pour l'itération dans la liste
           list* suivant;//Le prochain element de l'itération
     
   //Les méthodes
    public:   
                   Liste();
              bool listevide();
             list* renvoieTete();   // Renvoie le premier element de la liste
             list* renvoieQueue();  // Renvoie le dernier element de la liste  
              void empiler(client);
              void emfiler(client); 
            client depiler();
            client defiler();
              void supprimerElement(list* elt);
              void initialiserIteration(); //Initialiser l'itération sur le premier element de la liste
            client renvoyerEltIteration(); //renvoyer l'element de l'itération
              void modifierEltIteration(client);//Modifier l'élément courant 
              void suivantIteration(); //Avancer dans l'itération
              void supprimerEltIteration(); //Supprimer l'élément courant de l'itération
              bool finiIteration();// Verifier si l'iteration est finie   
 };
#endif
/*________________________________________________*/

