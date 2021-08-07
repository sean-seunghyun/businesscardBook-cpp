//IndexBook.cpp
#include"IndexBook.h"
#include"BusinesscardBook.h"
IndexBook::IndexBook() {
	this->length = 0;
}
IndexBook::IndexBook(const IndexBook& source) 
:indexes(source.indexes){
	this->length = source.length;
}
IndexBook::~IndexBook() {

}


Index* IndexBook::PutIn(Businesscard *businesscard) {
	string companyName;
	Index *index;
	BinaryTree<Index>::Node *node;
	
	companyName = businesscard->GetCompanyName();
	Index key(companyName);
	node = this->indexes.Search(key, IndexBook_CompareCompanyNames);
	if (node == 0) {
		node = this->indexes.Insert(key, IndexBook_CompareCompanyNames);
		this->length++;
	}
	index = &node->GetKey();
	index->PutIn(businesscard);

	return index;

}

Index* IndexBook::Find(string companyName) {
	BinaryTree<Index>::Node *node;
	Index *index = 0;
	Index key(companyName);
	node = this->indexes.Search(key, IndexBook_CompareCompanyNames);
	if (node != 0) {
		index = &node->GetKey();
	}
	return index;
}

Index* IndexBook::PullOut(Businesscard *businesscard, string companyName) {
	BinaryTree<Index>::Node *node;	
	Index *index;
	Long subscript;

	Index key(companyName);
	node = this->indexes.Search(key, IndexBook_CompareCompanyNames);
	index = &node->GetKey();
	subscript = index->Find(businesscard);
	subscript = index->PullOut(subscript);
	if (index->GetLength() <= 0) {
		node = this->indexes.Delete(key, IndexBook_CompareCompanyNames);
		this->length--;
		index = 0;
	}
	return index;
}




void IndexBook::Arrange() {
	this->indexes.MakeBalance();
	ArrayItems(&(this->indexes));

}

void IndexBook::MakeList(Index *(*indexes), Long *count) {
	this->indexes.MakeKeys(indexes, count);
}

void ArrayItems(BinaryTree<Index> *binaryTree) {
	Node_ArrayItems(binaryTree->GetRoot());	

}

IndexBook& IndexBook::operator=(const IndexBook& source) {
	this->indexes = source.indexes;
	this->length = source.length;

	return *this;
}
void Node_ArrayItems(BinaryTree<Index>::Node *node) {
	Index *index;
	if (node != 0) {
		index = &node->GetKey();
		index->Arrange();
		Node_ArrayItems(node->GetLeft());
		Node_ArrayItems(node->GetRight());
	}
}



void PrintKeys(BinaryTree<Index> *binaryTree) {
	Node_PrintKeys(binaryTree->GetRoot());
}

void Node_PrintKeys(BinaryTree<Index>::Node *node) {
	Index index;
	Long subscript=0;
	Businesscard *businesscard;
	if(node!=0){
	index = node->GetKey();
	cout << index.GetCompanyName() << endl;
	while (subscript < index.GetLength()) {
		businesscard=index.GetAt(subscript);
		cout << businesscard->GetName() << endl;

		subscript++;
	}


	Node_PrintKeys(node->GetLeft());
	Node_PrintKeys(node->GetRight());
	}
}




#if 0
#include"BusinesscardBook.h"
#include<iostream>
using namespace std;

int main(int argc, char* argv[]) {
	BusinesscardBook businesscardBook;
	Businesscard* index;
	Businesscard businesscard("홍길동", "사원", "010", "1@", "삼성", "서울시 강남구", "02", "02", "samsung.com");
	Long i = 0;
	Long count;
	IndexBook indexBook;
	Index(*indexes);
	Long subscript;
	Index *indexLink;
	Businesscard *businesscardLink;

	index = businesscardBook.PutIn(businesscard);
	indexLink = indexBook.PutIn(index);
	cout << indexLink->GetCompanyName() << endl;
	subscript = 0;
	while (subscript < indexLink->GetLength()) {
		businesscardLink = indexLink->GetAt(subscript);
		cout << businesscardLink->GetName() << " "
			<< businesscardLink->GetPosition() << " "
			<< businesscardLink->GetCellphoneNumber() << " "
			<< businesscardLink->GetEmailAddress() << " "
			<< businesscardLink->GetCompanyName() << " "
			<< businesscardLink->GetAddress() << " "
			<< businesscardLink->GetTelephoneNumber() << " "
			<< businesscardLink->GetFaxNumber() << " "
			<< businesscardLink->GetUrl() << endl;
		subscript++;
	}

	businesscard = Businesscard("김길동", "인턴", "010", "2@", "현대", "삼성동 현대사옥", "032", "032", "hyundai.com");

	index = businesscardBook.PutIn(businesscard);
	indexLink = indexBook.PutIn(index);
	cout << indexLink->GetCompanyName() << endl;
	subscript = 0;
	while (subscript < indexLink->GetLength()) {
		businesscardLink = indexLink->GetAt(subscript);
		cout << businesscardLink->GetName() << " "
			<< businesscardLink->GetPosition() << " "
			<< businesscardLink->GetCellphoneNumber() << " "
			<< businesscardLink->GetEmailAddress() << " "
			<< businesscardLink->GetCompanyName() << " "
			<< businesscardLink->GetAddress() << " "
			<< businesscardLink->GetTelephoneNumber() << " "
			<< businesscardLink->GetFaxNumber() << " "
			<< businesscardLink->GetUrl() << endl;
		subscript++;
	}
	businesscard = Businesscard("정길동", "사장", "010", "3@", "삼성", "서초구", "012", "012", "small.com");
	index = businesscardBook.PutIn(businesscard);
	indexLink = indexBook.PutIn(index);
	cout << indexLink->GetCompanyName() << endl;
	subscript = 0;
	while (subscript < indexLink->GetLength()) {
		businesscardLink = indexLink->GetAt(subscript);
		cout << businesscardLink->GetName() << " "
			<< businesscardLink->GetPosition() << " "
			<< businesscardLink->GetCellphoneNumber() << " "
			<< businesscardLink->GetEmailAddress() << " "
			<< businesscardLink->GetCompanyName() << " "
			<< businesscardLink->GetAddress() << " "
			<< businesscardLink->GetTelephoneNumber() << " "
			<< businesscardLink->GetFaxNumber() << " "
			<< businesscardLink->GetUrl() << endl;
		subscript++;
	}
	businesscard = Businesscard("가길동", "과장", "011", "4@", "현대", "도봉구", "022", "022", "middle.com");
	index = businesscardBook.PutIn(businesscard);
	indexLink = indexBook.PutIn(index);
	cout << indexLink->GetCompanyName() << endl;
	subscript = 0;
	while (subscript < indexLink->GetLength()) {
		businesscardLink = indexLink->GetAt(subscript);
		cout << businesscardLink->GetName() << " "
			<< businesscardLink->GetPosition() << " "
			<< businesscardLink->GetCellphoneNumber() << " "
			<< businesscardLink->GetEmailAddress() << " "
			<< businesscardLink->GetCompanyName() << " "
			<< businesscardLink->GetAddress() << " "
			<< businesscardLink->GetTelephoneNumber() << " "
			<< businesscardLink->GetFaxNumber() << " "
			<< businesscardLink->GetUrl() << endl;
		subscript++;
	}

	cout << "==================찾기=================" << endl;

	indexLink = indexBook.Find("현대");
	if (indexLink != 0) {
		cout << indexLink->GetCompanyName() << endl;
		subscript = 0;
		while (subscript < indexLink->GetLength()) {
			businesscardLink = indexLink->GetAt(subscript);
			cout << businesscardLink->GetName() << " "
				<< businesscardLink->GetPosition() << " "
				<< businesscardLink->GetCellphoneNumber() << " "
				<< businesscardLink->GetEmailAddress() << " "
				<< businesscardLink->GetCompanyName() << " "
				<< businesscardLink->GetAddress() << " "
				<< businesscardLink->GetTelephoneNumber() << " "
				<< businesscardLink->GetFaxNumber() << " "
				<< businesscardLink->GetUrl() << endl;
			subscript++;
		}
	}
	cout << "==================정렬하기=================" << endl;
	indexBook.Arrange();
	PrintKeys(&indexBook.GetIndexes());

	cout << "==================리스트만들기=================" << endl;
	indexBook.MakeList(&indexes, &count);
	while (i < count) {
		cout << indexes[i].GetCompanyName() << endl;
		subscript = 0;
		while (subscript < indexes[i].GetLength()) {
			businesscardLink = indexes[i].GetAt(subscript);
			cout << businesscardLink->GetName() << " "
				<< businesscardLink->GetPosition() << " "
				<< businesscardLink->GetCellphoneNumber() << " "
				<< businesscardLink->GetEmailAddress() << " "
				<< businesscardLink->GetCompanyName() << " "
				<< businesscardLink->GetAddress() << " "
				<< businesscardLink->GetTelephoneNumber() << " "
				<< businesscardLink->GetFaxNumber() << " "
				<< businesscardLink->GetUrl() << endl;
			subscript++;
		}
		i++;
	}

	cout << "==================빼내기=================" << endl;

	index = businesscardBook.Last();
	businesscard = businesscardBook.PullOut(index);

	indexLink = indexBook.PullOut(index,businesscard.GetCompanyName());
	if (indexLink != 0) {
		cout << indexLink->GetCompanyName() << endl;
		subscript = 0;
		while (subscript < indexLink->GetLength()) {
			businesscardLink = indexLink->GetAt(subscript);
			cout << businesscardLink->GetName() << " "
				<< businesscardLink->GetPosition() << " "
				<< businesscardLink->GetCellphoneNumber() << " "
				<< businesscardLink->GetEmailAddress() << " "
				<< businesscardLink->GetCompanyName() << " "
				<< businesscardLink->GetAddress() << " "
				<< businesscardLink->GetTelephoneNumber() << " "
				<< businesscardLink->GetFaxNumber() << " "
				<< businesscardLink->GetUrl() << endl;
			subscript++;
		}
	}
	else {
		cout << "색인이 지워졌어요" << endl;
	}
	cout << "==================빼내기=================" << endl;

	index = businesscardBook.Last();
	businesscard = businesscardBook.PullOut(index);

	indexLink = indexBook.PullOut(index, businesscard.GetCompanyName());
	if (indexLink != 0) {
		cout << indexLink->GetCompanyName() << endl;
		subscript = 0;
		while (subscript < indexLink->GetLength()) {
			businesscardLink = indexLink->GetAt(subscript);
			cout << businesscardLink->GetName() << " "
				<< businesscardLink->GetPosition() << " "
				<< businesscardLink->GetCellphoneNumber() << " "
				<< businesscardLink->GetEmailAddress() << " "
				<< businesscardLink->GetCompanyName() << " "
				<< businesscardLink->GetAddress() << " "
				<< businesscardLink->GetTelephoneNumber() << " "
				<< businesscardLink->GetFaxNumber() << " "
				<< businesscardLink->GetUrl() << endl;
			subscript++;
		}
	}
	else {
		cout << "색인이 지워졌어요" << endl;
	}
	cout << "==================빼내기=================" << endl;

	index = businesscardBook.Last();
	businesscard = businesscardBook.PullOut(index);

	indexLink = indexBook.PullOut(index, businesscard.GetCompanyName());
	if (indexLink != 0) {
		cout << indexLink->GetCompanyName() << endl;
		subscript = 0;
		while (subscript < indexLink->GetLength()) {
			businesscardLink = indexLink->GetAt(subscript);
			cout << businesscardLink->GetName() << " "
				<< businesscardLink->GetPosition() << " "
				<< businesscardLink->GetCellphoneNumber() << " "
				<< businesscardLink->GetEmailAddress() << " "
				<< businesscardLink->GetCompanyName() << " "
				<< businesscardLink->GetAddress() << " "
				<< businesscardLink->GetTelephoneNumber() << " "
				<< businesscardLink->GetFaxNumber() << " "
				<< businesscardLink->GetUrl() << endl;
			subscript++;
		}
	}
	else {
		cout << "색인이 지워졌어요" << endl;
	}
	cout << "==================빼내기=================" << endl;

	index = businesscardBook.Last();
	businesscard = businesscardBook.PullOut(index);

	indexLink = indexBook.PullOut(index, businesscard.GetCompanyName());
	if (indexLink != 0) {
		cout << indexLink->GetCompanyName() << endl;
		subscript = 0;
		while (subscript < indexLink->GetLength()) {
			businesscardLink = indexLink->GetAt(subscript);
			cout << businesscardLink->GetName() << " "
				<< businesscardLink->GetPosition() << " "
				<< businesscardLink->GetCellphoneNumber() << " "
				<< businesscardLink->GetEmailAddress() << " "
				<< businesscardLink->GetCompanyName() << " "
				<< businesscardLink->GetAddress() << " "
				<< businesscardLink->GetTelephoneNumber() << " "
				<< businesscardLink->GetFaxNumber() << " "
				<< businesscardLink->GetUrl() << endl;
			subscript++;
		}
	}
	else {
		cout << "색인이 지워졌어요" << endl;
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	return 0;
}
#endif

int IndexBook_CompareCompanyNames(void *one, void *other) {
	Index *one_ = static_cast<Index*>(one);
	Index *other_ = static_cast<Index*>(other);

	return one_->GetCompanyName().compare(other_->GetCompanyName());
}