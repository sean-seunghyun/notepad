// RightKeyAction.cpp
/*
���ϸ�Ī : RightKeyAction.cpp
��� : ������ Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "RightKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

RightKeyAction::RightKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

RightKeyAction::~RightKeyAction() {
}

void RightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	bool onIsLine = true;

	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long noteLength = this->notepadForm->note->GetLength();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long lineLength = this->notepadForm->current->GetLength();

	Glyph *nextLine = 0;

	if (lineCurrent < lineLength || noteCurrent >= noteLength - 1) {
		lineCurrent = this->notepadForm->current->Next();

		if (noteCurrent < noteLength - 1) {
			nextLine = this->notepadForm->note->GetAt(noteCurrent + 1);
			onIsLine = nextLine->GetOnIsLine();
		}
		
		if (this->notepadForm->onIsLineWrapping == TRUE && lineCurrent >= lineLength && onIsLine != true) {
			noteCurrent = this->notepadForm->note->Next();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			this->notepadForm->current->First();
		}
	}
	else {
		noteCurrent = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->First();
		onIsLine = this->notepadForm->current->GetOnIsLine();
		if (this->notepadForm->onIsLineWrapping == TRUE && noteCurrent < noteLength && onIsLine != true) {
			this->notepadForm->current->Next();
		}
	}
}