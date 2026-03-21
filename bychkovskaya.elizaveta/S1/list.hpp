template< class T > struct List {
	T val;
	List<T>* next;
};

template< class T >
List<T>* new_fake(void) {
	List<T>* r = static_cast<List<T>*>(::operator new (sizeof(List<T>)));
	r->next = r;
	return r;
}

template< class T >
List<T>* insert_after(List<T>* f, const T& d) {   //добавить после
	List<T>* n = new List<T>{ d, f->next };
	f->next = n;
	return n;   //возвращаем указатель на добавленный элемент
}

template< class T >
List<T>* erase_after(List<T>* f) noexcept { 	//удалить после 
	if (f->next == f) {
		return f;
	}
	List<T>* h = f->next;
	List<T>* subh = f->next->next;
	f->next = subh;
	delete h;
	return subh;   //возвращаем указатель на элемент до которого удалили
}

template< class T >
List<T>* clear(List<T>* fake) noexcept {     //очистить память
	List<T>* curr = fake->next;
	while (curr != fake) {
		List<T>* n = curr->next;
		delete curr;
		curr = n;
	}
	fake->next = fake;
	return fake;
}

