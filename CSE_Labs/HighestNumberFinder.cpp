#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

//Returns the highest number in a set of 10 random numbers
int main() {
    vector<int> numbers ={};

    // Get a different random number each time the program runs
    srand(time(0));

    for (int i = 0; i < 10; i++) {
        int random = rand() % 100;
        numbers.push_back(random);
    }
    
    cout << "List of numbers: ";

    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    
    
    int highest = numbers[0];
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] > highest) {
            highest = numbers[i];
        }
    }

    cout << endl << "The highest number is: " << highest << endl;
    return 0;
}
