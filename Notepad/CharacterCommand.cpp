// CharacterCommand.cpp
/*
���ϸ�Ī : CharacterCommand.cpp
��� : 1����Ʈ ���� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "CharacterCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "resource.h"

CharacterCommand::CharacterCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->onIsEnter = false;
}

CharacterCommand::~CharacterCommand() {
}

void CharacterCommand::Execute() {
	GlyphFactory glyphFactory;
	Glyph *line;
	Glyph *glyph;

	CString title;
	string text;

	Long lineCurrent;
	Long noteCurrent;
	Long lineLength;
	//Long prevLineCurrent;// ���� ���� current�� �������� �����Ƿ� ���� �ʿ� ����
	Long prevNoteCurrent;

	// 1. ���ڸ� �д´�.
	TCHAR *letter = this->notepadForm->GetLetter();

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

	// 5 ���� �����̸�
	if (letter[0] == '\n' || letter[0] == '\r') {
		this->onIsEnter = true;
		// 5.1. ���� �����.
		line = glyphFactory.Create((char*)&letter[0]);
		// 5.2. ���� ���� length�� current�� �ٸ��� ���� �����ش�.
		lineCurrent = this->notepadForm->current->GetCurrent();
		lineLength = this->notepadForm->current->GetLength();
		if (lineCurrent != lineLength) {
			this->notepadForm->current->Split(line, lineCurrent);
		}
		// 5.3. ��Ʈ���� �� ���� �����ִ´�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		noteCurrent = this->notepadForm->note->Add(noteCurrent + 1, line);

		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	// 6. ���� ���ڰ� �ƴϸ�
	else if ((letter[0] >= 32 && letter[0] < 127) || letter[0] == 9) {
		// 6.1. ���ڸ� �����.
		glyph = glyphFactory.Create((char*)&letter[0]);
		// 6.2. �������� current�� current�� length�� ������ ���� �ٿ��� �߰��Ѵ�.
		if (this->notepadForm->current->GetCurrent() == this->notepadForm->current->GetLength()) {
			this->notepadForm->current->Add(glyph);
		}
		else {
			//6.3.�ٸ��� ���ڸ� current��°�� �����ش�.
			this->notepadForm->current->Add(this->notepadForm->current->GetCurrent(), glyph);
		}
	}

	// 7. ���� ���¸� �����.
	this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
	if (this->onIsEnter == true) {
		// 8. ���๮���̸�
		// 8.1. ���� ��ġ�� �����Ѵ�.
		// prevLineCurrent = this->notepadForm->current->GetCurrent();// ���� ���� current�� ���� ���� �����Ƿ� ���� �ʿ� ����
		prevNoteCurrent = this->notepadForm->note->GetCurrent();

		// 8.2. ��Ʈ���� �������� �̵��Ѵ�.
		noteCurrent = prevNoteCurrent - 1;
		this->notepadForm->note->Move(noteCurrent);

		// 8.3. �ٿ��� ������ ��ġ�� �̵��Ѵ�.
		line = this->notepadForm->note->GetAt(noteCurrent);
		line->Last();

		// 8.4. ������ ��ġ�� �̸� ���Ѵ�.
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		// 8.5. �ٽ� ���� ��ġ�� ���ƿ´�.
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		// this->notepadForm->current->Move(prevLineCurrent); // ���� ���� current�� ���� ���� ����.
	}
	else {
		lineCurrent--;
	}

	if ((letter[0] == '\n' || letter[0] == '\r') || ((letter[0] >= 32 && letter[0] < 127) || letter[0] == 9)) {
		this->state = new State(lineCurrent, noteCurrent, letter);
	}

	// 8. �ڵ��������̸� �ڵ����� ���ش�.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	this->notepadForm->onIsComposing = FALSE;

	this->notepadForm->GetWindowText(title);
	if (this->state != 0 && title.GetAt(0) != '*') {
		title = "*" + title;
	}
	this->notepadForm->SetWindowTextA(title);
}

void CharacterCommand::UnExecute() {
	// 1. ���� ���� ������ �о�´�.
	Glyph *previousNote;
	Glyph *currentNote = this->state->GetNote();

	string text = currentNote->GetString();

	Long textCount;
	Long lineCurrent = this->state->GetLineCurrent();
	Long noteCurrent = this->state->GetNoteCurrent();
	Long i = 0;

	// 2. ��ġ�� �̵��ϰ�, �����Ѵ�.
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

	// 3. ���õ� ������ �����.
	this->notepadForm->note->RemoveSelect();
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 4. ���� ������ ������ ������
	if (this->previousState != 0) {
		// 4.1. ���� ���� ������ �о�´�.
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

		// 4.2. ���� ������ ������ �߰��Ѵ�.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 4.3. �޸������� ���� ���� ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void CharacterCommand::ReExecute() {
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

	// 2. ���� ���� ������ �о�´�.
	currentNote = this->state->GetNote();
	lineCurrent = this->state->GetLineCurrent();
	noteCurrent = this->state->GetNoteCurrent();

	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 5.4. �ڵ��������̸� �� ���� ��ģ��.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	// 3. ������ ������ �߰��Ѵ�.
	currentNote->SelectAll(true);
	this->notepadForm->note->Paste(currentNote);

	// 4. �޸������� ���� ���� ���Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

Long CharacterCommand::GetLineCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetLineCurrent();
	}

	return ret;
}

Long CharacterCommand::GetNoteCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetNoteCurrent();
	}

	return ret;
}