// HomeKeyAction.cpp
/*
���ϸ�Ī : HomeKeyAction.cpp
��� : ȨŰ�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "HomeKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

HomeKeyAction::HomeKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

HomeKeyAction::~HomeKeyAction() {
}

void HomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent;
	Long lineCurrent = this->notepadForm->current->GetCurrent();

	if (this->notepadForm->onIsLineWrapping == TRUE && lineCurrent <= 0 && this->notepadForm->current->GetOnIsLine() != true) {
		noteCurrent = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	this->notepadForm->current->First();
}