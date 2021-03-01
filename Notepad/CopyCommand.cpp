// CopyCommand.cpp
/*
���ϸ�Ī : CopyCommand.cpp
��� : �����Ѵ� ��� Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.07.03
*/
#include "CopyCommand.h"
#include "NotepadForm.h"
#include "Clipboard.h"
#include "Glyph.h"

CopyCommand::CopyCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CopyCommand::~CopyCommand() {
}

void CopyCommand::Execute() {
	CString copyString;

	copyString = this->notepadForm->note->GetSelectString().c_str();
	this->notepadForm->clipboard->Write(copyString);
}