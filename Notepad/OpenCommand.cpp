//OpenCommand.cpp
#include"OpenCommand.h"
#include"NotepadForm.h"
#include"Glyph.h"
#include"File.h"
#include"CommandHistory.h"
#include"GlyphFactory.h"
#include<afxdlgs.h>
#include"resource.h"

OpenCommand::OpenCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

OpenCommand::~OpenCommand() {
	
}

void OpenCommand::Execute() {
	CString fileName;
	CString pathName;
	CString asterisk;
	GlyphFactory glyphFactory;
	Glyph *line;
	
	LONG index;
	LONG ret = IDNO;
	CString saveMessage;
	string filePath;

	string noteStr;

	CHAR szFilters[] = _T("�ؽ�Ʈ���� (*.txt)|*.txt|All Files (*.*)|*.*||");
	CString windowTitle;
	CFileDialog fileDlgLoad(TRUE, _T("txt"), NULL, NULL, szFilters);
	/*
	1. ���� �޴��� ������ ��(2021.01.07)
		1.1.Ÿ��Ʋ ���� ������ �д´�.
		1.2.�޶����� ������(*ǥ�� ������) �Ǵ� ��������̸�
		1.2.1.���忩�θ� ���� �޼����ڽ��� ����.
		1.2.1.1.���� �������� �����ϴ� �޼����� ������.
		1.2.1.2.��Ұ� �ƴ� �� Ȥ�� �ƴϿ��� ��������
		1.2.1.2.1.���� ���� ���̾�α׸� ����.
		1.2.1.2.2.Ȯ���� ��������
		1.2.1.2.2.1.���� �����̸�, ���� ��θ� �д´�.
		1.2.1.2.2.2.���� ������ ���ش�.
		1.2.1.2.2.3.������ ���� �����.
		1.2.1.2.2.4.Ÿ��Ʋ�� ������ �����Ѵ�.
		1.2.1.2.2.5.���Ͽ��� �ҷ����⸦ �Ѵ�.	
		*/
	
	//1.1.Ÿ��Ʋ ���� ������ �д´�.
	this->notepadForm->GetWindowText(windowTitle);
	//1.2 �޶����� ������(*ǥ�� ������) �Ǵ� ��������̸�
	if (windowTitle.GetAt(0) == '*' || windowTitle.Compare("���� ���� - �޸���") == 0) {
		// �߰� " - �޸���"�� ������ ���ش�. (2021.01.08)
		if (windowTitle.GetAt(0) == '*') {
			asterisk = windowTitle.GetAt(0);
			windowTitle = windowTitle.Mid(1);
		}
		index = windowTitle.Find(" - �޸���");
		if (index >= 0) {
			windowTitle = windowTitle.Left(index);
		}

		//1.2.1.���忩�θ� ���� �޼����ڽ��� ����. + ���� ���� �޽��� �ڽ��� ����. (2021.01.08)
		filePath = this->notepadForm->file->GetPath();
		if (filePath != "") {
			windowTitle = (filePath + "\\").c_str() + windowTitle;
		}
		saveMessage.Format("���� ������ %s�� �����Ͻðڽ��ϱ�?", (LPCTSTR)windowTitle);
		if (asterisk == '*') {
			ret = SaveMessageBox(this->notepadForm->GetSafeHwnd(), (LPCTSTR)saveMessage, _T("�޸���"),
				MB_YESNOCANCEL);
		}

		//1.2.1.1.���� �������� �����ϴ� �޼����� ������.
		this->notepadForm->onIsSaving = TRUE;
		this->notepadForm->onIsSaveCanceled = FALSE;
		if (ret == IDYES) {//Yes
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FILE_SAVE);
		}
	}
	//1.2.1.2.��Ұ� �ƴ� �� Ȥ�� �ƴϿ��� ��������
	if (ret != IDCANCEL && this->notepadForm->onIsSaveCanceled != TRUE) {

		//1.2.1.2.1. Ȯ���� ��������
		if (fileDlgLoad.DoModal() == IDOK) {
			//1.2.1.2.2.1.���� �����̸�, ���� ��θ� �д´�.
			fileName = fileDlgLoad.GetFileName();
			pathName = fileDlgLoad.GetFolderPath();
			this->notepadForm->onIsSaving = TRUE; // (2021.02.22)

			//1.2.1.2.2.2.���� ������ ���ش�.
			if (this->notepadForm->file != NULL) {
				delete this->notepadForm->file;
			}
			//1.2.2.1.2.3.������ ���� �����.
			this->notepadForm->file = new File(this->notepadForm, (LPCTSTR)fileName, (LPCTSTR)pathName);
			//1.2.1.2.2.4.Ÿ��Ʋ�� ������ �����Ѵ�.
			this->notepadForm->SetWindowTextA(fileName);
			//1.2.1.2.2.5. ��Ʈ�� �ִ� ������� ��� �����.
			if (this->notepadForm->note != NULL) {
				delete this->notepadForm->note;
			}
			this->notepadForm->note = glyphFactory.Create((char*)0);
			line = glyphFactory.Create((char*)"\r");
			index = this->notepadForm->note->Add(line);
			this->notepadForm->note->First();
			this->notepadForm->current = this->notepadForm->note->GetAt(index);

			//1.2.1.2.2.6.���Ͽ��� �ҷ����⸦ �Ѵ�.
			this->notepadForm->file->Load();
			index = this->notepadForm->note->First();
			this->notepadForm->current = this->notepadForm->note->GetAt(index);
			this->notepadForm->current->First();
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
			}
			if (this->notepadForm->commandHistory != NULL) {
				delete this->notepadForm->commandHistory;
			}
			this->notepadForm->commandHistory = new CommandHistory(this->notepadForm);
		}
	}
}