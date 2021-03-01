// PagePreviousScrollAction.cpp
/*
���ϸ�Ī : PagePreviousScrollAction.cpp
��� : ���� �������� �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "PagePreviousScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

PagePreviousScrollAction::PagePreviousScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

PagePreviousScrollAction::~PagePreviousScrollAction() {
}

void PagePreviousScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->PreviousPage();
}

void PagePreviousScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->PreviousPage();
}