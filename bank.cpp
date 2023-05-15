#include <iostream>
#include "bank.h"
#include <string>

// Display the details of an account
void display(const bank_struct *my_bank, int acc_num) {
    if(acc_num >= my_bank->accounts_num) {
        std::cout << "Invalid account number\n";
        return;
    }
    system("clear");
    std::string status;

    // Determine the account status (frozen or not frozen)
    if(my_bank->accounts[acc_num].frozen == true){
        status = "frozen";
    }
    else{
        status = "not frozen";
    }

    // Display the account info
    std::cout << "\naccount number: " << acc_num << ", balance: " <<  my_bank->accounts[acc_num].balance << "$, minimum balance: " <<  my_bank->accounts[acc_num].min_bal << "$, maximum balance: " << 
            my_bank->accounts[acc_num].max_bal << "$, account status: " << status << std::endl;
}

// Freeze or unfreeze an account
void freeze(bank_struct *my_bank, int acc_num) {
    if(acc_num >= my_bank->accounts_num) {
        std::cout << "Invalid account number\n";
        return;
    }

    while(true){
        std::cout << "\nChoose an option\n";
        std::cout << "1) Freeze an account" << std::endl << "2) Unfreeze an account" << std::endl << "option:";
        int option;
        std::cin >> option;
        if(option == 1){
            if(my_bank->accounts[acc_num].frozen == true){
                system("clear");
                std::cout << "This account is already frozen\n";
                break;
            }
            my_bank->accounts[acc_num].frozen = true;
            system("clear");
            std::cout << "This account has been frozen\n";
            break;
        }
        else if(option == 2){
            if(my_bank->accounts[acc_num].frozen == false){
                system("clear");
                std::cout << "This account is already unfrozen\n";
                break;
            }
            my_bank->accounts[acc_num].frozen = false;
            system("clear");
            std::cout << "This account has been unfrozen\n";
            break;
        }
        else{
            std::cout << "Try Again";
            continue;
        }
        break;
    }
}

// Transfer money from one account to another
void transfer(bank_struct *my_bank, int account1, int account2, int money) {
    if(account1 >= my_bank->accounts_num || account2 >= my_bank->accounts_num) {
        std::cout << "Invalid account number\n";
        return;
    }
    if(my_bank->accounts[account1].frozen || my_bank->accounts[account2].frozen) {
        std::cout << "There is a frozen account, try again\n";
        return;
    }
    if(my_bank->accounts[account1].balance - money < my_bank->accounts[account1].min_bal) {
        std::cout << "Balance can't be less than minimum balance\n";
        return;
    }

    if(my_bank->accounts[account2].balance + money > my_bank->accounts[account2].max_bal) {
        std::cout << "Balance can't be more than maximum balance\n";
        return;
    }

    // Perform the transfer
    my_bank->accounts[account1].balance -= money;
    my_bank->accounts[account2].balance += money;
    system("clear");
    std::cout << "Transferred: " << money << "$ from "<< account1 << " to " << account2 << std::endl;
}

// Update the balance of multiple accounts
void update_account_balance(bank_struct *my_bank, int money, int option){
if(money <= 0){
        std::cout << "Invalid account number\n";
        return;
    }
    
    if(option == 1){
        system("clear");
        for(int i = 0; i < my_bank->accounts_num; ++i){
            if(my_bank->accounts[i].frozen == true){
                std::cout << "Skipping account: " << i << " (frozen)\n";
                continue;
            }
            if(my_bank->accounts[i].balance + money > my_bank->accounts[i].max_bal && my_bank->accounts[i].frozen != true){ // second argument for additional protection
                std::cout << "Skipped adding money to account: " << i << " (reached maximum balance limit)\n";
                continue;
            }
            my_bank->accounts[i].balance += money;
            std::cout << "Money added successfully to account: " << i << "\n";
        }
        return;
    }

    else if(option == 2){
        system("clear");
        for(int i = 0; i < my_bank->accounts_num; ++i){
            if(my_bank->accounts[i].frozen == true){
                std::cout << "Skipping account: " << i << " (frozen)\n";
                continue;
            }
            if(my_bank->accounts[i].balance - money < my_bank->accounts[i].min_bal && my_bank->accounts[i].frozen != true){ // second argument for additional protection
                std::cout << "Skipped withdrawing money from account: " << i << " (reached minimum balance limit)\n";
                continue;
            }
            my_bank->accounts[i].balance -= money;
            std::cout << "Money withdrawn successfully from account: " << i << "\n";
        }
        return;
    }
}

// Update the minimum balance of an account
void update_min_balance(bank_struct *my_bank, int acc_num, int new_min_balance){
    if(acc_num >= my_bank->accounts_num){
        std::cout << "Invalid account number\n";
        return;
    }
    if(my_bank->accounts[acc_num].balance < new_min_balance){
        std::cout << "Failed to set minimum balance: current balance is less than the new minimum balance\n";
        return;
    }
    my_bank->accounts[acc_num].min_bal = new_min_balance;
    system("clear");
    std::cout << "Minimum balance has been successfully set\n";
    return;
}

// Update the maximum balance of an account
void update_max_balance(bank_struct* my_bank, int acc_num, int new_max_balance) {
    if(acc_num >= my_bank->accounts_num){
        std::cout << "Invalid account number\n";
        return;
    }
    if(my_bank->accounts[acc_num].balance > new_max_balance){
        std::cout << "Failed to update maximum balance: the current balance exceeds the new maximum balance\n";
        return;
    }
    my_bank->accounts[acc_num].max_bal = new_max_balance;
    system("clear");
    std::cout << "Maximum balance updated successfully\n";
    return;
}