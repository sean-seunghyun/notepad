// FindCommand.cpp
/*
���ϸ�Ī : FindCommand.cpp
��� : ã�� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.20
*/
#include "FindCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "FindReplaceDialog.h"
//#include <Findtext.dlg>

FindCommand::FindCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

FindCommand::~FindCommand() {
}

void FindCommand::Execute() {
	CString findString;

	this->notepadForm->onIsOpeningFindReplace = TRUE;
	if (this->notepadForm->pFindReplaceDialog != 0) {
		this->notepadForm->pFindReplaceDialog->DestroyWindow();
	}

	findString = this->notepadForm->note->GetSelectString().c_str();
	if (findString.Compare("") == 0) {
		findString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	}

	this->notepadForm->pFindReplaceDialog = new FindReplaceDialog;
	this->notepadForm->pFindReplaceDialog->Create(TRUE, findString, NULL, 0, this->notepadForm);
	this->notepadForm->pFindReplaceDialog->ShowWindow(SW_SHOW);
}