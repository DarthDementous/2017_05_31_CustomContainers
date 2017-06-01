#pragma once
#include <iostream>

/*
	 ///
	<* \__/
	 \___/
	  _|
	 Jack Hunt
*/

template <typename T>
class Node {
public:
	Node() { nextNode = nullptr; prevNode = nullptr; }
	T data;
	Node* nextNode;
	Node* prevNode;
};

template <typename T>
class LinkedList {
public:
	//	Constructors and Destructor
	LinkedList() : m_size(0) { m_firstNode = nullptr; m_lastNode = nullptr; }
	LinkedList(LinkedList& ll) { m_firstNode = ll.first(); m_lastNode = ll.last(); m_size = ll.getSize(); }
	~LinkedList() {
		Node<T>* current = m_lastNode;
		for (auto i = m_size; i > 0; i--) {
			if (current->prevNode != nullptr) {
				delete current;
				return;
			}
			current = current->prevNode;
			delete current->nextNode;
		}
	}

	//	Adds value of type T to the end of the list
	void push_back(const T& a_value) {
		m_size++;
		Node<T>* tmpNode = new Node<T>();

		tmpNode->data = a_value;


		if (m_firstNode == nullptr) m_firstNode = tmpNode;
		if (m_lastNode == nullptr) m_lastNode = tmpNode;

		if (m_lastNode != tmpNode) {
			m_lastNode->nextNode = tmpNode;
			tmpNode->prevNode = m_lastNode;

			m_lastNode = tmpNode;
		}
	}

	//	Adds value of type T into list at position t
	void insert(const T& a_value, unsigned int t) {
		if (t > m_size) return;
		Node<T>* current = m_firstNode;
		Node<T>* tmpNode = new Node<T>();

		for (auto i = 0; i < (t); i++) {
			if (current->nextNode == nullptr) return;

			current = current->nextNode;
		}

		tmpNode->data = a_value;

		if (current->prevNode != nullptr) { 
			current->prevNode->nextNode = tmpNode; 
		} else {
			m_firstNode = tmpNode;
		} 
		if (current->nextNode == nullptr) {
			m_lastNode = tmpNode;
		}
		tmpNode->prevNode = current->prevNode;
		tmpNode->nextNode = current;
		current->prevNode = tmpNode;
		m_size++;
	}

	//	Removes last element in the list
	void pop_back() {
		if (m_lastNode != m_firstNode) m_lastNode->prevNode->nextNode = nullptr;
		if (m_lastNode == m_firstNode) m_firstNode = nullptr;
		m_lastNode = m_lastNode->prevNode;
		delete m_lastNode->nextNode;
		m_size--;
	}

	//	Removes element in the list at position t
	void erase(unsigned int t) {
		if (t >= m_size) return;

		Node<T>* current = m_firstNode;
		for (auto i = 0; i < t, i++) {
			if (current->nextNode == nullptr) return nullptr;

			current = current->nextNode;
		}

		if (current->nextNode != nullptr && current->prevNode != nullptr) { 
			current->nextNode->prevNode = current->prevNode;
			current->prevNode->nextNode = current->nextNode;
			delete current;
			return;
		}

		if (current->nextNode != nullptr && current->prevNode == nullptr) {
			current->nextNode->prevNode = nullptr;
			delete current;
			return;
		}

		if (current->nextNode == nullptr && current->prevNode != nullptr) {
			current->prevNode->nextNode = nullptr;
			delete current;
			return;
		}
	}

	//	Gets value of type T at position t using subscript operator
	T operator [](unsigned int t) {
		if (t >= m_size) return NULL;

		Node<T>* current = m_firstNode;
		for (auto i = 0; i < t; i++) {
			current = current->nextNode;
		}
		return current->data;
	}

	//	Gets the size of the list
	unsigned int getSize() {
		return m_size;
	}

	//	Returns pointer to the first node in the list
	Node<T>* first() {
		return m_firstNode;
	}

	//	Returns pointer to the last node in the list
	Node<T>* last() {
		return m_lastNode;
	}

private:
	unsigned int m_size;
	Node<T>* m_firstNode;
	Node<T>* m_lastNode;
};