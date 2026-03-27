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
    int listcapacity = hashTable.capacity(); // size of vector
    if (listcapacity*(.75) <= itemCount) { // # of buckets used is >=  75% capacity, double capacity

        hashTable.resize(listcapacity * 2);

    }

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
        cout << "\n" << vehicle.Model << " was added to the table!\n\n";
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
                    cout << "\n" << vehicle.Model << " was added to the table!\n\n";
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
                    cout << "\n" << vehicle.Model << " was added to the table!\n\n";
                    return elementInserted;
                }
            }
            if (bucket == startPosition) { //no position to insert
                cout << "\n" << "Element could not be inserted" << "\n\n";
                return false;
            }
        }

    }
    itemCount++;
}



bool deleteInTable(string Model) {
    int key = setHashValue(Model);
    for (auto bucket = hashTable.begin(); bucket != hashTable.end(); bucket++) {

        for(auto car = bucket->begin(); car != bucket->end(); car++) {

            if (setHashValue(car->Model) == key) {
                cout << "\n" << Model << " was deleted from the table!\n\n";
                bucket->erase(car);
                return true;
            }

        }
    }
    cout << "\n" << Model << " does not exist in the table!\n";
    return false;
}

int setHashValue(string key) {
    int hashcode = 0;
    for (char character : key) {
        hashcode += (int) character;
    }
    return hashcode;
}

bool findInTable(string Model) {

    int key = setHashValue(Model);
    for (auto bucket = hashTable.begin(); bucket != hashTable.end(); bucket++) {

        for(auto car = bucket->begin(); car != bucket->end(); car++) {

            if (setHashValue(car->Model) == key) {
                cout << "\n" << car->Model << " exists in the table!\n\n";
                return true;
            }

        }
    }
    cout << "\n" << Model << " does not exist in the table!\n\n";
    return false;
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

    vector<Vehicle> vehiclesToAdd = parseFile();

    for (int i = 0; i < vehiclesToAdd.size(); i++) {
        insertInTable(vehiclesToAdd[i]);
    }

    printTable();

    findInTable("2024 Subaru Forester");

    deleteInTable("2024 Honda Civic");

    deleteInTable("2024 Subaru Forester");

    printTable();

    findInTable("2024 Subaru Forester");

    return 0;
}
