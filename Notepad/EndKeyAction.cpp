// EndKeyAction.cpp
/*
���ϸ�Ī : EndKeyAction.cpp
��� : ���� Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "EndKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

EndKeyAction::EndKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

EndKeyAction::~EndKeyAction() {
}

void EndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long noteLength = this->notepadForm->note->GetLength();
	Long lineLength = this->notepadForm->current->GetLength();

	Glyph *nextLine = this->notepadForm->note->GetAt(noteCurrent + 1);

	if (this->notepadForm->onIsLineWrapping == TRUE && noteCurrent + 1 < noteLength && lineCurrent >= lineLength &&
		nextLine->GetOnIsLine() != true) {
		noteCurrent = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	this->notepadForm->current->Last();
}