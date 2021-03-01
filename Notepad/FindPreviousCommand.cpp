// FindPreviousCommand.cpp
/*
���ϸ�Ī : FindPreviousCommand.cpp
��� : ���� ã�� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.18
*/
#include "FindPreviousCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include <afxdlgs.h>

FindPreviousCommand::FindPreviousCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

FindPreviousCommand::~FindPreviousCommand() {
}

void FindPreviousCommand::Execute() {
	CString findString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	LONG onIsMatchCase = AfxGetApp()->GetProfileInt("NotepadSection", "MatchCase", -1);
	LONG onIsWrapAround = AfxGetApp()->GetProfileInt("NotepadSection", "WrapAround", -1);

	Long findStringLen;
	Long startLineCurrent;
	Long startNoteCurrent;
	Long endLineCurrent;
	Long endNoteCurrent;
	Long prevLineCurrent = 0;
	Long prevNoteCurrent = 0;
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	
	// 1. ���� ������ ���Ѵ�.
	this->notepadForm->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);

	// 2. ���õ� ������ ������ ��ġ�� ���� ��ġ�� ������
	if (endLineCurrent == lineCurrent && endNoteCurrent == noteCurrent) {
		// 2.1. ���� ��ġ�� �����Ѵ�.
		prevLineCurrent = lineCurrent;
		prevNoteCurrent = noteCurrent;
		// 2.2. ������ ���� ��ġ�� �̵��Ѵ�.
		this->notepadForm->note->Move(startNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(startNoteCurrent);
		this->notepadForm->current->Move(startLineCurrent);
	}

	// 3. ã�� ������ ���� ������ ���Ѵ�.
	findStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)findString);

	// 4. �޸������� ã�´�.
	this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindPrevious((LPCTSTR)findString, findStringLen, (bool)!onIsMatchCase);

	// 5. ã�� ���ϰ� ������ ��ġ ���ΰ� ���̸�
	if (this->notepadForm->onIsFound != TRUE && findString != "" && onIsWrapAround == 0) {
		// 5.1. ������ ���� ������ ĭ���� �̵��Ѵ�.
		noteCurrent = this->notepadForm->note->Last();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Last();
		// 5.2. �ٽ� �ѹ� ã�´�.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindPrevious((LPCTSTR)findString, findStringLen, (bool)!onIsMatchCase);
	}

	// 6. ã�� ���ϸ� ���� ��ġ�� ���ư���.
	if (this->notepadForm->onIsFound != TRUE) {
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		this->notepadForm->current->Move(prevLineCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
}