//Personal.cpp
#include"Personal.h"
Personal::Personal()
	:name(""), position(""), cellphoneNumber(""), emailAddress("") {

}
Personal::Personal(string name, string position, string cellphoneNumber, string emailAddress)
	: name(name), position(position), cellphoneNumber(cellphoneNumber), emailAddress(emailAddress) {

}
Personal::Personal(const Personal& source)
	: name(source.name), position(source.position), cellphoneNumber(source.cellphoneNumber), emailAddress(source.emailAddress) {

}
Personal::~Personal() {

}
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->position.compare(other.position) == 0 &&
		this->cellphoneNumber.compare(other.cellphoneNumber) == 0 &&
		this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}

bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->position.compare(other.position) != 0 ||
		this->cellphoneNumber.compare(other.cellphoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}

bool Personal::operator==(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) == 0 &&
		this->position.compare(other.position) == 0 &&
		this->cellphoneNumber.compare(other.cellphoneNumber) == 0 &&
		this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}

bool Personal::operator!=(const Personal& other) {
	bool ret = false;
	if (this->name.compare(other.name) != 0 ||
		this->position.compare(other.position) != 0 ||
		this->cellphoneNumber.compare(other.cellphoneNumber) != 0 ||
		this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}

Personal& Personal::operator=(const Personal& source) {
	this->name = source.name;
	this->position = source.position;
	this->cellphoneNumber = source.cellphoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}


#if 0
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Personal personalOne("홍길동", "사원", "010", "1@");
	Personal personalTwo("고길동", "과장", "011", "2@");
	Personal personalThree("홍길동", "사원", "010", "1@");
	bool ret;

	cout << personalOne.GetName() << " "
		<< personalOne.GetPosition() << " "
		<< personalOne.GetCellphoneNumber() << " "
		<< personalOne.GetEmailAddress() << endl;

	cout << personalTwo.GetName() << " "
		<< personalTwo.GetPosition() << " "
		<< personalTwo.GetCellphoneNumber() << " "
		<< personalTwo.GetEmailAddress() << endl;

	cout << personalThree.GetName() << " "
		<< personalThree.GetPosition() << " "
		<< personalThree.GetCellphoneNumber() << " "
		<< personalThree.GetEmailAddress() << endl;

	ret = personalOne.IsEqual(personalThree);
	if (ret == true) {
		cout << "같은 개인입니다." << endl;
	}

	ret = personalOne.IsNotEqual(personalTwo);
	if (ret == true) {
		cout << "다른 개인입니다." << endl;
	}

	if (personalOne == personalThree) {
		cout << "같은 개인입니다." << endl;
	}

	if (personalOne != personalTwo) {
		cout << "다른 개인입니다." << endl;
	}


	return 0;
}

#endif