#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<cstring>

class student{
 public:
  student(int n, double g, const char* l);//constructor
  int getID();//get id
  void setID(int n);//set id
  const char* getName();//get name
  void setName(const char* n);//setname
  double getGpa();//return gpa
  void setGpa(double n);//set gpa
  void printData();//print everything
 private:
  int Id;
  double GPA;
  char name[25];
};
#endif
