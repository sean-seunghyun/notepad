// Caret.cpp
/*
���ϸ�Ī : Caret.cpp
��� : ĳ�� Ŭ������ �����.
�ۼ���: ������
�ۼ����� : 2020.04.29
*/
#include "Caret.h"
#include "NotepadForm.h"
#include "CaretController.h"

Caret::Caret(CaretController *caretController) {
	this->caretController = caretController;
}

Caret::Caret(const Caret& source) {
	this->caretController = source.caretController;
}

Caret::~Caret() {
	// 1. ĳ���� �����.
	this->caretController->notepadForm->HideCaret();

	// 2. ĳ���� ���ش�.
	DestroyCaret();
}

void Caret::Create(Long width, Long height) {
	this->caretController->notepadForm->CreateSolidCaret(width, height);
}

void Caret::Move(Long x, Long y) {
	this->caretController->notepadForm->SetCaretPos(CPoint(x, y));
	this->caretController->notepadForm->ShowCaret();
}

void Caret::Hide() {
	this->caretController->notepadForm->HideCaret();
}

Caret& Caret::operator =(const Caret& source) {
	this->caretController = source.caretController;

	return *this;
}