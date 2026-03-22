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

template< class T >
Node<T>* clear(Node<T>* fake) noexcept {     //очистить память
	Node<T>* curr = fake->next;
	while (curr != fake) {
		Node<T>* n = curr->next;
		delete curr;
		curr = n;
	}
	fake->next = fake;
	return fake;
}

template< class T >
Node<T>* copy(const Node<T>* fake) {
	Node<T>* curr = fake->next;
	Node<T>* cpfake = new_fake();   //если исключение то все ок
	Node<T>* prev = cpfake;
	while (curr != fake) {
		try {
			Node<T>* n = new Node<T>{ curr->val, cpfake };
			prev->next = n;
			prev = n;
			curr = curr->next;
		}
		catch (const std::bad_alloc&) {
			Node<T>* cpcurr = cpfake->next;
			while (cpcurr != cpfake) {
				Node<T>* temp = cpcurr->next;
				delete cpcurr;
				cpcurr = temp;
			}
			delete cpfake;
			throw;
		}
	}
	return cpfake;
}
