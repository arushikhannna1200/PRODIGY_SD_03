#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string email;
};

class ContactManager {
private:
    vector<Contact> contacts;

    void loadContacts() {
        ifstream inFile("contacts.txt");
        if (inFile.is_open()) {
            Contact contact;
            while (getline(inFile, contact.name)) {
                getline(inFile, contact.phoneNumber);
                getline(inFile, contact.email);
                contacts.push_back(contact);
            }
            inFile.close();
        }
    }

    void saveContacts() {
        ofstream outFile("contacts.txt");
        for (const auto& contact : contacts) {
            outFile << contact.name << endl;
            outFile << contact.phoneNumber << endl;
            outFile << contact.email << endl;
        }
        outFile.close();
    }

public:
    ContactManager() {
        loadContacts();
    }

    ~ContactManager() {
        saveContacts();
    }

    void addContact() {
        Contact contact;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, contact.name);
        cout << "Enter phone number: ";
        getline(cin, contact.phoneNumber);
        cout << "Enter email: ";
        getline(cin, contact.email);
        contacts.push_back(contact);
        cout << "Contact added successfully!" << endl;
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "No contacts available." << endl;
            return;
        }
        cout << left << setw(20) << "Name" << setw(15) << "Phone Number" << "Email" << endl;
        cout << string(50, '-') << endl;
        for (const auto& contact : contacts) {
            cout << left << setw(20) << contact.name << setw(15) << contact.phoneNumber << contact.email << endl;
        }
    }

    void editContact() {
        string name;
        cout << "Enter the name of the contact to edit: ";
        cin.ignore();
        getline(cin, name);
        for (auto& contact : contacts) {
            if (contact.name == name) {
                cout << "Editing contact: " << contact.name << endl;
                cout << "Enter new phone number (leave empty to keep current): ";
                string newPhoneNumber;
                getline(cin, newPhoneNumber);
                if (!newPhoneNumber.empty()) {
                    contact.phoneNumber = newPhoneNumber;
                }
                cout << "Enter new email (leave empty to keep current): ";
                string newEmail;
                getline(cin, newEmail);
                if (!newEmail.empty()) {
                    contact.email = newEmail;
                }
                cout << "Contact updated successfully!" << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void deleteContact() {
        string name;
        cout << "Enter the name of the contact to delete: ";
        cin.ignore();
        getline(cin, name);
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->name == name) {
                contacts.erase(it);
                cout << "Contact deleted successfully!" << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }
};

int main() {
    ContactManager manager;
    int choice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                manager.addContact();
                break;
            case 2:
                manager.viewContacts();
                break;
            case 3:
                manager.editContact();
                break;
            case 4:
                manager.deleteContact();
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
