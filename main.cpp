#include <iostream>

#include "student.h"
#include "node.h"
//for set preceison
#include <iomanip>

using namespace std;

//By Ryan Veith
//
//This is a formerly the test class for the linked lists project
//I expanded t so it now works as intened using recursion
//it can ADD, DELTETE, and PRINT studetns from the lined list
//it also can AVERAGE the gpa of students on the list

void addStudent(Node* &head, Node* current, Node* previous,
		Student* newStudent);
void printStudent(Node* head, Node* current);
void deleteStudent(Node* &head, Node* current, Node* previous,
		   int identification);
void averageStudent(Node* head, Node* current, float value, int entrys);

int main() {
  cout << "hello world" << endl;
  bool quit = false;
  char input[80];
  Node* head = NULL;
  
  while (quit == false) {
    //get user input
    //ADD PRINT DELETE AVERAGE QUIT else HELP
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
      //ask what one and that gets sent too
      cout << "Enter the Students ID number" << endl;
      int number;
      cin >> number;
      deleteStudent(head, head, NULL,
		    number); //4 needs to be UI
    }
    if (strcmp(input, "AVERAGE") == 0) {
      averageStudent(head, head, 0, 0);
    }
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }

  }
}



//needs recursion so two adds one here and then one for recursion
//sorts from least to greatest Id of were to put new student
void addStudent(Node* &head, Node* current, Node* previous,
		Student* newStudent) {
  //cout << "addStudent Called" << endl;
  //cout << endl;
  //cout << endl;

  //figure out if we add it here or move to next place in list
  if (current != NULL) {
    //cout << "current != NULL" << endl;

    //if studentID > current Location in list studentID go to next
    if (newStudent->getID() > current->getStudent()->getID()) {      
      //cout << "studnetID > current spots studentID" << endl;
      
      if (current->getNext() != NULL) {
	//cout << "goiing next " << endl;
	
	addStudent(head, current->getNext(), current, newStudent);
      }
      else {
	//put it here next we are at end of list
	//cout << "end of list" << endl;
    
	//add new one (end of list so next is void)
        Node* newNode = new Node(newStudent);
	//reset pointers
	current->setNext(newNode);
      }
    }
    //studentId is <= to current location so add it here
    else {
      //cout << "<= to current location so add it" << endl;
      //This does not work specificly if it is the first one
      //since it is added before head
      //so set a new head
      
      Node* newNode = new Node(newStudent);
      newNode->setNext(current);

      if (previous == NULL) {
	//cout << "new head" << endl;
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
      //cout << "replace head node" << endl;
      //repaces head node
      head = new Node(newStudent);
    }
  }
}

void printStudent(Node* head, Node* current) {
  //cout << "prining" << endl;
  //check if it is first thing in list
  if (current == head) {
    cout << "StudentList:" << endl;
  }
  //cout next student
  if (current != NULL) {
    //cout << "next != NULL" << endl;
    cout << current->getStudent()->getFirst() << ", ";
    cout << current->getStudent()->getLast() << ", ";
    cout << current->getStudent()->getID() << ", ";
    cout << setprecision(3) << current->getStudent()->getGPA() << endl;
    //dont forgetrecusion
    printStudent(head, current->getNext());
    //cout << "end" << endl;
  }
}

//this function gave me trouble while coding so it has alot of couts
void deleteStudent(Node* &head, Node* current, Node* previous,
		   int identification) {
  //delete needs id
  //this will be basically same as add but delete current
  //and have previous go to current->getNext or void in last clase spot
  //cout << "del" << endl;

  if (head->getStudent()->getID() == identification) {
    //deal with it now!
    //since there was a seg fault when it was lower in the code

    //if we  delete set 2nd to head then delete
    if (current->getNext() != NULL) {
      //cout << "head to node" << endl;
      //head = current->getNext();
      //cout << "delete" << endl;
      //current = head;
      Node* temporary = head;
      head = head->getNext();
      //delete temporary;
      //cout << "?" << endl;
      //in this case current = head so this works
    }
    else {
      //cout << "head to null" << endl;
      head = NULL;
    }
  }
  else {
    //it is not head!!!
    
    //figure out if we there is anything to even delete
    if (current != NULL) {
      //is it the correct one
      //cout is a visual check for NULL before seg fault
      //cout << "!= NULL " <<current->getStudent() << endl;
      
      //does this id match the one given to delete
      if (current->getStudent()->getID() == identification) {      
	//delete it
	//cout << "found a 4" << endl;
	
	//figure out how to delete it and do so
	if (previous != NULL) {
	  //cout << "pre != null" << endl;
	  if (current->getNext() != NULL) {
	    //cout << "found something to delte" << endl;
	    previous->setNext(current->getNext());
	    current = NULL;
	    delete current;
	  }
	  else {
	    //a special case that was giving me trouble
	    //cout << "deleting last" << endl;
	    previous->setNext(NULL);
	    current = NULL;
	    delete current;
	  }
	}
	//no else head is deleted further up
      }
    }
    //go next
    //cout << "go next??? " << endl;
    if (current != NULL) {
      if (current->getNext()) {
	//current + current->getnext() should be non null,
	//cout << "current->getNext() != null" << endl;
	deleteStudent(head, current->getNext(), current, identification);
	//cout << "done" << endl;
      }
    }
    //cout << "did not breack" << endl;
  }
}

void averageStudent(Node* head, Node* current, float value, int entrys) {
  //cout << "average" << endl;
  //next student
  if (current != NULL) {
    value = value + current->getStudent()->getGPA();
    entrys++;
    averageStudent(head, current->getNext(), value, entrys);
  }
  //if current = null cout average since we are done
  else {
    if (entrys != 0) {
      cout << "Class Average: " << setprecision(3) << value/entrys << endl;
    }
  }
}
