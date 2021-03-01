// EditCommand.cpp
/*
���ϸ�Ī : EditCommand.cpp
��� : ���� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.18
*/
#include "EditCommand.h"
#include "State.h"

EditCommand::EditCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->previousState = 0;
	this->id = ETCCOMMAND;
	this->onIsCommandSaving = false;
}

EditCommand::~EditCommand() {
	if (this->previousState != 0) {
		delete this->previousState;
	}
}