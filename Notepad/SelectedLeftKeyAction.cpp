// SelectedLeftKeyAction.cpp
/*
���ϸ�Ī : SelectedLeftKeyAction.cpp
��� : ���õǾ� ���� �� ���� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.02.05
*/
#include "SelectedLeftKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

SelectedLeftKeyAction::SelectedLeftKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SelectedLeftKeyAction::~SelectedLeftKeyAction() {
}

void SelectedLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent;

	this->notepadForm->note->MoveToFirstSelectedCurrent();
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
}