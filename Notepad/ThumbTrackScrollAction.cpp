// ThumbTrackScrollAction.cpp
/*
���ϸ�Ī : ThumbTrackScrollAction.cpp
��� : ��ġ�� �̵� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.13
*/
#include "ThumbTrackScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

ThumbTrackScrollAction::ThumbTrackScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

ThumbTrackScrollAction::~ThumbTrackScrollAction() {
}

void ThumbTrackScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->Move(nPos);
}

void ThumbTrackScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->Move(nPos);
}