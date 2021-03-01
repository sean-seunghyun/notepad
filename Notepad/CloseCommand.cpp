// CloseCommand.cpp
/*
���ϸ�Ī : CloseCommand.cpp
��� : �ݱ� �޴��� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "CloseCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"

CloseCommand::CloseCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CloseCommand::~CloseCommand() {
}

void CloseCommand::Execute() {
	this->notepadForm->PostMessage(WM_CLOSE);
}