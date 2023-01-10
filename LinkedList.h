#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <set>
#include "LinkedListInterface.h"

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>{
private:
	struct node{
		node(T _value){
			value = _value;
			next = NULL;
		}
		node *next;
		T value;
	};

	node *head;
	set<T> elements;

public:

	LinkedList() {
		head = NULL;
	}
	~LinkedList() {
		clear();
	};

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	void insertHead(T value){
		if(elements.find(value) != elements.end()){
			return;
		}
		elements.insert(value);
		node *tmp = head;
		head = new node(value);
		head->next = tmp;
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value){
		if(head == NULL){
			insertHead(value);
			return;
		}

		if(elements.find(value) != elements.end()){
			return;
		}
		elements.insert(value);

		node *current = head;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = new node(value);
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode){
		if(elements.find(insertionNode) == elements.end()){
			cout << "insertion " << insertionNode << " not found." << endl;
			return;
		}
		if(elements.find(value) != elements.end()){
			cout << "element " << value << " already in list" << endl;
			return;
		}

		node *current = head;
		while(current->value != insertionNode){
			current = current->next;
		}

		node *tmp = current->next;
		cout << "adding " << value << " after " << insertionNode << endl;
		current->next = new node(value);
		elements.insert(value);
		current->next->next = tmp;

	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value){
		if(head == NULL){return;}
		node *current = head;
		if(current->value == value){
			head = current->next;
			delete current;
		}else{
			while(current->next != NULL){
				cout << current->next->value << endl;
				if(current->next->value == value){
					node* tmp = current->next->next;
					delete current->next;
					current->next = tmp;
					break;
				}else{
					current = current->next;
				}
			}
		}
		elements.erase(value);
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear(){
		while(head != NULL){
			node *tmp = head->next;
			delete head;
			head = tmp;
		}
		elements.clear();
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index){

		if(head == NULL || index < 0){throw out_of_range("index outside list");}

		node *current = head;
		int i = 0;
		while(i < index){
			if(current->next == NULL){
				cout << "*"<< endl;
				throw out_of_range("index outside list");
			}
			else{
				i++;
				current = current->next;
			}
		}
		return current->value;
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size(){
		int size = 0;
		for(node *current = head; current != NULL; current = current->next){
			size++;
		}
		return size;
	}

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString(){
		stringstream ss;

		node *current = head;
		while(current != NULL){
			if(current->next == NULL){
				ss << current->value;
			}
			else {ss << current->value << " ";}
			current = current->next;
		}
		return ss.str();
	}

};

#endif