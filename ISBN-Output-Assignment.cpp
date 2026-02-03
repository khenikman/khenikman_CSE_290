#include <iostream>
#include <vector>
using namespace std;

//change made by Kyle
vector<int> createCodes(vector<int> input) {

    int sum = 0;

    for (int i = 0; i < 13; i++){

        sum += input[i]; //sum all 12 numbers




    }

    if ((sum % 10) != 0) {
        thirteenthnum = 10 - (sum % 10);
    }
    else {
        thirteenthnum = 0;
    }

        if (input[i] % == 0)

    // Get a different random number each time the program runs
    srand(time(0));

    int random = rand() % 2;
    input.push_back(random);
    
    return input;

}

int main() {
    vector<int> numbers = {1,4,2,3,4,5,2,2,1,4,6,7};
    vector<int> thriteen_digits = createCodes(numbers);
    for (int i = 0; i < 13; i++) {
        cout << thriteen_digits[i] << " ";
    }
    
    
    return 0;
}
