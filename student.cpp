#include <iostream>
#include <cstring>

#include "student.h"

using namespace std;

Student::Student() {

}

Student::Student(char* newFirst,
		 char* newLast,
		 int newID, float  newGPA) {
  strcpy(first, newFirst);
  strcpy(last, newLast);
  ID = newID;
  GPA = newGPA;
}

Student::~Student() {
  delete first;
  delete last;
}

char* Student::getFirst() {
  return first;
}

char* Student::getLast() {
  return last;
}

int Student::getID() {
  return ID;
}

float Student::getGPA() {
  return GPA;
}
