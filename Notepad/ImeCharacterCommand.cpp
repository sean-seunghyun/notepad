// ImeCharacterCommand.cpp
/*
���ϸ�Ī : ImeCharacterCommand.cpp
��� : 1����Ʈ ���� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "ImeCharacterCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "resource.h"

ImeCharacterCommand::ImeCharacterCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->onIsCommandSaving = false;
}

ImeCharacterCommand::~ImeCharacterCommand() {
}

void ImeCharacterCommand::Execute() {
	// 1. ���ڸ� �����.
	GlyphFactory glyphFactory;
	Glyph *glyph;
	TCHAR letter[3];

	string text;

	Long lineCurrent;
	Long noteCurrent;

	// 2. ���õ� ������ �ִ��� Ȯ���Ѵ�.
	this->onIsSelected = this->notepadForm->note->GetOnIsSelected();

	// 3. �ڵ��������̸� ���ÿ��θ� Ȯ���Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
		// 3.1. ���õǾ� ������ ���õ� �ٵ��� ��ģ��.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 3.2. ���õǾ� ���� ������ ���� ���� ��ģ��.
		this->notepadForm->note->Combine(noteCurrent);
	}
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 4. ���õ� ������ ������
	if (this->onIsSelected == true) {
		this->onIsCommandSaving = true;
		// 4.1. ���õ� ������ �д´�.
		text = this->notepadForm->note->GetSelectString();

		// 4.2. ���õ� ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		this->previousState = new State(lineCurrent, noteCurrent, text);
		this->onIsMore = false;
	}

	letter[0] = this->notepadForm->GetLetter()[0];
	letter[1] = this->notepadForm->GetLetter()[1];
	letter[2] = '\0';
	if (letter[0] != '\0') {
		this->onIsCommandSaving = true;

		glyph = glyphFactory.Create(letter);

		// 5. �޸����� �ٿ��� ���ش�.
		this->notepadForm->current->Remove(this->notepadForm->current->GetCurrent() - 1);

		// 6. �޸����� �ٿ��� �߰��Ѵ�.
		if (this->notepadForm->current->GetCurrent() == this->notepadForm->current->GetLength()) {
			this->notepadForm->current->Add(glyph);
		}
		else {
			this->notepadForm->current->Add(this->notepadForm->current->GetCurrent(), glyph);
		}

		// 7. ���¸� �����.
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		this->state = new State(lineCurrent - 1, noteCurrent, letter);
	}
	// 8. �ڵ��������̸� �ڵ������Ѵ�.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	this->notepadForm->onIsComposing = FALSE;
}

void ImeCharacterCommand::UnExecute() {
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
		if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
			this->notepadForm->note->CombineSelectedLines();
		}
		else if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
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

void ImeCharacterCommand::ReExecute() {
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
		if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
			this->notepadForm->note->CombineSelectedLines();
		}
		else if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
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

Long ImeCharacterCommand::GetLineCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetLineCurrent();
	}

	return ret;
}

Long ImeCharacterCommand::GetNoteCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetNoteCurrent();
	}

	return ret;
}