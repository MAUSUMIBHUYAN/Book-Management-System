#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Book {
    int BookId;
    string title;
    string author;
    string category;
    double price;
    int quantity;
};


string normalizestring(const string& str) {
    string result = str;

    result.erase(result.begin(), find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    result.erase(find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), result.end());
    transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) {
        return tolower(ch);
    });
    result.erase(remove_if(result.begin(), result.end(), [](unsigned char ch) {
        return ispunct(ch);
    }), result.end());
    stringstream ss(result);
    string normalized, word;
    while (ss >> word) {
        if (!normalized.empty()) normalized += ' ';
        normalized += word;
    }

    return normalized;
}


float computesimilarity(const string& s1, const string& s2) {
    set<string> words1, words2;
    string word;
    stringstream ss1(s1), ss2(s2);
    while (ss1 >> word) words1.insert(word);
    while (ss2 >> word) words2.insert(word);
    vector<string> intersection;
    set_intersection(words1.begin(), words1.end(), words2.begin(), words2.end(), back_inserter(intersection));
    int partialMatches = 0;
    for (const auto& w1 : words1) {
        for (const auto& w2 : words2) {
            if (w1.find(w2) != string::npos || w2.find(w1) != string::npos) {
                ++partialMatches;
                break; 
            }
        }
    }
    float totalMatches = static_cast<float>(intersection.size() + partialMatches);
    return totalMatches / max(words1.size(), words2.size());
}

void printbill(const vector<pair<string, pair<int, double>>>& purchasebooks) {
    double totalamount = 0.0;

    cout << "\n\n\t\t\t\t*** Bill ***\n";
    cout << "===========================================================================================\n";
    cout << left << setw(10) << "BookID"
         << setw(20) << "Quantity"
         << setw(20) << "Price"
         << setw(20) << "Total\n";
    cout << "===========================================================================================\n";

    for (const auto& book : purchasebooks) {
        int quantity = book.second.first;
        double price = book.second.second;
        double total = quantity * price;
        totalamount += total;

        cout << left << setw(10) << book.first
             << setw(20) << quantity
             << setw(20) << price
             << setw(20) << total
             << "\n";
    }

    cout << "===========================================================================================\n";
    cout << "Total Amount: " << totalamount << endl;
}

void displaybook(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "\nBooks Available: \n";
    cout << "===========================================================================================\n";
    cout << left << setw(10) << "BookID"
         << setw(50) << "Title"
         << setw(20) << "Author"
         << setw(15) << "Category"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << "\n";
    cout << "===========================================================================================\n";

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, author, category, price, quantity;
        if (line.find('"') != string::npos) {
            vector<string> fields;
            bool inquotes = false;
            string field;

            for (char c : line) {
                if (c == '"') {
                    inquotes = !inquotes;
                } else if (c == ',' && !inquotes) {
                    fields.push_back(field);
                    field.clear();
                } else {
                    field += c;
                }
            }
            if (!field.empty()) fields.push_back(field);
            if (fields.size() >= 6) {
                id = fields[0];
                title = fields[1];
                author = fields[2];
                category = fields[3];
                price = fields[4];
                quantity = fields[5];
            }
        } else {
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, category, ',');
            getline(ss, price, ',');
            getline(ss, quantity);
        }
        cout << left << setw(10) << id
             << setw(50) << title
             << setw(20) << author
             << setw(15) << category
             << setw(10) << price
             << setw(10) << quantity
             << "\n";
    }
    cout << "===========================================================================================\n";

    file.close();
}


void addbook(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    Book book;
    cout << "Enter Book ID: ";
    cin >> book.BookId;
    cin.ignore();  
    cout << "Enter Book Title: ";
    getline(cin, book.title);
    cout << "Enter Author Name: ";
    getline(cin, book.author);
    cout << "Enter category: ";
    getline(cin, book.category);
    cout << "Enter Price: ";
    cin >> book.price;
    cout << "Enter Quantity: ";
    cin >> book.quantity;

    file << book.BookId << "," << book.title << "," << book.author << "," << book.category << "," 
         << book.price << "," << book.quantity << endl;
    cout << "Book added successfully!" << endl;
    file.close();
}

void searchbook(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Search Options:" << endl;
    cout << "1. Search by Title" << endl;
    cout << "2. Search by Category" << endl;
    cout << "3. Search by Price Range" << endl;
    cout << "Please enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); 
    
    string query;
    switch (choice) {
        case 1:
            cout << "Enter the title to search: ";
            getline(cin, query);
            break;
        case 2:
            cout << "Choose a category to search:" << endl;
            cout << "1. Romance" << endl;
            cout << "2. Fantansy" << endl;
            cout << "3. Mystery" << endl;
            cout << "4. Action" << endl;
            cout << "5. Adventure" << endl;
            cout << "6. Slice of Life" << endl;
            cout << "Enter your choice: ";
            int categorychoice;
            cin >> categorychoice;
            cin.ignore(); 
            switch (categorychoice) {
                case 1: query = "Romance"; break;
                case 2: query = "Fantansy"; break;
                case 3: query = "Mystery"; break;
                case 4: query = "Action"; break;
                case 5: query = "Adventure"; break;
                case 6: query = "Slice of Life"; break;
                default: cout << "Invalid category!" << endl; return;
            }
            break;
        case 3:
            cout << "Choose a price range to search:" << endl;
            cout << "1. Under 300" << endl;
            cout << "2. Under 500" << endl;
            cout << "3. Above 500" << endl;
            cout << "Enter your choice: ";
            int pricechoice;
            cin >> pricechoice;
            cin.ignore(); 
            if (pricechoice == 1) query = "under 300";
            else if (pricechoice == 2) query = "under 500";
            else if (pricechoice == 3) query = "above 500";
            else {
                cout << "Invalid price range!" << endl;
                return;
            }
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    cout << "\nSearch Results:" << endl;
    cout << "------------------------------------------------------------\n";

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, author, category, pricestr, quantitystr;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, pricestr, ',');
        getline(ss, quantitystr);
        double price = 0;
        int quantity = 0;

        try {
            price = stod(pricestr);  
            quantity = stoi(quantitystr); 
        } catch (const invalid_argument&) {
            continue; 
        }

        bool matches = false;
        switch (choice) {
            case 1:
                matches = normalizestring(title).find(normalizestring(query)) != string::npos;
                break;
            case 2:
                matches = normalizestring(category) == normalizestring(query);
                break;
            case 3:
                if (query == "under 300")
                    matches = price < 300;
                else if (query == "under 500")
                    matches = price < 500;
                else if (query == "above 500")
                    matches = price > 500;
                break;
        }

        if (matches) {
            found = true;
            cout << "Book ID   : " << id << endl;
            cout << "Title     : " << title << endl;
            cout << "Category  : " << category << endl;
            cout << "Price     : " << price << endl;
            cout << "Quantity  : " << quantity << endl;
            cout << "------------------------------------------------------------\n";
        }
    }

    if (!found) {
        cout << "None" << endl;
    }
}


void deletebook(const string& filename, const string& Booktitleinput) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    string normalizedinput = normalizestring(Booktitleinput);
    string bestmatch;
    float bestsimilarity = 0.0;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, author, category, pricestr, quantitystr;
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, pricestr, ',');
        getline(ss, quantitystr);
        string normalizedtitle = normalizestring(title);
        float similarity = computesimilarity(normalizedinput, normalizedtitle);
        if (similarity > bestsimilarity) {
            bestsimilarity = similarity;
            bestmatch = line;
        } else {
            lines.push_back(line);
        }
    }
    file.close();

    if (bestsimilarity >= 0.5) { 
        cout << "\nClosest match found:\n";
        stringstream ss(bestmatch);
        string id, title, author, category, pricestr, quantitystr;
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, pricestr, ',');
        getline(ss, quantitystr);
        cout << "Book ID   : " << id << "\n";
        cout << "Title     : " << title << "\n";
        cout << "Author    : " << author << "\n";
        cout << "Category  : " << category << "\n";
        cout << "Price     : " << pricestr << "\n";
        cout << "Quantity  : " << quantitystr << "\n";
        char confirm;
        cout << "\nDo you want to delete this book? (y/n): ";
        cin >> confirm;
        cin.ignore();

        if (tolower(confirm) == 'y') {
            ofstream outFile(filename);
            if (!outFile.is_open()) {
                cout << "Error writing to file!" << endl;
                return;
            }
            for (const string& l : lines) {
                outFile << l << endl;
            }
            outFile.close();
            cout << "Book deleted successfully!" << endl;
        } else {
            cout << "No changes made. Deletion canceled." << endl;
        }
    } else {
        cout << "\nNo close match found for the title: \"" << Booktitleinput << "\"." << endl;
    }
}

void updatebook(const string& filename, const string& Booktitleinput) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening book file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    string normalizedinput = normalizestring(Booktitleinput);
    string bestmatch;
    float bestsimilarity = 0.0;

    while (getline(file, line)) {
        stringstream ss(line);
        string idstr, title, author, category, priceStr, quantityStr;
        getline(ss, idstr, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, quantityStr);
        string normalizedtitle = normalizestring(title);
        float similarity = computesimilarity(normalizedinput, normalizedtitle);
        if (similarity > bestsimilarity) {
            bestsimilarity = similarity;
            bestmatch = line;
        }

        lines.push_back(line);
    }
    file.close();

    if (bestsimilarity >= 0.5) { 
        cout << "Closest match found: " << bestmatch << endl;
        cout << "Similarity score: " << bestsimilarity << endl;

        stringstream ss(bestmatch);
        string idstr, title, author, category, pricestr, quantitystr;
        getline(ss, idstr, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, category, ',');
        getline(ss, pricestr, ',');
        getline(ss, quantitystr);
        cout << "Current Details for Book Title \"" << title << "\":" << endl;
        cout << "ID: " << idstr << endl;
        cout << "Author: " << author << endl;
        cout << "Category: " << category << endl;
        cout << "Price: " << pricestr << endl;
        cout << "Quantity: " << quantitystr << endl;
        char confirm;
        cout << "Do you want to update this book? (y/n): ";
        cin >> confirm;
        cin.ignore();

        if (tolower(confirm) != 'y') {
            cout << "No updates made." << endl;
            return;
        }

        int updatechoice;
        cout << "What would you like to update?" << endl;
        cout << "1. ID" << endl;
        cout << "2. Title" << endl;
        cout << "3. Author" << endl;
        cout << "4. Category" << endl;
        cout << "5. Price" << endl;
        cout << "6. Quantity" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> updatechoice;
        cin.ignore();

        switch (updatechoice) {
            case 1: {
                cout << "Enter new Book ID: ";
                int id;
                cin >> id;
                idstr = to_string(id);
                break;
            }
            case 2:
                cout << "Enter new Book Title: ";
                getline(cin, title);
                break;
            case 3:
                cout << "Enter new Author Name: ";
                getline(cin, author);
                break;
            case 4:
                cout << "Enter new Category: ";
                getline(cin, category);
                break;
            case 5: {
                cout << "Enter new Price: ";
                double price;
                cin >> price;
                pricestr = to_string(price);
                break;
            }
            case 6: {
                cout << "Enter new Quantity: ";
                int quantity;
                cin >> quantity;
                quantitystr = to_string(quantity);
                break;
            }
            default:
                cout << "Invalid choice. No changes made." << endl;
                return;
        }

        for (string& l : lines) {
            if (normalizestring(l).find(normalizestring(bestmatch)) != string::npos) {
                l = idstr + "," + title + "," + author + "," + category + "," + pricestr + "," + quantitystr;
                break;
            }
        }

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error writing to file!" << endl;
            return;
        }
        for (const string& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
        cout << "Book updated successfully!" << endl;

    } else {
        cout << "No close match found for the title: \"" << Booktitleinput << "\"." << endl;
    }
}

void purchaseByBookID(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> bookdata;
    string line;
    while (getline(file, line)) {
        bookdata.push_back(line);
    }
    file.close();

    vector<pair<string, pair<int, double>>> purchasebooks; 
    bool continueshopping = true;

    while (continueshopping) {
        system("cls");
        displaybook(filename); 

        cout << "\nEnter the BookIDs of the books you want to purchase (comma-separated ex: 1,3,5....): ";
        cin.ignore();
        string inputIDs;
        getline(cin, inputIDs);

        vector<string> bookIDs;
        stringstream ss(inputIDs);
        string bookID;
        while (getline(ss, bookID, ',')) {
            bookIDs.push_back(bookID);
        }

        for (const auto& id : bookIDs) {
            bool found = false;
            for (auto& book : bookdata) {
                stringstream ss(book);
                string currentID, title, author, category, price, quantity;
                getline(ss, currentID, ',');
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, category, ',');
                getline(ss, price, ',');
                getline(ss, quantity);

                if (currentID == id) { 
                    found = true;

                    cout << "\nBook Found!" << endl;
                    cout << "===========================================================================================\n";
                    cout << left << setw(10) << "BookID"
                         << setw(50) << "Title"
                         << setw(20) << "Author"
                         << setw(15) << "Category"
                         << setw(10) << "Price"
                         << setw(10) << "Quantity"
                         << "\n";
                    cout << "===========================================================================================\n";
                    cout << left << setw(10) << currentID
                         << setw(50) << title
                         << setw(20) << author
                         << setw(15) << category
                         << setw(10) << price
                         << setw(10) << quantity
                         << "\n";
                    cout << "===========================================================================================\n";

                    int availablequantity = stoi(quantity);
                    int quantitypurchased;

                    cout << "\nEnter quantity you want to buy: ";
                    cin >> quantitypurchased;

                    if (quantitypurchased > availablequantity) {
                        cout << "Sorry, only " << availablequantity << " copies are available.\n";
                    } else if (quantitypurchased > 0) {
                        double bookprice = stod(price);
                        purchasebooks.push_back({currentID, {quantitypurchased, bookprice}});
                        int remainingquantity = availablequantity - quantitypurchased;
                        string updatedrecord = currentID + "," + title + "," + author + "," + category + "," + price + "," + to_string(remainingquantity);
                        book = updatedrecord;

                        cout << "\nBook added to your cart.\n";
                    }
                }
            }
            if (!found) {
                cout << "\nBookID " << id << " not found in the catalog.\n";
            }
        }

        cout << "\nDo you want to purchase another book? (Y/N): ";
        char cont;
        cin >> cont;
        if (cont == 'N' || cont == 'n') {
            continueshopping = false;
        }
    }
    printbill(purchasebooks);

    ofstream outFile(filename, ios::trunc);
    for (const auto& record : bookdata) {
        outFile << record << "\n";
    }
    outFile.close();
}

void purchasebyprice(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    vector<string> bookdata; 
    string line;
    while (getline(file, line)) {
        bookdata.push_back(line);
    }
    file.close();

    vector<pair<string, pair<int, double>>> purchasebooks; 
    bool continueshopping = true;

    while (continueshopping) {
        system("cls");

        cout << "\nChoose a price range:\n";
        cout << "1. Under 300\n";
        cout << "2. Under 500\n";
        cout << "3. Above 500\n";
        cout << "Enter your choice (1/2/3): ";
        int choice;
        cin >> choice;

        double minprice = 0, maxprice = 0;
        switch (choice) {
            case 1:
                maxprice = 300;
                break;
            case 2:
                maxprice = 500;
                break;
            case 3:
                minprice = 500;
                break;
            default:
                cout << "Invalid choice!" << endl;
                continue;
        }

        vector<string> matchingbooks; 
        cout << "\nSearching for books in the selected price range...\n";

        for (const auto& book : bookdata) {
            stringstream ss(book);
            string id, title, author, category, price, quantity;
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, category, ',');
            getline(ss, price, ',');
            getline(ss, quantity);

            try {
                double bookprice = stod(price);
                if ((bookprice >= minprice) && (maxprice == 0 || bookprice <= maxprice)) {
                    matchingbooks.push_back(book);
                }
            } catch (const invalid_argument& e) {
                cout << "\nError: Invalid price format for book ID: " << id << ". Skipping this record.\n";
            } catch (const out_of_range& e) {
                cout << "\nError: Price out of range for book ID: " << id << ". Skipping this record.\n";
            }
        }

        if (matchingbooks.empty()) {
            cout << "\nNo books found in the selected price range." << endl;
        } else {
            cout << "\nBooks Found:\n";
            cout << "===========================================================================================\n";
            cout << left << setw(10) << "BookID"
                 << setw(50) << "Title"
                 << setw(20) << "Author"
                 << setw(15) << "Category"
                 << setw(10) << "Price"
                 << setw(10) << "Quantity"
                 << "\n";
            cout << "===========================================================================================\n";

            for (const auto& book : matchingbooks) {
                stringstream ss(book);
                string id, title, author, category, price, quantity;
                getline(ss, id, ',');
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, category, ',');
                getline(ss, price, ',');
                getline(ss, quantity);

                cout << left << setw(10) << id
                     << setw(50) << title
                     << setw(20) << author
                     << setw(15) << category
                     << setw(10) << price
                     << setw(10) << quantity
                     << "\n";
            }

            cout << "===========================================================================================\n";

            cout << "\nEnter the Book ID to select the book, or type 'exit' to finish: ";
            string selectedID;
            cin >> selectedID;

            if (selectedID == "exit") {
                continueshopping = false;
                break;
            }

            bool bookfound = false;
            for (auto& book : matchingbooks) {
                stringstream ss(book);
                string id, title, author, category, price, quantity;
                getline(ss, id, ',');
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, category, ',');
                getline(ss, price, ',');
                getline(ss, quantity);

                if (selectedID == id) {
                    bookfound = true;
                    int availablequantity = stoi(quantity);
                    int quantitypurchased;

                    cout << "\nEnter quantity you want to buy: ";
                    cin >> quantitypurchased;

                    if (quantitypurchased > availablequantity) {
                        cout << "Sorry, only " << availablequantity << " copies are available." << endl;
                    } else {
                        double bookprice = stod(price);
                        purchasebooks.push_back({id, {quantitypurchased, bookprice}});

                        // Update the quantity in bookData
                        int remainingquantity = availablequantity - quantitypurchased;
                        string updatedrecord = id + "," + title + "," + author + "," + category + "," + price + "," + to_string(remainingquantity);
                        for (auto& record : bookdata) {
                            if (record.find(id) == 0) { // Update the matching book ID
                                record = updatedrecord;
                                break;
                            }
                        }

                        cout << "\nBook added to your cart." << endl;
                    }
                    break;
                }
            }

            if (!bookfound) {
                cout << "\nInvalid Book ID. Please try again." << endl;
            }
        }

        cout << "\nDo you want to purchase another book? (Y/N): ";
        char cont;
        cin >> cont;
        if (cont == 'N' || cont == 'n') {
            continueshopping = false;
        }
    }

    
    printbill(purchasebooks);

    ofstream outFile(filename, ios::trunc);
    for (const auto& record : bookdata) {
        outFile << record << "\n";
    }
    outFile.close();
}


















