// CtrlRightKeyAction.cpp
/*
���ϸ�Ī : CtrlRightKeyAction.cpp
��� : ��Ʈ�� ������ Ű�� ������ �� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "CtrlRightKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "resource.h"

CtrlRightKeyAction::CtrlRightKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CtrlRightKeyAction::~CtrlRightKeyAction() {
}

void CtrlRightKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long noteLength;
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long lineLength = this->notepadForm->current->GetLength();


	string text = "\0";
	bool onIsNext = true;
	bool onIsSpaceOrTab = false;
	if (lineCurrent >= lineLength) {
		onIsNext = false;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE && onIsNext == true) {
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	noteLength = this->notepadForm->note->GetLength();
	lineCurrent = this->notepadForm->current->GetCurrent();
	lineLength = this->notepadForm->current->GetLength();

	if (lineCurrent == lineLength && noteCurrent < noteLength - 1) {
		noteCurrent = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->First();
		lineLength = this->notepadForm->current->GetLength();
		if (lineCurrent < lineLength) {
			text = this->notepadForm->current->GetAt(lineCurrent)->GetString();
		}
	}

	if (text == " " || text == "\t") {
		onIsSpaceOrTab = true;
	}

	if (onIsSpaceOrTab == true || onIsNext == true) {
		this->notepadForm->current->NextWord();
	}

	if (this->notepadForm->onIsLineWrapping == TRUE && onIsNext == true) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAPLINE);
	}
}