#pragma once

#include "Container.hpp"

#define MAX_STACK_SIZE 100

/*
Stack stack;

stack.PushBack(thing);
stack.PopBack();
stack.Erase(T iterator);

int thing = stack.Top();




*/
template<class T> class Stack : public Container<T> {
	/*
	*	@brief Container that is contiguous in memory and has a last in first out approach.
	*/
	Stack();

	T PushBack();
};