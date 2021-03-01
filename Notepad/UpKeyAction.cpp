// UpKeyAction.cpp
/*
���ϸ�Ī : UpKeyAction.cpp
��� : ���� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "UpKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"

UpKeyAction::UpKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

UpKeyAction::~UpKeyAction() {
}

void UpKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long x;
	x = this->notepadForm->matrix->GetX(this->notepadForm->current->GetCurrent());
	
	Long noteCurrent;
	noteCurrent = this->notepadForm->note->Previous();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	Long lineCurrent;
	lineCurrent = this->notepadForm->matrix->GetLineCurrent(x);
	this->notepadForm->current->Move(lineCurrent);
}