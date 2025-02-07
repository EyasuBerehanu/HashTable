#include <iostream>
#include <cstring>
#include <iomanip>   
#include "student.h"
#include "head.h"

using namespace std;

struct HashMapNode;
struct HashMap;
void add(HashMap* map, student* newStudent); 
void print(HashMap* map);                                   
void deletee(HashMap* map, int id);      
void average(HashMap* map, double& GPA, int& count);       
void incHashMap(HashMap* map);


struct HashMapNode {
    student* studentPointer;  
   struct HashMapNode* next;    
};


struct HashMap {
    int capacity;
    int size; 
    HashMapNode** arr;  
};

void initializeHashMap(HashMap* map) {
    map->capacity = 100;  
    map->size = 0;       
    map->arr = new HashMapNode*[map->capacity];
    for (int i = 0; i < map->capacity; i++) {
        map->arr[i] = nullptr;
    }
}


int hashFunction(HashMap* map, int key) {
    return key % map->capacity;
}


void incHashMap(HashMap* map) {
    int oldCapacity = map->capacity;
    map->capacity = map->capacity * 2;    
    HashMapNode** newArr = new HashMapNode*[map->capacity];

    for (int i = 0; i < map->capacity; i++) {
        newArr[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) {
        HashMapNode* current = map->arr[i];
        while (current != nullptr) {
            int newIndex = hashFunction(map, current->studentPointer->getID());
            HashMapNode* newNode = new HashMapNode();
            newNode->studentPointer = current->studentPointer;
            newNode->next = newArr[newIndex];
            newArr[newIndex] = newNode;
            current = current->next;
        }
    }

    delete[] map->arr;
    map->arr = newArr;
}

int main() {
    char input[80];        
    bool start = true;
    HashMap map;
    initializeHashMap(&map);

    while (start) {
        cout << "Enter ADD, PRINT, DELETE, AVERAGE, or QUIT: " << endl; 
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
            add(&map, temp);  // Add student to the hash map

        } else if (strcmp(input, "PRINT") == 0) { 
            print(&map);

        } else if (strcmp(input, "DELETE") == 0) { 
            cout << "Enter ID to delete: " << endl;
            cin.getline(input, 80, '\n'); 
            deletee(&map, atoi(input)); 

        } else if (strcmp(input, "AVERAGE") == 0) { 
            double GPA = 0.0; 
            int count = 0;    
            average(&map, GPA, count); 

        } else if (strcmp(input, "QUIT") == 0) { 
            return 0; 
        } else {
            cout << "Invalid command." << endl; 
        }
    }

    return 0; 
}

void add(HashMap* map, student* newStudent) {
    int index = hashFunction(map, newStudent->getID());
    
    HashMapNode* current = map->arr[index];
    int collisionCount = 0;
    
    while (current != nullptr) {
        collisionCount++;
        current = current->next;
    }

    if (collisionCount >= 3) {
        incHashMap(map);
        index = hashFunction(map, newStudent->getID());  
    }

    HashMapNode* newNode = new HashMapNode();
    newNode->studentPointer = newStudent;
    newNode->next = map->arr[index];
    map->arr[index] = newNode;
    map->size++;
    cout << "Key: " << index << endl;
}

void print(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        HashMapNode* current = map->arr[i];
        while (current != nullptr) {
            current->studentPointer->printData();
            cout << "GPA: " << current->studentPointer->getGpa() << endl; 
             
            current = current->next;
        }
    }
}

void deletee(HashMap* map, int id) { //Very Good
    int index = hashFunction(map, id); 
    HashMapNode* prevNode = nullptr;
    HashMapNode* currNode = map->arr[index];

    while (currNode != nullptr) {
        if (currNode->studentPointer->getID() == id) {
            if (prevNode == nullptr) {
                map->arr[index] = currNode->next;  
            } else {
                prevNode->next = currNode->next;  
            }
            delete currNode;
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    cout << "Student ID not found." << endl;
}

void average(HashMap* map, double& GPA, int& count) {
    for (int i = 0; i < map->capacity; i++) {
        HashMapNode* current = map->arr[i];
        while (current != nullptr) {
            GPA += current->studentPointer->getGpa();
            count++;
            current = current->next;
        }
    }

    if (count > 0) {
        cout << "Average GPA: " << fixed << setprecision(2) << GPA / count << endl;
    }
}
