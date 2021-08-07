//BinaryTree.h
#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include<iostream>
using namespace std;
typedef signed long int Long;
template <typename T>

class BinaryTree {
public:
	class Node {
		friend class BinaryTree;
	public:
		Node() {
			this->left = 0;
			this->right = 0;
		}
		Node(T key) {
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		Node(const Node& source) {
			this->key = source.key;
			if (source.left != 0) {
				this->left = new Node(*source.left);
			}
			else {
				this->left = 0;
			}
			if (source.right != 0) {
				this->right = new Node(*source.right);
			}
			else {
				this->right = 0;
			}
		}
		~Node() {
			if (this->left != 0) {
				delete this->left;
			}
			if (this->right != 0) {
				delete this->right;
			}
		}
		void MakeKeys(T(*keys), Long *count, Long *i) {
			if (this->left != 0) {
				this->left->MakeKeys(keys, count, i);
			}
			keys[*i] = this->key;
			(*i)++;
			(*count)++;
			if (this->right != 0) {
				this->right->MakeKeys(keys, count, i);
			}
		}

		void DeleteAllItems() {
			if (this->left != 0) {
				this->left->DeleteAllItems();
			}
			if (this->right != 0) {
				this->right->DeleteAllItems();
			}
			this->left = 0;
			this->right = 0;
			delete this;
		}

		static Node* MakeTree(T(*keys), Long first, Long last) {
			Node *node = 0;
			Long mid;
			if (first <= last) {
				node = new Node;
				mid = (first + last) / 2;
				node->key = keys[mid];
				node->left = MakeTree(keys, first, mid - 1);
					node->right = MakeTree(keys, mid + 1, last);
			}
			return node;
		}

	
		Node& operator = (const Node& source) {
			if (this->left != 0) {
				delete this->left;
			}
			if (this->right != 0) {
				delete this->right;
			}
			this->key = source.key;
			if (source.left != 0) {
				this->left = new Node(*source.left);
			}
			else {
				this->left = 0;
			}
			if (source.right != 0) {
				this->right = new Node(*source.right);
			}
			else {
				this->right = 0;
			}
			return *this;
		}
		inline T& GetKey() {
			return const_cast<T&>(this->key);
		}
		inline Node* GetLeft() {
			return const_cast<Node*>(this->left);
		}
		inline Node* GetRight() {
			return const_cast<Node*>(this->right);
		}

		private:
			Node *left;
			T key;
			Node *right;
	};

	BinaryTree();
	BinaryTree(const BinaryTree& source);
	~BinaryTree();
	Node* Insert(T key, int(*compare)(void*, void*));
	Node* Search(T key, int(*compare)(void*, void*));
	Node* Delete(T key, int(*compare)(void*, void*));
	void MakeBalance();
	void MakeKeys(T *(*keys), Long *count);
	void DeleteAllItems();
	void MakeTree(T(*keys), Long count);	
	Node* GetRoot() const;
	Long GetLength() const;
	Long GetBalance() const;
	private:
		Node *root;
		Long length;
		Long balance;
};


template <typename T>
inline typename BinaryTree<T>::Node* BinaryTree<T>::GetRoot() const {
	return const_cast<Node*>(this->root);
}
template <typename T>
inline Long BinaryTree<T>::GetLength() const {
	return this->length;
}

template <typename T>
inline Long BinaryTree<T>::GetBalance() const {
	return this->balance;
}
template <typename T>
BinaryTree<T>::BinaryTree() {
	this->root = 0;
	this->length = 0;
	this->balance = 0;
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source) {
	this->root = new Node(*source.root);
	this->length = source.length;
	this->balance = source.balance;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
	if (this->root != 0) {
		delete this->root;
	}
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(T key, int(*compare)(void*, void*)) {
	Node *parent = 0;
	Node *child;
	child = this->root;
	while (child != 0) {
		parent = child;
		if (compare(&parent->key, &key) > 0) {
			child = child->left;
		}
		else {
			child = child->right;
		}
	}
	child = new Node(key);
	if (parent != 0) {
		if (compare(&parent->key, &key) > 0) {
			parent->left = child;
		}	
		else {
			parent->right = child;
		}
		if (compare(&this->root->key, &key) > 0) {
			this->balance--;
		}
		else {
			this->balance++;
		}
	}
	else {
		this->root = child;
	}
	this->length++;

	return child;
}

template <typename T>
typename BinaryTree<T>::Node*  BinaryTree<T>::Search(T key, int(*compare)(void*, void*)) {
	Node *index;
	index = this->root;
	while (index != 0 && compare(&index->key, &key) != 0) {
		if (compare(&index->key, &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Delete(T key, int(*compare)(void*, void*)) {
	Node *index; Node *parent = 0; Node *child = 0; Node *it; Node *secondParent = 0;
	index = this->root;
	while (compare(&index->key, &key) != 0) {
		parent = index;
		if (compare(&index->key, &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	it = index->right;
	while (it != 0) {
		secondParent = child;
		child = it;
		it = it->left;
	}
	if (child == 0) {
		it = index->left;
	}

	while (it != 0) {
		secondParent = child;
		child = it;
		it = it->right;
	}

	if (index->right != 0) {
		if (child->right != 0) {
			if (secondParent != 0) {
				if (compare(&secondParent->key, &child->right->key) > 0) {
					secondParent->left = child->right;
				}
				else {
					secondParent->right = child->right;
				}
				child->right = index->right;
			}
		}
		else {
			if (secondParent != 0) {
				child->right = index->right;
				secondParent->left = 0;
			}
		}
	}

	
	if (index->left != 0) {
		if (index->left != child) {
			if (index->right == 0 && secondParent != 0) {
				secondParent->right = 0;
			}
			child->left = index->left;
		}
	}

	if (parent != 0 && child != 0) {
		if (compare(&parent->key, &child->key) < 0) {
			parent->right = child;
		}
		else {
			parent->left = child;
		}
	}

	else {
		if (parent != 0 && child == 0) {
			if (compare(&parent->key, &index->key) < 0) {
				parent->right = 0;
			}
			else {
				parent->left = 0;
			}
		}
		else {
			this->root = child;
		}
	}

	if (index != 0) {
		index->left = 0;
		index->right = 0;
		delete index;
		index = 0;
	}
	if (this->root != 0) {
		if (parent == 0 && child != 0) {
			if (compare(&this->root->key, &key) < 0) {
				this->balance++;
			}
			else {
				this->balance--;
			}
		}
		else {
			if (compare(&this->root->key, &key) < 0) {
				this->balance--;
			}
			else {
				this->balance++;
			}
		}
	}
	this->length--;
	return index;
}

template<typename T>
void BinaryTree<T>::MakeKeys(T *(*keys), Long *count) {
	Long i = 0;
	*count = 0;
	if (this->root != 0) {
		*keys = new T[this->length];
		this->root->MakeKeys(*keys, count, &i);
	}
}
template<typename T>
void BinaryTree<T>::DeleteAllItems() {
	if (this->root != 0) {
		this->root->DeleteAllItems();
		this->root = 0;
		this->length = 0;
		this->balance=0;
	}
}

template<typename T>
void BinaryTree<T>::MakeTree(T(*keys), Long count) {
	Long remainder;
	this->root = Node::MakeTree(keys, 0, count - 1);
	this->length = count;
	remainder = count % 2;
	if (remainder == 0) {
		this->balance = 1;
	}
	else {
		this->balance = 0;
	}
}

template<typename T>
void BinaryTree<T>::MakeBalance() {
	T(*keys); Long count;
	this->MakeKeys(&keys, &count);
	this->DeleteAllItems();
	this->MakeTree(keys, count);
	if (keys != 0) {
		delete[] keys;
	}
}




#endif // !_BINARYTREE_H