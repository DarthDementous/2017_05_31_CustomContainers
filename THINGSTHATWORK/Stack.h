#pragma once
#include <iostream>
#include <assert.h>
#define MAX_STACK_SIZE 100

/*
	///
   <* \__/
	\___/
	 _|
	Jack Hunt
*/

template<typename T>
class Stack {
public:
	Stack() : m_size(0), m_top(-1) { m_data = new T[MAX_STACK_SIZE]; }
	~Stack() { delete[] m_data; }

	//	Adds new data to the top of the stack
	T& push(const T& data) {
		assert(!(m_top >= MAX_STACK_SIZE));
		m_size++;
		m_data[++m_top] = data;

		return data;
	}

	//	Removes top data and returns it
	T pop() {
		assert(!(m_top == -1));
		m_size--;
		return m_data[m_top--];
	}

	//	
	T& top() {
		return m_data[m_top];
	}

	unsigned int getSize() { 
		return m_size;
	}

	bool isEmpty() {
		return m_top == -1 ? false : true;
	}

private:
	T* m_data;
	unsigned int m_size;
	int m_top;

};