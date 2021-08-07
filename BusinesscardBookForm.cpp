//BusinesscardBookForm.cpp
#include"BusinesscardBookForm.h"
#include"BusinesscardBook.h"
#include"PuttingInForm.h"
#include"FindingForm.h"
#include"PullingOutForm.h"
#include"IndexBook.h"
#include<afxcmn.h>
#include<afxdb.h>





BEGIN_MESSAGE_MAP(BusinesscardBookForm,CDialog)

	ON_BN_CLICKED(IDC_BUTTON_FIRST,OnFirstButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS,OnPreviousButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_NEXT,OnNextButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_LAST,OnLastButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_PUTTINGIN,OnPuttingInButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_FINDING,OnFindingButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_PULLINGOUT,OnPullingOutButtonClicked)

	ON_BN_CLICKED(IDC_BUTTON_ARRANGING,OnArrangingButtonClicked)

	ON_NOTIFY(NM_DBLCLK,IDC_TREE_INDEXES,OnTreeViewItemDoubleClicked)

	ON_WM_CLOSE()

END_MESSAGE_MAP()


BusinesscardBookForm::BusinesscardBookForm(CWnd *parent)
	:CDialog(BusinesscardBookForm::IDD,parent){
	this->businesscardBook = NULL;
	this->indexBook = NULL;
}

BOOL BusinesscardBookForm::OnInitDialog() {
	CDialog::OnInitDialog();
	Businesscard *index=NULL;
	Businesscard *previous = NULL;
	Index *indexLink;
	Index(*indexes);
	Long count;
	TVINSERTSTRUCT tvins = { 0, };
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	CString companyName;
	CString companyNameKey;
	Businesscard *businesscard;
	Long i;
	Long subscript;

	this->businesscardBook = new BusinesscardBook;
	this->indexBook = new IndexBook;
	this->Load();

	if (this->businesscardBook->GetLength() > 0) {
		index = this->businesscardBook->First();

		
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
	
	
		while (index != previous) {
			previous = index;
			this->indexBook->PutIn(index);
			index = this->businesscardBook->Next();
		}

	}
	this->indexBook->MakeList(&indexes, &count);//할당해제!
	
	tvins.hParent = NULL; tvins.item.mask = TVIF_TEXT; tvins.item.pszText = _T("회사들");
	treeRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(&tvins);
	
	i = 0;
	while (i < count) {
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(indexes[i].GetCompanyName().c_str(), treeRoot);
		subscript = 0;
		while (subscript < indexes[i].GetLength()) {
			businesscard = indexes[i].GetAt(subscript);
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(businesscard->GetName().c_str(), treeParent);
			subscript++;
		}
		i++;
	}
		
		index = this->businesscardBook->First();
		if (index != NULL) {
			companyName = CString(index->GetCompanyName().c_str());
			indexLink = this->indexBook->Find((LPCTSTR)companyName);
			companyNameKey = CString(indexLink->GetCompanyName().c_str());
			subscript = indexLink->Find(index);

			treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeRoot, TVGN_CHILD);
			companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);

			while (companyName.Compare(companyNameKey) != 0) {
				treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_NEXT);
				companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
			}
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
			i = 0;
			while (i < subscript) {
				treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
				i++;
			}
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeRoot, TVE_EXPAND);
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeParent, TVE_EXPAND);
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(treeChild);
		}
		if (indexes != NULL) {
			delete[] indexes;
		}

	return FALSE;
}

void BusinesscardBookForm::OnFirstButtonClicked() {
	Businesscard *index;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	CString companyName;
	CString companyNameKey;
	Long i;
	Long subscript;
	Index *indexLink;

	index = this->businesscardBook->First();
	if (index != NULL) {
		companyName = CString(index->GetCompanyName().c_str());
		indexLink = this->indexBook->Find((LPCTSTR)companyName);
		companyNameKey = CString(indexLink->GetCompanyName().c_str());
		subscript = indexLink->Find(index);

		treeRoot= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeRoot, TVGN_CHILD);
		companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		while (companyName.Compare(companyNameKey) != 0) {
			treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_NEXT);
			companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		}
		treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeRoot, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeParent, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(treeChild);
	
	GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
	GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
	GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
	}

}
void BusinesscardBookForm::OnPreviousButtonClicked() {
	Businesscard *index;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	CString companyName;
	CString companyNameKey;
	Long i;
	Long subscript;
	Index *indexLink;

	index = this->businesscardBook->Previous();
	if (index != NULL) {
		companyName = CString(index->GetCompanyName().c_str());
		indexLink = this->indexBook->Find((LPCTSTR)companyName);
		companyNameKey = CString(indexLink->GetCompanyName().c_str());
		subscript = indexLink->Find(index);

		treeRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeRoot, TVGN_CHILD);
		companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		while (companyName.Compare(companyNameKey) != 0) {
			treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_NEXT);
			companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		}
		treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeRoot, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeParent, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(treeChild);

		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
	}
}


void BusinesscardBookForm::OnNextButtonClicked() {
	Businesscard *index;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	CString companyName;
	CString companyNameKey;
	Long i;
	Long subscript;
	Index *indexLink;

	index = this->businesscardBook->Next();
	if (index != NULL) {
		companyName = CString(index->GetCompanyName().c_str());
		indexLink = this->indexBook->Find((LPCTSTR)companyName);
		companyNameKey = CString(indexLink->GetCompanyName().c_str());
		subscript = indexLink->Find(index);

		treeRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeRoot, TVGN_CHILD);
		companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		while (companyName.Compare(companyNameKey) != 0) {
			treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_NEXT);
			companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		}
		treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeRoot, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeParent, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(treeChild);

		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
	}
}
void BusinesscardBookForm::OnLastButtonClicked() {
	Businesscard *index;
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	CString companyName;
	CString companyNameKey;
	Long i;
	Long subscript;
	Index *indexLink;

	index = this->businesscardBook->Last();
	if (index != NULL) {
		companyName = CString(index->GetCompanyName().c_str());
		indexLink = this->indexBook->Find((LPCTSTR)companyName);
		companyNameKey = CString(indexLink->GetCompanyName().c_str());
		subscript = indexLink->Find(index);

		treeRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeRoot, TVGN_CHILD);
		companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		while (companyName.Compare(companyNameKey) != 0) {
			treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_NEXT);
			companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		}
		treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeRoot, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeParent, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(treeChild);

		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
	}
}

void BusinesscardBookForm::OnPuttingInButtonClicked() {
	PuttingInForm puttingInForm;

	puttingInForm.DoModal();
}

void BusinesscardBookForm::OnFindingButtonClicked() {
	FindingForm findingForm;

	findingForm.DoModal();
}

void BusinesscardBookForm::OnPullingOutButtonClicked() {
	PullingOutForm pullingOutForm;
	pullingOutForm.DoModal();
}


void BusinesscardBookForm::OnArrangingButtonClicked() {
	Businesscard *index;
	Index *indexLink;
	Index(*indexes);
	Long count;
	TVINSERTSTRUCT tvins = { 0, };
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	CString companyName;
	CString companyNameKey;
	Businesscard *businesscard;
	Long i;
	Long subscript;

	this->indexBook->Arrange();
	this->indexBook->MakeList(&indexes, &count);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->DeleteAllItems();
	tvins.hParent = NULL; tvins.item.mask = TVIF_TEXT; tvins.item.pszText = _T("회사들");
	treeRoot = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(&tvins);
	i = 0;
	while (i < count) {
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(indexes[i].GetCompanyName().c_str(), treeRoot);
		subscript = 0;
		while (subscript < indexes[i].GetLength()) {
			businesscard = indexes[i].GetAt(subscript);
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(businesscard->GetName().c_str(), treeParent);
			subscript++;
		}
		i++;
	}
	if (this->businesscardBook->GetLength() > 0) {
		index = this->businesscardBook->First();
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());

		companyName = CString(index->GetCompanyName().c_str());
		indexLink = this->indexBook->Find((LPCTSTR)companyName);
		companyNameKey = CString(indexLink->GetCompanyName().c_str());
		subscript = indexLink->Find(index);

		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeRoot, TVGN_CHILD);
		companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);

		while (companyName.Compare(companyNameKey) != 0) {
			treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_NEXT);
			companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);
		}
		treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
		i = 0;
		while (i < subscript) {
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
			i++;
		}
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeRoot, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(treeParent, TVE_EXPAND);
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(treeChild);

	}
	if (indexes != NULL) {
		delete[] indexes;
	}
}

void BusinesscardBookForm::OnTreeViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result) {
	HTREEITEM treeRoot;
	HTREEITEM treeParent;
	HTREEITEM treeChild;
	HTREEITEM treeChildKey;
	HTREEITEM treeGrandChild;
	Long i;
	Long subscript=0;
	Index *indexLink;
	Businesscard *index;
	CString companyName;

	treeChildKey = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetSelectedItem();
	treeGrandChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChildKey, TVGN_CHILD);
	if (treeGrandChild == NULL) {
		treeParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChildKey, TVGN_PARENT);
		companyName = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(treeParent);

		indexLink = this->indexBook->Find((LPCTSTR)companyName);
		treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeParent, TVGN_CHILD);
		while (treeChild != treeChildKey) {
			treeChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(treeChild, TVGN_NEXT);
			subscript++;
		}
		index = indexLink->GetAt(subscript);
		GetDlgItem(IDC_STATIC_PERSONAL_NAME)->SetWindowTextA(index->GetName().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_POSITION)->SetWindowTextA(index->GetPosition().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_CELLPHONENUMBER)->SetWindowTextA(index->GetCellphoneNumber().c_str());
		GetDlgItem(IDC_STATIC_PERSONAL_EMAILADDRESS)->SetWindowTextA(index->GetEmailAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_NAME)->SetWindowTextA(index->GetCompanyName().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_ADDRESS)->SetWindowTextA(index->GetAddress().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_TELEPHONENUMBER)->SetWindowTextA(index->GetTelephoneNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_FAXNUMBER)->SetWindowTextA(index->GetFaxNumber().c_str());
		GetDlgItem(IDC_STATIC_COMPANY_URL)->SetWindowTextA(index->GetUrl().c_str());
		this->businesscardBook->Move(index);
	}


}

void BusinesscardBookForm::OnClose() {
	if (this->businesscardBook != NULL) {
		//this->Save();
		delete this->businesscardBook;
	}
	EndDialog(0);
}

void BusinesscardBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.name, Personal.position, Personal.cellphoneNumber, personal.emailAddress, Company.name, Company.address, Company.telephoneNumber, Company.faxNumber,Company.url FROM Company INNER JOIN Personal ON Personal.companyCode=Company.companyCode;";
	
	db.OpenEx("DSN=BusinesscardBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString name;
	CString position;
	CString cellphoneNumber;
	CString emailAddress;
	CString companyName;
	CString address;
	CString telephoneNumber;
	CString faxNumber;
	CString url;
	Businesscard businesscard;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, position);
		rs.GetFieldValue((short)2, cellphoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		rs.GetFieldValue((short)4, companyName);
		rs.GetFieldValue((short)5, address);
		rs.GetFieldValue((short)6, telephoneNumber);
		rs.GetFieldValue((short)7, faxNumber);
		rs.GetFieldValue((short)8, url);
		businesscard = Businesscard((LPCTSTR)name, (LPCTSTR)position, (LPCTSTR)cellphoneNumber, (LPCTSTR)emailAddress, (LPCTSTR)companyName, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)faxNumber, (LPCTSTR)url);
		this->businesscardBook->PutIn(businesscard);
		rs.MoveNext();	
	}
	rs.Close();
	db.Close();
}


void BusinesscardBookForm::Insert(Businesscard *index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql;
	CString companyCode;

	sql.Format("SELECT Company.companyCode FROM Company WHERE name='%s'AND address = '%s' AND telephoneNumber = '%s' AND faxNumber = '%s' AND url = '%s'; ",
		index->GetCompanyName().c_str(), index->GetAddress().c_str(), index->GetTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());

	db.OpenEx("DSN=BusinesscardBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	

	if (rs.IsEOF()) {
		companyCode = this->GetCompanyCode();
		sql.Format("INSERT INTO Company(companyCode, name, address, telephoneNumber, faxNumber, url) VALUES('%s','%s','%s','%s','%s','%s');",
			(LPCTSTR)companyCode, index->GetCompanyName().c_str(), index->GetAddress().c_str(), index->GetTelephoneNumber().c_str(), index->GetFaxNumber().c_str(), index->GetUrl().c_str());
		db.ExecuteSQL(sql);
	}
	else {
		rs.GetFieldValue((short)0, companyCode);
	}

	sql.Format("INSERT INTO Personal(code,companyCode,name,position,cellphoneNumber,emailAddress) VALUES('%s','%s','%s','%s','%s','%s');",
		(LPCTSTR)this->GetPersonalCode(), (LPCTSTR)companyCode, index->GetName().c_str(), index->GetPosition().c_str(), index->GetCellphoneNumber().c_str(), index->GetEmailAddress().c_str());
	db.ExecuteSQL(sql);		
	rs.Close();
	db.Close();	
}


//연산에 끼워넣기
void BusinesscardBookForm::Delete(Businesscard *index) {
	CDatabase db;
	CRecordset rs(&db);
	CRecordset rsForCompany(&db);
	CString code;
	CString companyCode;
	CString sql;

	sql.Format("SELECT Personal.code, Personal.companyCode FROM Personal WHERE name='%s' AND position='%s' AND cellphoneNumber='%s' AND emailAddress='%s';",
		index->GetName().c_str(), index->GetPosition().c_str(), index->GetCellphoneNumber().c_str(), index->GetEmailAddress().c_str());
	db.OpenEx("DSN=BusinesscardBook;UID=root;PWD=a8gkdlfn");

	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
		rs.GetFieldValue((short)1, companyCode);
	}	
	
	sql.Format("DELETE FROM Personal WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	//회사에 개인이 하나도 없으면 회사를 지운다.
	sql.Format("SELECT Personal.name, Company.name FROM Company INNER JOIN Personal ON Personal.companyCode=Company.companyCode WHERE Company.companyCode='%s';",
		(LPCTSTR)companyCode);
	rsForCompany.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (rsForCompany.IsEOF()) {
		sql.Format("DELETE FROM Company WHERE companyCode='%s';", (LPCTSTR)companyCode);
		db.ExecuteSQL(sql);
	}

	rsForCompany.Close();
	rs.Close();
	db.Close();
}


CString BusinesscardBookForm::GetCompanyCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Company.companyCode FROM Company ORDER BY companyCode DESC;";
	CString companyCode = "C0000";
	Long companyCodeNumber;
	db.OpenEx("DSN=BusinesscardBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, companyCode);
	}
	companyCodeNumber = atoi((LPCTSTR)companyCode.Right(4));
	companyCodeNumber++;
	companyCode.Format("C%04d", companyCodeNumber);
	rs.Close();
	db.Close();

	return companyCode;	
}

CString BusinesscardBookForm::GetPersonalCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	CString code = "P0000";
	Long codeNumber;
	db.OpenEx("DSN=BusinesscardBook;UID=root;PWD=a8gkdlfn");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
	}
	codeNumber = atoi((LPCTSTR)code.Right(4));
	codeNumber++;
	code.Format("P%04d", codeNumber);
	rs.Close();
	db.Close();

	return code;
}


void BusinesscardBookForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CRecordset rsForCode(&db);
	CString code;
	CString companyCode;
	Businesscard *previous = NULL;
	CString sql;

	db.OpenEx("DSN=BusinesscardBook;UID=root;PWD=a8gkdlfn");
	//개인의 코드와 회사코드를 레코드셋에 모두 저장함
	rsForCode.Open(AFX_DB_USE_DEFAULT_TYPE, "SELECT Personal.code, Personal.companyCode FROM Personal;");
	
	db.ExecuteSQL("DELETE FROM Personal;");
	db.ExecuteSQL("DELETE FROM Company;");
	this->businesscardBook->First();
	while (this->businesscardBook->GetCurrent() != previous) {
		previous = this->businesscardBook->GetCurrent();
		//코드와 회사코드를 각각 변수에 저장
		if (!rsForCode.IsEOF()) {
			rsForCode.GetFieldValue((short)0, code);
			rsForCode.GetFieldValue((short)1, companyCode);
			rsForCode.MoveNext();
		}
		//회사코드로 회사가 데이터베이스에 있는지 검색해 레코드셋에 저장함
		sql.Format("SELECT Company.name FROM Company WHERE companyCode='%s',(LPCTSTR)companyCode;");
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (rs.IsEOF()) {//만약 없으면 회사를 저장한다.
			sql.Format("INSERT INTO Company(companyCode,name,address,telephoneNumber,faxNumber,url) VALUES('%s','%s','%s','%s','%s','%s';)",
				(LPCTSTR)companyCode, previous->GetCompanyName().c_str(), previous->GetAddress().c_str(), previous->GetTelephoneNumber().c_str(), previous->GetFaxNumber().c_str(), previous->GetUrl().c_str());
			db.ExecuteSQL(sql);
		}
		rs.Close();
		//개인을 저장함
		sql.Format("INSERT INTO Personal(companyCode, code, name, position, cellphoneNumber, emailAddress) VALUES('%s','%s','%s','%s','%s','%s';)",
			(LPCTSTR)companyCode, (LPCTSTR)code, previous->GetName().c_str(), previous->GetPosition().c_str(), previous->GetCellphoneNumber().c_str(), previous->GetEmailAddress().c_str());
		db.ExecuteSQL(sql);
		this->businesscardBook->Next();
	}
	rsForCode.Close();
	db.Close();
}
