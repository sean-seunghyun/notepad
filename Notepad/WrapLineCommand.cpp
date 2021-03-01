// WrapLineCommand.cpp
/*
���ϸ�Ī : WrapLineCommand.cpp
��� : �� �� �ڵ����� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
*/
#include "WrapLineCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"
#include "Matrix.h"

WrapLineCommand::WrapLineCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

WrapLineCommand::~WrapLineCommand() {
}

void WrapLineCommand::Execute() {
	GlyphFactory glyphFactory;
	Glyph *line;
	Glyph *dummyLine;

	Long current = 0;
	Long noteIndex = 0;
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long i = noteCurrent;

	bool onIsFirst = true;
	bool onIsLine = false; // ���� ���� �翬�� ����(onIsLine�� true) ���̰� �ڵ������� �Ϸ� �� �� �������� �������̴� �� �������� �ݺ�

	bool onIsGreaterThanScreen;
	// 1. �߸��� ���� ������ ���Ѵ�.(2020.01.22)
	onIsGreaterThanScreen = this->notepadForm->matrix->GetOnIsGreaterThanScreen();

	// 2. �߸��� ���� ������ ȭ�� ũ�⺸�� ������ ���� ��ũ�ѹٰ� �ִ� ������ �����Ѵ�.(2020.01.22)
	if (onIsGreaterThanScreen == true) {
		this->notepadForm->onIsVerticalScrollBar = TRUE;
	}

	// 1. ���� ���� �ڵ������Ѵ�.
	while (i < this->notepadForm->note->GetLength() && onIsLine != true) {
		line = this->notepadForm->note->GetAt(i);
		if (onIsFirst != true) {
			onIsLine = line->GetOnIsLine();
		}
		current = this->notepadForm->matrix->GetSplitCurrent(line);
		if (current > 0) {
			dummyLine = glyphFactory.Create((char*)"\n", false);
			line->Split(dummyLine, current);
			this->notepadForm->note->Add(i + 1, dummyLine);
		}
		onIsFirst = false;
		i++;
	}

	// 2. ������ ���� ��ġ�� ���� ���� ��ġ�� ����Ѵ�.
	line = this->notepadForm->note->GetAt(noteCurrent);
	i = noteCurrent;
	while (i < this->notepadForm->note->GetLength() - 1 && lineCurrent > line->GetLength()) {
		noteCurrent++;
		lineCurrent -= line->GetLength();

		line = this->notepadForm->note->GetAt(i + 1);
		i++;
	}

	// 3. ���� ��ġ�� �̵��Ѵ�.
	this->notepadForm->note->Move(noteCurrent);
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	this->notepadForm->current->Move(lineCurrent);
}