//LinkedList.h
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
typedef signed long int Long;
template <typename T>

class LinkedList {
public:
	class Node {
		friend class LinkedList;
	public:
		Node() {
			this->previous = this;
			this->next = this;
		}
		Node(T object) {
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		Node(Node* previous, T object) {
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node* next) {
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		Node(Node* previous, T object, Node* next) {
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		Node(const Node& source) {
			this->previous = this;
			this->object = source.object;
			this->next = this;
		}
		~Node() {

		}
		Node& operator = (const Node& source) {
			this->previous = this;
			this->object = source.object;
			this->next = this;

			return *this;
		}
		inline T& GetObject() const {
			return const_cast<T&> (this->object);
		}

	private:
		Node *previous;
		T object;
		Node *next;
	};


	LinkedList();
	LinkedList(const LinkedList& source);
	~LinkedList();
	Node* InsertBefore(Node* index, T object);
	Node* InsertAfter(Node* index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node* index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*));
	T& GetAt(Node* index);
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();
	Node* Move(Node* index);
	LinkedList& operator = (const LinkedList& source);
	T& operator [] (Long index);
	Node* GetHead() const;
	Node* GetTail() const;
	Long GetLength() const;
	Node* GetCurrent() const;

private:
	Node* head;
	Node* tail;
	Long length;
	Node* current;
};

template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetHead() const {
	return const_cast<Node*>(this->head);
}

template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetTail() const {
	return const_cast<Node*>(this->tail);
}

template <typename T>
inline Long LinkedList<T>::GetLength() const {
	return this->length;
}

template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetCurrent() const {
	return const_cast<Node*>(this->current);
}

template <typename T>
LinkedList<T>::LinkedList() {
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& source) {
	Node *previous = 0;
	Node *previousForLinkedList;
	Node *current;
	Long i = 1;
	Long j = 1;
	current = source.head;
	this->current = new Node(current->object);
	this->head = this->current;
	previous = current;
	current = previous->next;
	while (previous != current) {
		previous = current;
		previousForLinkedList = this->current;
		this->current = new Node(previousForLinkedList, current->object);
		previousForLinkedList->next = this->current;
		current = previous->next;
	}
	this->tail = this->current;
	current = source.head;
	while (current != source.current) {
		i++;
		current = current->next;
	}
	this->current = this->head;
	while (j < i) {
		this->current = this->current->next;
		j++;
	}
	this->length = source.length;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node *previous = 0;
	this->current = this->head;
	while (previous != this->current) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0) {
			delete this->current;
		}
		this->current = this->head;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node* index, T object) {
	if (index->previous != index) {
		this->current = new Node(index->previous, object, index);
	}
	else {
		this->current = new Node(object, this->head);
	}
	if (index->previous != index) {
		this->current->previous->next = this->current;
	}
	else {
		this->head = this->current;
	}
	index->previous = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node* index, T object) {
	if (index->next != index) {
		this->current = new Node(index, object, index->next);
	}
	else {
		this->current = new Node(this->tail, object);
	}
	if (index->next != index) {
		this->current->next->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	index->next = this->current;
	this->length++;

	return this->current;
}




template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object) {
	if (this->head != 0) {
		this->current = new Node(object, this->head);
	}
	else {
		this->current = new Node(object);
	}
	if (this->head != 0) {
		this->current->next->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	this->head = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object) {
	if (this->tail != 0) {
		this->current = new Node(this->tail, object);
	}
	else {
		this->current = new Node(object);
	}
	if (this->tail != 0) {
		this->current->previous->next = this->current;
	}
	else {
		this->head = this->current;
	}
	this->tail = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node* index) {
	if (this->head != index && this->tail != index) {
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->previous;
	}
	else if (this->head == index && this->tail != index) {
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}
	else if (this->tail == index && this->head != index) {
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead() {
	Node* index;
	index = this->head;
	if (this->tail != index) {
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail() {
	Node* index;
	index = this->tail;
	if (this->head != index) {
		index->previous->next = index->previous;
		this->head = index->previous;
		this->current = index->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
void LinkedList<T>::DeleteAllItems() {
	Node *previous = 0;
	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0) {
			delete this->current;
			
		}
		this->current = this->head;
	}
	this->head = 0;
	this->tail = 0;	
	this->current = 0;
	this->length = 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Node *previous = 0;
	Node *index;

	index = this->head;
	while (index != previous && compare(&index->object, key) != 0) {
		previous = index;
		index = index->next;
	}
	if (index == previous) {
		index = 0;
	}
	return index;
}



template <typename T>
void LinkedList<T>::LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long i = 0;
	Node* previous = 0;
	Node* index;
	*count = 0;

	*indexes = new Node*[this->length];
	index = this->head;
	while (index != previous) {
		if (compare(&index->object, key) == 0) {
			(*count)++;
			(*indexes)[i] = index;
			i++;
		}
		previous = index;
		index = index->next;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node* index) {
	this->current = index;

	return this->current;
}

template <typename T>
T& LinkedList<T>::GetAt(Node *index) {
	return index->object;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First() {
	this->current = this->head;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last() {
	this->current = this->tail;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous() {
	this->current = this->current->previous;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next() {
	this->current = this->current->next;
	return this->current;
}

template <typename T>
T& LinkedList<T>::operator [] (Long index) {
	Long i = 0;
	Node* current;
	current = this->head;
	while (i < index) {
		current = current->next;
		i++;
	}
	return current->object;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList& source) {
	Node* previous = 0;
	Node* previosForLinkedList;
	Node* current;
	Long i = 1;
	Long j = 1;
	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0) {
			delete this->current;
		}
		this->current = this->head;
	}

	current = source.head;
	this->current = new Node(current->object);
	this->head = this->current;
	previous = current;
	current = current->next;
	while (previous != current) {
		previous = current;
		previosForLinkedList = this->current;
		this->current = new Node(previosForLinkedList, current->object);
		previosForLinkedList->next = this->current;
		current = previous->next;
	}
	this->tail = this->current;
	current = source.head;
	while (current != source.current) {
		i++;
		current = current->next;
	}
	this->current = this->head;
	while (j < i) {
		this->current = this->current->next;
		j++;
	}
	this->length = source.length;
	
	return *this;
}

#endif //_LINKEDLIST_H