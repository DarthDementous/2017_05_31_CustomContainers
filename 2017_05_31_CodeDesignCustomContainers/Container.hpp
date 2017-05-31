#pragma once
template<class T> class Container
{
public:
	/**
	*	@brief Pure virtual blueprints for a custom container with common elements.
	*/
	Container() = 0;
	
	/**
	*	@brief Delete memory in list.
	*/
	virtual ~Container{ delete[] m_data; }

#pragma region Overrided Functions
	/**
	*	@brief Push element to back of container.
	*/
	virtual void PushBack() = 0;

	/**
	*	@brief Remove element from back of container.
	*/
	virtual void PopBack() = 0;

#pragma endregion

	/**
	*	@brief Get number of elements in container
	*/
	size_t	GetSize() { return m_size; }

	/**
	*	@brief Are there any elements in the container?
	*/
	bool	IsEmpty() { return m_size > 0; }

	/**
	*	@brief	Return alias of element at the top of the container (relative).
	*/
	T& Top() { return m_data[m_top]; }

protected:
	size_t		m_size;			/* Amount of elements in container*/
	size_t		m_top;			/* Top of the container (relative)*/
	T*			m_data;			/* List of data in container*/

};

