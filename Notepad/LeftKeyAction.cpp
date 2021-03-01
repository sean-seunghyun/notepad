// LeftKeyAction.cpp
/*
���ϸ�Ī : LeftKeyAction.cpp
��� : ���� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "LeftKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

LeftKeyAction::LeftKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

LeftKeyAction::~LeftKeyAction() {
}

void LeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();

	if (lineCurrent > 0 || noteCurrent == 0) {
		this->notepadForm->current->Previous();
	}
	else if (this->notepadForm->current->GetOnIsLine() == true) {
		noteCurrent = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Last();
	}
	else {
		noteCurrent = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Last();
		this->notepadForm->current->Previous();
	}
}