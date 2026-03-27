#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

int itemCount;
int bucketSize = 3;


struct Vehicle {
    string Model;
    string brand;
    int year;
    int horsepower;
    int mpgCity;
    int mpgHighway;
    string drivetrain;
    string transmission;
    string engine;
};

//Key = Model and Value is the hash of the model
//unordered_map<string, Vehicle> vehicleTable;
vector<list<Vehicle>> hashTable(5);
//hashTable.resize(5);

int setHashValue(string key);

void printTable() {

    for (int i = 0; i < hashTable.size(); i++) {
    cout << "Bucket " << i << ": ";

    for (const Vehicle& car : hashTable[i]) {
        cout << car.Model << " | ";
    }

    cout << endl;
}

}

bool insertInTable(Vehicle vehicle) {
    int hashvalue = setHashValue(vehicle.Model); //hashes the vehicle model
    //int loadFactor = itemCount / hashTable.size();
    //int listSize = hashTable.size(); // # of buckets exists
    int listcapacity = hashTable.capacity(); // size of vector
    if (listcapacity*(.75) <= itemCount) { // # of buckets used is >=  75% capacity, double capacity

        hashTable.resize(listcapacity * 2);

    }
    
    //cout << hashTable.capacity() << ". ";
    //cout << itemCount << "! \n";

    int bucket = (hashvalue % (hashTable.capacity() -1)); //bucket #'s we can use are from 0 - capacity
    int startPosition = bucket; // first bucket we are checking
    bool elementInserted = false; //element bucket not found
    //cout << bucket << " ";
    //while (!elementInserted) {
    if (hashTable[bucket].size() < bucketSize) {

        if (hashTable[bucket].empty()) { //current bucket is empty add element
            itemCount++;
        }
        hashTable[bucket].push_back(vehicle);
        elementInserted = true;
        return elementInserted;
    }
    else {
        while(!elementInserted) { //while element has not been inserted
            if (bucket+1 < listcapacity) { //check if we have more buckets before we have to loop back to the start of the list
                bucket++; //iterate to the next bucket
                if (hashTable[bucket].size() < bucketSize) {

                    if (hashTable[bucket].empty() == true) { //check if its empty

                        itemCount++;

                    }
                    hashTable[bucket].push_back(vehicle); //add to that bucket
                    elementInserted = true;
                    return elementInserted;
                }
            }
            else { //we have gone through the whole list
                bucket = 0;
                if (hashTable[bucket].size() < bucketSize) {
                    if (hashTable[bucket].empty()) {
                        itemCount++;
                    }
                    hashTable[bucket].push_back(vehicle);
                    elementInserted = true;
                    return elementInserted;
                }
            }
            if (bucket == startPosition) { //no position to insert
                cout << "element not inserted";
                return false;
            }
        }

    }
    itemCount++;
}



void deleteInTable(int key) {
    
}

int setHashValue(string key) {
    int hashcode = 0;
    for (char character : key) {
        hashcode += (int) character;
    }
    return hashcode;
}




//returns a vector of all the isbn string inputs without the delimeters
vector<Vehicle> parseFile() {

    //vector<string> all_isbn_inputs;
    vector<Vehicle> vehicleinfos;


    Vehicle newVehicle = Vehicle();

     ifstream inFile("vehicle_specifications.txt");  // open isbn file for reading

    if (!inFile) { // makes sure the file opens correctly
        cout << "Error opening file.\n";
        return vehicleinfos;
    }

    string line;
    //Model|Brand|Year|Horsepower|MPG_City|MPG_Highway|Drivetrain|Transmission|Engine
    while (getline(inFile, line)) {
        vector<string> info;
        string vehicleInfo = line;
        
        int startpos = 0;
        int counter = -1;
        // string Model;
        // string Brand;
        // int Year;
        // int MPG_City;
        // int MPG_Highway;
        // string Drivetrain;
        // string Transmission;
        // string Engine;
        
        for (int i = 0; i < 9; i++) {
            counter++;
            startpos = counter;
            while (counter < vehicleInfo.length() && vehicleInfo.substr(counter, 1) != "|" ) {
                counter++;
            }

            info.push_back(vehicleInfo.substr(startpos, counter-startpos));
        }
        newVehicle.Model = info.at(0);
        newVehicle.brand = info.at(1);
        newVehicle.year = stoi(info[2]);
        newVehicle.horsepower = stoi(info[3]);
        newVehicle.mpgCity = stoi(info[4]);
        newVehicle.mpgHighway = stoi(info[5]);
        newVehicle.drivetrain = info.at(6);
        newVehicle.transmission = info.at(7);
        newVehicle.engine = info.at(8);

        vehicleinfos.push_back(newVehicle);

        //vehicleTable


    }
        //All lines of file have been parsed through
        inFile.close();
    return vehicleinfos;



}
int main() {
    //cout << "Hello World github FINALLY works :)" << endl;
    //cout << "Sucessfully cloned git repo from main pc to laptop only took like 2 hrs. Super frustrating!" << endl;
    // vector<string> data = parseFile();
    // for (int i= 0; i< data.size(); i++) {
    //     cout << data[i] << "\n";
    // }
    //cout << setHashValue("2024 Subaru Forester");
    vector<Vehicle> vehiclesToAdd = parseFile();



    // for (int i = 0; i < vehiclesToAdd.size(); i++) {
    //     cout << vehiclesToAdd[i].Model << " | ";
    // }

    for (int i = 0; i < vehiclesToAdd.size(); i++) {
        insertInTable(vehiclesToAdd[i]);
    }

    printTable();

    return 0;
}
