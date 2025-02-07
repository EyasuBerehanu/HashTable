#include<iostream>
#include<cstring>
#include "student.h"
using namespace std;
student::student(int n, double g,const char* l){
  Id=n;
  GPA=g;
  strncpy(name,l,25);
};
int student::getID(){
  return Id;
};
void student::setID(int n){
  Id=n;
};
const char* student::getName(){
  return name;
};
void student::setName(const char* n){
  strncpy(name,n,25);
}
double student :: getGpa(){
  return GPA;
};
void student::setGpa(double n){
  GPA=n;
};
void student::printData(){
  cout<< "student name: "<<name<<endl;
  cout<< "student id: "<< Id<<endl;
  //cout<< "student GPA: "<< GPA<<endl; commented out cuz used more better in main
};
