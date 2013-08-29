#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "node.h"

template <typename T>
class LinkedList
{
	protected:
		
		int length;
		Node<T>* head;
		
	public:
		
		LinkedList();
		LinkedList(const LinkedList<T>& other);
		~LinkedList();
	
		LinkedList<T>& operator=(const LinkedList<T> &other);
		
		bool empty() const;
		int size() const;		
		void push_front(const T& val);		
		T& at(const int& index);		
		void print() const;		
		void erase(const int& index);
		void pop_front();
		bool contains (const T& value) const;
		void reverse();
		Node<T>* reversehelp(Node <T>* hed);
		
	private:
	
		void copy(const LinkedList<T>& other);
		void destroy();
};

template <typename T>
LinkedList<T>::LinkedList()
{
	this->length = 0;
	this->head = NULL;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	this->length = 0;
	this->head = NULL;
	
	copy(other);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if(this != &other) copy(other);
	return *this;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& other)
{
	destroy();
	
	Node<T>* current = other.head;
	head = NULL;
	while(current != NULL)
	{
		// Is something wrong here?!
		this->push_front(current->data);
		current = current->next;
	}
	reverse();
	this->length = other.length;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	destroy();
}

template <typename T>
void LinkedList<T>::destroy()
{
	Node<T>* current = this->head;
	while(current != NULL)
	{
		Node<T>* toDelete = current;
		current = current->next;
		delete toDelete;
	}
	
	this->length = 0;
	this->head = NULL;
}

template <typename T>
bool LinkedList<T>::empty() const
{
	return this->length == 0;
}

template <typename T>
int LinkedList<T>::size() const
{
	return this->length;
}
		
template <typename T>
void LinkedList<T>::pop_front(){
	Node<T>* newOne = this->head;
	this->head = newOne->next;
	delete newOne;

}

template <typename T>
void LinkedList<T>::push_front(const T& val)
{
	//make a new node
	Node<T>* newOne = new Node<T>(val);
	
	//push it onto the front of the list
	newOne->next = this->head;
	this->head = newOne;

	//increase the length of the list by one
	this->length++;
}

template <typename T>
bool LinkedList<T>::contains(const T& value) const
{
	Node <T>* checker = this->head;
	while (checker->next != NULL)
	{
		if (checker->data == value)
		{
		checker = NULL;
		return true;
		}
		else
		checker = checker->next;

	}
	checker = NULL;
	return false;

}

template <typename T>
void LinkedList<T>::reverse()
{
/*non-recursively
	Node <T>* newList = NULL;
	while(this->head != NULL)
	{
	Node <T>* addon = this->head;
	this->head=this->head->next;
	addon->next = newList;
	newList = addon;	

	}	
	this->head = newList;
	newList = NULL;
*/
	this->head = reversehelp(head);
}

template <typename T>
Node<T>* LinkedList<T>::reversehelp(Node<T>* hed)
{
	if (hed == NULL)
	return hed;
	if (hed->next == NULL)
	return hed;

	Node<T>* temp = reversehelp(hed->next);
	hed->next->next = hed;
	hed->next = NULL;
	return temp;

}
	
template <typename T>
T& LinkedList<T>::at(const int& index)
{
	//make sure the index is in bounds
	if(index < 0 || index >= this->length)
	{
		throw std::out_of_range("index was out of bounds in at().");
	}

	//walk through the list until we hit the index we want
	Node<T>* current = this->head;
	int currentIndex = 0;
	while(currentIndex != index)
	{
		current = current->next;
		currentIndex++;
	}

	//return the data at the given index
	return current->data;
}
		
template <typename T>
void LinkedList<T>::erase(const int& index)
{
	//check that the index is in bounds
	if(index < 0 || index >= this->length)
	{
		throw std::out_of_range("index was out of bounds in erase()!");
	}

	Node<T>* previous = NULL;
	Node<T>* current = this->head;
	int currentIndex = 0;
	
	//walk through the list until "current" points to
	//the thing we want to get rid of
	while(currentIndex != index)
	{
		previous = current;
		current = current->next;
		currentIndex++;
	}
	
	//removing the first element
	if(previous == NULL)
	{
		this->head = head->next;
	}
	//remove a middle element
	else
	{
		previous->next = current->next;
	}
	
	//free up the memory that was allocated by the insert
	delete current;
	this->length--;
}
		
template <typename T>
void LinkedList<T>::print() const
{
	//walk through the list element by element and print
	//out the value of each element
	Node<T>* current = this->head;
	while(current != NULL)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

#endif
