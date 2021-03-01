// GoToLineDialog.cpp
/*
���ϸ�Ī : GoToLineDialog.cpp
��� : �� �̵� ��ȭ���� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.26
*/
#include "GoToLineDialog.h"
#include "NotepadForm.h"
#include "Glyph.h"

GoToLineDialog::GoToLineDialog(NotepadForm *notepadForm)
	: CDialog(GoToLineDialog::IDD, notepadForm) {
	this->notepadForm = notepadForm;
}

GoToLineDialog::~GoToLineDialog() {
}

BOOL GoToLineDialog::OnInitDialog() {
	Glyph *it;

	CString line;

	LONG realLineCount = 0;
	if (this->notepadForm->onIsLineWrapping != TRUE) {
		realLineCount = this->notepadForm->note->GetLength();
	}
	LONG i = 0;
	while (i < this->notepadForm->note->GetLength() && this->notepadForm->onIsLineWrapping == TRUE) {
		it = this->notepadForm->note->GetAt(i);
		if (it->GetOnIsLine() == true) {
			realLineCount++;
		}
		i++;
	}
	line.Format("�� ��ȣ(1 - %d)(&L):", realLineCount);
	this->GetDlgItem(IDC_STATIC_ROWNUMBER)->SetWindowText(line);

	return CDialog::OnInitDialog();
}

void GoToLineDialog::OnOK() {
	CString line;
	this->GetDlgItem(IDC_EDIT_ROWNUMBER)->GetWindowText(line);

	LONG rowNumber = _ttoi(line);

	if (rowNumber <= this->notepadForm->note->GetLength()) {
		this->notepadForm->note->Move(rowNumber - 1);
		this->notepadForm->current = this->notepadForm->note->GetAt(rowNumber - 1);
		this->notepadForm->current->First();

		CDialog::OnOK();
	}
	else {
		this->MessageBox("�� ��ȣ�� ��ü �� ���� �ѽ��ϴ�.", "�޸��� - �� �̵�", MB_OK);
	}
}