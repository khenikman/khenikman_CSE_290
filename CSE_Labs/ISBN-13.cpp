//#include "ISBNTester.h"
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

    struct Node {
        string isbncode;     // ISBN code
        string subject;  // Category for ISBN
        Node* next;      //Points to next node

        Node(string myData) : isbncode(myData), //Constructor for creating nodes
        subject(""), next(nullptr) {}



    };

    //Creating all the head nodes for the different subjects
    Node* biologyHead = nullptr;
    Node* englishHead = nullptr;
    Node* mathHead = nullptr;
    Node* physicsHead = nullptr;
    Node* psychologyHead = nullptr;
    Node* csHead = nullptr;
    Node* spanishHead = nullptr;
    Node* frenchHead = nullptr;
    Node* chemistryHead = nullptr;
    Node* uncategorizedHead = nullptr;

    //Appends new isbn nodes to the head nodes of each subject node
    void appendNode(Node*& head, Node* newNode) {
        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }

        cur->next = newNode;
    }

    //Prints the list of nodes
    void printlist(Node* head) {
        
        Node *referenceHead = head; //reference to head node we don't want to mess with that

        if (head == nullptr) {return;}   // <-- skip empty lists entirely        

        
        cout << referenceHead->subject << ": ";
        

        while (referenceHead != nullptr) {
            cout << referenceHead->isbncode << "  ";
            referenceHead = referenceHead->next;

        }
        cout << endl << endl;

    }

//prints a linked lists
void print_a_subject(Node* Subject) {
    printlist(Subject); 
}

//prints all of the linked lists
void print_all_subjects() {
    printlist(biologyHead); 
    printlist(chemistryHead);
    printlist(csHead);
    printlist(englishHead);
    printlist(frenchHead);
    printlist(mathHead);
    printlist(physicsHead);
    printlist(psychologyHead);
    printlist(spanishHead);
    printlist(uncategorizedHead);
}

//returns original isbn list with delimeters
vector<string> isbnlist() {


    vector<string> all_isbn_inputs_with_delimeters;

     ifstream inFile("isbn.txt");  // open isbn file for reading

    if (!inFile) { // makes sure the file opens correctly
        cout << "Error opening file.\n";
        return all_isbn_inputs_with_delimeters;
    }

    string line;
    while (getline(inFile, line)) {
        
        string thirteen_digit_number = line;
        all_isbn_inputs_with_delimeters.push_back(thirteen_digit_number); //add isbn to all_isbn_inputs_with_delimeters
    }
        //All lines of file have been parsed through
        inFile.close();
    return all_isbn_inputs_with_delimeters;


}   

//returns a vector of all the isbn string inputs without the delimeters
vector<string> parseFile() {

    vector<string> all_isbn_inputs;

     ifstream inFile("isbn.txt");  // open isbn file for reading

    if (!inFile) { // makes sure the file opens correctly
        cout << "Error opening file.\n";
        return all_isbn_inputs;
    }

    string line;
    while (getline(inFile, line)) {
        
        string thirteen_digit_number = line;

        for (int i = 0; i < thirteen_digit_number.length(); i++) {
            if (thirteen_digit_number.substr(i, 1) == "-") {
                thirteen_digit_number.erase(i, 1); //parse through each isbn and erase delimeters
                i--;
            }
        }
        all_isbn_inputs.push_back(thirteen_digit_number); //add isbn-13 to all_isbn_inputs
    }
        //All lines of file have been parsed through
        inFile.close();
    return all_isbn_inputs;


}

//Returns the sum of the first 12 digits and 
//determines if the isbn is real and its category 
int is_isbn_element(string thirteen_digit_number) { //takes in a 13 digit code

    int thirteenthnum;
    int sum = 0;

    for (int i = 0; i < thirteen_digit_number.length() -1; i++) {
            sum += stoi(thirteen_digit_number.substr(i, 1)); //sums up the first 12 digits
    }

    if (10 - (sum % 10) != 0) {
        thirteenthnum = 10 - (sum % 10); // for an isbn # to be real the sum of all
                                         // thirteen numbers must be divisible by 10
    }
    else {
        thirteenthnum = 0; // 12 numbers are divisible by 10
    }
    
    if (thirteenthnum == stoi(thirteen_digit_number.substr(12, 1))) { //checks the last digit
        return sum; //sum is the prime number we will be checking since this is a real isbn
    }
    else {
        return 0; //not a real isbn #
    }

    
}

//Assigns all of the head nodes with their respective isbn elements
void isbn_element() {

    vector<string> original_isbn = isbnlist(); //Isbn code we are adding to the node
    vector<string> thirteen_digits = parseFile(); //grabs the list of parsed isbn #'s
    for (int i = 0; i < thirteen_digits.size(); i++) {

        string thirteen_digit_number = thirteen_digits[i];

        int primeNumber = is_isbn_element(thirteen_digit_number); // assigns the prime number to the check sum of the
                                                                  // thirteen digit number or 0 if it's not an isbn
        

     
    
    // isbn code we will be adding to the node
    string isbnCode = original_isbn[i];

    // Adding potential ISBN to node
    Node *newIsbn = new Node(isbnCode);

    // if this 13 digit code is divisible by list of prime numbers, assign the respective head node
    switch (primeNumber) {

    case 0:

    newIsbn->subject = "Uncategorized";
    appendNode(uncategorizedHead, newIsbn);
    break;

    case 61:

    newIsbn->subject = "Biology";
    appendNode(biologyHead, newIsbn);
    break;

    case 71:

    newIsbn->subject = "English";
    appendNode(englishHead, newIsbn);
    break;

    case 97:

    newIsbn->subject = "Math";
    appendNode(mathHead, newIsbn);
    break;

    case 73:

    newIsbn->subject = "Physics";
    appendNode(physicsHead, newIsbn);
    break;

    case 103:

    newIsbn->subject = "Psychology";
    appendNode(psychologyHead, newIsbn);
    break;

    case 79 :

    newIsbn->subject = "Computer Science";
    appendNode(csHead, newIsbn);
    break;

    case 53 :

    newIsbn->subject = "Spanish";
    appendNode(spanishHead, newIsbn);

    break;

    case 83 :

    newIsbn->subject = "French";
    appendNode(frenchHead, newIsbn);

    break;

    case 113 :

    newIsbn->subject = "Chemistry";
    appendNode(chemistryHead, newIsbn);

    break;

    }
    
}
}


int main() {

    isbn_element(); //stores all isbn nodes in their respective categories

    int continueProgram = true;
    string choice;
    Node* selectedHead = nullptr;

    while (continueProgram) {
        
        cout << "Which ISBN subject do you want to view?\n"
         << "Options: all, biology, english, math, physics, psychology, computer science, "
         << "spanish, french, chemistry, uncategorized\n"
         << "Enter one: ";
        getline(cin, choice);
        if (choice == "all") { print_all_subjects(); continue; }
        else if (choice == "biology") { selectedHead = biologyHead; print_a_subject(selectedHead);}
        else if (choice == "english") { selectedHead = englishHead; print_a_subject(selectedHead);}
        else if (choice == "math") { selectedHead = mathHead; print_a_subject(selectedHead);}
        else if (choice == "physics") { selectedHead = physicsHead; print_a_subject(selectedHead);}
        else if (choice == "psychology") { selectedHead = psychologyHead; print_a_subject(selectedHead);}
        else if (choice == "computer science" || choice == "computerscience" || choice == "cs")
            { selectedHead = csHead; print_a_subject(selectedHead);}
        else if (choice == "spanish") { selectedHead = spanishHead; print_a_subject(selectedHead);}
        else if (choice == "french") { selectedHead = frenchHead; print_a_subject(selectedHead);}
        else if (choice == "chemistry") { selectedHead = chemistryHead; print_a_subject(selectedHead);}
        else if (choice == "uncategorized" || choice == "uncategorised")
            { selectedHead = uncategorizedHead; print_a_subject(selectedHead);}
        else {
        cout << "Invalid subject. Try again.\n";
        }

        


    }



    return 0;



}