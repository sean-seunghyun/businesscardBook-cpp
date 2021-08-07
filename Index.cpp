//Index.cpp
#include"Index.h"
#include"Businesscard.h"
Index::Index(Long capacity)
	:businesscards(capacity), companyName("") {
	this->capacity = capacity;
	this->length = 0;
}
Index::Index(string companyName, Long capacity)
	: businesscards(capacity), companyName(companyName) {
	this->capacity = capacity;
	this->length = 0;
}
Index::Index(const Index& source)
	: businesscards(source.businesscards), companyName(source.companyName) {
	this->capacity = source.capacity;
	this->length = source.length;
}
Index::~Index(){

}

Long Index::PutIn(Businesscard *businesscard) {
	Long subscript;
	if (this->length < this->capacity) {
		subscript = this->businesscards.Store(this->length, businesscard);
	}
	else {
		subscript = this->businesscards.AppendFromRear(businesscard);
		this->capacity++;
	}
	this->length++;

	return subscript;
}

Long Index::Find(Businesscard *businesscard) {
	Long subscript;
	subscript = this->businesscards.LinearSearchUnique(businesscard, Index_CompareBusinesscards);

	return subscript;
}
Long Index::PullOut(Long subscript) {
	
	subscript = this->businesscards.Delete(subscript);
	this->capacity--;
	this->length--;

	return subscript;
}

void Index::Arrange() {
	this->businesscards.SelectionSort(Index_CompareNames);
}

Businesscard* Index::GetAt(Long subscript) {
	return this->businesscards.GetAt(subscript);
}

Index& Index::operator=(const Index& source) {
	this->companyName = source.companyName;
	this->businesscards = source.businesscards;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

int Index_CompareNames(void *one, void *other) {
	Businesscard* *one_ = static_cast<Businesscard**>(one);
	Businesscard* *other_ = static_cast<Businesscard**>(other);

	return (*one_)->GetName().compare((*other_)->GetName());
}


int Index_CompareBusinesscards(void *one, void *other) {
	Businesscard* *one_ = static_cast<Businesscard**>(one);
	int ret;
	if (*one_ > other) {
		ret = 1;
	}
	else if (*one_ == other) {
		ret = 0;
	}
	else if (*one_ < other) {
		ret = -1;
	}
	return ret;
}
