// SelectedRightKeyAction.cpp
/*
���ϸ�Ī : SelectedRightKeyAction.cpp
��� : ���õǾ� ���� �� ���� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.02.05
*/
#include "SelectedRightKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

SelectedRightKeyAction::SelectedRightKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SelectedRightKeyAction::~SelectedRightKeyAction() {
}

void SelectedRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent;

	this->notepadForm->note->MoveToLastSelectedCurrent();
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
}