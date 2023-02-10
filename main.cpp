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
void printStudent(Node* head, Node* current);
void deleteStudent(Node* &head, Node* current, Node* previous,
		   int identification);
void rehash(Node* *&hashtable, int &size);

int main() {
  cout << "hello world" << endl;
  bool quit = false;
  char input[80];

  //create first hashtable
  int size = 100;
  Node* temphash[size];
  Node* *hashtable = temphash;
  for (int a = 0; a < size; a++) {
    hashtable[a] = NULL;
  }
  
  //Node* head = NULL;
  
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
      
      //find where student goes
      //cout << newStudent->getID()%size;

      //add student to correct spot
      //no rehash right now
      if (ID == 1 ) {
	rehash(hashtable, size);
      }
      
      addStudent(hashtable[newStudent->getID()%size],
		 hashtable[newStudent->getID()%size], NULL, newStudent); 
    }
    if (strcmp(input, "ADDS") == 0) {
      cout << "add multiple" << endl;
      cout << "Enter the number of Students you want to add" << endl;
      int numadd;
      cin >> numadd;
      for (int a = 0; a < numadd; a++) {
	char first[10];
	char last[10];
	int ID;
	float GPA;
	//student info
	//pull a name
	strcpy(first, "ryan");
	//pull another
	strcpy(last, "veith");
	//random 6 digit num/ increment it
	//ID = rand()%999999;
	ID = 1;
	//random 1-4 decimal
	GPA = rand()%40000/100;
	//add student
	
	Student* newStudent = new Student(first, last, ID , GPA);
	
        //add student to correct spot
	//no rehash right now
	addStudent(hashtable[newStudent->getID()%size],
		   hashtable[newStudent->getID()%size], NULL, newStudent); 
      }
    }
    if (strcmp(input, "PRINT") == 0) {
      //go though every linked list in the hastable
      for(int a = 0; a < size; a++) {
	cout << "  :" << a << endl;
	  printStudent(hashtable[a],hashtable[a]);
      }
    }
    if (strcmp(input, "DELETE") == 0) {
      //ask what one to delete
      cout << "Enter the Students ID number" << endl;
      int number;
      cin >> number;
      deleteStudent(hashtable[number%size],
		    hashtable[number%size], NULL, number);
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
    //dont want a cout here since call this multiple times
    //cout << "StudentList:" << endl;
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

void rehash(Node* *&hashtable, int & size) {
  cout << "rehash" << endl;
  size = 2 * size;
  cout << size << endl;
  Node* temphash[size];  
  for (int a = 0; a < size; a++) {
    temphash[a] = NULL;
  }
  
  for (int a = 0; a < size / 2; a++) {
    Node* current = hashtable[a];
    while (current != NULL) {
      //move current->getStudent based on
      //current->getStudent->getID
      cout << a << ": " << current->getStudent()->getID();
      addStudent(hashtable[current->getStudent()->getID()%size],
		 hashtable[current->getStudent()->getID()%size],
		 NULL, current->getStudent());

      //itterate
      current = current->getNext();
    }
  }
    
    
  //call print if bugged?
  hashtable = temphash;

  //there is no deleting of last function
}
