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

	/**
	*	@brief Remove specified element from container.
	*/
	virtual void Erase() = 0;

#pragma endregion

	/**
	*	@brief Get number of elements in container
	*/
	size_t	GetSize() { return m_size; }

	/**
	*	@brief Are there any elements in the container?
	*/
	bool	IsEmpty() { return m_size > 0; }

protected:
	size_t		m_size;			/* Amount of elements in container*/
	T*			m_data;			/* List of data in container*/
};

