#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

//EXCEPTION CLASSES\\

//All exception classes are children of standard library exception

class negativeClassException : std::exception { 
private:
    std::string message;
public:
    negativeClassException(const char* msg):message(msg){} //Initialization Constructor of msg
    const char* what() const throw() { //Derived class of Exception
        return message.c_str(); //Return the input of constructor
    }
};

class overdrawExcception : std::exception {
private:
    std::string message;
public:
    overdrawExcception(const char* msg):message(msg){} 
    const char* what() const throw() { 
        return message.c_str(); 
    }
};

class invalidAccountOperationException : std::exception {
private:
    std::string message;
public:
    invalidAccountOperationException(const char* msg) :message (msg){} 
    const char* what() const throw() { 
        return message.c_str(); 
    }
};

//MAIN CLASS\\

//All main functions use the exception classes above

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(std::string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        if (amount > 0 && isActive) {
            std::cout << "Verified for account " << accountNumber << std::endl;
            balance += amount;
        }
        else if (amount > 0 && !isActive)
            //Throw exception for a closed account
            throw invalidAccountOperationException("Account closed.");
        else if (amount < 0 && isActive)
            //Throw exception for neg
            throw negativeClassException("Attempt to enter negative values.");
        else
            //Throw exception for anything else
            throw std::runtime_error("Invalid.");
    }

    // Withdraw method
    void withdraw(double amount) {
        if (balance >= amount && isActive) {
            std::cout << "Verified for account " << accountNumber << std::endl;
            balance -= amount;
        }
        else if (balance >= amount && !isActive)
            throw invalidAccountOperationException("Account closed.");
        else if (balance <= amount && isActive)
            throw overdrawExcception("Attempt to overdraw than available.");
        else
            throw std::runtime_error("Invalid.");
    }

    // Method to get current balance
    double getBalance() const {
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        isActive = false;
    }
};

//DRIVER CODE\\

int main() {
    double request;
    auto account = std::make_unique<BankAccount>("123456", 0); //Initialization
    std::string option;
    std::cout << "Welcome to the bank system. Please enter your starting balance." << std::endl;
    std::cin >> request;
    std::cout << std::endl;
    try {
        std::cout << "Bank Account Created: #" << "123456" << std::endl;
        std::cout << "Depositing " << request << std::endl;
        account->deposit(request);
        std::cout << "Your balance is now: $" << account->getBalance() << std::endl;

        do {
            //Front-end 

            std::cout << std::endl << "Welcome to your bank account. " << std::endl;
            std::cout << "BANK OPTIONS: " << std::endl;
            std::cout << ">Deposit " << std::endl;
            std::cout << ">Withdraw " << std::endl;
            std::cout << ">Balance " << std::endl;
            std::cout << ">Close " << std::endl;
            std::cout << ">Exit " << std::endl;
            std::cin >> option;

            if (option == "Deposit") {
                std::cout << std::endl;
                std::cout << "How much would you like to deposit?" << std::endl;
                std::cin >> request;
                std::cout << "Depositing " << request << std::endl;
                account->deposit(request);
            }
            else if (option == "Withdraw") {
                std::cout << std::endl;
                std::cout << "How much would you like to Withdraw?" << std::endl;
                std::cin >> request;
                std::cout << "Withdrawing " << request << std::endl;
                account->withdraw(request);
            }
            else if (option == "Balance") {
                std::cout << std::endl;
                std::cout << std::endl << "Current Balance: $" << account->getBalance() << std::endl;
            }
            else if (option == "Close") {
                std::cout << std::endl;
                std::cout << "Your account has been successfully closed." << std::endl;
                account->closeAccount();
            }
            else {
                std::cout << std::endl << "Invalid input." << std::endl;
            }

        } while (option != "Exit");
    }

    //Error catching
    catch (invalidAccountOperationException& e) {
        std::cerr << "Account Status Error: " << e.what() << std::endl;
    }
    catch (overdrawExcception& e) {
        std::cerr << "Withdraw Input Error: " << e.what() << std::endl;
    }
    catch (negativeClassException& e) {
        std::cerr << "Signed Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "User Input Error: " << e.what() << std::endl;
    }

    return 0;
}