// PasteCommand.cpp
/*
���ϸ�Ī : PasteCommand.cpp
��� : �߶󳽴� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.25
*/
#include "PasteCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Clipboard.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "resource.h"

PasteCommand::PasteCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PasteCommand::~PasteCommand() {
}

void PasteCommand::Execute() {
	GlyphFactory glyphFactory;

	string text;

	bool onIsSelected;

	CString pasteString;
	CString title;

	LONG noteCurrent;
	LONG lineCurrent;
	LONG i = 0;

	// 1. ���õ� ������ �ִ��� Ȯ���Ѵ�.
	onIsSelected = this->notepadForm->note->GetOnIsSelected();

	// 2. �ڵ��������̸� ���õ� ������ �ִ��� Ȯ���Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && onIsSelected == true) {
		// 2.1. ���õ� ������ ������ ���õ� �ٵ��� ��ģ��.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 2.2. ���õ� ������ ������ �� ���� ��ģ��.
		this->notepadForm->note->Combine(noteCurrent);
	}
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 3. ���õ� ������ ������
	if (onIsSelected == true) {
		// 3.1. ���õ� ������ �д´�.
		text = this->notepadForm->note->GetSelectString();

		// 3.2. ���õ� ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		this->previousState = new State(lineCurrent, noteCurrent, text);
	}

	// 2. Ŭ�����忡�� ������ �о�´�.
	pasteString = this->notepadForm->clipboard->Read();

	// 3. ���¸� �����.
	if (pasteString != "") {
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
		
		this->state = new State(lineCurrent, noteCurrent, (LPCTSTR)pasteString);

		this->onIsCommandSaving = true;
	}

	// 4. �޸������� ������ �߰��Ѵ�.
	this->notepadForm->note->Paste((LPCTSTR)pasteString);
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 5. �ڵ����� ����̸� ��ü �ڵ������Ѵ�.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	// 6. ���� �߰��Ѵ�.
	this->notepadForm->GetWindowText(title);
	if (title.GetAt(0) != '*') {
		title = "*" + title;
	}
	this->notepadForm->SetWindowTextA(title);
}

void PasteCommand::UnExecute() {
	Glyph *previousNote;
	Glyph *currentNote;

	string text;

	Long textCount;
	Long lineCurrent;
	Long noteCurrent;
	Long i = 0;

	// 1. ���� ���� ������ ������
	if (this->state != 0) {
		// 1.1. ���� ���� ������ �о�´�.
		currentNote = this->state->GetNote();
		text = currentNote->GetString();
		lineCurrent = this->state->GetLineCurrent();
		noteCurrent = this->state->GetNoteCurrent();

		// 1.2. ��ġ�� �̵��ϰ�, �����Ѵ�.
		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();

		textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// + �ڵ��������̸� ���ÿ��θ� Ȯ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->CombineSelectedLines();
		}
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 1.3. ���õ� ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	// 2. ���� ������ ������ ������
	if (this->previousState != 0) {
		// 2.1. ���� ���� ������ �о�´�.
		previousNote = this->previousState->GetNote();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// �ڵ��������̸� �� ���� ��ģ��.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 2.2. ���� ������ ������ �߰��Ѵ�.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 2.3. �޸������� ���� ���� ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void PasteCommand::ReExecute() {
	Glyph *previousNote;
	Glyph *currentNote;

	string text;

	Long textCount;
	Long lineCurrent;
	Long noteCurrent;
	Long i = 0;
	// 1. ���� ���� ������ ������
	if (this->previousState != 0) {
		// 1.1.  ���� ���� ������ �о�´�.
		previousNote = this->previousState->GetNote();
		text = previousNote->GetString();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();

		// 1.2. ��Ī�Ǵ� ���ڸ� �����Ѵ�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// + �ڵ��������̸� ���ÿ��θ� Ȯ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->CombineSelectedLines();
		}
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 1.3. ���õ� ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	// 2. ���� ���� ������ ������
	if (this->state != 0) {
		// 2.1. ���� ���� ������ �о�´�.
		currentNote = this->state->GetNote();
		lineCurrent = this->state->GetLineCurrent();
		noteCurrent = this->state->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 2.2. �ڵ��������̸� �� ���� ��ģ��.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 2.3. ������ ������ �߰��Ѵ�.
		currentNote->SelectAll(true);
		this->notepadForm->note->Paste(currentNote);

		// 2.4. �޸������� ���� ���� ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}