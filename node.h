/*Name: Ishaan Varma
  Date: 1/17/2023
  Purpose: Where the Node class is defined
*/
//header gaurd and includes
#ifndef NODE_H
#define NODE_H
#include <cstring>
#include "student.h"

//creates the node class
class Node {
 public:
  //constructors
  Node();
  Node(Student* nstudent);
  //destructor
  ~Node();
  //getters and setters
  Student* getStudent();
  Node* getNext();
  void setNext(Node* nnext);
 private:
  //the content of the node(the student)
  Student* student;
  //the next node(NULL if there is no next node)
  Node* next;
};
#endif
