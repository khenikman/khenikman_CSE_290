# Tester
# ISBNTester.h

struct ISBNTester {
    vector<int> generateFirstNPrimeNumbers(int N);
    vector<int> getRandomNumberInVect(vector<int> primeVec, int N);
    vector<int> generatePrimeNumbers(int N);
    // GENERATE THE 12 digits
    vector<int> generate12dDigitsExactSum(int target, mt19937 &gen);

    // Create Codes 13 digit codes - kyle hadit, bianca
    vector< vector<int> > createCodes(vector< vector<int> > input)

    // Jeffrey Miguel
    void saveToFile(vector<vector<int>>) ISBNvectors, vector(int> list)

};

// Base class
class CodeEvaluator {
    protected :
    enum class Valid {
        NoValid,
        Valid

    };

    struct Node {
        string code;     // ISBN code
        //string name;     // Book name/title (or whatever "name" means)
        bool validCode;  // true/false
        string subject;
        Node* next;

        Node(string myData, bool valid ) : code(myData), 
        validCode(valid), subject(""), next(nullptr) {}



    };

    Node *head;
    // The first of the text file  51:71:
    vector<int> subjectCategories;

    public : 
    CodeEvaluator(const string &fileName) {
        head = nullptr;
        readFile(fileName);

    }

    // Member function
    // strip the prime numbers, translate to integers and to the the vector<int>
    vector<int> parse(string &code, char delimiter);
    // After reading file you data should be populated
    void readFile(fileName);
    void headInsert(vector<int> data, string name);

    // Virtual function that evaluate the ISBN code
    // Iterate over all the nodes and specify if the node is a valid
    // node
    virtual void evaulate() =0;

    // Iterate over the nodes that are valid and check what subject they 
    // might belong to.
    virtual void subjectEvaluate() = 0;

    virtual void printValidCodes() = 0;

    //string subjects = { biology, physics....}
    virtual void printSubjectCode(const &subjectName)





}


class ISBNEvaluator : public CodeEvaluator {
    public :
    ISBNEvaluator(const string& fileName) : Code(fileName)

    // Implementing the function that evaluate the ISBN code
    // Iterate over all the nodes and specify if the node is a valid
    // node
    void evaluate() override {
        Node *head;
        // while loop to iterate
        // inside the while loop you can determine if this node has 
        // a valid ISBN code

    }

    // Checking the first 12 digits of a valid code to find the subject
    void subjectEvaluate() override {


    }

    void printValidCodes() override{


    }

    void printSubjectCode() override {

    }



}


