//BusinesscardBookForm.h
#ifndef _BUSINESSCARDBOOKFORM_H
#define _BUSINESSCARDBOOKFORM_H

#include"resource.h"
#include<afxwin.h>
class BusinesscardBook;
class Businesscard;
class IndexBook;
class BusinesscardBookForm : public CDialog {
public:
	enum{IDD=IDD_BUSINESSCARDBOOKFORM};
public:
	BusinesscardBookForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
	void Load();
	void Save();
	void Insert(Businesscard *index);
	void Delete(Businesscard *index);
	CString GetCompanyCode();
	CString GetPersonalCode();

public:
	BusinesscardBook *businesscardBook;
	IndexBook *indexBook;

protected:

	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();

	afx_msg void OnPuttingInButtonClicked();

	afx_msg void OnFindingButtonClicked();
	afx_msg void OnPullingOutButtonClicked();
	afx_msg void OnArrangingButtonClicked();
	afx_msg void OnTreeViewItemDoubleClicked(NMHDR *pNotifyStruct, LRESULT *result);
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()


};

#endif //_BUSINESSCARDBOOKFORM_H
