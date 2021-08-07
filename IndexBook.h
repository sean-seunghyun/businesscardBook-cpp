//IndexBook.h
#ifndef _INDEXBOOK_H
#define _INDEXBOOK_H
#include"Index.h"
#include"BinaryTree.h"
#include<string>
using namespace std;
typedef signed long int Long;
class Businesscard;
class IndexBook {
public:
	IndexBook();
	IndexBook(const IndexBook& source);
	~IndexBook();
	Index* PutIn(Businesscard *businesscard);
	Index* Find(string companyName);
	Index* PullOut(Businesscard *businesscard, string companyName);
	void Arrange();
	void MakeList(Index *(*indexes), Long *count);
	
	IndexBook& operator = (const IndexBook& source);
	Long GetLength() const;
	BinaryTree<Index>& GetIndexes() const;
private:
	BinaryTree<Index> indexes;
	Long length;
};
int IndexBook_CompareCompanyNames(void *one, void *other);
void ArrayItems(BinaryTree<Index> *binaryTree);
void Node_ArrayItems(BinaryTree<Index>::Node *node);
void PrintKeys(BinaryTree<Index> *binaryTree);
void Node_PrintKeys(BinaryTree<Index>::Node *node);

inline Long IndexBook::GetLength() const {
	return this->length;
}
inline BinaryTree<Index>& IndexBook::GetIndexes() const {
	return const_cast<BinaryTree<Index>&>(this->indexes);
}


#endif // !_INDEXBOOK_H
