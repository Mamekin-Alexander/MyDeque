#pragma once
#include <iterator>
namespace my {

	template <class ValueType>
	class RandomAccesIteratorBase : public std::iterator<std::random_access_iterator_tag, ValueType>
	{
	public:
		RandomAccesIteratorBase();

		RandomAccesIteratorBase(const RandomAccesIteratorBase&);
		RandomAccesIteratorBase& operator=(const RandomAccesIteratorBase&);

		RandomAccesIteratorBase(RandomAccesIteratorBase&&) noexcept;
		RandomAccesIteratorBase& operator=(RandomAccesIteratorBase&&) noexcept;

		RandomAccesIteratorBase(ValueType*);

		ValueType& operator*() const;
		ValueType* operator->() const;

		bool operator!=(const RandomAccesIteratorBase&) const;
		bool operator==(const RandomAccesIteratorBase&) const;

		virtual ~RandomAccesIteratorBase();
	protected:
		ValueType* m_ptr;
	};

}
#include "RandomAccesIteratorBase.inl"