#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>



int main() {
    int shmid;
    int *X;
    key_t key = ftok("/Desktop/oslab", 'E');
    key_t skeya = ftok("/Desktop/oslab", 'F');
    key_t skeyb = ftok("/Desktop/oslab", 'G');
    //create shared memory using shmget
    // returns the identifier of the shared space corresp to key, min size of integer and ipc_creat flag to create the shared space
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666) ;
    //X will now be associated with the shared space, In shmid space, it will access the first available space and X stores that address, NULL pointer is given we do not need any particular flag here, we just need to access the memory, so 0 is given as a flag
    X = shmat(shmid, NULL, 0);
    *X = 0;
    int semA, semB;
    //semget will create a semaphore for the key skeya, number of semaphores is 1, and it creates new space using the ipc_creat flag
    semA = semget(skeya, 1, IPC_CREAT | 0666);
    
    semB = semget(skeyb, 1, IPC_CREAT | 0666);

   //semctrl will access the semA, 0 is the number of the semaphore in the semA semaphore - it is an array like data structure so we access the first semaphore using 0, then we set the valuew to 1
    semctl(semA, 0, SETVAL, 1); 
    semctl(semB, 0, SETVAL, 1); 

  
    pid_t childA = fork();
    if (childA == 0) {
        // Process A
        for (int i = 0; i < 100000; i++) {
            
            struct sembuf wait = {0, -1, 0};
            //sembuf struct has semnum, semoperaton, semflag
            // 0 - first semaphore, -1 is the operation which will decrease the semA value.
            semop(semA, &wait, 1);
            //semop has semid, then accesses the sembuf struct wait and then does the operation of decreasing to one semaphore

            (*X)++; 
            if(i%25000==0) 
            usleep(2);
            
            
            struct sembuf signal = {0, 1, 0};
            semop(semA, &signal, 1);
        }
        return 0;
    }


    pid_t childB = fork();
    if (childB == 0) {
        // Process B
        for (int i = 0; i < 100000; i++) {
           
            struct sembuf wait = {0, -1, 0};
            semop(semB, &wait, 1);

            (*X)--; 
            //if(i%25000==0) 
            //usleep(2);

         
            struct sembuf signal = {0, 1, 0};
            semop(semB, &signal, 1);
        }
        return 0;
    }

    
    wait(NULL);
    wait(NULL);

 
    printf("Final value of X: %d\n", *X);

   
    shmdt(X);
    shmctl(shmid, IPC_RMID, NULL);

   
    semctl(semA, 0, IPC_RMID);
    semctl(semB, 0, IPC_RMID);

    return 0;
}
