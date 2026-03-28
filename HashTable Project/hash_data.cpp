#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;


int bucketCount; //stores the amount of buckets in use
int bucketSize = 3; //amount of the buckets in a vehicle list


struct Vehicle {
    string Model; //String that will be hashed to store the vehicle objects
    string brand;
    int year;
    int horsepower;
    int mpgCity;
    int mpgHighway;
    string drivetrain;
    string transmission;
    string engine;
};

//Hash Map that originally can store 5 lists holding bucketSize buckets
vector<list<Vehicle>> hashTable(5);

//Prototype for getHashValue
int getHashValue(string key);

void printTable() { //prints all vehicles in the hash table

    for (int i = 0; i < hashTable.size(); i++) {
    cout << "Bucket " << i << ": ";

    for (const Vehicle& car : hashTable[i]) {
        cout << car.Model << " | ";
    }

    cout << endl;
}

}

bool insertInTable(Vehicle vehicle) {
    int hashvalue = getHashValue(vehicle.Model); //hashes the vehicle model
    int listcapacity = hashTable.capacity(); // size of vector
    if (listcapacity*(.75) <= bucketCount) { // # of buckets used is >=  75% capacity, then double capacity

        hashTable.resize(listcapacity * 2);

    }

    int bucket = (hashvalue % (hashTable.capacity() -1)); //bucket #'s we can use are from 0 - (capacity - 1)
    int startPosition = bucket; // first bucket we are checking
    bool elementInserted = false; //element bucket not found

    if (hashTable[bucket].size() < bucketSize) { //can we fit more in this list

        if (hashTable[bucket].empty()) { //current bucket is empty add element
            bucketCount++; //bucket list is no longer empty
        }
        hashTable[bucket].push_back(vehicle); //add element
        elementInserted = true;
        cout << "\n" << vehicle.Model << " was added to the table!\n\n";
        return elementInserted;
    }
    else { //current list is full
        while(!elementInserted) { //while element has not been inserted
            if (bucket+1 < listcapacity) { //check if we have more buckets before we have to loop back to the start of the list
                bucket++; //iterate to the next bucket
                if (hashTable[bucket].size() < bucketSize) { //checks if next bucket has room

                    if (hashTable[bucket].empty() == true) { //check if its empty

                        bucketCount++; //bucket is no longer epmty

                    }
                    hashTable[bucket].push_back(vehicle); //add to that bucket
                    elementInserted = true;
                    cout << "\n" << vehicle.Model << " was added to the table!\n\n";
                    return elementInserted;
                }
            }
            else { //we have gone through the whole list
                bucket = 0; //start at beginning
                if (hashTable[bucket].size() < bucketSize) {
                    if (hashTable[bucket].empty()) {
                        bucketCount++;
                    }
                    hashTable[bucket].push_back(vehicle);
                    elementInserted = true;
                    cout << "\n" << vehicle.Model << " was added to the table!\n\n";
                    return elementInserted;
                }
            }
            if (bucket == startPosition) { //end once we iterate through the entire vector
                cout << "\n" << "Element could not be inserted" << "\n\n";
                return false;
            }
        }

    }
    bucketCount++;
}



bool deleteInTable(string Model) { //iterates through the vector to find the element to delete
    int key = getHashValue(Model); //turns the string for the vehicle model into the key we want
    for (auto bucket = hashTable.begin(); bucket != hashTable.end(); bucket++) {

        for(auto car = bucket->begin(); car != bucket->end(); car++) {

            if (getHashValue(car->Model) == key) {
                cout << "\n" << Model << " was deleted from the table!\n\n";
                bucket->erase(car); //delete the vehicle
                if (bucket->empty() == true) {
                    bucketCount--; //bucket empty after deletion
                }
                return true;
            }

        }
    }
    cout << "\n" << Model << " does not exist in the table!\n";
    return false;
}

int getHashValue(string Model) { //return the ASCII hash for the model of a vehicle
    int hashcode = 0;
    for (char character : Model) {
        hashcode += (int) character;
    }
    return hashcode;
}

bool findInTable(string Model) { //iterates through the table to find hash key value pair

    int key = getHashValue(Model);
    for (auto bucket = hashTable.begin(); bucket != hashTable.end(); bucket++) {

        for(auto car = bucket->begin(); car != bucket->end(); car++) {

            if (getHashValue(car->Model) == key) {
                cout << "\n" << car->Model << " exists in the table!\n\n";
                return true;
            }

        }
    }
    cout << "\n" << Model << " does not exist in the table!\n\n";
    return false;
}



//returns a vector of vector<<Vehicle>> to be iterated over by the insert function
vector<Vehicle> parseFile() {

    vector<Vehicle> vehicleinfos;


     ifstream inFile("vehicle_specifications.txt");  // open vehicle file for reading

    if (!inFile) { // makes sure the file opens correctly
        cout << "Error opening file.\n";
        return vehicleinfos;
    }

    string line;
    //Model|Brand|Year|Horsepower|MPG_City|MPG_Highway|Drivetrain|Transmission|Engine
    while (getline(inFile, line)) {
        vector<string> info; //stores all vehicle info data in an easy way to add to variables
        string vehicleInfo = line;

        Vehicle newVehicle = Vehicle(); //creates a vehicle object to store parsed data
        
        int startpos = 0; //variable to help with parsing the string
        int counter = -1; //variable to help with parsing the string

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

    }
        //All lines of file have been parsed through
        inFile.close();
    return vehicleinfos;



}
int main() {

    vector<Vehicle> vehiclesToAdd = parseFile(); //parses through the vehicle list file

    for (int i = 0; i < vehiclesToAdd.size(); i++) {
        insertInTable(vehiclesToAdd[i]); //goes through the vector of vehicles and inserts them by hash
    }

    printTable(); //prints all table values

    findInTable("2024 Subaru Forester");

    deleteInTable("2024 Honda Civic");

    deleteInTable("2024 Subaru Forester");

    printTable();

    findInTable("2024 Subaru Forester");

    return 0;
}
