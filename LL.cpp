/***********************************************************
** File:    LL.cpp
** Project: CMSC 202 - Project 5
** Author:  Vy Nguyen
** Section: 12 - David Opie 
** Date:     4/20/2023
** Description: This program writes the functions associated to make the LL 
**********************************************************/


#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan

  pair<T,int>& GetData(); //Node Data Getter

  void SetData( const pair<T, int>& ); //Node Data Setter

  Node<T>* GetNext(); //Node m_next getter

  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();

  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();

  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);

  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);

  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);

  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);

  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);

  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();

  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();

  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);

  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL

private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};

//*******************************************************************************
//Implement LL here

// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr
template <class T>
LL<T>::LL()
{
  m_head = nullptr; 
  m_size = 0; 
}

// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
LL<T>::~LL()
{
  if (m_size == 0)
  {
    cout << "Linked List is empty." << endl; 
  }  

  // assigning currNode pointer to m_head (start of LL)
  Node<T> *currNode = m_head;
  //Iterates through and removes each node
  while(currNode != nullptr)
  { 
    // create a new node that is set to whatever curr is 
    Node<T>* tempNode = currNode;
    currNode = currNode->GetNext(); //moves curr to next node
    delete tempNode; //delete tempNode;
  }

  // reset all of the static LL pointers
  // set m_head to nullptr, and size of LL to 0
  m_head = nullptr; 
  m_size = 0; 
}

// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL
template <class T>
LL<T>::LL(const LL& originalLL)
{
  m_head = nullptr; 
  m_size = 0; 
  // otherwise, create an "original node" starting at m_head of originalLL
  Node<T>* originalNode = originalLL.m_head;

  // then traverse the original linked list until nullptr
  while (originalNode != nullptr)
  {
    // access the frequency of each data point to either 
    // add new data to the copyLL or increment within the LL 
    for (int i = 0; i < originalNode->GetData().second; i++)
    {
      Insert(originalNode->GetData().first);
    }
    originalNode = originalNode->GetNext(); 
  }
}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL
template <class T>
LL<T>& LL<T>::operator= (const LL& originalLL)
{
  // if this already equals the originalLL, then jusr return it
  if (this == &originalLL) { return *this; }

  // otherwise:
  // deallocate the existing nodes so that the LL is empty before 
  // copying contents over
  // (copy code of destructor)
  Node<T> *currNode = m_head;
  //Iterates through and removes each node
  while(currNode != nullptr)
  { 
    // create a new node that is set to whatever curr is 
    Node<T>* tempNode = currNode;
    currNode = currNode->GetNext(); //moves curr to next node
    delete tempNode; //delete tempNode;
  }
  m_head = nullptr; 
  m_size = 0; 

  // if the list of the original list is empty, 
  // then so is the copy list 
  if (originalLL.m_head == nullptr) { return *this; }

  // if the original LL is populated, then copy data to copyLL
  else
  {
    Node<T>* originalNode = originalLL.m_head;
    // then traverse the original linked list until nullptr
    while (originalNode != nullptr)
      {
        // access the frequency of each data point to either 
        // add new data to the copyLL or increment within the LL 
        for (int i = 0; i < originalNode->GetData().second; i++)
        {
          Insert(originalNode->GetData().first);
        }
        originalNode = originalNode->GetNext(); 
      }
    return *this; 
  }
}

// Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found
template <class T>
Node<T>* LL<T>::Find(const T& data)
{
  // start at the head of LL 
  Node<T>* currNode = m_head;
  // use for-loop to traverse LL until nodeNum index is reached 
  for (int i = 0; i < m_size; i++)
  {
      // bounds checker: if currNode is nullptr, its the end of the LL
      if (currNode == nullptr)
      {
        return nullptr; 
      }

      else if(currNode->GetData().first == data)
      {
        return currNode; 
      }
      // otherwise, currNode continues to point to the next node 
      else
      {
        currNode = currNode->GetNext(); 
      }
  }
  return currNode; 
}

// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)
template <class T>
void LL<T>::Insert(const T& data)
{
  //if the size of the LL is 0, the passed-in data becomes the first element/m_head
  if (m_size == 0)
  {
    Node<T>* newNode = new Node(data); 
    m_head = newNode;
    newNode->SetNext(nullptr);
    m_size++; 
    return; 
  }

  Node<T>* findData = Find(data);
  // if the data point does not already exist
  if(findData == nullptr)
  {
    // create/populate a new node and set it equal to m_head 
    Node<T>* currNode = m_head; 
    // if the size of the LL is 1, it will be inserted before or after m_head 
    // else if (m_size == 1)
    if (m_size == 1)
    {
      // populate and create a new node
      Node<T>* newNode = new Node(data); 
      // if data of m_head is GREATER than passed-in data, 
      // then the new data is positioned before m_head/BECOMES M_HEAD
      if (currNode->GetData().first > data) 
      { 
        newNode->SetNext(m_head);  
        m_head = newNode; 
        m_size++; 
        return; 
      }
      // otherwise, the new data is positioned after the m_head
      // if data of m_head is LESSER than passed-in data,  
      else 
      { 
        m_head->SetNext(newNode);
        newNode->SetNext(nullptr);
        m_size++; 
        return; 
      }
    }
    // if the size is more than 1 
    else if (m_size > 1)
    {
      // if the passed-in data does not exist yet, make a new node for it and insert it 
      Node<T>* newNode = new Node(data); 
      Node<T>* prevNode = nullptr; 
      // traverse the LL to find the position to insert the new node in order
      while ((currNode != nullptr) and (currNode->GetData().first < data))
      {
        prevNode = currNode;
        currNode = currNode->GetNext();
      }
      // if the new Node is to be inserted at the beginning
      // the newNode becomes m_head 
      if (prevNode == nullptr)
      {
        newNode->SetNext(currNode);
        m_head = newNode;
      }
      // otherwise, if newNode is to be inserted at the middle or end 
      else
      {
        newNode->SetNext(currNode);
        prevNode->SetNext(newNode);
      }
      m_size++; 
      return; 
    }
  }
  // otherwise, if the data already exists, increment its frequency
  else
  {
    // access the pair by passing Node into GetData()
    pair<T,int> targetData = findData->GetData(); 
    // increment the frequency
    targetData.second++; 
    // then repass data into SetData() for the Node 
    findData->SetData(targetData);
    return; 
  }
}


// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node. 
// Postconditions: Removes first node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T& removeData)
{
  // if the data point is at m_head of a LL of any size
  if (m_head->GetData().first == removeData)
  {
    // save head in a tempNode
    Node<T>* tempNode = m_head;
    // set m_head to temp next 
    m_head = tempNode->GetNext();
    // then delete/remove temp
    delete tempNode; 
    m_size--; 
  }
  // if the size is 1, then just delete m_head
  else if (m_size == 1)
  {
    delete m_head; 
    m_head = nullptr; 
    m_size--; 
  }

  // check if the LL is empty as well
  else if (m_size == 0)
  {
    cout << "Linked List is empty." << endl; 
    return; 
  }

  // if the data point is in the middle of the LL/somewhere else 
  else
  {
    // call Find to find location of data point (if it exists)
    Node<T>* dataLocation = Find(removeData);
    // if the data point doesnt exist, exit remove function
    if (dataLocation == nullptr)
    {
      return; 
    }
    // otherwise, if the data exists 
    else
    {
      // set a currNode and prevNode to m_head 
      Node<T>* currNode = m_head;
      Node<T>* prevNode = m_head; 
      // iterate until currnext is node to be deleted
      while (currNode != nullptr)
      {
        // when removeData is reached
        if(currNode->GetData().first == removeData)
        {   
            // readjust the position of the LL by setting 
            // the next of prevNode to the next of currNode 
            prevNode->SetNext(currNode->GetNext());
            // then delete currNode and decrement size 
            delete currNode;
            m_size--; 
            return; 
        }
        // otherwise,continue traversing through the list 
        else
        {
          prevNode = currNode; 
          currNode = currNode->GetNext(); 
        }
      }
    }
  }  
}

// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL 
template <class T>
void LL<T>::Display()
{
  // checks emptiness/size before displaying
  if (m_size == 0)
  {
    cout << "Linked List is empty" << endl; 
  }
  // otherwise traverse the LL
  // and display the pair in each node  
  else
  {
    Node<T>* currNode = m_head;
    while (currNode != nullptr)
    {
      cout << currNode->GetData().first << ":" << currNode->GetData().second << endl; 
      currNode = currNode->GetNext(); 
    }
    cout << "END" << endl; 
  }
}

// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size
template <class T>
int LL<T>::GetSize()
{
  return m_size;
}

// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream& output, const LL<U>& myData)
{
  // first check if the LL is empty: 
  if (myData.m_size == 0) 
  {
      output << "Linked List is empty."; 
  }
  // if LL is populated:
  else 
  { // create new node that is set to the head of LL 
    Node<U>* currNode = myData.m_head;
    // traverse LL until the end 
    while (currNode != nullptr)
    {
      // and output the data at each node 
      output << currNode->GetData().first <<":" << currNode->GetData().second << endl; // print out data 
      currNode = currNode->GetNext(); // then currNode becomes the next node 
    }
    output << "END" << endl; 
  }
  return output; 
}

// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
template <class T>
pair<T,int>& LL<T>::operator[] (int x) //Overloaded [] operator to pull data from LL
{
  // if the passed integer is out of bounds than the size of the LL 
  // indicate an error 
  if ((x < 0) or (x >= m_size))
  {
    cout << "Error: Index out of range. " << endl; 
  }

  // otherwise, if passed int is within bounds:
  // create a currNode for traversal
  Node<T>* currNode = m_head;
  // traverse based on the size of pass int
  for (int i = 0; i < x; i++)
  {
    currNode = currNode->GetNext();
  }
  // then return the data at currNode  
  return currNode->GetData();
}
