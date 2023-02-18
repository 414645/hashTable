#include <iostream>
#include <cstring>

#include <fstream>

#include "student.h"
#include "node.h"
//for set preceison
#include <iomanip>

using namespace std;

//By Ryan Veith
//
//This is the liked list project expanded for completing a hash table

//add a student to a linked list
void addStudent(Node* &head, Node* current, Node* previous,
		Student* newStudent);
//print out a linked list
void printStudent(Node* head, Node* current);
//delete a student by id from a linked list
void deleteStudent(Node* &head, Node* current, Node* previous,
		   int identification);
//rehash the hash table (double size)
void rehash(Node* *&hashtable, int &size);

int main() {
  cout << "This program is the same as student list," << endl;
  cout << "but it  stores students in a hash table" << endl;
  cout << "the AVERAGE command has been replaced with ADDS" << endl;
  cout << "ADDS, adds multiple randomish students to the linked list" << endl;
  bool quit = false;
  char input[80];
  int studentnumber = 1;

  //create first hashtable
  int size = 100;
  Node* temphash[size];
  Node* *hashtable = temphash;
  for (int a = 0; a < size; a++) {
    hashtable[a] = NULL;
  }
  
  //Node* head = NULL;
  
  while (quit == false) {
    //get user input: ADD PRINT DELETE AVERAGE QUIT (also ADDS)
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
      
      //find where student goes is
      //cout << newStudent->getID()%size;


      addStudent(hashtable[newStudent->getID()%size],
		 hashtable[newStudent->getID()%size], NULL, newStudent); 
      
      //figure out if we need a rehash
      //if we have 3 in same list rehash
      if (hashtable[newStudent->getID()%size] != NULL) {
	if (hashtable[newStudent->getID()%size]->getNext() != NULL) {
	  if (hashtable[newStudent->getID()%size]->getNext()->getNext()
	      != NULL) {
	    cout << "rehashing" << endl;
	    rehash(hashtable, size);
	  }
	}
      }


      //We are adding the student before rehasing since its an easier check
      //addStudent(hashtable[newStudent->getID()%size],
      //	 hashtable[newStudent->getID()%size], NULL, newStudent); 
    }
    if (strcmp(input, "ADDS") == 0) {
      //cout << "add multiple" << endl;
      cout << "Enter the number of Students you want to add" << endl;
      int numadd;
      cin >> numadd;
      for (int a = 0; a < numadd; a++) {
	char first[10];
	char last[10];
	int ID;
	float GPA;
	//student info
	//i know this means you will only get pairs of names
	//but I think it is funny so that why it is not two rand()s
	int tempNum = rand()%10;

	//pull a name
	ifstream myfile ("first.txt");
	if (myfile.is_open()){
	  for (int a = 0; a < tempNum; a++) {
	    myfile >> first;
	  }
	}
	myfile.close();
	//strcpy(first, );
	//pull another

	ifstream myFile ("last.txt");
	if (myFile.is_open()){
	  //cout << tempNum;
	  for (int a = 0; a < tempNum; a++) {
	    myFile >> last;
	    //cout << last;
	  }
	}
	myFile.close();
	//strcpy(last, "veith");
	//random 6 digit num/ increment it
	//ID = rand()%999999;
	ID = studentnumber;
	studentnumber++;
	//random 1-4 decimal
	GPA = (float)(rand()%400)/100;

	//add student
	Student* newStudent = new Student(first, last, ID , GPA);
	
        //add student to correct spot
	addStudent(hashtable[newStudent->getID()%size],
		 hashtable[newStudent->getID()%size], NULL, newStudent); 

	//this is the same code as above:
	//figure out if we need a rehash
	//if we have 3 in same list rehash
	if (hashtable[newStudent->getID()%size] != NULL) {
	  if (hashtable[newStudent->getID()%size]->getNext() != NULL) {
	    if (hashtable[newStudent->getID()%size]->getNext()->getNext()
		!= NULL) {
	      cout << "rehashing" << endl;
	      rehash(hashtable, size);
	    }
	  }
	}

      
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
      //delete it from the correct index in hashtable
      deleteStudent(hashtable[number%size],
		    hashtable[number%size], NULL, number);
    }
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }

  }
}

//adds a student to the liked list
//has a lot of comments because rehash was not working
//so extra prints was helpful
//this is just adding newStudent to a linked list (sorting by id)
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
      if (current->getNext() != NULL) {
	addStudent(head, current->getNext(), current, newStudent);
      }
      else {
	//put it here we are at end of list
	//cout << "added!" << endl;
        Node* newNode = new Node(newStudent);
	current->setNext(newNode);
      }
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

//print a linked list
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

//rehashs hashtable to a new array twice the size
void rehash(Node* *&hashtable, int &size) {
  //bugtest manages cout since I had some trouble
  bool bugtest = false;
  //there were alot of problems so the if(butest) was toubleshooting
  if (bugtest == true) {
    cout << "rehash" << endl;
  }
  //double size then create a new array
  size = 2 * size;
  if (bugtest == true) {
    cout << size << endl;
  }
  Node** temphash = new Node*[size];
  //set the new array to null
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

    //going though the old hashtable
    //move values to new one
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

	//if list is null it is head
	temphash[current->getStudent()->getID()%size] = current;

	if (bugtest == true) {
	  cout << "hash[" << current->getStudent()->getID()%size << "]"
	       << hashtable[current->getStudent()->getID()%size] << endl;
	  cout << "null->thing" << endl;
	}
      }
      else {
	//add them to the end of the list
	while (destination->getNext() != NULL) {
	  destination = destination->getNext();
        }
	destination->setNext(current);
      }
      
      
      
      //itterate so you get everything in the first hash not just the head
      
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

  //make our pointer point to our new hashtable
  hashtable = temphash;

  if (bugtest == true) {
    cout << "hash" << endl;
    for(int a = 0; a < size; a++) {
      cout << "  :" << a << endl;
      printStudent(hashtable[a],hashtable[a]);
    }
  }
  
  //there is no deleting of last function since things are moved
}
