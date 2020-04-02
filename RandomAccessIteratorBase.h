#pragma once
#include <iterator>
namespace my {

	template <class ValueType>
	class RandomAccesIteratorBase : public std::iterator<std::random_access_iterator_tag, ValueType>
	{
	public:
		RandomAccesIteratorBase() final;

		RandomAccesIteratorBase(const RandomAccesIteratorBase&) final;
		RandomAccesIteratorBase& operator=(const RandomAccesIteratorBase&) final;

		RandomAccesIteratorBase(RandomAccesIteratorBase&&) noexcept final;
		RandomAccesIteratorBase& operator=(RandomAccesIteratorBase&&) noexcept final;

		RandomAccesIteratorBase(ValueType*) final;

		ValueType& operator*() const final;
		ValueType* operator->()const final;
		virtual ValueType& operator[](const ptrdiff_t&);

		virtual RandomAccesIteratorBase& operator++();
		RandomAccesIteratorBase operator++(int) final;
		RandomAccesIteratorBase operator+(const ptrdiff_t&) final;
		RandomAccesIteratorBase& operator+=(const ptrdiff_t&) final;

		virtual RandomAccesIteratorBase& operator--();
		RandomAccesIteratorBase operator--(int) final;
		RandomAccesIteratorBase& operator-=(const ptrdiff_t&) final;
		RandomAccesIteratorBase operator-(const ptrdiff_t&) final;
		virtual ptrdiff_t operator-(const RandomAccesIteratorBase&);



		bool operator<(const RandomAccesIteratorBase&) const final;
		bool operator>(const RandomAccesIteratorBase&) const final;
		bool operator>=(const RandomAccesIteratorBase&) const final;
		bool operator<=(const RandomAccesIteratorBase&) const final;
		bool operator!=(const RandomAccesIteratorBase&) const final;
		bool operator==(const RandomAccesIteratorBase&) const final;

		~RandomAccesIteratorBase() final;
	private:
		ValueType* m_ptr;
	};

	template <class U>
	RandomAccesIteratorBase<U> operator+(const ptrdiff_t&, const RandomAccesIteratorBase<U>&);
}