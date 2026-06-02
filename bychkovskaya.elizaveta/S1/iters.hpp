#ifndef ITERS_HPP
#define ITERS_HPP

#include "list.hpp"

template < class T >
struct LIter {
private:
	friend class List<T>;
	Node<T>* node;

public:
	LIter() : node(nullptr) {};
	LIter(Node<T>* n) : node(n) {};
	LIter< T >& operator++();
	LIter< T > operator++(int);
	bool operator!=(LIter< T >) const;
	bool operator==(LIter< T >) const;
	T& operator*() const;
	T* operator->() const;
};

template< class T >
LIter< T >& LIter< T >::operator++() {
	assert(node != nullptr);
	node = node->next;
	return *this;
}

template< class T >
LIter< T > LIter< T >::operator++(int) {
	assert(node != nullptr);
	LIter< T > result(*this);
	++(*this);
	return result;
}

template< class T >
bool LIter< T >::operator==(LIter< T > rhs) const {
	return node == rhs.node;
}

template< class T >
bool LIter< T >::operator!=(LIter< T > rhs) const {
	return !(rhs == *this);
}

template< class T >
T& LIter< T >::operator*() const {
	assert(node != nullptr);
	return node->val;
}
template< class T >
T* LIter< T >::operator->() const {
	assert(node != nullptr);
	return std::addressof(node->val);
}

template < class T >
struct LCIter {
private:
	friend class List<T>;
	const Node<T>* node;

public:
	LCIter(const LIter<T>& other) : node(other.node) {}

	LCIter() : node(nullptr) {};
	LCIter(const Node<T>* n) : node(n) {};
	LCIter< T >& operator++();
	LCIter< T > operator++(int);
	bool operator!=(LCIter< T >) const;
	bool operator==(LCIter< T >) const;
	const T& operator*() const;
	const T* operator->() const;
};

template< class T >
LCIter< T >& LCIter< T >::operator++() {
	assert(node != nullptr);
	node = node->next;
	return *this;
}

template< class T >
LCIter< T > LCIter< T >::operator++(int) {
	assert(node != nullptr);
	LCIter< T > result(*this);
	++(*this);
	return result;
}

template< class T >
bool LCIter< T >::operator==(LCIter< T > rhs) const {
	return node == rhs.node;
}

template< class T >
bool LCIter< T >::operator!=(LCIter< T > rhs) const {
	return !(rhs == *this);
}

template< class T >
const T& LCIter< T >::operator*() const {
	assert(node != nullptr);
	return node->val;
}
template< class T >
const T* LCIter< T >::operator->() const {
	assert(node != nullptr);
	return std::addressof(node->val);
}

#endif