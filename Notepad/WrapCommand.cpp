// WrapCommand.cpp
/*
���ϸ�Ī : WrapCommand.cpp
��� : �ڵ����� ��� Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.10.14
*/
#include "WrapCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"
#include "Matrix.h"

WrapCommand::WrapCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

WrapCommand::~WrapCommand() {
}

void WrapCommand::Execute() {
	GlyphFactory glyphFactory;
	Glyph *line;
	Glyph *dummyLine;

	Long splitCount;
	Long height = this->notepadForm->matrix->GetHeight();
	Long current = 0;
	Long noteIndex = 0;
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long i = 0;

	bool onIsGreaterThanScreen;
	// 1. �߸��� ���� ������ ���Ѵ�.(2020.01.22)
	onIsGreaterThanScreen = this->notepadForm->matrix->GetOnIsGreaterThanScreen();

	// 2. �߸��� ���� ������ ȭ�� ũ�⺸�� ������ ���� ��ũ�ѹٰ� �ִ� ������ �����Ѵ�.(2020.01.22)
	if (onIsGreaterThanScreen == true) {
		this->notepadForm->onIsVerticalScrollBar = TRUE;
	}
	else {
		this->notepadForm->onIsVerticalScrollBar = FALSE;
	}

	// 1. ���� �ٵ��� �ڵ����� �� ��� �̸� ���� ���� ���Ѵ�.
	while (i < noteCurrent) {
		line = this->notepadForm->note->GetAt(i);
		splitCount = this->notepadForm->matrix->GetSplitCount(line);
		if (splitCount > 0) {
			noteIndex += splitCount;
		}
		i++;
	}
	if (noteIndex > 0) {
		noteCurrent += noteIndex;
	}

	// 2. �ڵ������Ѵ�.
	i = 0;
	while (i < this->notepadForm->note->GetLength()) {
		line = this->notepadForm->note->GetAt(i);
		current = this->notepadForm->matrix->GetSplitCurrent(line);
		if (current > 0) {
			dummyLine = glyphFactory.Create((char*)"\n", false);
			line->Split(dummyLine, current);
			this->notepadForm->note->Add(i + 1, dummyLine);
		}
		i++;
	}

	// 3. ������ ���� ��ġ�� ���� ���� ��ġ�� ����Ѵ�.
	line = this->notepadForm->note->GetAt(noteCurrent);
	i = noteCurrent;
	while (i < this->notepadForm->note->GetLength() - 1 && lineCurrent > line->GetLength()) {
		noteCurrent++;
		lineCurrent -= line->GetLength();

		line = this->notepadForm->note->GetAt(i + 1);
		i++;
	}

	// 4. ���� ��ġ�� �̵��Ѵ�.
	this->notepadForm->note->Move(noteCurrent);
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	this->notepadForm->current->Move(lineCurrent);
}