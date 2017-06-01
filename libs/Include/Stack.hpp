#pragma once

#include "Container.hpp"
#include "Container_Literals.h"

/*
Stack stack;

stack.PushBack(thing);
stack.PopBack();

int thing = stack.Top();

void thing() {
	int x = 4;
	stack.push_back(x);
	stack.push_back(2);
}

void main() {
	stack[0] = random garbage
}


*/
template<class T> class Stack : public Container<T> {
	/*
	*	@brief Container that is contiguous in memory and has a last in first out approach.
	*/
	Stack() { m_data = new T[MAX_SIZE]};			// Reserve space for data

	virtual void PushBack(T a_item) override {
		m_top = ++m_size;							// Set top to bottom element index in list

		assert(m_size <= MAX_SIZE && "Container breaches maximum stack size.");

		m_data[m_top] = a_item;						// Copy item to data list and increase list size
	}

	virtual void PopBack() override { 
		assert(m_size > 0 && "Attempting to pop back on an empty container.")
		m_top = --m_size;							// Decrease size to essentially 'ignore' last element and update top accordingly
	}
protected:
	List<T>		m_data;								/*Dynamic list of data.*/
};