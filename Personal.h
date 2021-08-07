//Personal.h
#ifndef _PERSONAL_H
#define _PERSONAL_H
#include<string>
using namespace std;

class Personal {
public:
	Personal();
	Personal(string name, string position, string cellphoneNumber, string emailAddress);
	Personal(const Personal& source);
	~Personal();
	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);
	Personal& operator =(const Personal& source);
	bool operator == (const Personal& other);
	bool operator != (const Personal& other);
	string& GetName() const;
	string& GetPosition() const;
	string& GetCellphoneNumber() const;
	string& GetEmailAddress() const;
private:
	string name;
	string position;
	string cellphoneNumber;
	string emailAddress;
};
inline string& Personal::GetName() const {
	return const_cast<string&>(this->name);
}
inline string& Personal::GetPosition() const {
	return const_cast<string&>(this->position);
}
inline string& Personal::GetCellphoneNumber() const {
	return const_cast<string&>(this->cellphoneNumber);
}
inline string& Personal::GetEmailAddress() const {
	return const_cast<string&>(this->emailAddress);
}

#endif//_PERSONAL_H

