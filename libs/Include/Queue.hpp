#pragma once

#include "Container.hpp"
#include "List.hpp"
#include "Container_Literals.h"

/*
Queue Queue;

Queue.PushBack(thing);
Queue.PopBack();

int thing = Queue.Top();

void thing() {
int x = 4;
Queue.push_back(x);
Queue.push_back(2);
}

void main() {
Queue[0] = random garbage
}


*/
template<class T> class Queue : public Container<T> {
	/*
	*	@brief Container that is contiguous in memory and has a first in first out approach.
	*/
	Queue()  {							
		m_data = new T[MAX_SIZE]					// Reserve space for data
	};			 

	virtual void PushBack(T a_item) override {
		assert(m_size <= MAX_SIZE && "Container breaches maximum Queue size.");

		m_data[m_size++] = a_item;					// Copy item to data list and increase list size
	}

	virtual void PopBack() override {
		assert(m_size > 0 && "Attempting to pop back on an empty container.")
		m_size--;									// Decrease size to essentially 'ignore' last element
	}
protected:
	List<T>		m_data;								/*Dynamic list of data.*/
};