//#include "ISBNTester.h"
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

    struct Node {
        string code;     // ISBN code
        // bool validCode;  // true/false
        string subject;  // Category for ISBN
        Node* next;      //Points to next node

        Node(string myData) : code(myData), //Constructor for creating nodes
        validCode(valid), subject(""), next(nullptr) {}



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

        if (head != nullptr) {
        
        cout << referenceHead->subject << ": ";
        }

        while (referenceHead != nullptr) {
            cout << referenceHead->code << " ";
            referenceHead = referenceHead->next;

        }

        delete referenceHead; //after we add the node we can delete our reference to the head node
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

        for (int i = 0; i < thirteen_digit_number.length() -1; i++) {
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

    vector<string> thirteen_digits = parseFile(); //grabs the list of parsed isbn #'s
    for (int i = 0; i < thirteen_digits.size(); i++) {

        string thirteen_digit_number = thirteen_digits[i];

        int primeNumber = is_isbn_element(thirteen_digit_number); // assigns the prime number to the check sum of the
                                                                  // thirteen digit number or 0 if it's not an isbn
    



     
    
    // isbn code we will be adding to the node
    string isbnCode = thirteen_digit_number;

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

    printlist(biologyHead); //prints some of the lists
    printlist(mathHead);
    printlist(frenchHead);

    return 0;



}