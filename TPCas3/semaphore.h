#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#ifndef SemC
 #define SemC

 int sem_create (unsigned,int); // Création d'un groupe de sémaphore
 int sem_delete (int);          // Suppression d'un groupe de sémaphore
 int P (int,unsigned);          // Verrouillage du semaphore
 int V (int,unsigned);          // Liberation du semaphore

#endif

