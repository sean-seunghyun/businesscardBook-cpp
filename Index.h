//Index.h
#ifndef _INDEX_H
#define _INDEX_H
#include"Array.h"
#include<string>
using namespace std;
typedef signed long int Long;
class Businesscard;
class Index {
public:
	Index(Long capacity = 256);
	Index(string companyName, Long capacity = 256);
	Index(const Index& source);
	~Index();
	Long PutIn(Businesscard *businesscard);
	Long Find(Businesscard *businesscard);
	Long PullOut(Long subscript);
	void Arrange();
	Businesscard* GetAt(Long subscript);
	Index& operator = (const Index& source);
	string& GetCompanyName() const;
	Long GetCapacity() const;
	Long GetLength() const;
private:
	Array<Businesscard*> businesscards;
	string companyName;
	Long capacity;
	Long length;
};

int Index_CompareBusinesscards(void *one, void *other);
int Index_CompareNames(void *one, void *other);

inline string& Index::GetCompanyName() const {
	return const_cast<string&>(this->companyName);
}
inline Long Index::GetCapacity() const {
	return this->capacity;
}
inline Long Index::GetLength() const {
	return this->length;
}


#endif // !_INDEX_H
