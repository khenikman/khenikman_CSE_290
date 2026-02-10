#include <iostream>
#include <vector>
using namespace std;

//change made by Kyle
//This Code works for all values of input less than 13 b/c int can only hold 12 values
vector<vector<int>> createCodes(vector<vector<int>> input) {

    int sum = 0;
    int thirteenthnum;
    vector<vector<int>> finalList;
    int randomThirteenth;

    //Change made by Hadit
    //Check if input size is less than 13.
    if (input.size() > 13) {
        cout <<"Error: input size exceeds 13. The maximun size allowed is 13."<< endl;
        return finalList; //This returns the empty vector
    }

    // Get a different random number each time the program runs
    srand(time(0));

    for (int vectorNum = 0; vectorNum < input.size(); vectorNum++) {

        sum = 0;

        vector<int> resultantThirteen = input[vectorNum];

        // ----------------- CASE 1  vectorNum % 3 == 0 -----
        // This code should add 1 more digit to twelveDigitCode 
        // All 13 digits, the sum is divisible by 10
        if (vectorNum % 3 == 0) {
            for (int i = 0; i < 12; i++){

            sum += resultantThirteen[i]; //sum all 12 digits
                

            }

            if (sum % 10 != 0) {
                thirteenthnum = 10 - (sum % 10);
            }
            else {
                thirteenthnum = 0;

            }

            resultantThirteen.push_back(thirteenthnum);

        }
        else {
            // -------  CASE 2  vectorNum % 3 != 0 
            // add 1 more digit to the twelveDigitCode - random number
            randomThirteenth = rand() % 10;
            resultantThirteen.push_back(randomThirteenth);
            
        }
    
        finalList.push_back(resultantThirteen);
    }

    
    return finalList;

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
