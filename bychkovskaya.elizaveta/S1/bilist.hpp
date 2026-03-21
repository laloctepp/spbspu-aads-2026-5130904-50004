template< class T > struct BiList {
	T val;
	BiList<T>* next;
};

template< class T >
BiList<T>* new_fake(void) {
	BiList<T>* r = static_cast<BiList<T>*>(::operator new (sizeof(BiList<T>)));
	r->next = r;
	return r;
}

template< class T >
BiList<T>* insert_after(BiList<T>* f, const T& d) {   //добавить после
	BiList<T>* n = new BiList<T>{ d, f->next };
	f->next = n;
	return n;   //возвращаем указатель на добавленный элемент
}

template< class T >
BiList<T>* erase_after(BiList<T>* f) noexcept { 	//удалить после 
	if (f->next == f) {
		return f;
	}
	BiList<T>* h = f->next;
	BiList<T>* subh = f->next->next;
	f->next = subh;
	delete h;
	return subh;   //возвращаем указатель на элемент после которого удалили
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
	return fake;
}

