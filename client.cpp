#include <iostream>
#include "bank.h"

// Function to validate the given account number
int validate_account_number(bank_struct *my_bank, int account_num) {
    // Continue looping until a valid account number is provided
    while (account_num < 0 || account_num >= my_bank->accounts_num) {
        std::cout << "Invalid account number. Please try again.\n";
        std::cout << "Enter account number: ";
        std::cin >> account_num;
    }
    return account_num;
}

// int check_account_number(bank_struct *my_bank){
//     int account_number;
    
//     // Continue looping until a valid account number is provided
//     while(true){
//         std::cout << "Enter account number: ";
//         std::cin >> account_number;
//         if(account_number >= my_bank->accounts_num){
//             std::cout << "Incorrect account number. Please try again.\n";
//             continue;
//         }
//         break;
//     }
//     return account_number;
// }

// Function to validate and return the account number
int validate_account_number(bank_struct* my_bank) {
    int account_number;

    do {
        std::cout << "Enter account number: ";
        std::cin >> account_number;

        if (account_number < 0 || account_number >= my_bank->accounts_num) {
            system("clear");
            std::cout << "Invalid account number. Please try again.\n";
        }
    } while (account_number < 0 || account_number >= my_bank->accounts_num);

    return account_number;
}

void client(bank_struct *my_bank){
    while(true){
        std::cout << "\n1) Display account balance (current/minimum/maximum)\n";
        std::cout << "2) Freeze/Unfreeze an account\n";
        std::cout << "3) Transfer money from one account to another\n";
        std::cout << "4) Add/Remove money from all accounts\n";
        std::cout << "5) Set minimum/maximum balance for an account\n";
        std::cout << "6) Exit\n";
        std::cout << "Enter option: ";
        
        std::string option;
        std::cin >> option;

        if(option == "1"){
            int account_number = validate_account_number(my_bank);
            display(my_bank, account_number);
            continue;
        }
        else if(option == "2"){
            int account_number = validate_account_number(my_bank);
            freeze(my_bank, account_number);
            continue;
        }
        else if(option == "3"){
            int account_number1, account_number2;
            std::cout << "Enter first account number: ";
            std::cin >> account_number1;
            account_number1 = validate_account_number(my_bank, account_number1);

            std::cout << "Enter second account number: ";
            std::cin >> account_number2;
            account_number1 = validate_account_number(my_bank, account_number1);

            std::cout << "Enter amount to transfer: ";
            int amount;
            std::cin >> amount;
            
            transfer(my_bank, account_number1, account_number2, amount);
            continue;
        }
        else if(option == "4"){
            std::cout << "Choose an action:\n";
            std::cout << "1) Add money to all accounts\n";
            std::cout << "2) Remove money from all accounts\n";
            std::cout << "Option: ";

            int action;
            std::cin >> action;

            std::cout << "Enter the amount of money: ";
            int amount;
            std::cin >> amount;

            update_account_balance(my_bank, amount, action);
            continue;
        }
        else if(option == "5"){
            std::cout << "Choose an action:\n";
            std::cout << "1) Set new maximum balance for an account\n";
            std::cout << "2) Set new minimum balance for an account\n";
            std::cout << "Option: ";

            int action;
            std::cin >> action;

            if(action == 1){
                int account_number;
                std::cout << "Enter account number: ";
                std::cin >> account_number;

                int maximum_balance;
                std::cout << "Enter new maximum balance: ";
                std::cin >> maximum_balance;

                update_max_balance(my_bank, account_number, maximum_balance);
                continue;
            }
            if(action == 2){
                int account_number;
                std::cout << "Enter account number: ";
                std::cin >> account_number;

                int minimum_balance;
                std::cout << "Enter new minimum balance: ";
                std::cin >> minimum_balance;

                update_min_balance(my_bank, account_number, minimum_balance);
                // continue;
            }
            else {
                std::cout << "Invalid option. Please try again.\n";
            }
        }
        else if(option == "6"){
            break; // Exit the loop and end the function
        }
        else{
            std::cout << "Invalid option. Please try again.\n";
            continue;
        }
    }
}