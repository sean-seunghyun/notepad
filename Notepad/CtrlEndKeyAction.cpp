// CtrlEndKeyAction.cpp
/*
���ϸ�Ī : CtrlEndKeyAction.cpp
��� : ��Ʈ�� ���� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "CtrlEndKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

CtrlEndKeyAction::CtrlEndKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CtrlEndKeyAction::~CtrlEndKeyAction() {
}

void CtrlEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long index = this->notepadForm->note->Last();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);
	this->notepadForm->current->Last();
}