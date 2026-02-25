//Take a string with 12 numbers and dashes
//string manip to get string with just numbers
//add each digit multiplied alternating by 1 and 3
//modulus 10 of sum
//10 - modulus gives digit 13
//if this 13 digit code is divisible by list of prime numbers, return category
//add code to appropriate linked list
//#include "ISBNTester.h"
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

    struct Node {
        string code;     // ISBN code
        //string name;     // Book name/title (or whatever "name" means)
        bool validCode;  // true/false
        string subject;
        Node* next;

        Node(string myData, bool valid ) : code(myData), 
        validCode(valid), subject(""), next(nullptr) {}



    };

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

    void printlist(Node* head) {
        
        Node *referenceHead = head;

        if (head != nullptr) {
        
        cout << referenceHead->subject << ": ";
        }

        while (referenceHead != nullptr) {
            cout << referenceHead->code << " ";
            referenceHead = referenceHead->next;

        }

        delete referenceHead;
    }

//SciElem *sciElem = new SciElem;
vector<string> parseFile() {

    vector<string> all_isbn_inputs;
    int linecounter = 0;

     ifstream inFile("isbn.txt");  // open file for reading

    if (!inFile) {
        cout << "Error opening file.\n";
        return all_isbn_inputs;
    }

    string line;
    while (getline(inFile, line)) {
        

        //int thirteenthnum;
        string thirteen_digit_number = line;

        for (int i = 0; i < thirteen_digit_number.length() -1; i++) {
            if (thirteen_digit_number.substr(i, 1) == "-") {
                thirteen_digit_number.erase(i, 1);
                i--;
            }
        }
        all_isbn_inputs.push_back(thirteen_digit_number);
        linecounter++;
    }
        // parse line here if needed
        inFile.close();
    return all_isbn_inputs;


}


   


int is_isbn_element(string thirteen_digit_number) {

    //cout << isbn_input; 

    //add each digit multiplied alternating by 1 and 3
    int thirteenthnum;
    int sum = 0;

    for (int i = 0; i < thirteen_digit_number.length() -1; i++) {
            sum += stoi(thirteen_digit_number.substr(i, 1));
            //cout << sum << endl;
    }

        
    

    //cout << sum << endl;

    if (10 - (sum % 10) != 0) {
        thirteenthnum = 10 - (sum % 10);
    }
    else {
        thirteenthnum = 0;
    }

    //10 - modulus gives digit 13

    //cout <<thirteen_digit_number.substr(12, 1);
    
    if (thirteenthnum == stoi(thirteen_digit_number.substr(12, 1))) {
        return sum;
    }
    else {
        return 0;
    }

    
}

void isbn_element() {



    vector<string> thirteen_digits = parseFile();
    for (int i = 0; i < thirteen_digits.size(); i++) {
        string thirteen_digit_number = thirteen_digits[i];
    if (is_isbn_element(thirteen_digit_number) != 0) {
        int primeNumber = is_isbn_element(thirteen_digit_number);
    



    //if this 13 digit code is divisible by list of prime numbers, return category
    string isbnCode = thirteen_digit_number;

    //cout << isbnCode << " ";
    
    //cout << "ISBN: " << isbnCode << " ";

    long long isbnNumber = stoll(isbnCode);

    Node *newIsbn = new Node(isbnCode, true);
    //newIsbn->data = isbnCode;

    //if this 13 digit code is divisible by list of prime numbers, return category
//cout << primeNumber << " ";
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
}

//int main() {

// string isbn_input = "9781861972712"; 



//     isbn_element(isbn_input);

    
//     return 0;

int main() {

  
    isbn_element();

    printlist(biologyHead);
    printlist(mathHead);
    printlist(frenchHead);

    return 0;



}