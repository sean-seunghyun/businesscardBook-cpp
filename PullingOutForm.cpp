//PullingOutForm.cpp
#include"PullingOutForm.h"
#include"BusinesscardBookForm.h"
#include"BusinesscardBook.h"
#include"IndexBook.h"
#include<afxcmn.h>

BEGIN_MESSAGE_MAP(PullingOutForm,CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PullingOutForm::PullingOutForm(CWnd *parent)
	:CDialog(PullingOutForm::IDD, parent) {

}

BOOL PullingOutForm::OnInitDialog() {
	CDialog::OnInitDialog();
	BusinesscardBookForm *businesscardBookForm;
	Businesscard *index;
	Businesscard businesscard;

	Long i;
	Long subscript;
	Index(*indexes);
	Long count;
	Index *indexLink;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	Businesscard *BusinesscardForTreeChild;
	CString companyName;
	CString companyNameKey;
	TVINSERTSTRUCT tvins = { 0, };

	businesscardBookForm = (BusinesscardBookForm*) CWnd::FindWindowA("#32770", "명함철");
	index = businesscardBookForm->businesscardBook->GetCurrent();
	businesscard = businesscardBookForm->businesscardBook->PullOut(index);
	businesscardBookForm->Delete(&businesscard);
	companyName = CString(businesscard.GetCompanyName().c_str());
	businesscardBookForm->indexBook->PullOut(index, (LPCTSTR)companyName);
	
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(businesscard.GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(businesscard.GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(businesscard.GetCellphoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(businesscard.GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(businesscard.GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(businesscard.GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(businesscard.GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(businesscard.GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(businesscard.GetUrl().c_str());

	businesscardBookForm->indexBook->MakeList(&indexes, &count);
	((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->DeleteAllItems();


	tvins.hParent = NULL; tvins.item.mask = TVIF_TEXT; tvins.item.pszText = _T("회사들");
	treeRoot = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->InsertItem(&tvins);
	i = 0;
	while (i < count) {
		treeParent = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->InsertItem(indexes[i].GetCompanyName().c_str(), treeRoot);
		subscript = 0;
		while (subscript < indexes[i].GetLength()) {
			BusinesscardForTreeChild = indexes[i].GetAt(subscript);
			((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->InsertItem(BusinesscardForTreeChild->GetName().c_str(), treeParent);
			subscript++;
		}
		i++;
	}


	   	 
	index = businesscardBookForm->businesscardBook->GetCurrent();
	if (index != NULL) {
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
		subscript = indexLink->Find(index); treeParent = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->GetNextItem(treeRoot, TVGN_CHILD);
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

	}
	else {
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA("");
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA("");
	}

	return FALSE;
}


void PullingOutForm::OnClose() {
	int msgBoxId;
	BusinesscardBookForm *businesscardBookForm;
	Businesscard *index;
	CString name;  CString position; CString cellphoneNumber; CString emailAddress;
	CString companyName; CString address;
	CString telephoneNumber; CString faxNumber; CString url;
	Businesscard businesscard;


	Long i;
	Long subscript;
	Index(*indexes);
	Long count;
	Index *indexLink;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	Businesscard *BusinesscardForTreeChild;
	CString companyNameKey;
	TVINSERTSTRUCT tvins = { 0, };

	msgBoxId = MessageBoxA(
		"명함을 다시 끼워넣으시겠어요?",
		"주의",
		MB_YESNOCANCEL | MB_ICONINFORMATION
	);
	if (msgBoxId == IDYES) {
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->GetWindowTextA(name);
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->GetWindowTextA(position);
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->GetWindowTextA(cellphoneNumber);
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->GetWindowTextA(emailAddress);
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->GetWindowTextA(companyName);
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->GetWindowTextA(address);
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->GetWindowTextA(telephoneNumber);
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->GetWindowTextA(faxNumber);
		GetDlgItem(IDC_STATIC_COMPANY_URL)->GetWindowTextA(url);
		Businesscard businesscard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress,
			(LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);

		businesscardBookForm = (BusinesscardBookForm*)CWnd::FindWindowA("#32770", "명함철");
		index = businesscardBookForm->businesscardBook->PutIn(businesscard);
		indexLink = businesscardBookForm->indexBook->PutIn(index);
		businesscardBookForm->Insert(index);

		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		businesscardBookForm->GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());

		businesscardBookForm->indexBook->MakeList(&indexes, &count);
		((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->DeleteAllItems();


		tvins.hParent = NULL; tvins.item.mask = TVIF_TEXT; tvins.item.pszText = _T("회사들");
		treeRoot = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->InsertItem(&tvins);
		i = 0;
		while (i < count) {
			treeParent = ((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->InsertItem(indexes[i].GetCompanyName().c_str(), treeRoot);
			subscript = 0;
			while (subscript < indexes[i].GetLength()) {
				BusinesscardForTreeChild = indexes[i].GetAt(subscript);
				((CTreeCtrl*)(businesscardBookForm->GetDlgItem(IDC_TREE_INDEXES)))->InsertItem(BusinesscardForTreeChild->GetName().c_str(), treeParent);
				subscript++;
			}
			i++;
		}

		companyName = CString(index->GetCompanyName().c_str());
		indexLink = businesscardBookForm->indexBook->Find((LPCTSTR)companyName);
		companyNameKey = CString(indexLink->GetCompanyName().c_str());
		subscript = indexLink->Find(index);


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

		if (indexes != NULL) {
			delete[] indexes;
		}


		EndDialog(0);

	}
	else if (msgBoxId == IDNO) {
		EndDialog(0);
	}
}