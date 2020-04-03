#include "RandomAccessIteratorBase.h"
#include <assert.h>
namespace my {

	//Default constructor
	template <class ValueType>
	RandomAccesIteratorBase<ValueType>::RandomAccesIteratorBase()
	{
		m_ptr = nullptr;
	}


	//Copy constructor and copy assignable
	template <class ValueType>
	RandomAccesIteratorBase<ValueType>::RandomAccesIteratorBase(const RandomAccesIteratorBase<ValueType>& other)
	{
		m_ptr = other.m_ptr;
	}

	template <class ValueType>
	RandomAccesIteratorBase<ValueType>& RandomAccesIteratorBase<ValueType>::operator= (const RandomAccesIteratorBase<ValueType>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		m_ptr = other.m_ptr;
		return *this;
	}



	//Move constructor and move assignable
	template <class ValueType>
	RandomAccesIteratorBase<ValueType>::RandomAccesIteratorBase(RandomAccesIteratorBase<ValueType>&& other) noexcept
	{
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
	}

	template <class ValueType>
	RandomAccesIteratorBase<ValueType>& RandomAccesIteratorBase<ValueType>::operator= (RandomAccesIteratorBase<ValueType>&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
		return *this;
	}



	//Constructor from ptr
	template <class ValueType>
	RandomAccesIteratorBase<ValueType>::RandomAccesIteratorBase(ValueType* ptr)
	{
		m_ptr = ptr;
	}


	//Dereferencing operators
	template <class ValueType>
	ValueType& RandomAccesIteratorBase<ValueType>::operator*() const
	{
		return *(m_ptr);
	}

	template <class ValueType>
	ValueType* RandomAccesIteratorBase<ValueType>::operator->() const
	{
		return m_ptr;
	}

	
	//Bool operators
	template<class ValueType>
	bool RandomAccesIteratorBase<ValueType>::operator==(const RandomAccesIteratorBase<ValueType>& other) const
	{
		return (m_ptr == other.m_ptr);
	}

	template<class ValueType>
	bool RandomAccesIteratorBase<ValueType>::operator!=(const RandomAccesIteratorBase<ValueType>& other) const
	{
		return (m_ptr != other.m_ptr);
	}


	//Distructor
	template<class ValueType>
	RandomAccesIteratorBase<ValueType>::~RandomAccesIteratorBase()
	{
		m_ptr = nullptr;
	}
}