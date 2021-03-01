// NewCommand.cpp
/*
���ϸ�Ī : NewCommand.cpp
��� : ���� ����� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.02.01
*/
#include "NewCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"
#include "File.h"
#include "resource.h"

NewCommand::NewCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

NewCommand::~NewCommand() {
}

void NewCommand::Execute() {	
	CString title;
	this->notepadForm->GetWindowText(title);

	CString asterisk = title.Left(1);
	if (asterisk.Compare("*") == 0) {
		title = title.Mid(1);
	}

	LONG index = title.Find(" - �޸���");
	if (index >= 0) {
		title = title.Left(index);
	}

	CString fileName;
	if (this->notepadForm->file->GetPath() != "") {
		fileName = (this->notepadForm->file->GetPath() + "\\").c_str();
	}
	fileName += (LPCTSTR)title;

	CString closeMessage;
	closeMessage.Format("���� ������ %s�� �����Ͻðڽ��ϱ�?", (LPCTSTR)fileName);

	LONG id = IDNO;
	if (asterisk.Compare("*") == 0) {
		id = SaveMessageBox(this->notepadForm->GetSafeHwnd(), (LPCTSTR)closeMessage, "�޸���", MB_YESNOCANCEL);
	}

	if (id == IDYES || id == IDNO) {
		GlyphFactory glyphFactory;
		if (id == IDYES) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FILE_SAVE);
		}
		if (this->notepadForm->onIsSaveCanceled != TRUE) {
			if (this->notepadForm->note != 0) {
				delete this->notepadForm->note;
			}
			this->notepadForm->note = glyphFactory.Create(0);
			this->notepadForm->current = glyphFactory.Create((char*)"\n");
			this->notepadForm->note->Add(this->notepadForm->current);
			this->notepadForm->note->First();

			if (this->notepadForm->file != 0) {
				delete this->notepadForm->file;
			}
			this->notepadForm->file = new File(this->notepadForm);
			this->notepadForm->onIsSaving = FALSE;

			this->notepadForm->SetWindowText("������� - �޸���");
		}
	}
}