#pragma once

#include "List.hpp"

/*
LinkedList<float> test;

test.PushBack(40);

for (auto obj : ll) {
	
}

*/

template<class T> class LinkedList : public Container<T> {
public:
	LinkedList() = default;
	~LinkedList();

	virtual void PushBack(T a_item) override {
		LinkNode *tmp = new LinkNode();
		tmp->m_value  = a_item;

		// If LinkedList is not empty, point new LinkNode at previously last element and position it in the list with pointers
		if (m_firstNode != nullptr) {
			m_lastNode->m_next	= tmp;
			tmp->m_prev			= m_lastNode;
			m_lastNode			= tmp;
		}
		// Assign first and last node in no-longer empty LinkedList and position it with pointers
		else {
			m_firstNode, m_lastNode	= tmp;
			m_firstNode->m_next		= m_lastNode;
			m_lastNode->m_prev		= m_firstNode;
		}
	}

	virtual void PopBack() override {
		assert(m_firstNode != nullptr && "Attempting to pop back on empty linked list.");
		
		LinkNode *prevNode = m_lastNode->m_prev;

		// Sever links with end node, delete memory and replace
		prevNode->m_next = nullptr;
		delete m_lastNode;
		m_lastNode = prevNode;
	}

#pragma region Iteration functionality
	Iterator begin() {
		return Iterator(m_firstNode);
	}

	T* end() {
		return nullptr;						// Next of the last LinkNode will always be nullptr				
	}

	void Iterator::operator++() {
		m_ptr = m_ptr->m_next;				// Point at the next object in the linked list
	}

	void Iterator::operator--() {
		m_ptr = m_ptr->m_prev;				// Point at previous object in the linked list
	}
#pragma endregion

#pragma region LinkNode
	/**
	*	@brief Entity that holds a value and pointers to the previous and next element in the linked list.
	*/
	struct LinkNode {
		LinkNode()	 = default;
		~LinkNode()	 = default;

		T	m_value;						// Current copy in possession
		T*	m_next	 = nullptr;				// Next element in linked list
		T*	m_prev   = nullptr;				// Previous element in linked list

		operator T() { return m_value; }	/* Typecast instance of LinkNode to its value (LinkNode() = LinkNode.m_value)
											NOTE: This allows it to be used both ways instead of overloading operator[]*/
	};
#pragma endregion

protected:
	// Keep track of beginning and end of linked list
	LinkNode*	m_firstNode	= nullptr;
	LinkNode*	m_lastNode	= nullptr;
};
