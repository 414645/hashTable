#include <iostream>
#include <cstring>

#include "student.h"
#include "node.h"
//for set preceison
#include <iomanip>

using namespace std;

//By Ryan Veith
//
//This is the liked list project expanded for completing a hash table

void addStudent(Node* &head, Node* current, Node* previous,
		Student* newStudent);
//newstudent should be unecessary
void addStudents(Node* &head, Node* current, Node* previous,
		 int number);
void printStudent(Node* head, Node* current);
void deleteStudent(Node* &head, Node* current, Node* previous,
		   int identification);

int main() {
  cout << "hello world" << endl;
  bool quit = false;
  char input[80];
  Node* head = NULL;
  
  while (quit == false) {
    //get user input: ADD PRINT DELETE AVERAGE QUIT else HELP
    cin.getline(input, 80);
    if (strcmp(input, "ADD") == 0) {
      char first[10];
      char last[10];
      int ID;
      float GPA;
      //get studnet info
      cout << "Enter the Students first name" << endl;
      cin.getline(first, 10);
      cout << "Enter the Students last name" << endl;
      cin.getline(last, 10);
      cout << "Enter the Students ID number" << endl;
      cin >> ID;
      cout << "Enter the Students GPA" << endl;
      cin >> GPA;
      //add student
      Student* newStudent = new Student(first, last, ID , GPA);
      addStudent(head, head, NULL, newStudent);
    }
    if (strcmp(input, "PRINT") == 0) {
      printStudent(head, head);
    }
    if (strcmp(input, "DELETE") == 0) {
      //ask what one to delete
      cout << "Enter the Students ID number" << endl;
      int number;
      cin >> number;
      deleteStudent(head, head, NULL,
		    number);
    }
    if (strcmp(input, "ADDS") == 0) {
      cout << "add multiple" << endl;
      cout << "Enter the number of Students you want to add" << endl;
      int numbadd;
      cin >> numbadd;
      //for (int a = 0; a < numadd; a++) {
      addStudents(head, head, NULL, 1); //1 -> a + 1
      //}
    }
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }

  }
}

//adds a student to the liked list
void addStudent(Node* &head, Node* current, Node* previous,
		Student* newStudent) {
  //figure out if we add it here or move to next place in list
  if (current != NULL) {
    //if studentID > current Location in list studentID go to next
    if (newStudent->getID() > current->getStudent()->getID()) {            
      if (current->getNext() != NULL) {
	addStudent(head, current->getNext(), current, newStudent);
      }
      else {
	//put it here we are at end of list
        Node* newNode = new Node(newStudent);
	current->setNext(newNode);
      }
    }
    //studentId is <= to current location so add it here
    else {
      Node* newNode = new Node(newStudent);
      newNode->setNext(current);
      if (previous == NULL) {
	head = newNode;
      }
      else {
	previous->setNext(newNode);
      }      
    }
  }
  else {
    Node* next = NULL;
    if (previous == NULL) {
      //repaces head node
      head = new Node(newStudent);
    }
  }
}

//print will need updated with the hash
void printStudent(Node* head, Node* current) {
  //check if it is first thing in list
  if (current == head) {
    cout << "StudentList:" << endl;
  }
  //cout next student
  if (current != NULL) {
    cout << current->getStudent()->getFirst() << ", ";
    cout << current->getStudent()->getLast() << ", ";
    cout << current->getStudent()->getID() << ", ";
    cout << setprecision(3) << current->getStudent()->getGPA() << endl;
    //dont forget recusion
    printStudent(head, current->getNext());
  }
}

//delete a student with given ID from a linkedlist
void deleteStudent(Node* &head, Node* current, Node* previous,
		   int identification) {
  if (head->getStudent()->getID() == identification) {
    //deal with it now!
    if (current->getNext() != NULL) {
      Node* temporary = head;
      head = head->getNext();
    }
    else {
      head = NULL;
    }
  }
  else {
    //it is not head!!!
    if (current != NULL) {
      //does this id match the one given to delete
      if (current->getStudent()->getID() == identification) {      
	//figure out how to delete it and do so
	if (previous != NULL) {
	  if (current->getNext() != NULL) {
	    previous->setNext(current->getNext());
	    current = NULL;
	    delete current;
	  }
	  else {
	    //a special case that was giving me trouble
	    previous->setNext(NULL);
	    current = NULL;
	    delete current;
	  }
	}
	//no else head is deleted further up
      }
    }
    //go next
    if (current != NULL) {
      if (current->getNext()) {
	//current + current->getnext() should be non null,
	deleteStudent(head, current->getNext(), current, identification);
      }
    }
  }
}

void addStudents(Node* &head, Node* current, Node* previous, int number) {
  //first create a new student randomly
  char first[10];
  char last[10];
  int ID;
  float GPA;
  //pull a name
  strcpy(first, "ryan");
  //pull another
  strcpy(last, "veith");
  //random 6 digit num/ increment it
  //ID = rand()%999999;
  ID = number;
  //random 1-4 decimal
  GPA = rand()%40000/100;
  //add student
  Student* newStudent = new Student(first, last, ID , GPA);
  
  //then figure out what to do with them
    //figure out if we add it here or move to next place in list
  if (current != NULL) {
    //if studentID > current Location in list studentID go to next
    if (newStudent->getID() > current->getStudent()->getID()) {            
      if (current->getNext() != NULL) {
	addStudent(head, current->getNext(), current, newStudent);
      }
      else {
	//put it here we are at end of list
        Node* newNode = new Node(newStudent);
	current->setNext(newNode);
      }
    }
    //studentId is <= to current location so add it here
    else {
      Node* newNode = new Node(newStudent);
      newNode->setNext(current);
      if (previous == NULL) {
	head = newNode;
      }
      else {
	previous->setNext(newNode);
      }      
    }
  }
  else {
    Node* next = NULL;
    if (previous == NULL) {
      //repaces head node
      head = new Node(newStudent);
    }
  }
}
