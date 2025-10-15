#include <iostream.h> // Old C++ header
#include <stdlib.h>   // For exit()
#include <string.h>   // For string functions like strcmp
#include <stdio.h>    // For fflush(stdin) and gets()

// Define a maximum number of records since std::vector is not used
#define MAX_RECORDS 50 

// --- Helper Functions for Turbo C3 I/O ---
// We must clear the input buffer after numeric input in this environment
void clear_input_buffer() {
    fflush(stdin);
}

// --- 1. Book Class (Encapsulation) ---
class Book {
private:
    char isbn[15];
    char title[50];
    char author[50];
    int is_available; // Use int (1 for true, 0 for false)
    
public:
    // Constructor (uses strcpy for char arrays)
    Book() { is_available = 0; isbn[0] = '\0'; } // Default constructor
    
    void set_info(char* i, char* t, char* a) {
        strcpy(isbn, i);
        strcpy(title, t);
        strcpy(author, a);
        is_available = 1; // Available
    }

    // Public Getters (Accessors)
    char* get_isbn() { return isbn; }
    char* get_title() { return title; }
    int get_status() { return is_available; }

    // Mutator methods
    void check_out() { is_available = 0; } // Checked Out
    void check_in() { is_available = 1; }  // Available

    // Display method
    void display_info() {
        cout << "    - ISBN: " << isbn 
             << " | Title: " << title 
             << " | Author: " << author
             << " | Status: " << (is_available ? "Available" : "Checked Out") << endl;
    }
};

// --- 2. Patron Class (Encapsulation) ---
class Patron {
private:
    int id;
    char name[50];

public:
    Patron() { id = 0; name[0] = '\0'; } // Default constructor
    
    void set_info(int i, char* n) {
        id = i;
        strcpy(name, n);
    }
    
    int get_id() { return id; }
    char* get_name() { return name; }

    void display_info() {
        cout << "    - ID: " << id << " | Name: " << name << endl;
    }
};


// --- 3. Library Class (The Management/Controller) ---
class Library {
private:
    // Fixed-size arrays to simulate dynamic data structures
    Book books[MAX_RECORDS];
    Patron patrons[MAX_RECORDS];
    
    int book_count;
    int patron_count;
    int next_patron_id;

public:
    // Constructor
    Library() {
        book_count = 0;
        patron_count = 0;
        next_patron_id = 1001;
    }

    // --- Book Management ---

    void add_book() {
        if (book_count >= MAX_RECORDS) {
            cout << "\nError: Book limit reached (" << MAX_RECORDS << ").\n";
            return;
        }
        
        char isbn[15], title[50], author[50];
        cout << "\n--- Add New Book ---\n";
        
        clear_input_buffer();
        cout << "Enter ISBN: ";
        gets(isbn);
        
        cout << "Enter Title: ";
        gets(title);
        
        cout << "Enter Author: ";
        gets(author);

        // Set info on the next available array element
        books[book_count].set_info(isbn, title, author);
        cout << "Book '" << title << "' added to the library." << endl;
        book_count++;
    }

    void display_all_books() {
        if (book_count == 0) {
            cout << "\nThe library catalogue is currently empty.\n";
            return;
        }
        cout << "\n--- Library Catalogue (" << book_count << " Books) ---\n";
        for (int i = 0; i < book_count; i++) {
            books[i].display_info();
        }
    }

    // --- Patron Management ---

    void add_patron() {
        if (patron_count >= MAX_RECORDS) {
            cout << "\nError: Patron limit reached (" << MAX_RECORDS << ").\n";
            return;
        }

        char name[50];
        cout << "\n--- Add New Patron ---\n";

        clear_input_buffer();
        cout << "Enter Patron Name: ";
        gets(name);
        
        // Add Patron using the generated ID
        patrons[patron_count].set_info(next_patron_id, name);
        cout << "Patron '" << name << "' added with ID: " << next_patron_id << endl;
        next_patron_id++;
        patron_count++;
    }
    
    // --- Borrow/Return (The core logic) ---

    void borrow_book() {
        char isbn[15];
        cout << "\n--- Borrow Book ---\n";
        clear_input_buffer();
        cout << "Enter ISBN of the book to borrow: ";
        gets(isbn);

        for (int i = 0; i < book_count; i++) {
            // Use strcmp for comparing C-style strings
            if (strcmp(books[i].get_isbn(), isbn) == 0) {
                if (books[i].get_status()) {
                    books[i].check_out();
                    cout << "Book '" << books[i].get_title() << "' successfully checked out." << endl;
                    return;
                } else {
                    cout << "Error: Book is currently unavailable.\n";
                    return;
                }
            }
        }
        cout << "Error: Book with ISBN " << isbn << " not found in the catalogue.\n";
    }

    void return_book() {
        char isbn[15];
        cout << "\n--- Return Book ---\n";
        clear_input_buffer();
        cout << "Enter ISBN of the book to return: ";
        gets(isbn);

        for (int i = 0; i < book_count; i++) {
            if (strcmp(books[i].get_isbn(), isbn) == 0) {
                if (!books[i].get_status()) {
                    books[i].check_in();
                    cout << "Book '" << books[i].get_title() << "' successfully returned.\n";
                    return;
                } else {
                    cout << "Error: Book was not checked out.\n";
                    return;
                }
            }
        }
        cout << "Error: Book with ISBN " << isbn << " not found in the catalogue.\n";
    }
};


// -----------------------------------------------------------------
//               MAIN FUNCTION (Program Entry Point)
// -----------------------------------------------------------------

void display_main_menu() {
    cout << "\n=======================================\n";
    cout << "  LIBRARY MANAGEMENT SYSTEM (Turbo C++)\n";
    cout << "=======================================\n";
    cout << "1. Add New Book\n";
    cout << "2. Register New Patron\n";
    cout << "3. Display All Books\n";
    cout << "4. Borrow Book\n";
    cout << "5. Return Book\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

// Turbo C++ main function definition
void main() { 
    // Use void main() instead of int main() for TC3 compatibility
    
    // Create the main Library object
    Library central_library;
    int choice;

    do {
        display_main_menu();
        
        if (!(cin >> choice)) {
            // This error handling is less reliable in TC3, but included for best effort
            cout << "\nInvalid input. Please enter a number.\n";
            clear_input_buffer();
            choice = 0; 
            continue;
        }

        switch (choice) {
            case 1:
                central_library.add_book();
                break;
            case 2:
                central_library.add_patron();
                break;
            case 3:
                central_library.display_all_books();
                break;
            case 4:
                central_library.borrow_book();
                break;
            case 5:
                central_library.return_book();
                break;
            case 6:
                cout << "\nExiting Library Management System. Goodbye!\n";
                exit(0); // Use exit(0) for clean program termination in TC3
                break;
            default:
                cout << "\nInvalid choice. Please select an option.\n";
        }
    } while (choice != 6);
}