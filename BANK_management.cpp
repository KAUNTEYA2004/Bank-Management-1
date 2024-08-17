#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(string t, double a, string d) : type(t), amount(a), date(d) {}
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount, const string& date) {
        if (amount > 0) {
            balance += amount;
            transactions.push_back(Transaction("Deposit", amount, date));
            cout << "Deposited $" << amount << " on " << date << ". New balance: $" << balance << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void withdraw(double amount, const string& date) {
        if (amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                transactions.push_back(Transaction("Withdrawal", amount, date));
                cout << "Withdrew $" << amount << " on " << date << ". New balance: $" << balance << endl;
            } else {
                cout << "Insufficient funds for withdrawal." << endl;
            }
        } else {
            cout << "Withdrawal amount must be positive." << endl;
        }
    }

    void displayStatement() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Transaction History:" << endl;
        for (const auto& txn : transactions) {
            cout << txn.date << " - " << txn.type << ": $" << txn.amount << endl;
        }
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount(int accNum, double initialBalance) {
        accounts.push_back(Account(accNum, initialBalance));
        cout << "Account created successfully with account number: " << accNum << endl;
    }

    Account* findAccount(int accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    void deposit(int accNum, double amount, const string& date) {
        Account* acc = findAccount(accNum);
        if (acc) {
            acc->deposit(amount, date);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void withdraw(int accNum, double amount, const string& date) {
        Account* acc = findAccount(accNum);
        if (acc) {
            acc->withdraw(amount, date);
        } else {
            cout << "Account not found." << endl;
        }
    }

    void checkBalance(int accNum) {
        Account* acc = findAccount(accNum);
        if (acc) {
            cout << "Account Number: " << accNum << " has a balance of $" << acc->getBalance() << endl;
        } else {
            cout << "Account not found." << endl;
        }
    }

    void printStatement(int accNum) {
        Account* acc = findAccount(accNum);
        if (acc) {
            acc->displayStatement();
        } else {
            cout << "Account not found." << endl;
        }
    }
};

int main() {
    Bank bank;
    int choice, accNum;
    double amount;
    string date;

    while (true) {
        cout << "\nBank Management System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Print Statement" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter initial balance: ";
                cin >> amount;
                bank.createAccount(accNum, amount);
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                bank.deposit(accNum, amount, date);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                bank.withdraw(accNum, amount, date);
                break;
            case 4:
                cout << "Enter account number: ";
                cin >> accNum;
                bank.checkBalance(accNum);
                break;
            case 5:
                cout << "Enter account number: ";
                cin >> accNum;
                bank.printStatement(accNum);
                break;
            case 6:
                cout << "Exiting the system." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
