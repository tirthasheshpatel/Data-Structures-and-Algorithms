#ifndef GUARD_QUEUE_H
#define GUARD_QUEUE_H

#include <memory>
#include <algorithm>
#include <stdexcept>

using std::max;

template<class T>
class Queue
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

	Queue() { create(); }
	explicit Queue(size_type n, const T& val = T()) { create(n, val); }
	Queue(const Queue& q) { create(q.begin(), q.end()); }
	Queue& operator=(const Queue&);
	~Queue() { uncreate(); }

	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }

	size_type size() const { return  avail - data; }
	void empty() { return avail == data; }
	void clear() { uncreate(); }

	T& dequeue() {
		if (data) {
			T val = data[0];
			size_type new_size = max(limit - data, ptrdiff_t(1));
			iterator new_data = alloc.allocate(new_size);
			iterator new_avail = std::uninitialized_copy(data + 1, avail, new_data);
			uncreate();
			data = new_data;
			avail = new_avail;
			limit = data + new_size;
			return val;
		}
		else throw std::domain_error("Queue Underflow!");
	}
	void enqueue(const T& val) {
		if (avail == limit) grow();
		append(val);
	}


private:
	iterator data;
	iterator avail;
	iterator limit;
	std::allocator<T> alloc;

	void create() {
		data = avail = limit = 0;
	}
	void create(size_type n, const T& val) {
		data = alloc.allocate(n);
		avail = limit = data + n;
		std::uninitialized_fill(data, avail, val);
	}
	void create(const_iterator i, const_iterator j) {
		data = alloc.allocate(j - i);
		avail = limit = std::uninitialized_copy(i, j, data);
	}

	void uncreate() {
		if (data) {
			iterator it = avail;
			while (it != avail) {
				alloc.destroy(--it);
			}
			alloc.deallocate(data, limit - data);
		}
		data = avail = limit = 0;
	}

	void grow() {
		size_type new_size = max(2 * (avail - data), ptrdiff_t(1));
		iterator new_data = alloc.allocate(new_size);
		iterator new_avail = std::uninitialized_copy(data, avail, new_data);
		uncreate();
		data = new_data;
		avail = new_avail;
		limit = new_data + new_size;
	}

	void append(const T& val) {
		alloc.construct(avail++, val);
	}
};

#endif

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	if (&rhs != this) {
		uncreate();

		create(rhs.begin(), rhs.end());
	}
	return *this;
}
