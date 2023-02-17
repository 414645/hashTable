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


      addStudent(hashtable[newStudent->getID()%size],
		 hashtable[newStudent->getID()%size], NULL, newStudent); 
      
      //add student to correct spot
      //no rehash right now
      if (ID == 1 ) {
	rehash(hashtable, size);
      }
      
      //addStudent(hashtable[newStudent->getID()%size],
      //	 hashtable[newStudent->getID()%size], NULL, newStudent); 
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
  //cout << "adding student" << endl;
  //cout << current << endl;
  //cout << newStudent << endl;
  //figure out if we add it here or move to next place in list
  if (current != NULL) {
    /*
    cout << "1:" << endl;
    cout << newStudent->getID() << endl;
    cout << current << endl;
    cout << current->getStudent() << endl;
    cout << current->getStudent()->getID() << endl;
    cout << ":11" << endl;
    */
    
    //if studentID > current Location in list studentID go to next
    if (newStudent->getID() > current->getStudent()->getID()) {            
      cout << "2" << endl;
      if (current->getNext() != NULL) {
	cout << "3" << endl;
	addStudent(head, current->getNext(), current, newStudent);
      }
      else {
	//put it here we are at end of list
	//cout << "added!" << endl;
        Node* newNode = new Node(newStudent);
	current->setNext(newNode);
      }
      cout << "here" << endl;
    }
    //studentId is <= to current location so add it here
    else {
      //cout << "ADDED" << endl;
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
    //cout << "current: " << current << endl;
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

void rehash(Node* *&hashtable, int &size) {
  //bugtest manages cout since I had some trouble
  bool bugtest = false;
  if (bugtest == true) {
    cout << "rehash" << endl;
  }
  size = 2 * size;
  if (bugtest == true) {
    cout << size << endl;
  }
  Node** temphash = new Node*[size];  
  for (int a = 0; a < size; a++) {
    temphash[a] = NULL;
    if (bugtest == true) {
      //cout << "  :temphash[" << a << "]= " << temphash[a] << endl;
    }
  }
  if (bugtest == true) {
    cout << "cool, size:" << size << endl;
  }
  
  for (int a = 0; a < size / 2; a++) {
    if (bugtest == true) {
      cout << "for lp "<< a << endl;
    }

    Node* current = hashtable[a];

    if (bugtest == true) {
      cout << "hash[a]: " << hashtable[a] << endl;
    }

    while (current != NULL) {
      //cout << "hello" << endl;
      //cout << "current>next: " << current->getNext() << endl;
      //move current->getStudent based on
      //current->getStudent->getID
      if (bugtest == true) {
	cout << a << ": " << current->getStudent()->getID();
	
	cout << current->getStudent()->getID()%size << endl;

	//cout << "crash?" << endl;
      }
      
      /*
	addStudent(hashtable[current->getStudent()->getID()%size],
	hashtable[current->getStudent()->getID()%size],
	NULL, current->getStudent());
      */
      Node* destination = temphash[current->getStudent()->getID()%size];
      if (destination == NULL) {
	if (bugtest == true) {
	  cout << destination << endl;
	  cout << current << endl;
	}
	
	temphash[current->getStudent()->getID()%size] = current;

	if (bugtest == true) {
	  cout << "hash[" << current->getStudent()->getID()%size << "]"
	       << hashtable[current->getStudent()->getID()%size] << endl;
	  cout << "null->thing" << endl;
	}
      }
      else {
	while (destination->getNext() != NULL) {
	  destination = destination->getNext();
        }
	destination->setNext(current);
      }
      
      
      
      //itterate
      
      //cout << "no crash" << endl;
      Node* temp = current;
      
      current = current->getNext();
      if (bugtest == true) {
	cout << "current: " << current << endl;
      }
      
      temp->setNext(NULL);
    }
    //cout << "hiiiiiii" << endl;
  }

  if (bugtest == true) {
    cout << "temp" << endl;
    for(int a = 0; a < size; a++) {
      cout << "  :" << a << endl;
      printStudent(temphash[a],temphash[a]);
    }
  }
    
  hashtable = temphash;

  if (bugtest == true) {
    cout << "hash" << endl;
    for(int a = 0; a < size; a++) {
      cout << "  :" << a << endl;
      printStudent(hashtable[a],hashtable[a]);
    }
  }
  
  //there is no deleting of last function
}
