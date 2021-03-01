// WriteCommand.cpp
/*
���ϸ�Ī : WriteCommand.cpp
��� : ���� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "WriteCommand.h"
#include "State.h"

WriteCommand::WriteCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->state = 0;
	this->id = EditCommand::WRITECOMMAND;
	this->onIsNew = true;
	this->onIsMore = true;
	this->onIsCommandSaving = true;
	this->onIsSelected = false;
}

WriteCommand::~WriteCommand() {
	if (this->state != 0) {
		delete this->state;
	}
}

void WriteCommand::SetOnIsNew(bool onIsNew) {
	this->onIsNew = onIsNew;
}