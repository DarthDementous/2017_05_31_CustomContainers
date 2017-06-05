#pragma once

#include "List.hpp"

/**
*	@brief Container that is non-contiguous in memory.
*/
template<class T> class LinkedList : public Container<T> {
public:
	LinkedList() = default;

	/**
	*	@brief Delete all dynamically allocated LinkNodes
	*/
	~LinkedList() {
		Erase(begin(), end());
	}

	virtual void PushBack(T a_item) override {
		++m_size;
		
		LinkNode*	tmp = new LinkNode(a_item);

		// Initialize first and last nodes with new node in no longer empty list
		if (m_firstNode == nullptr) {
			m_firstNode = tmp;
			m_lastNode	= tmp;		
		}
		// If LinkedList is not empty, point new LinkNode at previously last element and position it in the list with pointers
		else {
			LinkNode* tmp = new LinkNode(a_item);

			m_lastNode->m_next	= tmp;
			tmp->m_prev			= m_lastNode;
			m_lastNode			= tmp;
		}
	}

	virtual void PopBack() override {
		assert(m_firstNode != nullptr && "Attempting to pop back on empty linked list.");
		
		--m_size;

		LinkNode *prevNode = m_lastNode->m_prev;

		// Sever links with end node and replace
		prevNode->m_next = nullptr;
		m_lastNode = prevNode;
	}

#pragma region LinkNode
	/**
	*	@brief Entity that holds a value and pointers to the previous and next element in the linked list.
	*/
	struct LinkNode {
		LinkNode()	 = default;
		LinkNode(T a_val) : m_value(a_val) {}
		~LinkNode()	 = default;

		T			m_value;						// Current copy in possession
		LinkNode*	m_next	 = nullptr;				// Next element in linked list
		LinkNode*	m_prev   = nullptr;				// Previous element in linked list
		
		T& GetValue() { return m_value; }

		operator T() { return m_value; }		/* Conversion of LinkNode to its value (LinkNode() = LinkNode.m_value)
												NOTE: This allows it to be used both ways instead of overloading all operators*/
	};
#pragma endregion

#pragma region Iteration functionality
	/**
	*	@brief Entity that holds a pointer to a link node and can be used in iteration structures.
	*/
	struct LinkIterator {
		LinkIterator(LinkNode* a_link) : m_link(a_link) {}
		LinkNode*	m_link;						/*LinkNode we're pointing at*/

		LinkIterator& operator--() {			/*PREFIX: Move to previous link node value*/
			m_link = m_link->prev;
			return *this;
		}

		LinkIterator operator--(int) {			/*POSTFIX: Move to the previous link node value after leaving the expression*/
			LinkNode result(*this);
			--(*this);
			return result;
		}

		LinkIterator& operator++() {			/*PREFIX: Move to next link node value*/
			m_link = m_link->m_next;
			return *this;
		}

		LinkIterator operator++(int) {			/*POSTFIX: Move to the next link node value after leaving the expression*/
			LinkNode result(*this);
			++(*this);
			return result;
		}

		///Check if the link node is the sentinel node by checking if its pointing to nullptr
		bool operator==(LinkIterator a_iter) {
			return (m_link == a_iter.GetLink());
		}

		bool operator!=(LinkIterator a_iter) {
			return (m_link != a_iter.GetLink());
		}

		LinkNode* GetLink() { return m_link; }

		T& operator*() {						/*De-reference and return aliased value in LinkNode*/
			return m_link->GetValue();
		}
	};

	/**
	*	@brief Delete dynamically allocated memory held by iterator
	*	@param a_first is the minimum range of removal
	*	@param a_last is the maximum range of removal
	*	@returns iterator position after deleted elements in linked list
	*/
	LinkIterator Erase(LinkIterator a_first, LinkIterator a_last) {
		auto iter = a_first;
		while (iter != a_last) {
			// Save next position
			LinkIterator nextPos = iter;
			++nextPos;
			
			// Delete dynamically allocated memory at current position and set iter to next position
			delete iter.GetLink();
			iter = nextPos;
		}

		return iter;
	}

#pragma endregion

#pragma region Ranged-for functionality
	LinkIterator begin() {
		return LinkIterator(m_firstNode);
	}

	LinkIterator end() {						/*Point after the linked list ends (sentinel iterator)*/
		return LinkIterator(m_lastNode->m_next);
	}
#pragma endregion

protected:
	// Keep track of beginning and end of linked list
	LinkNode* m_firstNode	= nullptr;
	LinkNode* m_lastNode	= nullptr;
};
