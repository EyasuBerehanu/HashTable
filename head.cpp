#include<iostream>
#include<cstring>
#include "head.h"
#include"student.h"
using namespace std;

Node::Node() : studentPtr(nullptr), next(nullptr) {};


Node::~Node() {
  delete studentPtr; // deletes from memory
  next = NULL;//null
}

void Node::setStudent(student* newStudent) {
  studentPtr = newStudent;
}

student* Node::getStudent() {
  return studentPtr;
}

void Node::setNext(Node* nNext) {
  next = nNext;
}

Node* Node::getNext() {
  return next;
}
