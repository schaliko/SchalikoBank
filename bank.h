//#pragma once
#ifndef BANK
#define BANK

struct account_struct {
    double balance;
    double min_bal;
    double max_bal;
    bool frozen;
};

struct bank_struct {
    int accounts_num;
    account_struct accounts[100];
};

void display(const bank_struct *my_bank, int acc_num);

bank_struct *create_bank(int num_accounts, int max_bal);

void client(bank_struct *my_bank);

void freeze(bank_struct *my_bank, int acc_num);

void transfer(bank_struct *my_bank, int account1, int account2, int money);

void update_account_balance(bank_struct *my_bank, int money, int option);

void update_min_balance(bank_struct *my_bank, int acc_num, int new_min_balance);

void update_max_balance(bank_struct* my_bank, int account_num, int new_max_balance);

#endif