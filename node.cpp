/*Name: Ishaan Varma
  Date: 1/17/2023
  Purpose: Where the Node class is implemented
*/
//includes
#include "node.h"
#include <iostream>

//constructors
Node::Node() {
  student = NULL;
  next = NULL;
}

Node::Node(Student* nstudent) {
  student = nstudent;
  next = NULL;
}

//gets the student in the node
Student* Node::getStudent() {
  return student;
}

//gets the next node
Node* Node::getNext() {
  return next;
}

//sets the next node to the node you want
void Node::setNext(Node* nnext) {
  next = nnext;
}

Node::~Node() {
  delete student;
}

