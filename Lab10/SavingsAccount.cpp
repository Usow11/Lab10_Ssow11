#include "SavingsAccount.h"
#include <fstream>
#include <iomanip>

/**
 * @brief Default constructor
 */
SavingsAccount::SavingsAccount() : interest(1)
{
}

/**
 * @brief Parameterized constructor
 */
SavingsAccount::SavingsAccount(const string& accNum, double initialBalance, float interest, const Customer& customer)
    : Account(accNum, initialBalance, customer)
{
    this->interest = interest;
}

/**
 * @brief Processes end-of-day transactions and applies interest
 */
void SavingsAccount::closeOfBusiness()
{
    double totalDeposits = accumulate(deposits.begin(), deposits.end(), 0.0);
    double totalWithdrawals = accumulate(withdrawals.begin(), withdrawals.end(), 0.0);

    double previousBalance = balance;
    double interestToApply = previousBalance <= 0 ? 0 : interest;
    double newBalance = (previousBalance + totalDeposits - totalWithdrawals) * (1 + interestToApply);

    printSummary(previousBalance, totalDeposits, totalWithdrawals, newBalance);

    balance = newBalance;

    deposits.clear();
    withdrawals.clear();
}

/**
 * @brief Prints account information
 */
void SavingsAccount::printAccountInfo() const
{
    cout << "Account Number: " << accountNumber << endl;
    cout << "Current Balance: $" << balance << endl;
    cout << "Interest Rate: " << interest * 100 << "%" << endl;
    owner.printCustomerInfo();
}

/**
 * @brief Saves account details to a file
 */
void SavingsAccount::Save() const
{
    ofstream outFile("account_summary.txt");

    if (outFile.is_open())
    {
        outFile << "Account Number: " << accountNumber << endl;
        outFile << endl;
        outFile << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
        outFile << endl;
        outFile << "Daily Interest Rate: " << interest << endl;

        outFile.close();
    }
}