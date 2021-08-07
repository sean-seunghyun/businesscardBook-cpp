//Businesscard.h
#ifndef _BUSINESSCARD_H
#define _BUSINESSCARD_H
#include"Personal.h"
#include"Company.h"
#include<string>
using namespace std;
class Businesscard {
public:
	Businesscard();
	Businesscard(string name, string position, string cellphoneNumber, string emailAddress, string companyName, string address, string telephoneNumber, string faxNumber, string url);
	Businesscard(const Businesscard& source);
	~Businesscard();
	bool IsEqual(const Businesscard& other);
	bool IsNotEqual(const Businesscard& other);
	Businesscard& operator = (const Businesscard& source);
	bool operator == (const Businesscard& other);
	bool operator != (const Businesscard& other);
	string& GetName() const;
	string& GetPosition() const;
	string& GetCellphoneNumber() const;
	string& GetEmailAddress() const;
	string& GetCompanyName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetFaxNumber() const;
	string& GetUrl() const;
private:
	Personal personal;
	Company company;
};

inline string& Businesscard::GetName() const {
	return const_cast<string&>(this->personal.GetName());
}
inline string& Businesscard::GetPosition() const {
	return const_cast<string&>(this->personal.GetPosition());
}
inline string& Businesscard::GetCellphoneNumber() const {
	return const_cast<string&>(this->personal.GetCellphoneNumber());
}
inline string& Businesscard::GetEmailAddress() const {
	return const_cast<string&>(this->personal.GetEmailAddress());
}
inline string& Businesscard::GetCompanyName() const {
	return const_cast<string&>(this->company.GetName());
}
inline string& Businesscard::GetAddress() const {
	return const_cast<string&>(this->company.GetAddress());
}
inline string& Businesscard::GetTelephoneNumber() const {
	return const_cast<string&>(this->company.GetTelephoneNumber());
}
inline string& Businesscard::GetFaxNumber() const {
	return const_cast<string&>(this->company.GetFaxNumber());
}
inline string& Businesscard::GetUrl() const {
	return const_cast<string&>(this->company.GetUrl());
}
#endif//_BUSINESSCARD_H
