//BusinesscardBook.cpp
#include"BusinesscardBook.h"
BusinesscardBook::BusinesscardBook() {
	this->length = 0;
	this->current = 0;
}
BusinesscardBook::BusinesscardBook(const BusinesscardBook& source)
	:businesscards(source.businesscards) {
	this->length = source.length;
	this->current = &(this->businesscards.GetCurrent()->GetObject());
}
BusinesscardBook::~BusinesscardBook() {

}

Businesscard* BusinesscardBook::PutIn(Businesscard businesscard) {
	LinkedList<Businesscard>::Node *node;
	node = this->businesscards.AppendFromTail(businesscard);
	this->current = &node->GetObject();
	this->length++;

	return this->current;
}

void BusinesscardBook::Find(string name, Businesscard* *(*indexes), Long *count) {
	Long i = 0;
	LinkedList<Businesscard>::Node*(*nodes);
	this->businesscards.LinearSearchDuplicate(&name, &nodes, count, CompareNames);
	*indexes = new Businesscard*[*count];
	while (i < *count) {
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}
	if (nodes != 0) {
		delete[] nodes;
	}

}

Businesscard BusinesscardBook::PullOut(Businesscard* index) {
	LinkedList<Businesscard>::Node *node;
	Businesscard businesscard;

	node = this->businesscards.LinearSearchUnique(index, CompareBusinesscards);
	businesscard = this->businesscards.GetAt(node);
	this->businesscards.Delete(node);
	this->length--;
	if (this->businesscards.GetCurrent() != 0) {
		this->current = &(this->businesscards.GetCurrent()->GetObject());
	}
	else {
		this->current = 0;
	}
	return businesscard;
}

Businesscard* BusinesscardBook::FindByCompanyName(string companyName) {
	LinkedList<Businesscard>::Node *node;
	Businesscard *index = 0;
	node = this->businesscards.LinearSearchUnique(&companyName, CompareCompanyNames);
	if (node != 0) {
		index = &node->GetObject();
	}
	return index;
}

Businesscard* BusinesscardBook::Move(Businesscard* index) {
	LinkedList<Businesscard>::Node *node;
	node = this->businesscards.LinearSearchUnique(index, CompareBusinesscards);
	node = this->businesscards.Move(node);
	this->current = &node->GetObject();

	return this->current;
}

Businesscard* BusinesscardBook::First() {
	LinkedList<Businesscard>::Node *node;
	node = this->businesscards.First();
	this->current = &node->GetObject();

	return this->current;
}

Businesscard* BusinesscardBook::Last() {
	LinkedList<Businesscard>::Node *node;
	node = this->businesscards.Last();
	this->current = &node->GetObject();

	return this->current;
}


Businesscard* BusinesscardBook::Previous() {
	LinkedList<Businesscard>::Node *node;
	node = this->businesscards.Previous();
	this->current = &node->GetObject();

	return this->current;
}

Businesscard* BusinesscardBook::Next() {
	LinkedList<Businesscard>::Node *node;
	node = this->businesscards.Next();
	this->current = &node->GetObject();

	return this->current;
}

BusinesscardBook& BusinesscardBook::operator=(const BusinesscardBook& source) {
	this->businesscards.DeleteAllItems();
	this->businesscards = source.businesscards;
	this->length = source.length;
	this->current = &(this->businesscards.GetCurrent()->GetObject());

	return *this;
}


#if 0
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	BusinesscardBook businesscardBook;
	Businesscard* index;
	Businesscard businesscard("홍길동", "사원", "010", "1@", "삼성", "서울시 강남구", "02", "02", "samsung.com");
	Long i = 0;
	Long count;
	Businesscard* (*indexes);
	
	index=businesscardBook.PutIn(businesscard);
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	businesscard=Businesscard("김길동", "인턴", "010", "2@", "현대", "삼성동 현대사옥", "032", "032", "hyundai.com");


	index = businesscardBook.PutIn(businesscard);
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	businesscard = Businesscard("정길동", "사장", "010", "3@", "중소기업", "서초구", "012", "012", "small.com");
	index = businesscardBook.PutIn(businesscard);
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	businesscard = Businesscard("홍길동", "과장", "011", "4@", "중견기업", "도봉구", "022", "022", "middle.com");
	index = businesscardBook.PutIn(businesscard);
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;


	index = businesscardBook.First();
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	index = businesscardBook.Next();
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	index = businesscardBook.Previous();
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	index = businesscardBook.Last();
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;

	cout << "===================" << endl;

	businesscardBook.Find("홍길동", &indexes, &count);
	while (i < count) {
		cout<< indexes[i]->GetName() << " "
			<< indexes[i]->GetPosition() << " "
			<< indexes[i]->GetCellphoneNumber() << " "
			<< indexes[i]->GetEmailAddress() << " "
			<< indexes[i]->GetCompanyName() << " "
			<< indexes[i]->GetAddress() << " "
			<< indexes[i]->GetTelephoneNumber() << " "
			<< indexes[i]->GetFaxNumber() << " "
			<< indexes[i]->GetUrl() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	businesscard=businesscardBook.PullOut(index);
	cout << businesscard.GetName() << " "
		<< businesscard.GetPosition() << " "
		<< businesscard.GetCellphoneNumber() << " "
		<< businesscard.GetEmailAddress() << " "
		<< businesscard.GetCompanyName() << " "
		<< businesscard.GetAddress() << " "
		<< businesscard.GetTelephoneNumber() << " "
		<< businesscard.GetFaxNumber() << " "
		<< businesscard.GetUrl() << endl;
	cout << "===================" << endl;
	index = businesscardBook.FindByCompanyName("현대");
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;


	index = businesscardBook.Move(index);
	cout << index->GetName() << " "
		<< index->GetPosition() << " "
		<< index->GetCellphoneNumber() << " "
		<< index->GetEmailAddress() << " "
		<< index->GetCompanyName() << " "
		<< index->GetAddress() << " "
		<< index->GetTelephoneNumber() << " "
		<< index->GetFaxNumber() << " "
		<< index->GetUrl() << endl;
	return 0;
}
#endif
int CompareNames(void *one, void *other) {
	Businesscard *one_ = static_cast<Businesscard*>(one);
	string *other_ = static_cast<string*>(other);

	return one_->GetName().compare(*other_);
}

int CompareBusinesscards(void *one, void *other) {
	
	int ret;

	if (one > other) {
		ret = -1;
	}
	else if (one == other) {
		ret = 0;
	}
	else if (one < other) {
		ret = 1;
	}

	return ret;
}

int CompareCompanyNames(void *one, void *other) {
	Businesscard *one_ = static_cast<Businesscard*>(one);
	string *other_ = static_cast<string*>(other);

	return one_->GetCompanyName().compare(*other_);
}

