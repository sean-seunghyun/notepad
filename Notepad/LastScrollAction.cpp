// LastScrollAction.cpp
/*
���ϸ�Ī : LastScrollAction.cpp
��� : ���������� �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "LastScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

LastScrollAction::LastScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

LastScrollAction::~LastScrollAction() {
}

void LastScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->Last();
}

void LastScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->Last();
}