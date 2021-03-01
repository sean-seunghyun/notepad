// CtrlHomeKeyAction.cpp
/*
���ϸ�Ī : CtrlHomeKeyAction.cpp
��� : ��Ʈ�� Ȩ Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "CtrlHomeKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

CtrlHomeKeyAction::CtrlHomeKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CtrlHomeKeyAction::~CtrlHomeKeyAction() {
}

void CtrlHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->note->First();
	this->notepadForm->current = this->notepadForm->note->GetAt(0);
;	this->notepadForm->current->First();
}