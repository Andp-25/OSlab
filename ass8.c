#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    int shmid;
    int *X;

    key_t key = ftok("/Desktop/oslab", 'E');
    //create shared memory using shmget
    // returns the identifier of the shared space corresp to key, min size of integer and ipc_creat flag to create the shared space
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666) ;
    //X will now be associated with the shared space, In shmid space, it will access the first available space and X stores that address, NULL pointer is given we do not need any particular flag here, we just need to access the memory, so 0 is given as a flag
    X = shmat(shmid, NULL, 0) ;

    *X = 0; 


    pid_t a = fork();
    if (a == 0) {
        // Process A
        for (int i = 0; i < 100000; i++) {
            (*X)++;
            if(i%25000==0) 
            usleep(2);
        }
        return 0;
    }

  
    pid_t b = fork();
    if (b == 0) {
        // Process B
        for (int i = 0; i < 100000; i++) {
            (*X)--; 
            //if(i%25000==0) 
            //usleep(2);
        }
        return 0;
    }

   
    wait(NULL);
    wait(NULL);

  
    printf("Final value of X: %d\n", *X);
	//shmdt detactches X from the shared space
    shmdt(X);
    //shm control will now remove shmid access to the shared space using the flag IPC_RMID, the struct shmid_buf field is NULL because we need did not access it
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
