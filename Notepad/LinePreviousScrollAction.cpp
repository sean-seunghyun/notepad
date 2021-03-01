// LinePreviousScrollAction.cpp
/*
���ϸ�Ī : LinePreviousScrollAction.cpp
��� : �� �������� �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "LinePreviousScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

LinePreviousScrollAction::LinePreviousScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

LinePreviousScrollAction::~LinePreviousScrollAction() {
}

void LinePreviousScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->PreviousUnit();
}

void LinePreviousScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->PreviousUnit();
}