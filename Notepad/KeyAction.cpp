// KeyAction.cpp
/*
���ϸ�Ī : KeyAction.cpp
��� : Ű �Է� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "KeyAction.h"
#include "NotepadForm.h"

KeyAction::KeyAction() {
	this->notepadForm = 0;
}

KeyAction::KeyAction(const KeyAction& source) {
	this->notepadForm = source.notepadForm;
}

KeyAction::~KeyAction() {
}

KeyAction& KeyAction::operator =(const KeyAction& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}