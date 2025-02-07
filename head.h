#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<cstring>
#include"student.h"
class Node {
public:
  Node();
  ~Node();
  
  void setStudent(student* newStudent);
  student* getStudent();

  void setNext(Node* nNext);
  Node* getNext();

private:
  student* studentPtr;
  Node* next;
};
#endif
