#pragma once

#include "Container.hpp"
#include <memory>
#include <assert.h>

#define MAX_STACK_SIZE 100

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
	Stack() { m_data = new T[MAX_STACK_SIZE]};		// Reserve space for data

	void PushBack(T a_item) {
		m_top = m_size++;							// Set bottom element position of list to top

		assert(m_top <= MAX_STACK_SIZE && "Container breaches maximum stack size.");

		m_data[m_top] = a_item;						// Copy item to data list and increase list size
	}

	void PopBack() { m_top = m_size--; }			// Decrease size to essentially 'ignore' last element and update top accordingly
};