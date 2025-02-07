#include <iostream>  
#include <cstring>   
#include <iomanip>   // For setting precision
#include "student.h" 
#include "head.h"    

using namespace std; 

void add(Node*& head, Node* current, student* newStudent); 
void print(Node* next);                                   
void deletee(Node*& head, Node* current, int id);      
void average(Node* next, double& GPA, int& count);       

int main() {
    char input[80];        
    bool start = true;   
    Node* head = nullptr;   //starts head of linked list to null


    while (start = true) {
        cout << "Enter ADD, PRINT, DELETE, AVERAGE, or QUIT: " << endl; 
        cin.getline(input, 80, '\n'); 

        if (strcmp(input, "ADD") == 0) { 
            char names[80];              
            cout << "Enter name: " << endl;
            cin.getline(input, 80, '\n'); // gets the student's name and copys input to  names
            strcpy(names, input);         

            double gpa;  
            int id;     
            cout << "Enter ID: " << endl;
            cin >> id;  

            cout << "Enter GPA: " << endl;
            cin >> gpa;          
            cin.ignore();       

            student* temp = new student(id, gpa, names); //new student object with all 3 variables/charateristics
            add(head, head, temp); //adds student to linked list

        } else if (strcmp(input, "PRINT") == 0) { 
            print(head); 

        } else if (strcmp(input, "DELETE") == 0) { 
            cout << "Enter ID to delete: " << endl;
            cin.getline(input, 80, '\n'); 
            deletee(head, head, atoi(input)); // ATOI convers string to interger so what this does it changes the inputed thing to and integer then deletes student

        } else if (strcmp(input, "AVERAGE") == 0) { 
            double GPA = 0.0; 
            int count = 0;    
            average(head, GPA, count); // calculates the avarage GPA also amount of students as its need for calculation

            if (count > 0) { 
                cout << "Average GPA: " << fixed << setprecision(2) << GPA / count << endl; // print average GPA
           
            }

        } else if (strcmp(input, "QUIT") == 0) { 
            return 0; 
        } else {
            cout << "Invalid command." << endl; 
        }
    }

    return 0; 
}

void add(Node*& head, Node* current, student* newStudent) { // add a student to the linked list
    if (head == nullptr) { 
        head = new Node(); 
        head->setStudent(newStudent); // sets student in new node
        head->setNext(nullptr); 
    } else if (current == nullptr || current->getStudent()->getID() > newStudent->getID()) {// basically when current position = null or current ID is larger than new ID
        Node* newNode = new Node(); 
        newNode->setStudent(newStudent); //we point the new node to new student when the new student is smaller the the current one
        newNode->setNext(current); //then  the new node to point to the the current node

        if (current == head) { 
            head = newNode; 
        } else { 
            Node* temp = head;
            while (temp->getNext() != current) { // move through the link list to get previous node
                temp = temp->getNext();
            }
            temp->setNext(newNode); // Update the next pointer of the previous node
        }
    } else {
        add(head, current->getNext(), newStudent); // use recurtion to call add again for the next node insted of using a for loop or other iterator
    }
}


void print(Node* next) { // print all students in the linked list
    if (next == nullptr) { 
        return;
    }

    cout << fixed << setprecision(2); // used somthing called set precision so this changes it to 2 decimal spots in the output
    next->getStudent()->printData(); 
    cout << "GPA: " << next->getStudent()->getGpa() << endl; // Print the GPA (i commented out the gpa in the student.cpp so it wouldnt double)

    print(next->getNext()); // uses recurtion to call print for next node in link list
}


void deletee(Node*& head, Node* current, int id) { // Delete a student by ID
    if (current == nullptr) { 
        cout << "Student ID not found." << endl; 
        return;
    }

    if (current == head && current->getStudent()->getID() == id) { // if the student chossen to delete is at the head/start of list
        Node* temp = head; // store the head node in a node* temp 
        head = head->getNext(); //then changes the head to the next node
        delete temp; //and then it deletes the head node stored in temp so then new head node is the next
        return;
    }

    if (current->getNext() != nullptr && current->getNext()->getStudent()->getID() == id) { // If next node contains the student that we ided to delete it baasically does the temp process like eailer but with next pointer
        Node* temp = current->getNext(); 
        current->setNext(temp->getNext()); 
        delete temp; 
        return;
    }

    deletee(head, current->getNext(), id); // uses recurtion to use deleteNode again for the next node
}

void average(Node* next, double& GPA, int& count) {  // calculate the average GPA of all students
    if (next == nullptr) {
        return;
    }

    GPA += next->getStudent()->getGpa(); 
    count++; 

    average(next->getNext(), GPA, count); 
}
