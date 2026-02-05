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

};

SciElem *sciElem = new SciElem;

int main() {

    string isbn_input = "978038554734";
    int thirteenthnum;
    // Remove dashes from the input
    for (int i = 0; i < isbn_input.length(); i++) {
        if (isbn_input.substr(i, 1) == "-") {
            isbn_input.erase(i, 1);
            i--;
        }
    }
    //cout << isbn_input; 

    //add each digit multiplied alternating by 1 and 3
    int sum = 0;

    for (int i = 0; i < isbn_input.length(); i++) {
        if (i % 2) {
            sum += stoi(isbn_input.substr(i, 1)) * 1;
        }
        else {
            sum += stoi(isbn_input.substr(i, 1)) * 3;
        }
        
    }

    //10 - modulus gives digit 13

    if (10 - (sum % 10) != 0) {
        thirteenthnum = 10 - (sum % 10);
    }
    else {
        thirteenthnum = 0;
    }

    //if this 13 digit code is divisible by list of prime numbers, return category

    string isbnCode = isbn_input + to_string(thirteenthnum);
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
    else if ((isbnNumber % 17) == 0) {
        cout << "Astronomy";
    }
    else if ((isbnNumber % 19) == 0) {
        cout << "Math";
    }
    else {
        cout << "Give me a real isbn number.";
    }


    return 0;
}