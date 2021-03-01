// FindNextCommand.cpp
/*
���ϸ�Ī : FindNextCommand.cpp
��� : ���� ã�� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.20
*/
#include "FindNextCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include <afxdlgs.h>

FindNextCommand::FindNextCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

FindNextCommand::~FindNextCommand() {
}

void FindNextCommand::Execute() {
	CString findString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	LONG onIsMatchCase = AfxGetApp()->GetProfileInt("NotepadSection", "MatchCase", -1);
	LONG onIsWrapAround = AfxGetApp()->GetProfileInt("NotepadSection", "WrapAround", -1);

	LONG findStringLen;
	LONG startLineCurrent;
	LONG startNoteCurrent;
	LONG endLineCurrent;
	LONG endNoteCurrent;
	LONG prevLineCurrent = 0;
	LONG prevNoteCurrent = 0;
	LONG lineCurrent = this->notepadForm->current->GetCurrent();
	LONG noteCurrent = this->notepadForm->note->GetCurrent();

	// 1. ���� ������ ���Ѵ�.
	this->notepadForm->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);

	// 2. ���õ� ������ ���� ��ġ�� ���� ��ġ�� ������
	if (startLineCurrent == lineCurrent && startNoteCurrent == noteCurrent) {
		// 2.1. ���� ��ġ�� �����Ѵ�.
		prevLineCurrent = lineCurrent;
		prevNoteCurrent = noteCurrent;
		// 2.2. ������ ���� ��ġ�� �̵��Ѵ�.
		this->notepadForm->note->Move(endNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(endNoteCurrent);
		this->notepadForm->current->Move(endLineCurrent);
	}

	// 3. ã�� ������ ���� ������ ���Ѵ�.
	findStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)findString);

	// 4. �޸������� �������� ã�´�.
	this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!onIsMatchCase);

	// 5. ã�� ���ϰ� ������ ��ġ ���ΰ� ���̸�
	if (this->notepadForm->onIsFound != TRUE && findString != "" && onIsWrapAround == 0) {
		// 5.1. ó�� ��ġ�� ù ��° ĭ���� �̵��Ѵ�.
		noteCurrent = this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->First();
		// 5.2. �޸������� �������� ã�´�.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!onIsMatchCase);
	}
	// 6. ã�� ���ϸ� ���� ��ġ�� ���ư���.
	if (this->notepadForm->onIsFound != TRUE && onIsWrapAround == 0) {
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		this->notepadForm->current->Move(prevLineCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
}