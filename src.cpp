#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// colors for terminal
string RED = "\033[1;31m";
string GREEN = "\033[1;32m";
string YELLOW = "\033[1;33m";
string BLUE = "\033[1;34m";
string MAGENTA = "\033[1;35m";
string CYAN = "\033[1;36m";
string RESET = "\033[0m";

string filename = "users.txt";
string tempFile = "temp.txt";

void registerUser()
{
    string username, password;

    cout << CYAN << "\n============================" << RESET << endl;
    cout << MAGENTA << "      REGISTER NEW USER     " << RESET << endl;
    cout << CYAN << "============================" << RESET << endl;

    cout << YELLOW << "Enter username: " << RESET;
    cin >> username;
    cout << YELLOW << "Enter password: " << RESET;
    cin >> password;

    // check if user already exists
    ifstream checkFile(filename);

    if (checkFile.is_open())
    {
        string savedUser, savedPass;

        while (checkFile >> savedUser >> savedPass)
        {
            if (savedUser == username)
            {
                cout << RED << "\n>> Username already exists! Try a different one." << RESET << endl;
                checkFile.close();
                return;
            }
        }
        checkFile.close();
    }

    // save the new user
    ofstream file(filename, ios::app);

    if (!file.is_open())
    {
        cout << RED << "\n>> Error: Could not open file to save user!" << RESET << endl;
        return;
    }

    file << username << " " << password << endl;
    file.close();

    cout << GREEN << "\n>> Registration successful! You can now login." << RESET << endl;
}

void loginUser()
{
    string username, password;

    cout << CYAN << "\n============================" << RESET << endl;
    cout << MAGENTA << "        USER LOGIN          " << RESET << endl;
    cout << CYAN << "============================" << RESET << endl;

    cout << YELLOW << "Enter username: " << RESET;
    cin >> username;
    cout << YELLOW << "Enter password: " << RESET;
    cin >> password;

    // check the file for matching user
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << RED << "\n>> No users registered yet! Please register first." << RESET << endl;
        return;
    }

    string savedUser, savedPass;
    bool found = false;

    while (file >> savedUser >> savedPass)
    {
        if (savedUser == username && savedPass == password)
        {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
    {
        cout << GREEN << "\n>> Login successful! Welcome, " << username << "!" << RESET << endl;
    }
    else
    {
        cout << RED << "\n>> Invalid username or password!" << RESET << endl;
    }
}

void viewAllUsers()
{
    cout << CYAN << "\n============================" << RESET << endl;
    cout << MAGENTA << "     REGISTERED USERS       " << RESET << endl;
    cout << CYAN << "============================" << RESET << endl;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << RED << "\n>> No users found! File does not exist." << RESET << endl;
        return;
    }

    string savedUser, savedPass;
    int count = 0;

    while (file >> savedUser >> savedPass)
    {
        count++;
        cout << GREEN << "  " << count << ". " << RESET << savedUser << endl;
    }
    file.close();

    if (count == 0)
    {
        cout << RED << "\n>> No users registered yet!" << RESET << endl;
    }
    else
    {
        cout << YELLOW << "\nTotal users: " << count << RESET << endl;
    }
}

void changePassword()
{
    string username, oldPassword, newPassword;

    cout << CYAN << "\n============================" << RESET << endl;
    cout << MAGENTA << "     CHANGE PASSWORD        " << RESET << endl;
    cout << CYAN << "============================" << RESET << endl;

    cout << YELLOW << "Enter username: " << RESET;
    cin >> username;
    cout << YELLOW << "Enter old password: " << RESET;
    cin >> oldPassword;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << RED << "\n>> No users found! File does not exist." << RESET << endl;
        return;
    }

    ofstream temp(tempFile);

    if (!temp.is_open())
    {
        cout << RED << "\n>> Error: Could not create temp file!" << RESET << endl;
        file.close();
        return;
    }

    string savedUser, savedPass;
    bool found = false;

    while (file >> savedUser >> savedPass)
    {
        if (savedUser == username && savedPass == oldPassword)
        {
            found = true;
            cout << GREEN << "\n>> User verified!" << RESET << endl;
            cout << YELLOW << "Enter new password: " << RESET;
            cin >> newPassword;
            temp << savedUser << " " << newPassword << endl;
        }
        else
        {
            temp << savedUser << " " << savedPass << endl;
        }
    }

    file.close();
    temp.close();

    if (found)
    {
        remove(filename.c_str());
        rename(tempFile.c_str(), filename.c_str());
        cout << GREEN << ">> Password changed successfully!" << RESET << endl;
    }
    else
    {
        remove(tempFile.c_str());
        cout << RED << "\n>> Invalid username or password!" << RESET << endl;
    }
}

void deleteUser()
{
    string username, password;

    cout << CYAN << "\n============================" << RESET << endl;
    cout << MAGENTA << "      DELETE ACCOUNT        " << RESET << endl;
    cout << CYAN << "============================" << RESET << endl;

    cout << YELLOW << "Enter username: " << RESET;
    cin >> username;
    cout << YELLOW << "Enter password: " << RESET;
    cin >> password;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << RED << "\n>> No users found! File does not exist." << RESET << endl;
        return;
    }

    ofstream temp(tempFile);

    if (!temp.is_open())
    {
        cout << RED << "\n>> Error: Could not create temp file!" << RESET << endl;
        file.close();
        return;
    }

    string savedUser, savedPass;
    bool found = false;

    while (file >> savedUser >> savedPass)
    {
        if (savedUser == username && savedPass == password)
        {
            found = true;
            // skip writing this user to delete them
        }
        else
        {
            temp << savedUser << " " << savedPass << endl;
        }
    }

    file.close();
    temp.close();

    if (found)
    {
        remove(filename.c_str());
        rename(tempFile.c_str(), filename.c_str());
        cout << GREEN << "\n>> Account deleted successfully!" << RESET << endl;
    }
    else
    {
        remove(tempFile.c_str());
        cout << RED << "\n>> Invalid username or password!" << RESET << endl;
    }
}

int main()
{
    int choice;

    while (true)
    {
        cout << BLUE << "\n================================" << RESET << endl;
        cout << MAGENTA << "   LOGIN / REGISTRATION SYSTEM  " << RESET << endl;
        cout << BLUE << "================================" << RESET << endl;

        cout << CYAN << "  1. " << RESET << "Register" << endl;
        cout << CYAN << "  2. " << RESET << "Login" << endl;
        cout << CYAN << "  3. " << RESET << "View All Users" << endl;
        cout << CYAN << "  4. " << RESET << "Change Password" << endl;
        cout << CYAN << "  5. " << RESET << "Delete Account" << endl;
        cout << CYAN << "  6. " << RESET << "Exit" << endl;

        cout << YELLOW << "\nEnter your choice: " << RESET;
        cin >> choice;

        if (choice == 1)
        {
            registerUser();
        }
        else if (choice == 2)
        {
            loginUser();
        }
        else if (choice == 3)
        {
            viewAllUsers();
        }
        else if (choice == 4)
        {
            changePassword();
        }
        else if (choice == 5)
        {
            deleteUser();
        }
        else if (choice == 6)
        {
            cout << GREEN << "\nGoodbye! Thanks for using the system." << RESET << endl;
            break;
        }
        else
        {
            cout << RED << "\n>> Invalid choice! Please try again." << RESET << endl;
        }
    }

    return 0;
}
