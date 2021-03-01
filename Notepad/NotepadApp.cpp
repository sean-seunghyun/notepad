// NotepadApp.cpp
/*
���ϸ�Ī : NotepadApp.cpp
��� : �޸���ö �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2020.04.14
*/
#include "NotepadApp.h"
#include "NotepadForm.h"
#include <afxdisp.h>

NotepadApp notepadApp;

BOOL NotepadApp::InitInstance() {
	// Remainder of function definition omitted.
	CWinApp::InitInstance();
	
	NotepadForm *notepadForm;
	notepadForm = new NotepadForm;

	this->m_pMainWnd = notepadForm;

	SetRegistryKey("NotepadForm");
	LoadStdProfileSettings(8);

	notepadForm->Create(NULL, "���� ���� - �޸���");
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CoInitialize(NULL);
	AfxEnableControlContainer();
	notepadForm->MoveWindow(400, 100, 900, 500);
	notepadForm->ShowWindow(SW_SHOW);
	notepadForm->UpdateWindow();

	return TRUE;
}