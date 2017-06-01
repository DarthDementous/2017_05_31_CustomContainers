#pragma once
#include <assert.h>
#include <iostream>

#define MAX_QUEUE_SIZE 100

/*
	///
   <* \__/
	\___/
	 _|
	Jack Hunt
*/

template <typename T>
class Queue {
public:
	Queue() { 
		m_data = new T[MAX_QUEUE_SIZE] 
	}

	~Queue() {
		delete[] m_data;
	}

	void enqueue(T& data) {
		assert(!(size() == MAX_QUEUE_SIZE - 1));

		data[rear] = data;
		rear = ++rear % MAX_QUEUE_SIZE;
	}

	T& dequeue() {
		assert(!isEmpty());

		T tmp = m_data[front];
		front = ++front % MAX_SIZE;

		return tmp;
	}

	T& front() {
		assert(!isEmpty());

		return m_data[front];
	}

	unsigned int size() { 
		return abs(rear - front); 
	}

	bool isEmpty() {
		return (m_front == m_rear) ? true : false;
	}

private:
	T* m_data;
	unsigned int m_front = -1, m_rear = -1;
};