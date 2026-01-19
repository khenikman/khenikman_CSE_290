#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

//Returns the highest number in a set of 100 random numbers and the number of times it appeared
int main() {
    int numbers[100]; //100 numbers being used 
    // int k;
    // cout << "How many of the top numbers do you want to see? ";
    // cin >> k; //value for 
    int highestNums[1]; //I made the highest number an array
    int numAppearance = 1; //how many times the top number appears

    srand(time(0)); //makes random truly random every code run

    for (int i = 0; i < 100; i++) {
        int random = rand() % 100;
        numbers[i] = random; //sets each value of the array to a random value between 0 and 99
    }

    // for (int i = 0; i < k; i++) {
    //     highestNums[i] = -1; //our dataset does not deal with negative numbers so this is out placeholder
    // }
    
    highestNums[0] = -1; //our dataset does not deal with negative numbers so this is out placeholder


    int getArrayLength = sizeof(numbers) / sizeof(numbers[0]); //finds the size of the numbers array

    cout << "List of numbers: ";

    for (int i = 0; i < getArrayLength; i++) {
        cout << numbers[i] << " "; //displays all random numbers
    }
    
    

    for (int i = 0; i < getArrayLength; i++) {

        if (highestNums[0] == numbers[i]) { //has this highest number been seen, then add one to its appearance
            numAppearance++;
        }

        if (highestNums[0] < numbers[i]) { //checks if the last number in the set of highestNumbers is less than a new value, if it is new highest number and 1 appearance
            highestNums[0] = numbers[i]; 
            numAppearance = 1;
        }

        //sort(numbers, numbers + 100); //Sorts the highest numbers data in ascending order
        
    }




    cout << " The highest number: " << highestNums[0] << " appeared " << numAppearance << " times!"; //prints out the highest number and how many times it appeared
    
    return 0;

}
