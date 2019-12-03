#ifndef GUARD_STACK_H
#define GUARD_STACK_H

#include <memory>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

template<class T>
class Stack
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

	Stack() { create(); }
	explicit Stack(size_type n, const T& val = T()) { create(n, val); }
	Stack(const Stack& s) { create(s.begin(), s.end()); }
	Stack& operator=(const Stack&);
	~Stack() { uncreate(); }

	size_type size() const { return avail - data; }

	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return avail; }
	const_iterator end() const { return avail; }

	T& pop_back();
	void push_back(const T&);
	void clear() { uncreate(); }
	bool empty() { return data == avail; }


private:
	iterator data;
	iterator avail;
	iterator limit;
	std::allocator<T> alloc;

	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	void grow();
	void uncreate();
	void append(const T&);

};

#endif

template<class T>
T& Stack<T>::pop_back()
{
	if (avail == data) { throw std::domain_error("Stack Underflow!"); }
	iterator it = avail;
	T val = *(it - 1);
	alloc.destroy(--it);
	avail--;
	return val;
}

template<class T>
void Stack<T>::push_back(const T& val)
{
	if (avail == limit) grow();
	append(val);
}

template<class T>
void Stack<T>::create()
{
	data = avail = limit = 0;
}

template<class T>
void Stack<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n);
	limit = avail = data + n;
	std::uninitialized_fill(data, avail, val);
}

template<class T>
void Stack<T>::create(const_iterator i, const_iterator j)
{
	data = alloc.allocate(j - i);
	avail = limit = std::uninitialized_copy(i, j, data);
}

template<class T>
void Stack<T>::grow()
{
	size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = std::uninitialized_copy(data, avail, new_data);

	uncreate();

	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

template<class T>
void Stack<T>::uncreate()
{
	if (data) {
		iterator it = avail;
		while (it != data) {
			alloc.destroy(--it);
		}
		alloc.deallocate(data, limit - data);
	}
	data = avail = limit = 0;
}

template<class T>
void Stack<T>::append(const T& val)
{
	alloc.construct(avail++, val);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (&rhs != this) {
		uncreate();

		create(rhs.begin(), rhs.end());
	}
	return *this;
}

