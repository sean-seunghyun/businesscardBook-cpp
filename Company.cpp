//Company.cpp
#include"Company.h"

Company::Company()
	:name(""), address(""), telephoneNumber(""), faxNumber(""), url("") {

}
Company::Company(string name, string address, string telephoneNumber, string faxNumber, string url)
	: name(name), address(address), telephoneNumber(telephoneNumber), faxNumber(faxNumber), url(url) {

}
Company::Company(const Company& source)
	: name(source.name), address(source.address), telephoneNumber(source.telephoneNumber), faxNumber(source.faxNumber), url(source.url) {

}
Company::~Company() {

}

bool Company::IsEqual(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->faxNumber.compare(other.faxNumber) == 0 &&
		this->url.compare(other.url) == 0) {
		ret = true;
	}
	return ret;
}

bool Company::IsNotEqual(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->faxNumber.compare(other.faxNumber) != 0 ||
		this->url.compare(other.url) == 0) {
		ret = true;
	}
	return ret;
}


bool Company::operator==(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->faxNumber.compare(other.faxNumber) == 0 &&
		this->url.compare(other.url) == 0) {
		ret = true;
	}
	return ret;
}

bool Company::operator!=(const Company& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->faxNumber.compare(other.faxNumber) != 0 ||
		this->url.compare(other.url) == 0) {
		ret = true;
	}
	return ret;
}

Company& Company::operator =  (const Company& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->faxNumber = source.faxNumber;
	this->url = source.url;

	return *this;
}

#if 0
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	bool ret;
	Company companyOne("삼성", "서초구", "02", "02", "samsung.com");
	Company companyTwo("LG", "마포구", "042", "052", "lg.com");
	Company companyThree("삼성", "서초구", "02", "02", "samsung.com");

	cout << companyOne.GetName() << " "
		<< companyOne.GetAddress() << " "
		<< companyOne.GetTelephoneNumber() << " "
		<< companyOne.GetFaxNumber() << " "
		<< companyOne.GetUrl() << endl;
	
	cout << companyTwo.GetName() << " "
		<< companyTwo.GetAddress() << " "
		<< companyTwo.GetTelephoneNumber() << " "
		<< companyTwo.GetFaxNumber() << " "
		<< companyTwo.GetUrl() << endl;

	cout << companyThree.GetName() << " "
		<< companyThree.GetAddress() << " "
		<< companyThree.GetTelephoneNumber() << " "
		<< companyThree.GetFaxNumber() << " "
		<< companyThree.GetUrl() << endl;

	ret = companyOne.IsEqual(companyThree);
	if (ret == true) {
		cout << "같은 회사입니다." << endl;
	}

	ret = companyOne.IsNotEqual(companyTwo);
	if (ret == true) {
		cout << "다른 회사입니다." << endl;
	}

	if (companyOne == companyThree) {
		cout << "같은 회사입니다." << endl;
	}

	if (companyOne != companyTwo) {
		cout << "다른 회사입니다." << endl;
	}
	return 0;
}
#endif