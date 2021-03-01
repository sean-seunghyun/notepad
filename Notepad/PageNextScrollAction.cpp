// PageNextScrollAction.cpp
/*
���ϸ�Ī : PageNextScrollAction.cpp
��� : ���� �������� �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "PageNextScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

PageNextScrollAction::PageNextScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

PageNextScrollAction::~PageNextScrollAction() {
}

void PageNextScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->NextPage();
}

void PageNextScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->NextPage();
}