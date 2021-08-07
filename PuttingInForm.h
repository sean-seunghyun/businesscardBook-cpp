//PuttingInForm.h
#ifndef _PUTTINGINFORM_H
#define _PUTTINGINFORM_H
#include"resource.h"
#include<afxwin.h>

class PuttingInForm : public CDialog {
public:
	enum{IDD=IDD_PUTTINGINFORM};
public:
	PuttingInForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnPuttingInButtonClicked();
	afx_msg void OnCompanyNameFocusLost();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // !_PUTTINGINFORM_H
