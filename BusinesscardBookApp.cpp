//BusinesscardBookApp.cpp
#include"BusinesscardBookApp.h"
#include"BusinesscardBookForm.h"

BOOL BusinesscardBookApp::InitInstance() {
	BusinesscardBookForm businesscardBookForm;
	this->m_pMainWnd = &businesscardBookForm;
	businesscardBookForm.DoModal();

	return TRUE;
}

BusinesscardBookApp businesscardBookApp;