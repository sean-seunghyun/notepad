// SelectAllCommand.cpp
/*
���ϸ�Ī : SelectAllCommand.cpp
��� : ��ü ���� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "SelectAllCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"

SelectAllCommand::SelectAllCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SelectAllCommand::~SelectAllCommand() {
}

void SelectAllCommand::Execute() {
	Long noteCurrent;
	this->notepadForm->note->SelectAll(true);
	noteCurrent = this->notepadForm->note->Last();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	this->notepadForm->current->Last();
}