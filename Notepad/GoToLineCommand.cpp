// GoToLineCommand.cpp
/*
���ϸ�Ī : GoToLineCommand.cpp
��� : �� �̵� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "GoToLineCommand.h"
#include "GoToLineDialog.h"
#include "NotepadForm.h"

GoToLineCommand::GoToLineCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

GoToLineCommand::~GoToLineCommand() {
}

void GoToLineCommand::Execute() {
	GoToLineDialog dlg(notepadForm);
	dlg.DoModal();
}