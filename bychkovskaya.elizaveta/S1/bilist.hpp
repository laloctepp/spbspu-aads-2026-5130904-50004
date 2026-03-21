template< class T > struct BiList {
	T val;
	BiList<T>* next;
	BiList<T>* prev;
};

template< class T >
BiList<T>* new_fake(void) {
	BiList<T>* r = static_cast<BiList<T>*>(::operator new (sizeof(BiList<T>)));
	r->next = r;
	r->prev = r;
	return r;
}

template< class T >
BiList<T>* add(BiList<T>* f, const T& d) {   //добавить перед головой (в начало)
	BiList<T>* n = new BiList<T>{ d, f->next, f };
	f->next->prev = n;
	f->next = n;
	return n;
}

template< class T >
BiList<T>* cut(BiList<T>* f) noexcept { 	//удалить голову 
	if (f->next == f) {
		return f;
	}
	BiList<T>* h = f->next;
	BiList<T>* subh = f->next->next;
	f->next = subh;
	subh->prev = f;
	delete h;
	return subh;   //возвращаем указатель на новую голову
}

template< class T >
BiList<T>* clear(BiList<T>* fake) noexcept {     //очистить память
	BiList<T>* curr = fake->next;
	while (curr != fake) {
		BiList<T>* n = curr->next;
		delete curr;
		curr = n;
	}
	fake->next = fake;
	fake->prev = fake;
	return fake;
}

