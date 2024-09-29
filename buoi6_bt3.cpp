#include <iostream>
#include <string>
#include <vector>
//Hệ thống Tài khoản Ngân hàng
class Account {
    protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;

    public:
    Account(std::string number, std::string name, double initialBalance)
        : accountNumber(number), ownerName(name), balance(initialBalance) {}

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Da nap " << amount << " vao tai khoan." << std::endl;
        } else {
            std::cout << "So tien khong hop le." << std::endl;
        }
    }

    virtual bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            std::cout << "Da rut " << amount << " tu tai khoan." << std::endl;
            return true;
        } else {
            std::cout << "Khong the rut tien. So du khong du hoac so tien khong hop le." << std::endl;
            return false;
        }
    }

    virtual void displayInfo() const {
        std::cout << "So tai khoan: " << accountNumber << std::endl;
        std::cout << "Chu tai khoan: " << ownerName << std::endl;
        std::cout << "So du: " << balance << std::endl;
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
    private:
    double interestRate;

    public:
    SavingsAccount(std::string number, std::string name, double initialBalance, double rate)
        : Account(number, name, initialBalance), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * interestRate;
        deposit(interest);
        std::cout << "Da cong lai: " << interest << std::endl;
    }

    void displayInfo() const override {
        Account::displayInfo();
        std::cout << "Lai suat: " << (interestRate * 100) << "%" << std::endl;
    }
};

class CheckingAccount : public Account {
    private:
    double overdraftLimit;

    public:
    CheckingAccount(std::string number, std::string name, double initialBalance, double limit)
        : Account(number, name, initialBalance), overdraftLimit(limit) {}

    bool withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            std::cout << "Da rut " << amount << " tu tai khoan." << std::endl;
            return true;
        } else {
            std::cout << "Khong the rut tien. Vuot qua gioi han thau chi hoac so tien khong hop le." << std::endl;
            return false;
        }
    }

    void displayInfo() const override {
        Account::displayInfo();
        std::cout << "Gioi han thau chi: " << overdraftLimit << std::endl;
    }
};

class Bank {
    private:
    std::vector<Account* > accounts;

    public:
    void addAccount(Account* account) {
        accounts.push_back(account);
    }

    void displayAllAccounts() const {
        for (const auto& account : accounts) {
            account->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }

    ~Bank() {
        for (auto account : accounts) {
            delete account;
        }
    }
};

int main() {
    Bank myBank;

    myBank.addAccount(new SavingsAccount("SA001", "Nguyen Van A", 1000000, 0.05));
    myBank.addAccount(new CheckingAccount("CA001", "Tran Thi B", 2000000, 500000));

    std::cout << "Thong tin tat ca tai khoan:" << std::endl;
    myBank.displayAllAccounts();

    return 0;
}