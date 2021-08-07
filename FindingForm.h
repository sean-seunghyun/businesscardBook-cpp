//FindingForm.h
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include"resource.h"
#include<afxwin.h>
class Businesscard;
typedef signed long int Long;

class FindingForm : public CDialog {
public:
	enum{IDD=IDD_FINDINGFORM};
public:
	FindingForm(CWnd *parent = NULL);
protected:
	afx_msg void OnFindingButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnSelectingButtonClicked();
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
private:
	Businesscard* (*indexes);
	Long count;
	Long current;

	
};

#endif // !_FINDINGFORM_H
