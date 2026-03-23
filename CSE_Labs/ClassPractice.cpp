    #include <iostream>
    using namespace std;

class ClassPractice {

    public:
    int m = 3;

    void killAaron() {
        cout << "I bet march 11th will be an interesting day!" << sharedVariable << "\n";
    }



    virtual void Aaron() = 0;

    

    private:
    int baseclassvar = 10;

    protected:
    int sharedVariable = 67;

};

class derivedAaron: public ClassPractice {
    public:
    void executeAaron() {
        cout << m << sharedVariable << endl;
    }

    void Aaron() {
        cout << "gitgud";
    }
};

int main()
{

    //ClassPractice practice = ClassPractice();
    //practice.killAaron();

    derivedAaron practiceKill = derivedAaron();
    practiceKill.executeAaron();
    practiceKill.killAaron();
    practiceKill.Aaron();
    return 0;
}
