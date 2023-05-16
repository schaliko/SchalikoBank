#include "bank.h"
#include <iostream>
#include <sys/shm.h>

// Function to destroy the shared memory segment
void *destroy_bank(){
    // Generate a unique key for the shared memory segment
    key_t key = ftok("shm_file.txt", 'R');
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    // Get the shared memory segment associated with the key
    int shmid = shmget(key, sizeof(bank_struct), IPC_CREAT | 0666);
    if (shmid == -1) {
	    if(errno != EEXIST){
		    std::cerr << "shmget: share memory segment already exists" << std::endl;
	    }else{
        	perror("shmget");
	    }
	    exit(1);
    }

    // Destroy the shared memory segment
    int destroy = shmctl(shmid, IPC_RMID, nullptr);
    if (destroy == -1) {
        perror("shmctl");
        exit(1);
    }

    std::cout << "MEMORY DELETED SUCCESSFULLY\n";
    return NULL;
}

int main(){
    // Call the function to destroy the shared memory segment
    destroy_bank();
    exit(0);
}