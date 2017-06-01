#pragma once
#include <stdexcept>
#include <assert.h>
#include "Stack.h"
#define DEFAULT_VEC_CAP 10

/*
	///
   <* \__/
	\___/
	 _|
	Jack Hunt
*/

template<typename T>
class vector {
public:
	//	Sets m_data to default NULL values
	vector() : m_size(0), m_capacity(DEFAULT_VEC_CAP) {
		m_data = new T[m_capacity];
		memset(m_data, NULL, sizeof(T) * m_capacity);
	}

	//	Sets m_data to default NULL values with capacity of cap
	vector(unsigned int cap) : m_size(0), m_capacity(cap) {
		m_data = new T[m_capacity];
		memset(m_data, NULL, sizeof(T) * m_capacity);
	}

	//	Sets m_data to default data value with capacity of cap
	vector(unsigned int cap, T& data) : m_size(cap), m_capacity(cap) {
		m_data = new T[m_capacity];
		memset(m_data, data, sizeof(T) * m_capacity);
	}

	//	Deletes all values
	~vector() {
		delete[] m_data;
	}

	//	Adds data to m_data, increases capacity if necessary
	void push_back(const T& data) {
		if (m_size++ > m_capacity) {
			T* newData = new T[m_size];
			memcpy(newData, m_data, m_size);
			delete[] m_data;
			m_data = newData;
			m_capacity++;
		}

		m_data[m_size - 1] = data;
	}

	//	Removes last element in m_data and returns it
	T& pop_back() {
		assert(!(m_size <= 0));

		T tmp = m_data[--m_size];
		m_data[m_size] = NULL;
		return tmp;
	}

	//	Gets element at position t, throws error if out of bounds
	T& operator[] (const unsigned int t) {
		assert(!(t >= m_size));
		assert(!(t < 0));

		return m_data[t];
	}

	//	Gets the size of the array m_data
	unsigned int size() {
		return m_size;
	}

	//	Clears all data in m_data
	void clear() {
		memset(m_data, NULL, sizeof(T) * m_size);
	}

	//	Increases capacity of m_data if t > capacity
	void reserve(unsigned int t) {
		if (t > m_capacity) {
			T* tmpArray;
			tmpArray = new T[t];
			memset(tmpArray, NULL, sizeof(T) * t);

			memcpy(tmpArray, m_data, sizeof(T) * m_capacity);

			delete[] m_data;

			m_data = tmpArray;
			m_capacity = t;
		}
	}

	//	Find the element data in the array
	int find(T& data) {
		
	}

private:
	T* m_data;
	unsigned int m_size, m_capacity;
};