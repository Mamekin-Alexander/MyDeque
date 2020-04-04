#pragma once
#include <memory>
#include <vector>
template<class T>
class Deque
{
public:
	Deque();
	~Deque();

	void PushBack(const T&);
	void PopBack();
	T& Back();
	const T& Back() const;

	void PushFront(const T&);
	void PopFront();
	T& Front();
	const T& Front() const;

	size_t Size() const;
	T& operator[](const ptrdiff_t&);
	const T& operator[](const ptrdiff_t&) const;
private:
	T* m_first;
	ptrdiff_t m_last, m_shift, m_size;
	const ptrdiff_t M_CHUNK_SIZE;
	const int32_t BASIC_LENGTH;
	std::vector<T*> m_chunk_vector;

	void add_chunks(const int32_t&);
	void check_if_reduce();
};
#include "Deque.inl"
