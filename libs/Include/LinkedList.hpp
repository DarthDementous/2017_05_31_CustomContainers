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

#pragma region LinkNode
	/**
	*	@brief Entity that holds a value and pointers to the previous and next element in the linked list.
	*/
	struct LinkNode {
		LinkNode()	 = default;
		~LinkNode()	 = default;

		T			m_value;						// Current copy in possession
		LinkNode*	m_next	 = nullptr;				// Next element in linked list
		LinkNode*	m_prev   = nullptr;				// Previous element in linked list

		//operator T() { return m_value; }		/* Typecast instance of LinkNode to its value (LinkNode() = LinkNode.m_value)
		//										NOTE: This allows it to be used both ways instead of overloading operator[]*/

		/// Ranged-for functionality (cycling forwards)

		bool operator!=(LinkNode a_iter) {		/*Check if the link node is the last node by checking if its pointing to nullptr*/
			return (m_next != nullptr);
		}

		void operator++() {						/*Point current link node to the next one*/
			this = m_next;
		}

		T& operator*() {						/*De-reference and return alias object in LinkNode*/
			return m_value;
		}
	};
#pragma endregion

#pragma region Ranged-for functionality
	LinkNode begin() {
		return m_firstNode;
	}

	LinkNode end() {
		return m_lastNode;
	}
#pragma endregion

protected:
	// Keep track of beginning and end of linked list
	LinkNode*	m_firstNode	= nullptr;
	LinkNode*	m_lastNode	= nullptr;
};
