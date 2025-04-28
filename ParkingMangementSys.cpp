#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Car {
    int id;
    string plateNumber; 
    string model;       
    Car* next;          
};

class ParkingLot {
private:
    Car* head; 
    int capacity; 
    int currentCount;
    int idCounter=1; 
    int id;

public:
    ParkingLot(int cap) : head(nullptr), capacity(cap), currentCount(0) {}

    bool parkCar(string plateNumber, string model) {

        if (carExists(plateNumber)) {
            cout << "\t\t\t\t---ERROR: A car with this plate number is already parked!---" << endl;
            system("PAUSE");
            return false;
        }
        id=idCounter++;
        Car* newCar = new Car{id,plateNumber, model, head};
        head = newCar;
        currentCount++;
        cout << "\t\t\t\tCar parked: " << plateNumber << " (" << model << ")." << "Your Slot id is: "<<id<<endl;
        system("PAUSE");
        return true;
    }

    
    bool removeCar(string plateNumber) {
        if (head == nullptr) {
            cout << "\t\t\t\tParking lot is empty!" << endl;
            system("PAUSE");
            return false;
        }
        Car* temp = head;
        Car* prev = nullptr;

        while (temp != nullptr) {
            if (temp->plateNumber == plateNumber) {
                if (prev == nullptr) {
                    head = temp->next; 
                } else {
                    prev->next = temp->next; // Bypass the node
                }
                delete temp;
                currentCount--;
                cout << "\t\t\t\tCar with plate number: "<< plateNumber <<" is removed."<< endl;
                system("PAUSE");
                return true;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "\t\t\t\tCar not found: " << plateNumber << endl;
        system("PAUSE");
        return false;
    }

    void searchCar(ParkingLot& carLot, const string& plateNumber) {
       Car* temp = carLot.head;
        while (temp != nullptr) {
          if (temp->plateNumber == plateNumber) {
            cout << "\t\t\t\tCar Found!" << endl;
            cout << "\t\t\t\tSlot ID: " << temp->id << ", Number Plate: " << temp->plateNumber
                 << ", Model: " << temp->model << endl;
            system("PAUSE");
            return;
          }
        temp = temp->next;
    }
    cout << "\t\t\t\t---ERROR: Car with number plate " << plateNumber << " not found!---" << endl;
    system("PAUSE");
    return;
    }


    
    void displayCars() {
        
        if (head == nullptr) {
            cout << "\t\t\t\tParking lot is empty!" << endl;
            return;
        }

        Car* temp = head;
        cout << "\t\t\t\tParked cars:" << endl;
        while (temp != nullptr) {
            cout << "\t\t\t\tPlate: " << temp->plateNumber << ", Model: " << temp->model << endl;
            temp = temp->next;
        }
    }

    bool carExists(string plateNumber) {
        Car* temp = head;
        while (temp != nullptr) {
           if (temp->plateNumber == plateNumber) return true;
           temp = temp->next;
        }
        return false;
    }

    bool isFull(){
        if (currentCount >= capacity) {
            cout << "\t\t\t\t---ERROR: Car lot is full!---" << endl;
            return true;
        }
          return false;
    }

    void showAvailableSlotCar(){
        cout<<"\t\t\t\t========  AVAILABLE CAR SLOTS ===========\n\n";
        cout<<"\t\t\t\tAvailable slots: "<<capacity-currentCount<<"/"<<capacity<<endl;
    }    

    
    ~ParkingLot() {
        while (head != nullptr) {
            Car* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
//----------------------------------------------------------------------------------------------------------------------------------------------
class Bike {
public:
    string plateNumber;
    string model;
    int id;
    Bike* left;
    Bike* right;
    int height;

    Bike(string plate, string model, int id) : plateNumber(plate), model(model), id(id), left(nullptr), right(nullptr), height(1) {}
};

class BikeParkingAVL {
private:
    Bike* root;
    int capacity;
    int currentCount;
    int parkingIdCounter; 

     Bike* searchByPlateHelper(Bike* node, const string& plate) {
        if (node == nullptr || node->plateNumber == plate) {
            return node;
        }

        if (plate < node->plateNumber) {
            return searchByPlateHelper(node->left, plate);
        }
        return searchByPlateHelper(node->right, plate);
    }

public:
    BikeParkingAVL(int cap) : root(nullptr), capacity(cap), currentCount(0), parkingIdCounter(1) {}
     void searchByPlate(const string& plate) {
        Bike* result = searchByPlateHelper(root, plate);
        if (result) {
            cout << "\t\t\t\tBike found: Plate: " << result->plateNumber
                 << ", Model: " << result->model
                 << ", Parking ID: " << result->id << endl;
                 system("PAUSE");
        } else {
            cout << "\t\t\t\t---ERROR: Bike with plate number " << plate << " not found!---" << endl;
            system("PAUSE");
        }
    }
    int getHeight(Bike* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    void updateHeight(Bike* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalance(Bike* node) {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    bool isFull() {
        if (currentCount >= capacity) {
            cout << "\t\t\t\t---ERROR: Parking lot is full!---" << endl;
            system("PAUSE");
            return true;
        }
        return false;
    }

    Bike* rightRotate(Bike* y) {
        Bike* x = y->left;
        Bike* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Bike* leftRotate(Bike* x) {
        Bike* y = x->right;
        Bike* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Bike* insert(Bike* node, string plate, string model, int id) {
        if (node == nullptr) {
            return new Bike(plate, model, id);
        }

        if (plate < node->plateNumber) {
            node->left = insert(node->left, plate, model, id);
        } else if (plate > node->plateNumber) {
            node->right = insert(node->right, plate, model, id);
        } else {
            return node; 
        }

        updateHeight(node);

        int balance = getBalance(node);
        if (balance > 1 && plate < node->left->plateNumber) return rightRotate(node);
        if (balance < -1 && plate > node->right->plateNumber) return leftRotate(node);
        if (balance > 1 && plate > node->left->plateNumber) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && plate < node->right->plateNumber) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Bike* deleteNode(Bike* root, string plate, int& removedId, bool& found) {
        if (root == nullptr) {
            found = false;
            return root;
        }

        if (plate < root->plateNumber) {
            root->left = deleteNode(root->left, plate, removedId, found);
        } else if (plate > root->plateNumber) {
            root->right = deleteNode(root->right, plate, removedId, found);
        } else {
            found = true;
            removedId = root->id;

            if (root->left == nullptr || root->right == nullptr) {
                Bike* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }

            Bike* temp = minValueNode(root->right);
            root->plateNumber = temp->plateNumber;
            root->model = temp->model;
            root->id = temp->id;
            root->right = deleteNode(root->right, temp->plateNumber, removedId, found);
        }

        updateHeight(root);

        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Bike* minValueNode(Bike* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void displayBikes(Bike* node) {
        if (node == nullptr) return;
        displayBikes(node->left);
        cout << "\t\t\t\tParking ID: " << node->id << ", Plate: " << node->plateNumber << ", Model: " << node->model << endl;
        displayBikes(node->right);
    }

    bool checkDuplicatePlate(string plate) {
        Bike* current = root;
        while (current != nullptr) {
            if (plate == current->plateNumber) {
                return true;
            }
            if (plate < current->plateNumber) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void insertBike(string plate, string model) {
        if (isFull()) return;

        // Check for duplicate plate number
        if (checkDuplicatePlate(plate)) {
            cout << "\t\t\t\t---ERROR: Bike with plate number " << plate << " already parked!" << endl;
            system("PAUSE");
            return;
        }

        int id = parkingIdCounter++;

        root = insert(root, plate, model, id);
        currentCount++;
        cout << "\t\t\t\tBike parked successfully! Your parking ID is: " << id << endl;
        system("PAUSE");
    }

    void removeBike(string plate) {
        int removedId;
        bool found = false;
        root = deleteNode(root, plate, removedId, found);
        if (found) {
            currentCount--;
            cout << "\t\t\t\tBike with plate number " << plate << " has been removed. Parking ID " << removedId << " is now available." << endl;
            system("PAUSE");
        } else {
            cout << "\t\t\t\t---ERROR: Bike with plate number " << plate << " not found!---" << endl;
            system("PAUSE");
        }
    }

    void showBikes() {
        if (currentCount == 0) {
            cout << "\t\t\t\tNo bikes are currently parked." << endl;
            return;
        }

        cout << "\t\t\t\tParked bikes: " << endl;
        displayBikes(root);
    }

    void showAvailableSlotsbike() {
        cout << "\t\t\t\tAvailable slots: " << capacity - currentCount << "/" << capacity << endl;
    }
};
//-----------------------------------------------------------------------------------------------------------------------------------------------
class Truck {
public:
    string numberPlate;
    string model;

    Truck(const string& numberPlate, const string& model) : numberPlate(numberPlate), model(model) {}
};

class HashMap {
private:
    vector<list<pair<int, Truck>>> table; 
    int numBuckets;                       
    int idCounter;
    int currentCount=0;
    int capacity;

    int hashFunction(int key) {
        return key % numBuckets;
    }

public:
    int getNumBuckets(){
        return numBuckets;
    }

    const vector<list<pair<int, Truck>>>& getTable() const {
        return table;
    }

    HashMap(int capacity) : numBuckets(capacity), idCounter(1), capacity(capacity) {
        table.resize(capacity);
    }

    void parkTruck(const string& numberPlate, const string& model) {
        int slotID = idCounter++;
        int index = hashFunction(slotID);

        for (const auto& pair : table[index]) {
            if (pair.second.numberPlate == numberPlate) {
                cout << "\t\t\t\t---ERROR: Truck with number plate " << numberPlate << " is already parked!---" << endl;
                system("PAUSE");
                return; 
            }
        }

        Truck newTruck(numberPlate, model);
        table[index].emplace_back(slotID, newTruck);
        currentCount++;
        cout << "\t\t\t\tTruck parked successfully! Slot ID: " << slotID << endl;
        system("PAUSE");
    }

    void removeTruck(int slotID) {
        int index = hashFunction(slotID);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == slotID) {
                cout << "\t\t\t\tTruck with number plate " << it->second.numberPlate 
                     << " removed successfully from Slot ID: " << slotID << endl;
                table[index].erase(it);
                system("PAUSE");
                return;
            }
        }
        cout << "\t\t\t\tTruck with Slot ID " << slotID << " not found!" << endl;
        system("PAUSE");
    }

    void searchTruck(HashMap& truckLot, const string& plateNumber) {
        for (int i = 0; i < truckLot.getNumBuckets(); ++i) {
            for (const auto& pair : truckLot.getTable()[i]) {
                if (pair.second.numberPlate == plateNumber) {
                    cout << "\t\t\t\tTruck Found!" << endl;
                    cout << "Slot ID: " << pair.first << ", Number Plate: " << pair.second.numberPlate
                     << ", Model: " << pair.second.model << endl;
                    system("PAUSE");
                    return;
                }
            }
        }
        cout << "\t\t\t\t---ERROR: Truck with number plate " << plateNumber << " not found!---" << endl;
        system("PAUSE");
    }


    void displayTrucks() {
        bool empty = true;

        for (int i = 0; i < numBuckets; ++i) {
            for (const auto& pair : table[i]) {
                cout << "\t\t\t\tSlot ID: " << pair.first
                     << ", Number Plate: " << pair.second.numberPlate
                     << ", Model: " << pair.second.model << endl;
                empty = false;
            }
        }
        if(!empty){
            system("PAUSE");
            return;
        }

        if (empty) {
            cout << "\t\t\t\tNo trucks parked." << endl;
        }
    }

    void showAvailableSlotsTruck() {
        cout<<"\t\t\t\t========  AVAILABLE TRUCK SLOTS ===========\n\n";
        cout << "\t\t\t\tAvailable slots: " << capacity - currentCount << "/" << capacity << endl;
    }

    bool isFull(){
        if (currentCount >= capacity) {
            cout << "\t\t\t\t---ERROR: Truck lot is full!---" << endl;
            return true;
        }
          return false;
    }
};


void welcomeScreen() {
    cout << "\n\n\t\t\t\t====================================================\n";
    cout << "\n\n\n\t\t\t\t     Welcome to Parking Management System   \n";
    cout << "\n\n\n\t\t\t\t====================================================\n";
    cout << endl;
}

void showMenu() {
    system("CLS");
    cout << "\t\t\t\t====================================================\n";
    cout << "\n\t\t\t\t                     MENU                           \n";
    cout << "\n\t\t\t\t====================================================\n";
    cout << "\n\n\t\t\t\tPlease select the type of vehicle:\n";
    cout << "\t\t\t\t1. Car\n";
    cout << "\t\t\t\t2. Bike\n";
    cout << "\t\t\t\t3. Truck\n";
    cout << "\t\t\t\t4. Display All Parked Vehicles\n";
    cout << "\t\t\t\t5. Exit\n";
    cout << "\t\t\t\tEnter your choice: ";
}

bool validatePlateInput(string& plate, string& model) {
    do {
        cin.ignore();
        cout << "\t\t\t\tEnter plate number: ";
        getline(cin, plate);
        cout << "\t\t\t\tEnter model: ";
        getline(cin, model);
        if (plate.empty() ) {
            cout << "\t\t\t\t---ERROR: Plate number cannot be empty---" << endl;
        }
    } while (plate.empty());
    return true;
}


int main() {
    welcomeScreen();

    int carCapacity, bikeCapacity, truckCapacity;

    cout << "\t\t\t\tEnter car parking lot capacity: ";
    while (true) {
        cin >> carCapacity;
        if (cin.fail() || carCapacity <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\t\t\t\t---ERROR: Invalid input. Please enter a valid number greater than 0---\n";
            cout << "\t\t\t\tEnter car parking lot capacity: ";
        } else {
            break;
        }
    }
    ParkingLot carLot(carCapacity);

    cout << "\t\t\t\tEnter bike parking lot capacity: ";
    while (true) {
        cin >> bikeCapacity;
        if (cin.fail() || bikeCapacity <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\t\t\t\t---ERROR: Invalid input. Please enter a valid number greater than 0---\n";
            cout << "\t\t\t\tEnter bike parking lot capacity: ";
        } else {
            break;
        }
    }
    BikeParkingAVL bikeLot(bikeCapacity);

    cout << "\t\t\t\tEnter truck parking lot capacity: ";
    while (true) {
        cin >> truckCapacity;
        if (cin.fail() || truckCapacity <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\t\t\t\t---ERROR: Invalid input. Please enter a valid number greater than 0---\n";
            cout << "\t\t\t\tEnter truck parking lot capacity: ";
        } else {
            break;
        }
    }
    HashMap truckLot(truckCapacity);

    int choice;

    while (true) {
        showMenu();

        while (true) {
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > 5) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\t\t\t\t---ERROR: Invalid input. Enter a number between 1 and 5---\n";
                system("PAUSE");
                showMenu();
            } else {
                break;
            }
        }
        system("CLS");

        switch (choice) {
            case 1: {
                int carChoice;
                cout << "\n\n\n\t\t\t\t===== Car Parking Management =====\n\n";
                cout << "\t\t\t\t1. Park a car\n";
                cout << "\t\t\t\t2. Remove a car\n";
                cout << "\t\t\t\t3. Display parked cars\n";
                cout << "\t\t\t\t4. View available parking slots\n";
                cout << "\t\t\t\t5. Search a Car\n";
                cout << "\t\t\t\t6. Back to main menu\n";

                while (true) {
                    cout << "\t\t\t\tEnter your choice: ";
                    cin >> carChoice;
                    if (cin.fail() || carChoice < 1 || carChoice > 6) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "\t\t\t\t---ERROR: Invalid input. Enter a number between 1 and 4---\n";
                    } else {
                        system("CLS");
                        break;
                    }
                }
                

                switch (carChoice) {
                    case 1: {
                        cout << "\n\n\n\t\t\t\t=========  PARK A CAR ==========\n\n";
                        if (carLot.isFull()) {
                            cout << "\t\t\t\t--Cannot park more cars.--\n";
                            system("PAUSE");
                            break;
                        }
                       
                        string plate, model;
                        validatePlateInput(plate,model);
                        carLot.parkCar(plate, model);
                        break;
                    }
                    case 2: {
                        cout << "\n\n\n\t\t\t\t=========  REMOVE A CAR ==========\n\n";
                        string plate;
                        cout << "\t\t\t\tEnter car plate number to remove: ";
                        cin >> plate;
                        carLot.removeCar(plate);
                        break;
                    }
                    case 3:
                        cout << "\n\n\n\t\t\t\t=========  DISPLAY CARS ==========\n\n";
                        carLot.displayCars();
                        system("PAUSE");
                        break;
                    case 4:
                        carLot.showAvailableSlotCar();
                        break;
                    case 5:{
                        cout << "\n\n\n\t\t\t\t=========  SEARCH A CAR ==========\n\n";
                        string plate;
                        cout << "\t\t\t\tEnter car plate number to search: ";
                        cin >> plate;
                        carLot.searchCar(carLot,plate);
                        break;
                    }
                    case 6:
                        break;
                    
                }
                break;
            }
            case 2: {
                int bikeChoice;
                cout << "\n\n\n\t\t\t\t===== Bike Parking Management =====\n\n";
                cout << "\t\t\t\t1. Park a bike\n";
                cout << "\t\t\t\t2. Remove a bike\n";
                cout << "\t\t\t\t3. Display parked bikes\n";
                cout << "\t\t\t\t4. View available parking slots\n";
                cout << "\t\t\t\t5. Search parked bikes\n";
                cout << "\t\t\t\t6. Back to main menu\n";

                while (true) {
                    cout << "\t\t\t\tEnter your choice: ";
                    cin >> bikeChoice;
                    if (cin.fail() || bikeChoice < 1 || bikeChoice > 6) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "-\t\t\t\t--ERROR: Invalid input. Enter a number between 1 and 6---\n";
                    } else {
                        system("CLS");
                        break;
                    }
                }

                switch (bikeChoice) {
                    case 1: {
                        cout << "\n\n\n\t\t\t\t=========  PARK A BIKE ==========\n\n";
                        if (bikeLot.isFull()) {
                            cout << "\t\t\t\tBike lot is full. Cannot park more bikes.\n";
                            system("PAUSE");
                            break;
                        }
                        string plate, model;
                        cout << "\t\t\t\tEnter bike plate number: ";
                        cin.ignore();
                        getline(cin, plate);
                        if (plate.empty()) {
                        cout << "\t\t\t\t---ERROR: Plate number cannot be empty!" << endl;
                        break;
                    }
                        cout << "\t\t\t\tEnter bike model (optional): ";
                        getline(cin, model);
                        bikeLot.insertBike(plate, model);
                        break;
                    }
                    case 2: {
                        cout << "\n\n\n\t\t\t\t=========  REMOVE A BIKE ==========\n\n";
                        string plate;
                        cout << "\t\t\t\tEnter bike plate number to remove: ";
                        cin.ignore();
                        getline(cin, plate);
                        bikeLot.removeBike(plate);
                        break;
                    }
                    case 3:
                        cout << "\n\n\n\t\t\t\t=========  DISPLAY BIKES ==========\n\n";
                        bikeLot.showBikes();
                        system("PAUSE");
                        break;
                    case 4:
                        cout<<"\t\t\t\t========  AVAILABLE BIKE SLOTS ===========\n\n";
                        bikeLot.showAvailableSlotsbike();
                        system("PAUSE");
                        break;
                    case 5:{
                            int choice;
                            cout << "\n\n\n\t\t\t\t=========  SEARCH A BIKE ==========\n\n";
                            string plate;
                            cout << "\t\t\t\tEnter bike plate number to search: ";
                            cin.ignore();
                            getline(cin, plate);
                            bikeLot.searchByPlate(plate); 
                    }
                    case 6:
                        break;
                }
                break;
            } 
            case 3: {
                int truckChoice;
                cout << "\n\n\n\t\t\t\t===== Truck Parking Management =====\n\n";
                cout << "\t\t\t\t1. Park a truck\n";
                cout << "\t\t\t\t2. Remove a truck\n";
                cout << "\t\t\t\t3. Display parked trucks\n";
                cout << "\t\t\t\t4. View available slots:\n";
                cout << "\t\t\t\t5. Search a truck:\n";
                cout << "\t\t\t\t6. Back to main menu\n";

                while (true) {
                    cout << "\t\t\t\tEnter your choice: ";
                    cin >> truckChoice;
                    if (cin.fail() || truckChoice < 1 || truckChoice > 6) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "\t\t\t\t---ERROR: Invalid input. Enter a number between 1 and 4---\n";
                    } else {
                        system("cls");
                        break;
                    }
                }

                switch (truckChoice) {
                    case 1: {
                        cout << "\n\n\n\t\t\t\t=========  PARK A TRUCK ==========\n\n";
                        if (truckLot.isFull()) {
                            cout << "\t\t\t\t--Cannot park more trucks.--\n";
                            system("PAUSE");
                            break;
                        }
                        string plate, model;
                        validatePlateInput(plate,model);
                        truckLot.parkTruck(plate, model);
                        break;
                    }
                    case 2: {
                        cout << "\n\n\n\t\t\t\t=========  REMOVE A TRUCK ==========\n\n";
                        int slotID;
                        cout << "\t\t\t\tEnter your slotID to remove: ";
                        cin >> slotID;
                        truckLot.removeTruck(slotID);
                        break;
                    }
                    case 3:
                        cout << "\n\n\n\t\t\t\t=========  DISPLAY TRUCKS ==========\n\n";
                        cout << "\n\t\t\t\tParked Trucks:" << endl;
                        truckLot.displayTrucks();
                        system("PAUSE");
                        break;
                    case 4:
                        truckLot.showAvailableSlotsTruck();
                        break;
                    case 5:{
                        cout << "\n\n\n\t\t\t\t=========  SEARCH A TRUCK ==========\n\n";
                        string plate;
                        cin>>plate;
                        cout<<"\t\t\t\tEnter the plate number of Truck to search: ";
                        truckLot.searchTruck(truckLot,plate);
                    }

                    case 6:
                        break;
                }
                break;
            }
            case 4: {
                cout << "\n\t\t\t\t===== All Parked Vehicles =====\n";
                cout << "\n\t\t\t=========================================\n";
                cout << "\n\t\t\t\tCars:\n";
                carLot.displayCars();
                cout << "\n\t\t\t=========================================\n";
                cout << "\n\t\t\t\tBikes:\n";
                bikeLot.showBikes();
                cout << "\n\t\t\t=========================================\n";
                cout << "\n\t\t\t\tTrucks:\n";
                truckLot.displayTrucks();
                cout << "\n\t\t\t=========================================\n";
                system("PAUSE");
                break;
            }
            case 5:
                cout << "\n\n\n\n\t\t\t\t============================================================\n";
                cout << "\n\t\t\t\tTHANK YOU! for using the Parking Management System. Goodbye!\n\n";
                cout << "\t\t\t\t==============================================================\n";
                return 0;
        }

        cout << "\n";
    }

    return 0;
}
