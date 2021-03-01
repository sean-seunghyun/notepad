// UndoCommand.cpp
/*
���ϸ�Ī : UndoCommand.cpp
��� : �ǵ����� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "UndoCommand.h"
#include "NotepadForm.h"
#include "CommandHistory.h"

UndoCommand::UndoCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

UndoCommand::~UndoCommand() {
}

void UndoCommand::Execute() {
	this->notepadForm->commandHistory->Undo();
}