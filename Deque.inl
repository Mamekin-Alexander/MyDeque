#pragma once
#include "deque.h"
#include <assert.h>
#include <iostream>

	//Constructor and destructor
	template<class T>
	Deque<T>::Deque() : M_CHUNK_SIZE(5), m_size(0), BASIC_LENGTH(10)
	{
		m_chunk_vector.resize(BASIC_LENGTH);
		for (int32_t i = 0; i < m_chunk_vector.size(); ++i)
		{
			m_chunk_vector.at(i) = new T[M_CHUNK_SIZE];
		}
		m_first = m_chunk_vector.front();
		m_shift = m_last = BASIC_LENGTH / 2 * M_CHUNK_SIZE+2;
	}

	template<class T>
	Deque<T>::~Deque()
	{
		for (int32_t i = 0; i < m_chunk_vector.size(); ++i)
		{
			delete[] m_chunk_vector.at(i);
			m_chunk_vector.at(i) = nullptr;
		}
		m_first = nullptr;
		m_last = NULL;
		m_shift = NULL;
		m_size = NULL;
	}

	//Accessing
	template<class T>
	T& Deque<T>::operator[](const ptrdiff_t& index)
	{
		int32_t chunk_number = 0;
		int32_t cell_number =0 ;
		if (m_last > m_shift)
		{
			assert(((index < (m_last - m_shift)) || index < 0) && "Index is out of range!");
		}
		else
		{
			assert((index < (m_last + m_chunk_vector.size()*M_CHUNK_SIZE - m_shift) || index < 0) && "Index is out of range!");

		}
		chunk_number = ((index + m_shift) / M_CHUNK_SIZE) % m_chunk_vector.size();
		cell_number = (index + m_shift) % M_CHUNK_SIZE;
		return (m_chunk_vector.at(chunk_number))[cell_number];
	}

	template<class T>
	const T& Deque<T>::operator[](const ptrdiff_t& index) const
	{
		int32_t chunk_number = 0;
		int32_t cell_number = 0;
		if (m_last > m_shift)
		{
			assert(((index < (m_last - m_shift)) || index < 0) && "Index is out of range!");
		}
		else
		{
			assert((index < (m_last + m_chunk_vector.size() * M_CHUNK_SIZE - m_shift) || index < 0) && "Index is out of range!");

		}
		chunk_number = ((index + m_shift) / M_CHUNK_SIZE) % m_chunk_vector.size();
		cell_number = (index + m_shift) % M_CHUNK_SIZE;
		return (m_chunk_vector.at(chunk_number))[cell_number];
	}

	template<class T>
	T& Deque<T>::Back()
	{
		ptrdiff_t prev = m_last - 1;
		if (prev < 0)
		{
			prev = m_chunk_vector.size() * M_CHUNK_SIZE-1;
		}
		return (m_chunk_vector.at(prev/M_CHUNK_SIZE))[prev%M_CHUNK_SIZE];
	}

	template<class T>
	const T& Deque<T>::Back() const
	{
		ptrdiff_t prev = m_last - 1;
		if (prev < 0)
		{
			prev = m_chunk_vector.size() * M_CHUNK_SIZE - 1;
		}
		return (m_chunk_vector.at(prev / M_CHUNK_SIZE))[prev % M_CHUNK_SIZE];
	}

	template<class T>
	T& Deque<T>::Front()
	{
	
		return (m_chunk_vector.at(m_shift / M_CHUNK_SIZE))[m_shift % M_CHUNK_SIZE];
	}

	template<class T>
	const T& Deque<T>::Front() const
	{

		return (m_chunk_vector.at(m_shift / M_CHUNK_SIZE))[m_shift % M_CHUNK_SIZE];
	}

	template<class T>
	size_t Deque<T>::Size() const
	{

		return m_size;
	}

	//Editing member functions
	template<class T>
	void Deque<T>::PushBack(const T& elem)
	{
		int32_t count_of_chanks = m_chunk_vector.size();
		int32_t last_chunk_number = m_last / M_CHUNK_SIZE;
		int32_t shift_chunk_number = m_shift / M_CHUNK_SIZE;
		if ((shift_chunk_number == last_chunk_number) && (m_size!=0) && (m_last<=m_shift))
		{
			add_chunks(count_of_chanks);
		}
		(m_chunk_vector.at(last_chunk_number))[m_last % M_CHUNK_SIZE] = elem;
		++m_last;
		++m_size;
		if (m_last / (M_CHUNK_SIZE * m_chunk_vector.size()) > 0)
		{
			m_last = 0;
		}
		return;
	}

	template<class T>
	void Deque<T>::PushFront(const T& elem)
	{	
		int32_t count_of_chanks = m_chunk_vector.size();
		int32_t last_chunk_number = m_last / M_CHUNK_SIZE;
		int32_t new_shift = m_shift;
		--new_shift;
		if (new_shift < 0)
		{
			new_shift = count_of_chanks * M_CHUNK_SIZE - 1;
		}
		int32_t new_shift_chunk_number = new_shift / M_CHUNK_SIZE;
	
		if ((new_shift_chunk_number == last_chunk_number) && (m_size != 0) && (m_last <= new_shift))
		{
			add_chunks(count_of_chanks);
			new_shift = m_shift;
			--new_shift;
		}
		m_shift = new_shift;
		int32_t shift_chunk_number = m_shift / M_CHUNK_SIZE;
		(m_chunk_vector.at(shift_chunk_number))[m_shift % M_CHUNK_SIZE] = elem;
		++m_size;
		return;
	}

	template<class T>
	void Deque<T>::PopBack()
	{
		if (m_size == 0) {
			return;
		}
		else
		{
			--m_last;
			if (m_last < 0)
			{
				m_last = m_chunk_vector.size() * M_CHUNK_SIZE - 1;
			}
			--m_size;
			check_if_reduce();
		}

	}

	template<class T>
	void Deque<T>::PopFront()
	{
		if (m_size == 0) {
			return;
		}
		else
		{
			++m_shift;
			if (m_shift == m_chunk_vector.size()*M_CHUNK_SIZE)
			{
				m_shift = 0;
			}
			--m_size;
			check_if_reduce();
		}

	}

	template<class T>
	void Deque<T>::check_if_reduce()
	{
		if (m_chunk_vector.size() <= BASIC_LENGTH ||  m_size > m_chunk_vector.size()*M_CHUNK_SIZE*1/3)
		{
			return;
		}
		else
		{
			if (m_last > m_shift)
			{
				ptrdiff_t delete_from_begin = (m_shift+1) / (2* M_CHUNK_SIZE);
				ptrdiff_t delete_from_end = (m_chunk_vector.size() - ((m_last-1) / M_CHUNK_SIZE+1)) / 2;
				for (int32_t i = 0; i < delete_from_begin; ++i)
				{
					delete[] m_chunk_vector.at(i);
				}
				for (int32_t i = m_chunk_vector.size()-1; i >= m_chunk_vector.size() - delete_from_end; --i)
				{
					delete[] m_chunk_vector.at(i);
				}
				m_chunk_vector.erase(m_chunk_vector.begin(), m_chunk_vector.begin() + delete_from_begin);
				m_chunk_vector.erase(m_chunk_vector.end() - delete_from_end, m_chunk_vector.end());
				m_first = m_chunk_vector.front();
				m_last = m_last - M_CHUNK_SIZE * delete_from_begin;
				m_shift = m_shift - M_CHUNK_SIZE * delete_from_begin;
			}
			else
			{
				ptrdiff_t chunks_to_del_from_each_side = ((m_shift - m_last) / M_CHUNK_SIZE -1 )/4;
				for (int32_t i = m_last / M_CHUNK_SIZE + 1; i < m_last / M_CHUNK_SIZE + 1 + chunks_to_del_from_each_side; ++i)
				{
					delete[] m_chunk_vector.at(i);
				}
				for (int32_t i = m_shift / M_CHUNK_SIZE - 1; i > m_shift / M_CHUNK_SIZE - 1 - chunks_to_del_from_each_side; --i)
				{
					delete[] m_chunk_vector.at(i);
				}
				m_chunk_vector.erase(m_chunk_vector.begin() + m_shift / M_CHUNK_SIZE - chunks_to_del_from_each_side, m_chunk_vector.begin() + m_shift / M_CHUNK_SIZE);
				m_chunk_vector.erase(m_chunk_vector.begin() + m_last / M_CHUNK_SIZE + 1, m_chunk_vector.begin() + m_last / M_CHUNK_SIZE + chunks_to_del_from_each_side +1);
				
				m_first = m_chunk_vector.front();
				m_shift = m_shift - M_CHUNK_SIZE * 2 * chunks_to_del_from_each_side;
			}
			std::cout << "Cutted!!!" << '\n';
		}
	}

	template<class T>
	void Deque<T>::add_chunks(const int32_t& chunks_count)
	{
		std::vector<T*> new_chunks;
		int32_t shift_chunk_number = m_shift / M_CHUNK_SIZE;
		for (int32_t i = 0; i < chunks_count; ++i)
		{
			new_chunks.push_back(new T[M_CHUNK_SIZE]);
		}
		m_chunk_vector.insert(m_chunk_vector.begin() + shift_chunk_number, new_chunks.begin(), new_chunks.end());
		m_first = m_chunk_vector.front();
		m_shift += chunks_count * M_CHUNK_SIZE;
	}