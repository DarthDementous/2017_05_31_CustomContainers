#pragma once

#include "Container.hpp"
#include "List.hpp"
#include "Container_Literals.h"

/*
*	@brief Container that is contiguous in memory and has a first in first out approach.
*/
template<class T> class Queue : public Container<T> {
public:
	Queue() {
		m_top = 0;
	}

	virtual void PushBack(T a_item) override {
		++m_size;

		m_data.PushBack(a_item);					// Push back copy of item to data list
	}

	virtual void PopBack() override {
		assert(m_size > 0 && "Attempting to pop back on an empty container.");
		m_size--;									// Decrease size to essentially 'ignore' last element
	}

	/**
	*	@brief	Return alias of element at the top of the container (relative).
	*/
	T&		Top() { return m_data[m_top]; }
protected:
	List<T>		m_data;								/*Dynamic list of data.*/
};