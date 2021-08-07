//PuttingInForm.cpp
#include"PuttingInForm.h"
#include"BusinesscardBookForm.h"
#include"BusinesscardBook.h" //BusinesscardBookForm.h에는 전방선언만 했음
#include"IndexBook.h"
#include<afxcmn.h>

 BEGIN_MESSAGE_MAP(PuttingInForm,CDialog)

	 ON_BN_CLICKED(IDC_BUTTON_PUTTINGIN,OnPuttingInButtonClicked)

	 ON_EN_KILLFOCUS(IDC_EDIT_COMPANY_NAME,OnCompanyNameFocusLost)

	 ON_WM_CLOSE()

END_MESSAGE_MAP()


 PuttingInForm::PuttingInForm(CWnd *parent)
	 :CDialog(PuttingInForm::IDD, parent) {
 }

 BOOL PuttingInForm::OnInitDialog() {
	 CDialog::OnInitDialog();
	 TCHAR position[][5] = { "인턴","사원","과장","대리","부장","사장" };
	 TCHAR domain[][16] = { "google.com","naver.com","samsung.com" };
	 Long i = 0;
	 
	 while (i < sizeof(position) / sizeof(position[0])) {
		 ((CComboBox*)GetDlgItem(IDC_COMBOBOX_PERSONAL_POSITION))->AddString(position[i]);
		 i++;
	 }
	 i = 0;
	 while (i < sizeof(domain) / sizeof(domain[0])) {
		 ((CComboBox*)GetDlgItem(IDC_COMBOBOX_PERSONAL_EMAILADDRESS_DOMAIN))->AddString(domain[i]);
		 i++;
	 }
	 return FALSE;
 }

 void PuttingInForm::OnPuttingInButtonClicked() {
	 CString name;  CString position; CString cellphoneNumber; CString emailAddress;
	 CString emailId; CString domain; CString companyName; CString address;
	 CString telephoneNumber; CString faxNumber; CString url;
	 BusinesscardBookForm *businesscardBookForm;
	 Businesscard *index;

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


	 GetDlgItem(IDC_EDIT_PERSONAL_NAME)->GetWindowTextA(name);
	 GetDlgItem(IDC_COMBOBOX_PERSONAL_POSITION)->GetWindowTextA(position);
	 GetDlgItem(IDC_EDIT_PERSONAL_CELLPHONENUMBER)->GetWindowTextA(cellphoneNumber);
	 GetDlgItem(IDC_EDIT_PERSONAL_EMAILADDRESS_ID)->GetWindowTextA(emailId);
	 GetDlgItem(IDC_COMBOBOX_PERSONAL_EMAILADDRESS_DOMAIN)->GetWindowTextA(domain);
	 emailAddress.Format("%s@%s", emailId, domain);
	 GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowTextA(companyName);
	 GetDlgItem(IDC_EDIT_COMPANY_ADDRESS)->GetWindowTextA(address);
	 GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER)->GetWindowTextA(telephoneNumber);
	 GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER)->GetWindowTextA(faxNumber);
	 GetDlgItem(IDC_EDIT_COMPANY_URL)->GetWindowTextA(url);
	 
	 businesscardBookForm = (BusinesscardBookForm*)CWnd::FindWindowA("#32770", "명함철");
	 Businesscard businesscard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress,
		 (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
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

 void PuttingInForm::OnCompanyNameFocusLost() {
	 CString companyName;
	 BusinesscardBookForm *businesscardBookForm;
	 Businesscard *index;
	 Index *indexLink;
	 

	 GetDlgItem(IDC_EDIT_COMPANY_NAME)->GetWindowTextA(companyName);
	 businesscardBookForm = (BusinesscardBookForm*)FindWindow("#32770", "명함철");
	 indexLink = businesscardBookForm->indexBook->Find((LPCTSTR)companyName);



	 if (indexLink != NULL) {
		 index = indexLink->GetAt(0);
		 GetDlgItem(IDC_EDIT_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		 GetDlgItem(IDC_EDIT_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		 GetDlgItem(IDC_EDIT_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		 GetDlgItem(IDC_EDIT_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
	 }
 }

 void PuttingInForm::OnClose() {
	 EndDialog(0);
 }