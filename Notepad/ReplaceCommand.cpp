// ReplaceCommand.cpp
/*
���ϸ�Ī : ReplaceCommand.cpp
��� : �ٲٱ� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.22
*/
#include "ReplaceCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "FindReplaceDialog.h"
//#include <FindreplaceString.dlg>

ReplaceCommand::ReplaceCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->state = 0;
}

ReplaceCommand::~ReplaceCommand() {
}

void ReplaceCommand::Execute() {
	CString findString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	CString replaceString = AfxGetApp()->GetProfileString("NotepadSection", "ReplaceString", "");
	CString findMessage;
	CString previousreplaceString;
	CString title;

	LONG findStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)findString);
	LONG replaceStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)replaceString);
	LONG prevLineCurrent = 0;
	LONG prevNoteCurrent = 0;
	LONG stateLineCurrent = 0;
	LONG stateNoteCurrent = 0;
	LONG startLineCurrent = 0;
	LONG startNoteCurrent = 0;
	LONG lineCurrent = 0;
	LONG noteCurrent = 0;

	Glyph *line = 0;

	this->onIsMatchCase = AfxGetApp()->GetProfileInt("NotepadSection", "MatchCase", -1);
	this->onIsWrapAround = AfxGetApp()->GetProfileInt("NotepadSection", "WrapAround", -1);

	bool onIsReplaced = false;
	bool onIsFindingNext = true; // ���� ã���� ����.

	// 1. ���� ���õ� ���� �ٲٴ���, ��� �ٲٴ��� ���θ� Ȯ���Ѵ�.
	if (this->notepadForm->pFindReplaceDialog != NULL) {
		this->onIsReplacedCurrent = true;
		if (this->notepadForm->pFindReplaceDialog->ReplaceAll() != 0) {
			this->onIsReplacedCurrent = false;
		}
		this->onIsMatchCase = ((FindReplaceDialog*)this->notepadForm->pFindReplaceDialog)->MatchCase();
		this->onIsWrapAround = !((FindReplaceDialog*)this->notepadForm->pFindReplaceDialog)->WrapAround();
	}

	// 2. ���õ� ������ �д´�.
	previousreplaceString = this->notepadForm->note->GetSelectString().c_str();

	// 3. ã�� ����� ���õ� ������ ����, ���� ���õ� ���� �ٲ���ϸ�
	if (findString == previousreplaceString && findString != "" && this->onIsReplacedCurrent == true) {
		onIsReplaced = true; // �ٲ� ���θ� ������ �Ѵ�.

		// 3.1. ���õ� ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 3.2. �ڵ��������̸� �޸������� ���� ���� �ڵ����� Ǭ��.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 3.3. ã�� ������ �߰��Ѵ�.
		// + ������ ��ġ�� ���Ѵ� (2021.01.28)
		startNoteCurrent = noteCurrent;
		startLineCurrent = this->notepadForm->current->GetCurrent();
		this->notepadForm->note->Paste((LPCTSTR)replaceString);
		this->notepadForm->note->SelectCount(startLineCurrent, startNoteCurrent, replaceStringLen);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 3.4. �ڵ��������̸� �� �� �ڵ����� �Ѵ�.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAPLINE);
		}
	}
	// 4. ��ü �ٲٱ��̸�
	if (this->onIsReplacedCurrent != true) {
		// 4.1. ó�� ��ġ�� �̵��Ѵ�.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();

		// 4.2. �޸������� �������� ã�´�.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 4.3. ã�� ������ ���� ���� �ݺ��Ѵ�.
		while (this->notepadForm->onIsFound == TRUE) {
			onIsReplaced = true;
			onIsFindingNext = false;

			// 4.3.1. ���õ� ������ �����.
			this->notepadForm->note->RemoveSelect();
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			lineCurrent = this->notepadForm->current->GetCurrent();

			// 4.3.2. �ڵ��������̸� �޸������� ���� ���� �ڵ����� Ǭ��.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->note->Combine(noteCurrent);
				noteCurrent = this->notepadForm->note->GetCurrent();
				this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			}

			// 4.3.3. ã�� ������ �߰��Ѵ�.
			this->notepadForm->note->Paste((LPCTSTR)replaceString);
			this->notepadForm->current->Move(lineCurrent);
			this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, replaceStringLen);

			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			// 4.3.4. �޸������� �������� ã�´�.
			this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}
		// 4.4. �ٲ� ���ΰ� ������
		if (onIsReplaced == true) {
			// 4.4.1. �ڵ����� ����̸� ��ü �ڵ����� �Ѵ�.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
			}
			// 4.4.2. ��ü ���� �����Ѵ�.
			this->notepadForm->note->SelectAll(false);
			// 4.4.3. ã�� ���θ� ������ �Ѵ�.
			this->notepadForm->onIsFound = TRUE;
		}
		// 4.5. ó�� ��ġ�� �̵��Ѵ�.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();
	}

	// 5. �������� ã���� ���ΰ� ���̸� �޸������� �������� ã�´�.
	if (findString != "" && onIsFindingNext == true) {
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	// 6. ���� ��ġ�� �����Ѵ�.
	prevLineCurrent = this->notepadForm->current->GetCurrent();
	prevNoteCurrent = this->notepadForm->note->GetCurrent();
	// 7. ã�� ���ϰ� (��ü �ٲٱⰡ �ƴϰ�) ������ ��ġ ���ΰ� ���̸� (2021.02.18)
	if (findString != "" && this->notepadForm->onIsFound != TRUE && this->onIsReplacedCurrent == true && this->onIsWrapAround == 0) {
		// 7.1. ó�� ��ġ�� ù ��° ĭ���� �̵��Ѵ�.
		noteCurrent = this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->First();
		// 7.2. �޸������� �������� ã�´�.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
	}
	// 8. ã�� ���ϸ� ���� ��ġ�� ���ư���.
	if (this->notepadForm->onIsFound != TRUE) {
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		this->notepadForm->current->Move(prevLineCurrent);
	}

	// 9. �ٲ� ���ΰ� ������ ���� ���¿� ���� ���¸� �����.
	if (onIsReplaced == true) {
		stateLineCurrent = 0;
		stateNoteCurrent = 0;
		if (this->onIsReplacedCurrent == true) {
			prevLineCurrent = this->notepadForm->current->GetCurrent();
			prevNoteCurrent = this->notepadForm->note->GetCurrent();

			this->notepadForm->note->Move(startNoteCurrent);
			line = this->notepadForm->note->GetAt(startNoteCurrent);
			line->Move(startLineCurrent);

			this->notepadForm->note->GetCombineCurrent(&stateLineCurrent, &stateNoteCurrent);

			this->notepadForm->note->Move(prevNoteCurrent);
			this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
			this->notepadForm->current->Move(prevLineCurrent);
		}

		this->previousState = new State(stateLineCurrent, stateNoteCurrent, (LPCTSTR)findString);
		this->state = new State(stateLineCurrent, stateNoteCurrent, (LPCTSTR)replaceString);
		this->onIsCommandSaving = true;

		this->notepadForm->GetWindowText(title);
		if (title.GetAt(0) != '*') {
			title = "*" + title;
		}
		this->notepadForm->SetWindowTextA(title);
	}
}

void ReplaceCommand::UnExecute() {
	string previousString;
	string currentString;

	LONG textCount;
	LONG noteCurrent;
	LONG lineCurrent;

	// 1. ���� ���¸� �д´�.
	currentString = this->state->GetNote()->GetString();
	noteCurrent = this->state->GetNoteCurrent();
	lineCurrent = this->state->GetLineCurrent();

	// 2. ���� ���¸� �д´�.
	previousString = this->previousState->GetNote()->GetString();

	// + ��ġ�� �̵��Ѵ�.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 3. �� �ܾ �ٲ�����
	if (this->onIsReplacedCurrent == true) {
		// 3.1. �ڵ����� ����̸� �� ���� ��ģ��.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 3.2. ���� ������ ���� ���� ���Ѵ�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());

		// 3.3. ���ڸ�ŭ �����Ѵ�.
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// 3.4. ������ ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();
		
		// 3.5. �޸����� �߰��Ѵ�.
		this->notepadForm->note->Paste(previousString);

		// 3.6. ���ڸ�ŭ �����Ѵ�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)previousString.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 3.7. �ڵ��������̸� �����ڵ������Ѵ�.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
	}

	// 4. ��ü �ٲٱ��̸�
	if (this->onIsReplacedCurrent != true) {
		// 4.2. �޸������� �������� ã�´�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);

		// 4.3. ã�� ������ ���� ���� �ݺ��Ѵ�.
		while (this->notepadForm->onIsFound == TRUE) {
			// 4.3.1. ���õ� ������ �����.
			this->notepadForm->note->RemoveSelect();
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			// 4.3.2. �ڵ��������̸� �޸������� ���� ���� �ڵ����� Ǭ��.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->note->Combine(noteCurrent);
				noteCurrent = this->notepadForm->note->GetCurrent();
				this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			}

			// 4.3.3. ã�� ������ �߰��Ѵ�.
			this->notepadForm->note->Paste(previousString);

			// 4.3.4. �޸������� �������� ã�´�.
			this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);
		}
		
		// 4.4. �ڵ����� ����̸� ��ü �ڵ����� �Ѵ�.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
		// 4.5. ��ü ���� �����Ѵ�.
		this->notepadForm->note->SelectAll(false);
		
		// 4.6. ó�� ��ġ�� �̵��Ѵ�.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();
	}
}

void ReplaceCommand::ReExecute() {
	string previousString;
	string currentString;

	LONG textCount;
	LONG noteCurrent;
	LONG lineCurrent;

	// 1. ���� ���¸� �д´�.
	currentString = this->previousState->GetNote()->GetString();
	noteCurrent = this->previousState->GetNoteCurrent();
	lineCurrent = this->previousState->GetLineCurrent();

	// 2. ���� ���¸� �д´�.
	previousString = this->state->GetNote()->GetString();

	// + ��ġ�� �̵��Ѵ�.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 3. �� �ܾ �ٲ�����
	if (this->onIsReplacedCurrent == true) {
		// 3.1. �ڵ����� ����̸� �� ���� ��ģ��.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 3.2. ���� ������ ���� ���� ���Ѵ�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());

		// 3.3. ���ڸ�ŭ �����Ѵ�.
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// 3.4. ������ ������ �����.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();

		// 3.5. �޸����� �߰��Ѵ�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)previousString.c_str());
		this->notepadForm->note->Paste(previousString);

		// 3.6. ���ڸ�ŭ �����Ѵ�.
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// 3.7. �ڵ��������̸� �����ڵ������Ѵ�.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
	}

	// 4. ��ü �ٲٱ��̸�
	if (this->onIsReplacedCurrent != true) {
		// 4.2. �޸������� �������� ã�´�.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);

		// 4.3. ã�� ������ ���� ���� �ݺ��Ѵ�.
		while (this->notepadForm->onIsFound == TRUE) {
			// 4.3.1. ���õ� ������ �����.
			this->notepadForm->note->RemoveSelect();
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			// 4.3.2. �ڵ��������̸� �޸������� ���� ���� �ڵ����� Ǭ��.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->note->Combine(noteCurrent);
				noteCurrent = this->notepadForm->note->GetCurrent();
				this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			}

			// 4.3.3. ã�� ������ �߰��Ѵ�.
			this->notepadForm->note->Paste(previousString);

			// 4.3.4. �޸������� �������� ã�´�.
			this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);
		}

		// 4.4. �ڵ����� ����̸� ��ü �ڵ����� �Ѵ�.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
		// 4.5. ��ü ���� �����Ѵ�.
		this->notepadForm->note->SelectAll(false);

		// 4.6. ó�� ��ġ�� �̵��Ѵ�.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();
	}
}