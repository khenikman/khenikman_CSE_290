//Take a string with 12 numbers and dashes
//string manip to get string with just numbers
//add each digit multiplied alternating by 1 and 3
//modulus 10 of sum
//10 - modulus gives digit 13
//if this 13 digit code is divisible by list of prime numbers, return category
//add code to appropriate linked list
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct SciElem {

std::string name;

std::string isbnCode;

public:

SciElem(string bookName, string code) { //standard OOP element allocation

    name = bookName;
    isbnCode = code;

}

};

//SciElem *sciElem = new SciElem;

bool is_isbn_element(string thirteen_digit_number) {

    //cout << isbn_input; 

    //add each digit multiplied alternating by 1 and 3
    int thirteenthnum;
    int sum = 0;

    for (int i = 0; i < thirteen_digit_number.length() -1; i++) {
        if (i % 2 == 0) {
            sum += stoi(thirteen_digit_number.substr(i, 1)) * 1;
            //cout << sum << endl;
        }
        else {
            sum += stoi(thirteen_digit_number.substr(i, 1)) * 3;
            //cout << sum << endl;
        }
        
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
        return true;
    }
    else {
        return false;
    }

    
}

void isbn_element(string isbn_input) {


    int thirteenthnum;
    string thirteen_digit_number = isbn_input;

    for (int i = 0; i < thirteen_digit_number.length() -1; i++) {
        if (thirteen_digit_number.substr(i, 1) == "-") {
            thirteen_digit_number.erase(i, 1);
            i--;
        }
    }

    if (is_isbn_element(thirteen_digit_number)) {
    
    

    //cout << isbn_input; 

    //add each digit multiplied alternating by 1 and 3
    

    //if this 13 digit code is divisible by list of prime numbers, return category
    string isbnCode = thirteen_digit_number;
    
    cout << "ISBN: " << isbnCode << "\n";

    long long isbnNumber = stoll(isbnCode);

    //if this 13 digit code is divisible by list of prime numbers, return category
    // Chemistry: 3
    // Physics: 7
    // Biology: 13
    // Astronomy: 17
    // Math: 19
    if ((isbnNumber % 3) == 0) {
        cout << "Chemistry";
    }
    else if ((isbnNumber % 7) == 0) {
        cout << "Physics";
    }
    else if ((isbnNumber % 13) == 0) {
        cout << "Physics";
    }
    else if ((isbnNumber % 17) == 0) {
        cout << "Astronomy";
    }
    else if ((isbnNumber % 19) == 0) {
        cout << "Math";
    }
    else {
        cout << "Give me a real isbn number.";
    }
    }
    else { //add code to list of non-isbn codes
        cout << "Not an isbn number";
    }
}

//int main() {

// string isbn_input = "9781861972712"; 



//     isbn_element(isbn_input);

    
//     return 0;

int main() {

    SciElem book1 = SciElem("Gatsby", "9780306406157");
    SciElem book2 =  SciElem("Gatsby2", "978-0-306-40615-7");
    SciElem book3 = SciElem("Gatsby3", "9780306406158");
    SciElem book4 = SciElem("Gatsby4", "9780306406157");
    SciElem book5 = SciElem("Gatsby5", "9781861972712");
    SciElem book6 = SciElem("Gatsby6", "978-0-306-40615-7-");
    
    SciElem[] library = {book1,book2,book3,book4,book5,book6};

    Node* chemistryHead = nullptr;
    Node* physicsHead = nullptr;
    Node* biologyHead = nullptr;
    Node* astronomyHead = nullptr;
    Node* mathHead = nullptr;
    Node* invalidHead = nullptr;

    // string tests[] = {
    //     "9780306406157",      // valid, no dashes
    //     "978-0-306-40615-7",  // valid, with dashes
    //     "9780306406158",      // invalid check digit
    //     "9781861972712",      // valid (likely reveals your sum loop bug)
    //     "978-0-306-40615-7-"  // trailing dash edge case
    // };

    for (auto &t : library) {
        cout << "\n\nTEST: " << t << "\n";
        isbn_element(t);
        cout << "\n";
    }

    return 0;



}