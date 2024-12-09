#include <iostream>
#include <bits/stdc++.h>
#include <windows.h> // For Windows API functions and types
#include "bookstructure.cpp"

using namespace std;
int error;

void login(string& admin, string& password);

void staff(string& user,string& pass);

void Adminoption();
void adminmenu();
void guestmenu();
void printBill(vector<pair<string,pair<int,int>>>&purchasebooks);

//Password asterisk generator
string getpass(const char *prompt, bool show_asterisk = true){
    const char BACKSPACE = 8;
    const char RETURN = 13;
    string password;
    unsigned char ch = 0;
    cout<<"\n\n\t" << prompt;
    DWORD con_mode;
    DWORD dwRead;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn,con_mode & ~(ENABLE_ECHO_INPUT|ENABLE_LINE_INPUT));

    while(ReadConsoleA(hIn, &ch,1,&dwRead,NULL) && ch != RETURN){
        if(ch == BACKSPACE){
            if(password.length() != 0){
                if(show_asterisk){
                    cout<<"\b \b";
                }
                password.resize(password.length() - 1);
            }
        }
        else{
            password += ch;
            if(show_asterisk){
                cout<<"*";
            }
        }
        
    }
    
    SetConsoleMode(hIn, con_mode);
    cout << endl;
    return password;
}

int main() {
    int choice;
    cout << "\n\tWelcome to our Books Plaza" << endl;
    cout << "\n *****************************Please login***********************************" << endl;
    do {
        cin.clear();
        string user, password;
        cout << "\n\n\tPlease select an option from the given menu below\n\n";
        cout << "\t\t1. Admin Login \n"
             << "\t\t2. Guest Login. \n"
             << "\t\t3. Exit. \n";
        do {
            error = 0;
            cout << "\n\tPlease enter your selection: ";
            cin >> choice;
            if (cin.fail()) {
                cout << "\n\tPlease enter a valid name." << endl;
                error = 1;
                cin.clear();
                cin.ignore(80, '\n');
            }
        } while (error == 1);

        switch (choice) {
            case 1: {
                cout << "\n\tPlease enter the admin username: ";
                cin >> user;
                password = getpass("Please enter the password: ",true);
                login(user, password);
            } break;
            
            case 2: {
                guestmenu();
            }
            break;

            case 0:
            {
                system("pause");
                return 0;
            }

            case 3:
                cout << "\n\tExiting the application." << endl;
                return 0;

            default:
                cout << "\n\tInvalid option. Please try again." << endl;
        }

    } while (choice != 3);
    return 0;
}

// Function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Login function for action
void login(string& admin, string& password) {
    string users[200];
    string pass[200];
    bool valid = false;
    int x = 0;

    ifstream textfile("admin.txt");  
    if (!textfile.is_open()) {
        cout << "\n\tError opening file. Please check if 'admin.txt' exists." << endl;
        return;
    }

    // Read user names and passwords from file and store them in arrays
    while (textfile >> users[x] >> pass[x]) {
        users[x] = trim(users[x]);
        pass[x] = trim(pass[x]);
        x++;
        if (x >= 200) // Avoid exceeding array limit
        {
            break;
        }
    }
    textfile.close();

    // Validate admin credentials
    for (int a = 0; a < x; a++) {
        if (admin == users[a] && password == pass[a]) {
            cout << "\n\tSuccessfully logged into admin account" << endl;
            valid = true;
            adminmenu();
            break;
        }
    }

    if (!valid) {
        cout << "\n\tUsername & password are invalid. Try again." << endl;
        system("pause");
    }
}

void Adminoption() {
    system("cls");
    cout << "\n\n Welcome to Books Plaza Administration Menu" << endl;
    cout << "=========================================\n";
    cout << "\n\t1 : ADD NEW BOOKS" << endl;
    cout << "\n\t2 : DISPLAY ALL BOOKS" << endl;
    cout << "\n\t3 : SEARCH BOOKS" << endl;
    cout << "\n\t4 : DELETE BOOKS" << endl;
    cout << "\n\t5 : UPDATE BOOKS" << endl;
    cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}

void adminmenu() {
    int sel;
    do {
        Adminoption();
        cout << "\nPlease enter your selection: ";
        cin >> sel;

        // Ignore any remaining characters in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (sel) {
            case 1:
                addbook("Book.csv");
                break;
            case 2:
                displaybook("Book.csv");
                break;
            case 3: {
                searchbook("Book.csv");
                break;
            }
            case 4: {
                string title;
                cout << "\nEnter the book title to delete: ";
                getline(cin,title);
                deletebook("Book.csv", title);
                break;
            }
            case 5: {
                string title;
                cout << "\nEnter the book title to update: ";
                getline(cin, title);  // Properly reads the entire line
                updatebook("Book.csv", title);  // Updated to use the title-based version
                break;
            }
            case 0:
                return;
            default:
                cout << "\n\tInvalid selection... try again..." << endl;
                
        }

        // Optional pause for user readability (if you feel output is fast)
        system("pause");

    } while (sel != 0);
}

void guestmenu() {
    int choice;
    do {
        system("cls");
        cout << "\n\tWelcome to the Guest Menu" << endl;
        cout << "\n**********************************" << endl;
        cout << "\n\t1. Search for a Book by Title" << endl;
        cout << "\n\t2. Search for a Book by Price" << endl;
        cout << "\n\t3. Exit to Main Menu" << endl;
        cout << "\nPlease enter your selection: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                purchaseByBookID("Book.csv");
                break;
            }
            case 2: {
                purchasebyprice("Book.csv");
                break;
            }
            case 3:
                return;
            default:
                cout << "\n\tInvalid selection... Please try again..." << endl;
        }

        system("pause");

    } while (choice != 4);
}











