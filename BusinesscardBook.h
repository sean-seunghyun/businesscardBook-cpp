//BusinesscardBook.h
#ifndef _BUSINESSCARDBOOK_H
#define _BUSINESSCARDBOOK_H
#include"Businesscard.h"
#include"LinkedList.h"
#include<string>
using namespace std;
typedef signed long int Long;
class BusinesscardBook {
public:
	BusinesscardBook();
	BusinesscardBook(const BusinesscardBook& source);
	~BusinesscardBook();
	Businesscard* PutIn(Businesscard businesscard);
	void Find(string name, Businesscard* *(*indexes), Long *count);
	Businesscard PullOut(Businesscard* index);
	Businesscard* FindByCompanyName(string companyName);
	Businesscard* Move(Businesscard* index);
	Businesscard* First();
	Businesscard* Previous();
	Businesscard* Next();
	Businesscard* Last();
	BusinesscardBook& operator = (const BusinesscardBook& source);
	Long GetLength() const;
	Businesscard* GetCurrent() const;
private:
	LinkedList<Businesscard> businesscards;
	Long length;
	Businesscard* current;
};

int CompareNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int CompareBusinesscards(void *one, void *other);

inline Long BusinesscardBook::GetLength() const {
	return this->length;
}

inline Businesscard* BusinesscardBook::GetCurrent() const {
	return const_cast<Businesscard*>(this->current);
}
#endif//_BUSINESSCARDBOOK_H