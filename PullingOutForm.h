//PullingOutForm.h
#ifndef _PULLINGOUTFORM_H
#include<afxwin.h>
#include"resource.h"

class PullingOutForm : public CDialog {
public:
	enum{IDD=IDD_PULLINGOUTFORM};
public:
	PullingOutForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
};

#endif // !_PULLINGOUTFORM_H
