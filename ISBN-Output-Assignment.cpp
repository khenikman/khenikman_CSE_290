#include <iostream>
#include <vector>
using namespace std;

//change made by Kyle
vector<vector<int>> createCodes(vector<vector<int>> input) {

    int sum = 0;
    int thirteenthnum;

    for (int vectorNum = 0; vectorNum < input.size(); vectorNum++) {
        sum = 0;
        for (int i = 0; i < 12; i++) {

            sum += input[vectorNum][i]; //sum all 12 digits
            



        }

        if (sum % 10 != 0) {
            thirteenthnum = 10 - (sum % 10);
        }
        else {
            thirteenthnum = 0;

        }

        input[vectorNum].push_back(thirteenthnum);
}
    //     if (input[i] % == 0)

    // // Get a different random number each time the program runs
    // srand(time(0));

    // int random = rand() % 2;

    
    return input;

}

int main() {
    vector<int> numbers1 = {1,4,2,3,4,5,2,2,1,4,6,7}; //41
    vector<int> numbers2 = {1,4,2,3,4,5,2,2,1,4,6,8}; //42
    vector<int> numbers3 = {1,4,2,3,4,5,2,2,1,4,6,9}; //43
    vector<int> numbers4 = {1,4,2,3,4,5,2,2,1,4,6,6}; //40
    vector<int> numbers5 = {1,4,2,3,4,5,2,2,1,4,6,5}; //39
    vector<vector<int>> twodarray = {numbers1, numbers2, numbers3, numbers4, numbers5};
    vector<vector<int>> thriteen_digits = createCodes(twodarray);
    for (int vectorNum = 0; vectorNum < 5; vectorNum++) {
        for (int i = 0; i < 13; i++) {
            cout << thriteen_digits[vectorNum][i] << " ";
        }
        cout << endl;
    }
    
    
    return 0;
}
