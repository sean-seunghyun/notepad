// CutCommand.cpp
/*
���ϸ�Ī : CutCommand.cpp
��� : �߶󳽴� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.25
*/
#include "CutCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Clipboard.h"
#include "Glyph.h"
#include "Matrix.h"
#include "resource.h"

CutCommand::CutCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CutCommand::~CutCommand() {
}

void CutCommand::Execute() {
	LONG lineCurrent;
	LONG noteCurrent;

	CString title;
	CString copyString;
	copyString = this->notepadForm->note->GetSelectString().c_str();

	noteCurrent = this->notepadForm->note->GetCurrent();
	if (copyString != "" && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->CombineSelectedLines();
	}

	if (copyString != "") {
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);// ���õ� ������ �־�� �����ϰԲ� ����(2021.02.09)
		lineCurrent = this->notepadForm->current->GetCurrent(); // ����� ���� ���� ��ġ�� �аԲ� ����(2021.02.09)

		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
		this->previousState = new State(lineCurrent, noteCurrent, (LPCTSTR)copyString);
		this->notepadForm->clipboard->Write(copyString);
		this->onIsCommandSaving = true;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAPLINE);
	}

	this->notepadForm->GetWindowText(title);
	if (title.GetAt(0) != '*' && copyString != "") {
		title = "*" + title;
	}
	this->notepadForm->SetWindowTextA(title);
}

void CutCommand::UnExecute() {
	Glyph *previousNote;

	Long lineCurrent;
	Long noteCurrent;

	if (this->previousState != 0) {
		// 2.1. ���� ���� ������ �о�´�.
		previousNote = this->previousState->GetNote();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		if (this->notepadForm->onIsLineWrapping == TRUE) {// �ڵ��������̸� �� �� �ڵ������Ѵ�.(2021.02.09)
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->note->Combine(noteCurrent);
		}

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 2.2. ���� ������ ������ �߰��Ѵ�.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 2.3. �޸������� ���� ���� ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->previousState != 0 && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void CutCommand::ReExecute() {
	Glyph *previousNote;

	string text;

	Long lineCurrent;
	Long noteCurrent;
	Long textCount;

	// 1. ���� ���� ������ �о�´�.
	previousNote = this->previousState->GetNote();
	text = previousNote->GetString();
	lineCurrent = this->previousState->GetLineCurrent();
	noteCurrent = this->previousState->GetNoteCurrent();

	// 2. �о�� ��ġ�� �̵��Ѵ�.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// 3. ������ �����Ѵ�.
	textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
	this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

	// 4. �ڵ��������̰� ���õǾ� ������ ���õ� �ٵ��� �����ش�.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->CombineSelectedLines();
	}
	
	this->notepadForm->note->RemoveSelect();

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}