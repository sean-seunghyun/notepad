// LineNextScrollAction.cpp
/*
���ϸ�Ī : LineNextScrollAction.cpp
��� : �� �������� �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "LineNextScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

LineNextScrollAction::LineNextScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

LineNextScrollAction::~LineNextScrollAction() {
}

void LineNextScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->NextUnit();
}

void LineNextScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->NextUnit();
}