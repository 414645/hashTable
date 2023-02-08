#ifndef Student_H
#define Student_H

#include <iostream>
#include <cstring>

//this takes the place of a student struct

class Student {
 public:
  Student(); //not used
  Student(char*, char*, int, float);
  ~Student(); //char* will need delete
  char* getFirst();
  char* getLast();
  int getID();
  float getGPA();
 private:
  char* first = new char[10];
  char* last = new char[10];
  int ID;
  float GPA;
};

#endif
