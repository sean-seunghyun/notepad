// FirstScrollAction.cpp
/*
���ϸ�Ī : FirstScrollAction.cpp
��� : ó������ �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "FirstScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

FirstScrollAction::FirstScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

FirstScrollAction::~FirstScrollAction() {
}

void FirstScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->First();
}

void FirstScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->First();
}