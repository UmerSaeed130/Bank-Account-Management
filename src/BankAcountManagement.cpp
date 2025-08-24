#include <iostream>
#include <string>
using namespace std;

const int MAX_AVAILABLE_ACCOUNTS = 3;

struct BankAccount
{
    unsigned int AccountNumber;
    bool AccountType;
    string AccountHolderName;
    string CNIC; // It is better to keep the CNIC as a string rather than a char array
    double CurrentBalance;
    unsigned int PIN;
};

// Global variables (can be accessed by any function)
// Here we are telling the program that BankAccount is an array of size MAX_AVAILABLE_ACCOUNTS
BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS]; 
int accountCount = 0;

// Some of the parameters in these functions are const bcz we do not want them to change
// Some of the parameters in these functions are not const bcz they change the account info

// Function to display the title
void Title();
// Function to display an options menu and let customer choose an option
unsigned int OptionsMenu();
// Function to make a new account
void OpenAccount(BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int& accountCount);
// Function to deposit ammount into the customer's account (if he enters the AccNo and PIN correct)
void Deposit(BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount);
// Function to withdraw ammount from the customer's account (if he enters the AccNo and PIN correct)
void Withdraw(BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount);
// Function to display account info of the customer's account (if he enters the AccNo and PIN correct)
void DisplayAccountDetails(const BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount);
// Function to display the account info of all of the customers
void DisplayAllCustomersAccountsDetails(const BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount);
// Function to search for an account by entering account number
int SearchAccount(const BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount, int AccountNumber);
// Function to make sure the CNIC format is correct 
bool isValidCNIC(const string& CNIC);
// Ending line
void EndLine();

int main()
{
    // Variables
    unsigned int choice = 6;
    int accountIndex = -1; // Initialized accountIndex before the switch statement
                           // Reason: If the variable initialization appears after the switch statement or isn't properly handled in the default case, 
                           // it can lead to situations where the variable might not be initialized when the default case executes.
    // Display the title
    Title();
    // Loop to keep asking for an input if the user enters invalid input

    while (true)
    {
        // Display the options menu and ask user for a choice
        choice = OptionsMenu();

        // Call the necessary function depending on what the user has choosen
        switch (choice)
        {
        case 1:
            OpenAccount(CustomerAccount, accountCount);
            break;
        case 2:
            Deposit(CustomerAccount, accountCount);
            break;
        case 3:
            Withdraw(CustomerAccount, accountCount);
            break;
        case 4:
            int accountNumber;
            cout << "Enter the account number to search: ";
            cin >> accountNumber;
            cout << endl;
            // Calling SearchAccount and checking if the account is found
            accountIndex = SearchAccount(CustomerAccount, accountCount, accountNumber);
            cout << "\n\n";
            if (accountIndex != -1) //Acc exists
            {
                DisplayAccountDetails(CustomerAccount, accountCount);
            }
            else
            {
                cout << "!!! Account not found !!!" << endl;
            }
            break;
        case 5:
            DisplayAccountDetails(CustomerAccount, accountCount);
            break;
        case 6:
            DisplayAllCustomersAccountsDetails(CustomerAccount, accountCount);
            break;
        case 7:
            cout << "Thank you for using our services. If you need help, please contact support at support@bank.com" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again!" << endl;
            continue;
        }
    }
    return 0;
}

void Title()
{
    cout << "\"Welcome to the Bank Al-PIEAS Limited!\"\n";
}

unsigned int OptionsMenu()
{
    unsigned int choice = 6;

    cout << "\n========== Bank Menu ==========\n";
    cout << "-------------------------------\n";
    cout << "| 1. Open New Account          |\n";
    cout << "| 2. Deposit                   |\n";
    cout << "| 3. Withdraw                  |\n";
    cout << "| 4. Search Account            |\n";
    cout << "| 5. Display Account Details   |\n";
    cout << "| 6. Display All Accounts Info |\n";
    cout << "| 7. Exit                      |\n";
    cout << "-------------------------------\n\n";
    cout << "Please enter your choice (1-7): ";
    cin >> choice;
    cout << endl;
    return choice;
}

void OpenAccount(BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int& accountCount)
{
    if (accountCount >= MAX_AVAILABLE_ACCOUNTS)
    {
        cout << "Account limit reached. Cannot open new account." << endl;
        return; // return statement exits the loop
    }

    // TAKING IN THE ACCOUNT TYPE
    cout << "Select the account type (Savings/Current):\n";
    while (true)
    {    
        cout << "Press 0 for Current OR 1 for Savings: ";
        cin >> CustomerAccount[accountCount].AccountType;
        if (CustomerAccount[accountCount].AccountType != 0 && CustomerAccount[accountCount].AccountType != 1)
        {
            cout << "Invalid Input! You can enter either 0 or 1.\n";
        }
        else
        {
            break;
        }
    }
    cout << endl;

    //TAKING IN THE ACCOUNT HOLDER'S NAME
    cout << "Enter Account Holder's Name: ";
    cin.ignore();  // To ignore the newline character from previous input
    getline(cin, CustomerAccount[accountCount].AccountHolderName);
    cout << endl;

    // TAKING IN THE ACCOUND HOLDER'S CNIC
    while (true) 
    {
        cout << "Enter CNIC (format: *****-*******-*): ";
        getline(cin, CustomerAccount[accountCount].CNIC);

        // Validate CNIC format
        if (!isValidCNIC(CustomerAccount[accountCount].CNIC))
        {
            cout << "\nInvalid format!\n";
        }
        else // Valid input
        {
            break;
        }
        cout << endl;
    }
    cout << endl;
    // TAKING IN THE ACCOUND HOLDER'S PIN
    while (true)
    {
        cout << "Please set 4-digit PIN. (This PIN will be used to access your acccount): ";
        cin >> CustomerAccount[accountCount].PIN;
        cout << endl;
        // validate PIN length
        if (CustomerAccount[accountCount].PIN < 1000 || CustomerAccount[accountCount].PIN > 9999)
        {
            cout << "Error! The PIN you have entered is not of 4-digits: \n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl;
        }
        else
        {
            cout << "Your PIN has been created.\Do not share your PIN with anyone!\n";
            break;
        }
    }
    cout << endl;
    // TAKING IN THE ACCOUND HOLDER'S INITIAL BALANCE
    while (true)
    {
        cout << "Enter Initial Balance (minimum Rs. 5000/-): ";
        cin >> CustomerAccount[accountCount].CurrentBalance;
        cout << endl;
        // validate initial amount deposited
        if (CustomerAccount[accountCount].CurrentBalance < 5000)
        {
            cout << "Invalid amount!\n";
            cin.clear();
            cin.ignore(5000, '\n');
        }
        else
        {
            cout << "Amount has been added to you account.\n\nCurrent amount in your account is: Rs. ";
            cout << CustomerAccount[accountCount].CurrentBalance;
            cout << endl;
            break;
        }
    }
    cout << endl;
    // ALLOTT ACCOUNT NUMBER
    CustomerAccount[accountCount].AccountNumber = 5995801937 + accountCount;
    accountCount++;  // Increment account count after assignment
    cout << "Congratulations! Your bank account has been created.\n\nYour Account Number is " << CustomerAccount[accountCount - 1].AccountNumber << ". ";
    cout << "Remember it for future reference.\n";
    EndLine;
}

void Deposit(BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount)
{
    int accountNumber;
    int index = -1;
    int retryCount = 0; // Counter for retry attempts for account number
    int pinRetryCount = 0; // Counter for retry attempts for PIN

    while (true)
    {
        cout << "Enter your account number (10 digits): ";
        cin >> accountNumber;
        cout << endl;
        // Validate the length of the account number
        if (accountNumber < 1000000000 || accountNumber > 9999999999)
        {
            cout << "Invalid no of digits!\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            // Search for the account using the account number
            index = SearchAccount(CustomerAccount, accountCount, accountNumber);

            // If account is not found
            if (index == -1)
            {
                cout << "!!! Account not found !!!\n\n";

                // Give user a choice whether they want to try again or go to main menu
                char choice;
                cout << "Would you like to try again? (Y/N): ";
                cin >> choice;
                cout << endl;

                if (choice == 'Y' || choice == 'y')
                {
                    retryCount++; // Increment retry count
                    if (retryCount >= 3) // Limit retries to 3
                    {
                        cout << "Too many failed attempts. Returning to main menu.\n";
                        return; // Exit after 3 failed attempts
                    }
                    else
                    {
                        cout << "You have " << (3 - retryCount) << " attempt(s) remaining.\n\n";
                        continue; // Restart the loop to enter account number again
                    }
                }
                else if (choice == 'N' || choice == 'n')
                {
                    return; // Exit the function and go back to the main menu
                }
                else
                {
                    cout << "Invalid choice! Returning to main menu.\n";
                    return; // Exit the function for an invalid choice as well
                }
            }
            else // Account is found
            {
                break; // Exit the loop if account is found
            }
        }
    }
    cout << endl;
    // PIN retry logic (limit to 3 attempts)
    unsigned int pin;
    while (pinRetryCount < 3) // Allow up to 3 PIN attempts
    {
        cout << "Enter you 4-digit PIN: ";
        cin >> pin;
        cout << endl;

        if (pin != CustomerAccount[index].PIN)
        {
            pinRetryCount++; // Increment PIN retry count
            cout << "!!! Incorrect PIN !!!\n";

            if (pinRetryCount >= 3) // Limit retries to 3
            {
                cout << "Too many incorrect PIN attempts. Returning to main menu.\n";
                return; // Exit after 3 failed PIN attempts
            }
            cout << endl;
            cout << "You have " << (3 - pinRetryCount) << " attempt(s) remaining.\n";
        }
        else
        {
            break; // Exit loop if PIN is correct
        }
        cout << endl;
    }

    // If the PIN is correct, ask for deposit amount
    double amount;
    cout << "Enter deposit amount: ";
    while (!(cin >> amount) || amount <= 0)
    {
        cout << "Invalid amount! Enter a positive number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // Add the deposit to the account balance
    CustomerAccount[index].CurrentBalance += amount;
    cout << "Rs. " << amount << " deposited. New balance: " << CustomerAccount[index].CurrentBalance << endl;
    EndLine;
}

void Withdraw(BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount)
{
    int accountNumber;
    int index = -1;
    int retryCount = 0; // Counter for retry attempts for account number
    int pinRetryCount = 0; // Counter for retry attempts for PIN

    while (true)
    {
        cout << "Enter your account number (10 digits): ";
        cin >> accountNumber;
        cout << endl;

        // Validate the length of the account number
        if (accountNumber < 1000000000 || accountNumber > 9999999999)
        {
            cout << "Invalid digits length! Enter a 10-digit account number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            // Search for the account using the account number
            index = SearchAccount(CustomerAccount, accountCount, accountNumber);
            cout << endl;
            // If account is not found
            if (index == -1)
            {
                cout << "Account not found!\n";

                // Give user a choice whether they want to try again or go to main menu
                char choice;
                cout << "Would you like to try again? (Y/N): ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y')
                {
                    retryCount++; // Increment retry count
                    if (retryCount >= 3) // Limit retries to 3
                    {
                        cout << "Too many failed attempts. Returning to main menu.\n";
                        return; // Exit after 3 failed attempts
                    }
                    else
                    {
                        cout << "You have " << (3 - retryCount) << " attempt(s) remaining.\n\n";
                        continue; // Restart the loop to enter account number again
                    }
                }
                else if (choice == 'N' || choice == 'n')
                {
                    return; // Exit the function and go back to the main menu
                }
                else
                {
                    cout << "Invalid choice! Returning to main menu.\n";
                    return; // Exit the function for an invalid choice as well
                }
            }
            else // Account is found
            {
                break; // Exit the loop if account is found
            }
        }
    }
    cout << endl;

    unsigned int pin;
    while (pinRetryCount < 3) // Allow up to 3 PIN attempts
    {
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;
        cout << endl;

        if (pin != CustomerAccount[index].PIN)
        {
            pinRetryCount++; // Increment PIN retry count
            cout << "Incorrect PIN!\n";

            if (pinRetryCount >= 3) // Limit retries to 3
            {
                cout << "Too many incorrect PIN attempts. Returning to main menu.\n";
                return; // Exit after 3 failed PIN attempts
            }
            cout << endl;
            cout << "You have " << (3 - pinRetryCount) << " attempt(s) remaining.\n";
        }
        else
        {
            break; // Exit loop if PIN is correct
        }
        cout << endl;
    }

    double amount;
    while (true)
    {
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        cout<<endl;

        if (amount <= 0)
        {
            cout << "Invalid amount! Enter a positive number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            // Check if withdrawal amount exceeds balance
            if (amount > CustomerAccount[index].CurrentBalance)
            {
                cout << "Insufficient balance! You cannot withdraw more than your current balance.\n\n";

                // Ask the user if they want to try again or go back to the main menu
                char choice;
                cout << "Would you like to try again or return to main menu? (T for Try Again / M for Main Menu): ";
                cin >> choice;
                cout << endl;

                if (choice == 'T' || choice == 't')
                {
                    Withdraw(CustomerAccount, accountCount);  // Recursively call the Withdraw function to try again
                }
                else if (choice == 'M' || choice == 'm')
                {
                    return; // Exit the function and go back to the main menu
                }
                else
                {
                    cout << "Invalid choice! Returning to main menu.\n";
                    return; // Exit the function for an invalid choice
                }
            }
        }
        break;
    }

    // If withdrawal is valid, subtract from balance
    CustomerAccount[index].CurrentBalance -= amount;
    cout << "Rs. " << amount << "/- have been withdrawn from your account. Remaining balance: " << CustomerAccount[index].CurrentBalance << "/-" << endl;
    EndLine;
}

int SearchAccount(const BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount, int accountNumber)
{
    for (int i = 0; i < accountCount; i++) // Loop through all accounts
    {
        if (CustomerAccount[i].AccountNumber == accountNumber) // Check if account number matches
        {
            cout << "Your account exists in our bank branch.\n\n";
            cout << "Account Holder: " << CustomerAccount[i].AccountHolderName << endl;
            return i; // Return the index of the found account
        }
    }
    return -1; // Account not found, return -1
}

void DisplayAccountDetails(const BankAccount CustomerAccount[MAX_AVAILABLE_ACCOUNTS], int accountCount)
{
    int accountNumber;
    int index = -1;
    int retryCount = 0; // Counter for retry attempts for account number
    int pinRetryCount = 0; // Counter for retry attempts for PIN

        while (true)
        {
            cout << "Enter your account number (10 digits): ";
            cin >> accountNumber;

            // Validate the length of the account number
            if (accountNumber < 1000000000 || accountNumber > 9999999999)
            {
                cout << "Invalid digits length! Enter a 10-digit account number: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else
            {
                // Search for the account using the account number
                index = SearchAccount(CustomerAccount, accountCount, accountNumber);

                // If account is not found
                if (index == -1)
                {
                    cout << "Account not found!\n";

                    // Give user a choice whether they want to try again or go to main menu
                    char choice;
                    cout << "Would you like to try again? (Y/N): ";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y')
                    {
                        retryCount++; // Increment retry count
                        if (retryCount >= 3) // Limit retries to 3
                        {
                            cout << "Too many failed attempts. Returning to main menu.\n";
                            return; // Exit after 3 failed attempts
                        }
                        continue; // Restart the loop to enter account number again
                    }
                    else if (choice == 'N' || choice == 'n')
                    {
                        return; // Exit the function and go back to the main menu
                    }
                    else
                    {
                        cout << "Invalid choice! Returning to main menu.\n";
                        return; // Exit the function for an invalid choice as well
                    }
                }
                else // Account is found
                {
                    break; // Exit the loop if account is found
                }
            }
        }

    unsigned int pin;
    while (pinRetryCount < 3) // Allow up to 3 PIN attempts
    {
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;

        // Validate that the PIN matches the account
        if (pin != CustomerAccount[index].PIN)
        {
            pinRetryCount++; // Increment PIN retry count
            cout << "Incorrect PIN for the given account number!\n";

            if (pinRetryCount >= 3) // Limit retries to 3
            {
                cout << "Too many incorrect PIN attempts. Returning to main menu.\n";
                return; // Exit after 3 failed PIN attempts
            }
            cout << "You have " << (3 - pinRetryCount) << " attempt(s) remaining.\n";
        }
        else
        {
            break; // Exit loop if PIN matches the account
        }
    }

    // Display account details after successful validation
    cout << "\nAccount Details:-" << endl;
    cout << "-------------------------------" << endl;
    cout << "Account Number: " << CustomerAccount[index].AccountNumber << endl;
    cout << "Account Type: " << (CustomerAccount[index].AccountType ? "Savings" : "Current") << endl;
    cout << "Account Holder: " << CustomerAccount[index].AccountHolderName << endl;
    cout << "CNIC: " << CustomerAccount[index].CNIC << endl;
    cout << "Balance: Rs. " << CustomerAccount[index].CurrentBalance << endl;
    cout << "-------------------------------" << endl;
    cout << "Thank you for using our service.\n";
}

void DisplayAllCustomersAccountsDetails(const BankAccount CustomerAccounts[MAX_AVAILABLE_ACCOUNTS], int accountCount)
{
    const unsigned int EMPLOYEE_PIN = 1234; // Employee PIN
    unsigned int enteredPin;
    int retryCount = 0; // Retry counter for PIN attempts

    // Ask the employee for the PIN
    while (retryCount < 3) // Allow up to 3 attempts
    {
        cout << "Enter the Employee PIN: {The employee PIN is 1234 ;-) }";
        cin >> enteredPin;

        if (enteredPin == EMPLOYEE_PIN)
        {
            // If PIN is correct, display all customer account details
            cout << "\nEmployee PIN verified successfully.\n";
            for (int i = 0; i < accountCount; i++)
            {
                cout << "\nAccount Number: " << CustomerAccounts[i].AccountNumber << endl;
                cout << "Account Type: " << (CustomerAccounts[i].AccountType ? "Savings" : "Current") << endl;
                cout << "Account Holder: " << CustomerAccounts[i].AccountHolderName << endl;
                cout << "CNIC: " << CustomerAccounts[i].CNIC << endl;
                cout << "Balance: " << CustomerAccounts[i].CurrentBalance << endl;
                cout << "-------------------------------" << endl;
            }
            return; // Exit function after displaying details
        }
        else
        {
            // Increment retry count and notify the employee
            retryCount++;
            cout << "Incorrect PIN! You have " << (3 - retryCount) << " attempt(s) remaining.\n";

            if (retryCount >= 3)
            {
                cout << "Too many incorrect attempts. Access denied.\n";
                return; // Exit function if max retries are exceeded
            }
        }
    }
    EndLine;
}

bool isValidCNIC(const string& CNIC)
{
    // Check length of CNIC first
    if (CNIC.length() != 15)
    {
        return false;
    }

    // Check the correct positions of dashes
    if (CNIC[5] != '-' || CNIC[13] != '-') 
    {
        return false;
    }

    // Check if all characters (except dashes) are digits
    for (int i = 0; i < CNIC.length(); ++i) 
    {
        if ((i != 5 && i != 13) && !isdigit(CNIC[i]))
        {
            return false;
        }
    }

    return true;
}

void EndLine()
{
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
