#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "structuredonnees.h"

//________________Constructeur de Liste________________//

   Liste::Liste()
   {
    tete=NULL;
    queue=NULL;
    iterateur=NULL;
    suivant=NULL; 
   }

//____________________________________________________//


//_____Methode pour verifier si la liste est vide____//

bool Liste::listevide()
{ 
 return (tete==NULL);
}

//__________________________________________________//

//_____Methode qui renvoie la tete de la liste______//

list* Liste::renvoieTete()
{
  return tete;
}
//__________________________________________________//

//_____Methode qui renvoie la tete de la liste______//

list* Liste::renvoieQueue()
{
  return queue;
}
//__________________________________________________//

//_______________Methode d'empilement_______________// 
void Liste::empiler(client c)
{
 list* p;
 
 p=(list*)malloc(sizeof(list));
 p->Client=c;
 p->prc=NULL;
 p->svt=renvoieTete();
 if(listevide())
 {
  this->queue=p;  
 }else{
  this->tete->prc=p;
  if(renvoieQueue()->prc==NULL)
  {
   this->queue->prc=renvoieTete();
  }
 }
 this->tete=p;

}
//_________________________________________________//

//_______________Methode d'emfilement_______________//
void Liste::emfiler(client c)
{
 list* p;
 
 p=(list*)malloc(sizeof(list));
 p->Client=c;
 p->svt=NULL;
 p->prc=this->queue;
 if(listevide())
 {
  this->tete=p;  
 }else{
  if(this->tete->svt==NULL)
  {
   p->prc=tete;
  }
  this->queue->svt=p;
  
 }
 this->queue=p;

}
//_________________________________________________//

//_______________Methode de depilement_______________//
client Liste::depiler()
{
  client c;list*p;
  
  p=renvoieTete();
  c=p->Client;
  if(!listevide())
  { 
   p=p->svt;
   if(p!=NULL)
    p->prc=NULL;
   else
    this->queue=NULL;

   free(renvoieTete());
   this->tete=p;
  }
  return c;
}
//_________________________________________________//

//______________Methode de defilement______________//
client Liste::defiler()
{
  client c;list*p;
  
  p=renvoieQueue();
  c=p->Client;
  if(!listevide())
  { 
   p=p->prc;
   if(p!=NULL)
    p->svt=NULL;
   else
    this->tete=NULL;
   free(renvoieQueue());
   this->queue=p;
  }
  return c;
}
//__________________________________________________//


//_______Methode de suppression d'une element_______//
void Liste::supprimerElement(list* elt)
  { 
    list *ptr; 
    
    if(elt->prc!=NULL){
            ptr=elt->prc;
            ptr->svt=elt->svt;
            free(elt);
            elt=ptr->svt;
            if(ptr->svt==NULL)
            {
             this->queue=ptr;
            }
          }else if(elt->svt!=NULL){
           ptr=elt->svt;
           ptr->prc=NULL;
           free(elt);
           tete=ptr;
          }else{ 
                this->tete=NULL;
                this->queue=NULL; 
                free(elt);
               }
           
           
   
  }
//__________________________________________________//

//_____Methode d'initialisation d'une itération_____//
void Liste::initialiserIteration()
{
 iterateur=tete;
 suivant=NULL; 
 if(tete!=NULL)
  suivant=tete->svt;
}
//__________________________________________________//

//_____Methode de renvoie d'un element d'une itération_____//
client Liste::renvoyerEltIteration()
{
   client c;
   c.id=1000;
   if(this->iterateur!=NULL)
     c=iterateur->Client;
   return c;
}
//__________________________________________________//

//_____Methode de renvoie d'un element d'une itération_____//
void Liste::modifierEltIteration(client c)
{
  if(this->iterateur!=NULL) 
   iterateur->Client=c;
   
}
//__________________________________________________//

//_____Methode pour avancer dans l'itération_____//
void Liste::suivantIteration()
{
  list* p=this->suivant;
  this->iterateur=this->suivant;
  if(this->suivant!=NULL)
    this->suivant=p->svt;
}
//__________________________________________________//

//_____Methode de suppression d'un element d'une itération_____//
void Liste::supprimerEltIteration()
{
  
    list *ptr; client c;
    
   
    
    if(iterateur->prc!=NULL)
    {
     ptr=iterateur->prc;
     ptr->svt=iterateur->svt;
     
     if(ptr->svt==NULL)
       this->queue=ptr;
     else
       ptr->svt->prc=ptr;
             
     this->suivant=ptr->svt;
                  
    }else if(iterateur->svt!=NULL){
      ptr=iterateur->svt;
      ptr->prc=NULL;
      this->tete=ptr;
      this->suivant=ptr;
    }else{ 
      this->tete=NULL;
      this->queue=NULL; 
      this->suivant=NULL;
    }

     free(this->iterateur);
                 
 
}
//__________________________________________________//

//__Methode verifiant si une iteration est finie__//
bool Liste::finiIteration()
{
  return(this->iterateur==NULL);
}

//______________________________________________//


