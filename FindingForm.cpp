//FindingForm.cpp
#include"FindingForm.h"
#include"BusinesscardBookForm.h"
#include"BusinesscardBook.h"
#include"IndexBook.h"
#include<afxcmn.h>

BEGIN_MESSAGE_MAP(FindingForm, CDialog)

	ON_BN_CLICKED(IDC_BUTTON_FINDING, OnFindingButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS,OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT,OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST,OnLastButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_SELECTING,OnSelectingButtonClicked)

	ON_WM_CLOSE()

END_MESSAGE_MAP()


FindingForm::FindingForm(CWnd *parent)
	:CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
	this->current = -1;
}


void FindingForm::OnFindingButtonClicked() {
	CString name;
	BusinesscardBookForm *businesscardBookForm;
	GetDlgItem(IDC_EDIT_PERSONAL_NAME)->GetWindowTextA(name);
	businesscardBookForm = (BusinesscardBookForm*)CWnd::FindWindowA("#32770", "¸íÇÔÃ¶");
	if (this->indexes != NULL) {
		delete[] this->indexes;
	}
	businesscardBookForm->businesscardBook->Find((LPCTSTR)name, &this->indexes, &this->count);
	if (this->count > 0) {
		this->current = 0;
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(indexes[0]->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(indexes[0]->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(indexes[0]->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(indexes[0]->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(indexes[0]->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(indexes[0]->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(indexes[0]->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(indexes[0]->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(indexes[0]->GetUrl().c_str());
	}
	else {
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA("");
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA("");
	}
}

void FindingForm::OnFirstButtonClicked() {
	this->current = 0;
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetCellphoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(indexes[this->current]->GetUrl().c_str());
}

void FindingForm::OnPreviousButtonClicked() {
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetCellphoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(indexes[this->current]->GetUrl().c_str());

}

void FindingForm::OnNextButtonClicked() {
	this->current++;
	if (this->current >= this->count) {
		this->current = this->count - 1;
	}
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetCellphoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(indexes[this->current]->GetUrl().c_str());
}

void FindingForm::OnLastButtonClicked() {
	this->current = this->count - 1;

	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(indexes[this->current]->GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(indexes[this->current]->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetCellphoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(indexes[this->current]->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(indexes[this->current]->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(indexes[this->current]->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(indexes[this->current]->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(indexes[this->current]->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(indexes[this->current]->GetUrl().c_str());

}

void FindingForm::OnSelectingButtonClicked() {
	BusinesscardBookForm *businesscardBookForm;
	Businesscard *index;
	
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	Long i;
	Long subscript;
	Index *indexLink;
	CString companyNameKey;
	CString companyName;

	businesscardBookForm = (BusinesscardBookForm*) CWnd::FindWindowA("#32770", "¸íÇÔÃ¶");
	index = businesscardBookForm->businesscardBook->Move(this->indexes[this->current]);
	businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
	businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());


	companyName = CString(index->GetCompanyName().c_str());
	indexLink = businesscardBookForm->indexBook->Find((LPCTSTR)companyName);
	companyNameKey = CString(indexLink->GetCompanyName().c_str());
	subscript = indexLink->Find(index);

	treeRoot= ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetNextItem(NULL, TVGN_ROOT);
	treeParent = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetNextItem(treeRoot, TVGN_CHILD);
	companyName = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetItemText(treeParent);

	while (companyName.Compare(companyNameKey) != 0) {
		treeParent = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetNextItem(treeParent, TVGN_NEXT);
		companyName = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetItemText(treeParent);
	}
	treeChild = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetNextItem(treeParent, TVGN_CHILD);
	i = 0;
	while (i < subscript) {
		treeChild = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetNextItem(treeChild, TVGN_NEXT);
		i++;
	}

	((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->Expand(treeRoot, TVE_EXPAND);
	((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->Expand(treeParent, TVE_EXPAND);
	((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->SelectItem(treeChild);



	if (this->indexes != NULL) {
		delete[] indexes;
	}
	EndDialog(0);

}

void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] indexes;
	}
	EndDialog(0);
}