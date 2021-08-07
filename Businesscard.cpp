//Businesscard.cpp
#include"Businesscard.h"
Businesscard::Businesscard() {

}
Businesscard::Businesscard(string name, string position, string cellphoneNumber, string emailAddress, string companyName, string address, string telephoneNumber, string faxNumber, string url)
	:personal(name, position, cellphoneNumber, emailAddress), company(companyName, address, telephoneNumber, faxNumber, url) {

}
Businesscard::Businesscard(const Businesscard& source)
	: personal(source.personal), company(source.company) {

}
Businesscard::~Businesscard() {

}

bool Businesscard::IsEqual(const Businesscard& other) {
	bool ret = false;
	if (this->personal.IsEqual(other.personal) == true &&
		this->company.IsEqual(other.company) == true) {
		ret = true;
	}
	return ret;
}
bool Businesscard::IsNotEqual(const Businesscard& other) {
	bool ret = false;
	if (this->personal.IsNotEqual(other.personal) == true ||
		this->company.IsNotEqual(other.company) == true) {
		ret = true;
	}
	return ret;
}

bool Businesscard::operator==(const Businesscard& other) {
	bool ret = false;
	if (this->personal == other.personal &&
		this->company == other.company) {
		ret = true;
	}
	return ret;
}

bool Businesscard::operator!=(const Businesscard& other) {
	bool ret = false;
	if (this->personal != other.personal ||
		this->company != other.company) {
		ret = true;
	}
	return ret;
}


Businesscard& Businesscard::operator=(const Businesscard& source) {
	this->personal = source.personal;
	this->company = source.company;

	return *this;
}

#if 0
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	bool ret;
	Businesscard businesscardOne("ȫ�浿", "���", "010", "1@", "�Ｚ", "����� ������", "02", "02", "samsung.com");
	Businesscard businesscardTwo("��浿", "����", "011", "2@", "����", "�λ�� ���ϱ�", "052", "052", "lifeIsGood.com");
	Businesscard businesscardThree("ȫ�浿", "���", "010", "1@", "�Ｚ", "����� ������", "02", "02", "samsung.com");

	cout << businesscardOne.GetName() << " "
		<< businesscardOne.GetPosition() << " "
		<< businesscardOne.GetCellphoneNumber() << " "
		<< businesscardOne.GetCompanyName() << " "
		<< businesscardOne.GetAddress() << " "
		<< businesscardOne.GetTelephoneNumber() << " "
		<< businesscardOne.GetFaxNumber() << " "
		<< businesscardOne.GetUrl() << endl;

	cout << businesscardTwo.GetName() << " "
		<< businesscardTwo.GetPosition() << " "
		<< businesscardTwo.GetCellphoneNumber() << " "
		<< businesscardTwo.GetCompanyName() << " "
		<< businesscardTwo.GetAddress() << " "
		<< businesscardTwo.GetTelephoneNumber() << " "
		<< businesscardTwo.GetFaxNumber() << " "
		<< businesscardTwo.GetUrl() << endl;

	cout << businesscardThree.GetName() << " "
		<< businesscardThree.GetPosition() << " "
		<< businesscardThree.GetCellphoneNumber() << " "
		<< businesscardThree.GetCompanyName() << " "
		<< businesscardThree.GetAddress() << " "
		<< businesscardThree.GetTelephoneNumber() << " "
		<< businesscardThree.GetFaxNumber() << " "
		<< businesscardThree.GetUrl() << endl;

	ret = businesscardOne.IsEqual(businesscardThree);
	if (ret == true) {
		cout << "���� �����Դϴ�." << endl;
	}

	ret = businesscardOne.IsNotEqual(businesscardTwo);
	if (ret == true) {
		cout << "�ٸ� �����Դϴ�." << endl;
	}

	if (businesscardOne == businesscardThree) {
		cout << "���� �����Դϴ�." << endl;
	}

	if (businesscardOne != businesscardTwo) {
		cout << "�ٸ� �����Դϴ�." << endl;
	}

	return 0;
}
#endif