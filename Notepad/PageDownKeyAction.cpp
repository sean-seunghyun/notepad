// PageDownKeyAction.cpp
/*
���ϸ�Ī : PageDownKeyAction.cpp
��� : �������ٿ� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.27
*/
#include "PageDownKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "ScrollController.h"
#include "Scroll.h"

PageDownKeyAction::PageDownKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PageDownKeyAction::~PageDownKeyAction() {
}

void PageDownKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long x = this->notepadForm->matrix->GetX(lineCurrent);
	Long y = this->notepadForm->matrix->GetY(noteCurrent);

	Long scrollCurrent = this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent();
	Long height = this->notepadForm->matrix->GetHeight();
	Long count = 0;
	Long max = y - scrollCurrent + 2;
	Long i = 0;
	while (i < max) {
		count++;
		i += height;
	}

	this->notepadForm->SendMessage(WM_VSCROLL, SB_PAGEDOWN);
	scrollCurrent = this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent();
	noteCurrent = this->notepadForm->matrix->GetNoteCurrent(height * count + scrollCurrent);
	this->notepadForm->note->Move(noteCurrent);
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->matrix->GetLineCurrent(x);
	this->notepadForm->current->Move(lineCurrent);
}