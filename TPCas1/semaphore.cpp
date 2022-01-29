#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semaphore.h"

//___________Création d'un groupe de sémaphores___________//

int sem_create (unsigned numSemaphore, int initval)
{   
        int semid = semget (500, numSemaphore, IPC_CREAT | 0666);
        if (semid == -1) return -1;
        if (semctl (semid, 0, SETVAL, initval) == -1) return -1;
        return semid;
}

//_______________________________________________________//

//_________Suppression d'un groupe de sémaphore__________//

int sem_delete ( int semid)
{
        return semctl (semid , 0 , IPC_RMID , 0) ;
}

//______________________________________________________//

//______________Verouillage d'un sémaphore______________//

int P (int semid,unsigned sem_num)
{
        struct sembuf sempar;
        sempar.sem_num = sem_num;
        sempar.sem_op = -1;
        sempar.sem_flg = 0;
        return semop (semid , &sempar , 1);
}

//______________________________________________________//

//______________Libération d'un sémaphore_______________//

int V (int semid,unsigned sem_num)
{
        struct sembuf sempar;
        sempar.sem_num = sem_num;
        sempar.sem_op = 1;
        sempar.sem_flg = 0;
        return semop (semid , &sempar , 1);
}

//_____________________________________________________//


