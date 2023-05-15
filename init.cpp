#include "bank.h"
#include <iostream>
#include <sys/shm.h>

// Create a bank with the given number of accounts and maximum balance
bank_struct* create_bank(int num_accounts, int max_balance){
    if(num_accounts <= 0){
        std::cout << "Number of accounts should be greater than 0\n";
        return 0;
    }

    key_t key = ftok("bank.h", 'R');
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    // Create or get the shared memory segment
    int shmid = shmget(key, sizeof(bank_struct) + num_accounts * sizeof(account_struct), IPC_CREAT | 0666);
    if (shmid == -1) {
	    if(errno != EEXIST){
		    std::cerr << "shmget: share memory segment already exists" << std::endl;
	    }else{
        	perror("shmget");
	    }
	    exit(1);
    }

    // Attach the shared memory segment
    void* shm = (char *)shmat(shmid, nullptr, 0);
    if (shm == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    // Set up the bank structure and account data within the shared memory segment
    bank_struct *my_bank = (bank_struct*) shm;
    account_struct *accounts = (account_struct*) ((char*) shm + sizeof(bank_struct));

    my_bank->accounts_num = num_accounts;

    for(int i = 0; i < num_accounts; ++i) {
        my_bank->accounts[i].balance = 50;
        my_bank->accounts[i].min_bal = 0;
        my_bank->accounts[i].max_bal = max_balance;
        my_bank->accounts[i].frozen = false;
    }
    return my_bank;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        perror("Not enough args\n");
        exit(1);
    }

    int num_accounts, max_bal;
    num_accounts = std::atoi(argv[1]);
    max_bal = std::atoi(argv[2]);

    // Create the bank
    bank_struct *my_bank = create_bank(num_accounts, max_bal);

    // Call the client function
    client(my_bank);

    return 0;
}