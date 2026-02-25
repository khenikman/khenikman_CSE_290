#include "ISBNTester.h"
#include <iostream>
#include <vector>
using namespace std;



int main() {
    CodeEvaluator *evaluator = new ISBNEvaluator("ISBN_Codes.txt");

    evaluator->evaluate();
    evaluator->subjectEvaluate();
    evaluator->printCodes();
    
    // Loop over all the subjects
    string subject = "Biology"
    evaluator->printSubjectCodes(subject)

    

}

g++ main.cpp ISBNtester.cpp -o executable