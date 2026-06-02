#ifndef LIST_HPP
#define LIST_HPP

#include "iters.hpp"

template< class T > struct Node{
	T val;
	Node<T>* next;
};

template< class T >
Node<T>* new_fake(void) {
	Node<T>* r = static_cast<Node<T>*>(::operator new (sizeof(Node<T>)));
	r->next = r;
	return r;
}

template< class T >
Node<T>* insert_after(Node<T>* f, const T& d) {   //добавить после
	Node<T>* n = new Node<T>{ d, f->next };
	f->next = n;
	return n;   //возвращаем указатель на добавленный элемент
}

template< class T >
Node<T>* erase_after(Node<T>* f) noexcept { 	//удалить после 
	if (f->next == f) {
		return f;
	}
	Node<T>* h = f->next;
	Node<T>* subh = f->next->next;
	f->next = subh;
	delete h;
	return subh;   //возвращаем указатель на элемент до которого удалили
}

template< class T > struct List {
	Node<T>* fake;
	LIter<T> begin() {
		return LIter(fake->next);
	}
	LIter<T> end() {
		return LIter(fake);
	}

	LCIter<T> cbegin() const {
		return LCIter(fake->next);
	}
	LCIter<T> cend() const {
		return LCIter(fake);
	}

	void clear() noexcept;
	List() : fake(new_fake<T>()) {}
	~List() {
		clear();
		::operator delete(fake); 
	}
	List(const List& other);
	List& operator=(List other);
	void swap(List& other) noexcept;
	void pop_front() noexcept;
	T& front();
	const T& front() const;
	void push_front(const T& d);

	LIter<T> insertAfter(LIter<T> pos, const T& val);
    LIter<T> eraseAfter(LIter<T> pos);
};

template< class T >
void List<T>::push_front(const T& d) {
	insert_after(fake, d);
}

template< class T >
T& List<T>::front() {
	if (fake->next != fake) {
		return fake->next->val;
	}
	throw std::out_of_range("Empty list");
}

template< class T >
const T& List<T>::front() const {
		if (fake->next != fake) {
		return fake->next->val;
	}
	throw std::out_of_range("Empty list");
}

template< class T >
void List<T>::pop_front() noexcept {
	if (fake->next != fake) {
		erase_after(fake);
	}
}

template< class T >
void List<T>::clear() noexcept {     //очистить память
	Node<T>* curr = fake->next;
	while (curr != fake) {
		Node<T>* n = curr->next;
		delete curr;
		curr = n;
	}
	fake->next = fake;
}

template< class T >
List<T>::List(const List& other) {
	this->fake = new_fake<T>();
	Node<T>* cpcurr = other.fake->next;
	Node<T>* cpfake = other.fake;   
	Node<T>* prev = this->fake;
	while (cpcurr != cpfake) {
		try {
			Node<T>* n = new Node<T>{ cpcurr->val, fake };
			prev->next = n;
			prev = n;
			cpcurr = cpcurr->next;
		}
		catch (const std::bad_alloc&) {
			Node<T>* curr = fake->next;
			while (curr != fake) {
				Node<T>* temp = curr->next;
				delete curr;
				curr = temp;
			}
			::operator delete(fake);
			throw;
		}
	}
}

template< class T >
void List<T>::swap(List<T>& other) noexcept {
    Node<T>* tmp = fake;
    fake = other.fake;
    other.fake = tmp;
}

template< class T >
List<T>& List<T>::operator=(List<T> other) {
    swap(other);
    return *this;
}

template< class T >
LIter<T> List<T>::insertAfter(LIter<T> pos, const T& val) {
    Node<T>* newNode = insert_after(pos.node, val);
    return LIter<T>(newNode);
}

template< class T >
LIter<T> List<T>::eraseAfter(LIter<T> pos) {
    Node<T>* nextNode = erase_after(pos.node);
    return LIter<T>(nextNode);
}

#endif