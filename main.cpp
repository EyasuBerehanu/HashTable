//Eyasu Berehanu
//2/14/2025
//I got some help from my table mates about how my assiment should work/look like but no code from them
//a strong chuck of my code was orignated from my student list./link list assigment
//assigment and this link: https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/
// for randomizer i used: Generating unique, random, and evenly-distributed numbers in ascending order with C++ (and in O(1)memory space) by Tyler Burdsall https://www.geeksforgeeks.org/set-in-cpp-stl/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip> 
#include <cstdlib>
#include <ctime>
#include <set>
#include "student.h" 
#include "head.h"    

using namespace std;

struct HashMapNode;
struct HashMap;
void add(HashMap* map, student* newStudent); 
void print(HashMap* map);                                   
void deletee(HashMap* map, int id);      
void average(HashMap* map, double& GPA, int& count);       
void resizeHashMap(HashMap* map);
int randomizer(HashMap* map);
int rando();
void randomGenerator();


struct HashMapNode { //defines the pointer for stuendt object and the following node in the link list
    student* studentPointer;  
    struct HashMapNode* next; 
};


struct HashMap { //defines the hash map or hash table
    int capacity;  // number of slots in  hash table
    int size;      // number of things currently in hash table
    HashMapNode** arr;  
};


void initializeHashMap(HashMap* map) { // initialize the hash map with a given capacity of 100 slots
    map->capacity = 100;  // sets capacity to start  at 100
    map->size = 0;        
    map->arr = new HashMapNode*[map->capacity];  
    for (int i = 0; i < map->capacity; i++) {
        map->arr[i] = nullptr;  // initialize each slot as nullptr 
    }
}

int hashFunction(HashMap* map, int key) { //function to use modulus to calculate index based off of ID
    return key % map->capacity;  
}

void resizeHashMap(HashMap* map) { // resizes hash table if number of collisions exceeds 
    int oldCapacity = map->capacity;
    map->capacity = map->capacity * 2;  // then this doubles capacity of hash table
    HashMapNode** newArr = new HashMapNode*[map->capacity];  // new array for resized table

    for (int i = 0; i < map->capacity; i++) {
        newArr[i] = nullptr;
    }
    
   //(debugging line if you want to try) cout << "Old capacity before resizing " << oldCapacity << " to " << map->capacity << endl;
    
   
    for (int i = 0; i < oldCapacity; i++) {  // this rehashes the existing things into the new array from old smaller array
        HashMapNode* current = map->arr[i];
        while (current != nullptr) {
            int newIndex = hashFunction(map, current->studentPointer->getID());
            //(debugging line if you want to try) cout << "Rehashing ID " << current->studentPointer->getID() << " to new index " << newIndex << endl;  // Debugging line
            HashMapNode* newNode = new HashMapNode();
            newNode->studentPointer = current->studentPointer;
            newNode->next = newArr[newIndex];
            newArr[newIndex] = newNode;
            current = current->next;
        }
    }

    
    delete[] map->arr; // deletes old array 
    map->arr = newArr; //assigns the resized array to  map
}

int main() { //where all prompts are stored where the user can do commands and interact with the student list
    srand((unsigned) time(NULL));  
    char input[80]; 
    bool start;

    HashMap map;
    initializeHashMap(&map);  // initializes the hash map


    while (start = true) {
        cout << "Enter ADD, PRINT, DELETE, RANDOM, AVERAGE, or QUIT: " << endl;
        cin.getline(input, 80, '\n');  

        if (strcmp(input, "ADD") == 0) { 
            char names[80];              
            cout << "Enter name: " << endl;
            cin.getline(input, 80, '\n'); 
            strcpy(names, input);  

            double gpa;  
            int id;     
            cout << "Enter ID: " << endl;
            cin >> id;  

            cout << "Enter GPA: " << endl;
            cin >> gpa;          
            cin.ignore();  

            student* temp = new student(id, gpa, names); 
            add(&map, temp);  // add student to the hash map
        } else if (strcmp(input, "PRINT") == 0) { 
            print(&map);
            
        } else if (strcmp(input, "DELETE") == 0) { 
            cout << "Enter ID to delete: " << endl;
            cin.getline(input, 80, '\n'); 
            deletee(&map, atoi(input));  // converts the input to integer with ATOI and deletes the student
      
        } else if (strcmp(input, "AVERAGE") == 0) { 
            double GPA = 0.0; 
            int count = 0;    
            average(&map, GPA, count);  // calculates the avarage GPA also amount of students as its need for calculation
       
        } else if (strcmp(input, "RANDOM") == 0) { 
            randomizer(&map); //outputs random student based off of requested amount adding them to the hash table or map
            
        } else if (strcmp(input, "QUIT") == 0) { 
            return 0;  
        } else {
            
        }
    }

    return 0;  
} 


void add(HashMap* map, student* newStudent) { // add a student to the hash map
    int index = hashFunction(map, newStudent->getID());  //caluatees index using hash function
    
    HashMapNode* current = map->arr[index];
    int collisionCount = 0;
    
    while (current != nullptr) { //looks at the ammount of collistions that has happend
        collisionCount++;
        current = current->next;
    }

    if (collisionCount >= 3) { //resizes map if to many colliistons happen or when it excceds 3
        resizeHashMap(map);
        index = hashFunction(map, newStudent->getID());  // Recalculate index after resizing
    }

    
    HashMapNode* newNode = new HashMapNode(); // makes new node for the student adding it to the linked list
    newNode->studentPointer = newStudent;
    newNode->next = map->arr[index];
    map->arr[index] = newNode;
    map->size++;  
    cout << "Key: " << index << endl;  // debugging to show key being produced
}


void print(HashMap* map) { // prints all the students in the hash map
    for (int i = 0; i < map->capacity; i++) {
        HashMapNode* current = map->arr[i];
        while (current != nullptr) {
            current->studentPointer->printData();  // prints data of the student
            cout << "GPA: " << current->studentPointer->getGpa() << endl;  // this prints the gpa as its not in student.cpp
            current = current->next;
        }
    }
}


void deletee(HashMap* map, int id) { // deletes a student using ID from the hash map
    int index = hashFunction(map, id);  
    HashMapNode* prevNode = nullptr;
    HashMapNode* currNode = map->arr[index];


    while (currNode != nullptr) { // moves through linked list to find the student by ID then removes the srtudent from the list removing it from the has table as well
        if (currNode->studentPointer->getID() == id) {
            if (prevNode == nullptr) {
                map->arr[index] = currNode->next;  
            } else {
                prevNode->next = currNode->next;  
            }
            delete currNode;  // frees memory of deleted node
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    cout << "Student ID not found." << endl;  // If student not found
}

void average(HashMap* map, double& GPA, int& count) { //calculates the average GPA of all students in the hash map
    for (int i = 0; i < map->capacity; i++) {
        HashMapNode* current = map->arr[i];
        while (current != nullptr) {
            GPA += current->studentPointer->getGpa();  // adds all student's GPA
            count++;  // increases count of students
            current = current->next;
        }
    }

    if (count > 0) { //calculates and print the average GPA
        cout << "Average GPA: " << fixed << setprecision(2) << GPA / count << endl;
    }
}

int rando() {
  return(1 + rand() % 150);  
}


int randomizer(HashMap* map) { // adds random students to the hash map
    int b = 0;
    int a;
    cout << "How many students do you want to add?" << endl;
    cin >> a;  
    cin.ignore();  
    ifstream file("names.txt");
    set<int> usedIDs;  // keeps track of IDs that have already been use
    while (b < a) {
        string line;
        int current_line = 0;
        int randoID;

        while (getline(file, line)) { // pics  random line from the names file
            current_line++;
            if (current_line == rando()) {
                break;
            }
        }
        randoID = (rand() % 10000);  //  makes a random ID between 0 and 9999

        while (usedIDs.find(randoID) != usedIDs.end()) { //makes sure randomid is unique and generates a new one if it isnt
            randoID = (rand() % 10000); 
        }
        usedIDs.insert(randoID);  // add the made ID to the set
        
        int index = hashFunction(map, randoID);
        //(debugging line if you want to try) cout << "ID of random student: " << randoID << " with index: " << index << endl;  // Debugging line
        int rangpa = 1 + (rand() % 4); // makes random GPA

        cout << "Name: " << line << " ID: " << randoID << " GPA: " << rangpa << endl;
        student* newStudent = new student(randoID, rangpa, line.c_str()); // makes the student using all the info and then adds it to hash table
        add(map, newStudent);  

        b++;  // increases the counter for students added
    }

    file.close();  
    return 0;
}
