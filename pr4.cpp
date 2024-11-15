#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base Class: BankAccount
class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNum, string accHolder, double bal)
        : accountNumber(accNum), accountHolderName(accHolder), balance(bal) {}

    virtual ~BankAccount() {}

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << ". New Balance: $" << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << ". Remaining Balance: $" << balance << endl;
        }
    }

    double getBalance() const {
        return balance;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    virtual void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber
             << ", Holder: " << accountHolderName
             << ", Balance: $" << balance << endl;
    }

    virtual void calculateInterest() const {
        cout << "Interest calculation is not applicable for this account." << endl;
    }
};

// Derived Class: SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string accHolder, double bal, double rate)
        : BankAccount(accNum, accHolder, bal), interestRate(rate) {}

    void calculateInterest() const override {
        double interest = balance * interestRate / 100;
        cout << "Savings Account Interest: $" << interest << endl;
    }
};

// Derived Class: CheckingAccount
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNum, string accHolder, double bal, double overdraft)
        : BankAccount(accNum, accHolder, bal), overdraftLimit(overdraft) {}

    void withdraw(double amount) override {
        if (amount > balance + overdraftLimit) {
            cout << "Withdrawal exceeds overdraft limit!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << ". Remaining Balance: $" << balance << endl;
        }
    }

    void calculateInterest() const override {
        cout << "No interest for checking accounts." << endl;
    }
};

// Derived Class: FixedDepositAccount
class FixedDepositAccount : public BankAccount {
private:
    int term; // in months
    double interestRate;

public:
    FixedDepositAccount(string accNum, string accHolder, double bal, int term, double rate)
        : BankAccount(accNum, accHolder, bal), term(term), interestRate(rate) {}

    void calculateInterest() const override {
        double interest = balance * interestRate / 100 * (term / 12.0);
        cout << "Fixed Deposit Interest for " << term << " months: $" << interest << endl;
    }
};

// Menu-Driven Interface
void menu() {
    vector<BankAccount*> accounts;
    int choice;

    do {
        cout << "\n--- Bank Account Management ---" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Checking Account" << endl;
        cout << "3. Create Fixed Deposit Account" << endl;
        cout << "4. Deposit Money" << endl;
        cout << "5. Withdraw Money" << endl;
        cout << "6. Display Account Info" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string accNum, accHolder;
            double balance, rate;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Account Holder Name: ";
            cin >> accHolder;
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Interest Rate (%): ";
            cin >> rate;

            accounts.push_back(new SavingsAccount(accNum, accHolder, balance, rate));
            cout << "Savings Account created successfully!" << endl;
        } else if (choice == 2) {
            string accNum, accHolder;
            double balance, overdraft;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Account Holder Name: ";
            cin >> accHolder;
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Overdraft Limit: ";
            cin >> overdraft;

            accounts.push_back(new CheckingAccount(accNum, accHolder, balance, overdraft));
            cout << "Checking Account created successfully!" << endl;
        } else if (choice == 3) {
            string accNum, accHolder;
            double balance, rate;
            int term;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Account Holder Name: ";
            cin >> accHolder;
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Term (in months): ";
            cin >> term;
            cout << "Enter Interest Rate (%): ";
            cin >> rate;

            accounts.push_back(new FixedDepositAccount(accNum, accHolder, balance, term, rate));
            cout << "Fixed Deposit Account created successfully!" << endl;
        } else if (choice == 4) {
            string accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            bool found = false;
            for (auto acc : accounts) {
                if (acc->getAccountNumber() == accNum) {
                    acc->deposit(amount);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Account not found!" << endl;
            }
        } else if (choice == 5) {
            string accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            bool found = false;
            for (auto acc : accounts) {
                if (acc->getAccountNumber() == accNum) {
                    acc->withdraw(amount);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Account not found!" << endl;
            }
        } else if (choice == 6) {
            for (auto acc : accounts) {
                acc->displayAccountInfo();
            }
        } else if (choice == 7) {
            for (auto acc : accounts) {
                acc->calculateInterest();
            }
        }
    } while (choice != 8);

    for (auto acc : accounts) {
        delete acc;
    }

    cout << "Exiting system. Goodbye!" << endl;
}

int main() {
    menu();
    return 0;
}
