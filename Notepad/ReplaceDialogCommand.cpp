// ReplaceDialogCommand.cpp
/*
���ϸ�Ī : ReplaceDialogCommand.cpp
��� : �ٲٱ� ��ȭ���� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.22
*/
#include "ReplaceDialogCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "FindReplaceDialog.h"
//#include <Findtext.dlg>

ReplaceDialogCommand::ReplaceDialogCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

ReplaceDialogCommand::~ReplaceDialogCommand() {
}

void ReplaceDialogCommand::Execute() {
	CString csFindString;
	CString csReplaceString;

	this->notepadForm->onIsOpeningFindReplace = TRUE;

	if (this->notepadForm->pFindReplaceDialog != 0) {
		this->notepadForm->pFindReplaceDialog->DestroyWindow();
	}

	csFindString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	csReplaceString = AfxGetApp()->GetProfileString("NotepadSection", "ReplaceString", "");

	this->notepadForm->pFindReplaceDialog = new FindReplaceDialog;
	this->notepadForm->pFindReplaceDialog->Create(FALSE, csFindString, csReplaceString, 0, this->notepadForm);
	this->notepadForm->pFindReplaceDialog->ShowWindow(SW_SHOW);
}