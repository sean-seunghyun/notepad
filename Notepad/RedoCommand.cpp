// RedoCommand.cpp
/*
���ϸ�Ī : RedoCommand.cpp
��� : �ǵ����� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "RedoCommand.h"
#include "NotepadForm.h"
#include "CommandHistory.h"

RedoCommand::RedoCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

RedoCommand::~RedoCommand() {
}

void RedoCommand::Execute() {
	this->notepadForm->commandHistory->Redo();
}