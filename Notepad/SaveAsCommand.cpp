//SaveAsCommand.cpp
#include"SaveAsCommand.h"
#include"File.h"
#include"NotepadForm.h"
#include"Glyph.h"

#include<afxdlgs.h>
#include<string>
using namespace std;

SaveAsCommand::SaveAsCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SaveAsCommand::~SaveAsCommand() {

}

void SaveAsCommand::Execute() {

	CString windowText;
	CString pathName;
	CString fileName;
	string str;
	bool onIsSaving = false;
	string title="*";

	TCHAR szFilters[] = _T("�ؽ�Ʈ���� (*.txt)|*.txt|All Files (*.*)|*.*||");
	/*
	1. �ٸ��̸����� �����ϱ� �޴��� ������ ��
	1.1. ���� ���� ���̾�α׸� ����.
	1.2 Ȯ���� ��������
		1.2.1 ������ ���� �̸�, ��θ� �д´�.
		1.2.2. ���� ������ ���ش�.
		1.2.3. ������ ���� �����.
		1.2.4. ��Ʈ���� ���ڿ��� �����´�.
		1.2.5. ���Ͽ��� �����Ѵ�.
		1.2.6. Ÿ��Ʋ���� ������ �ٲ۴�.
		*/




		
		//1.1. ���� ���� ���̾�α׸� ����.	
		this->notepadForm->GetWindowTextA(windowText);	
		if (this->notepadForm->onIsSaving == TRUE) {
			title=this->notepadForm->file->GetTitle();
		}		
		CFileDialog fileDlg(FALSE, _T("txt"), title.c_str(), NULL, szFilters);
	
		
		//1.2 Ȯ���� ��������
		if (fileDlg.DoModal() == IDOK) {		
			//1.2.1 ������ ���� �̸�, ��θ� �д´�.
			fileName = fileDlg.GetFileName();
			pathName = fileDlg.GetFolderPath();
			//1.2.2. ���� ������ ���ش�.					
			if (this->notepadForm->file != NULL) {
				delete this->notepadForm->file;
			}
			//1.2.3. ������ ���� �����.
			this->notepadForm->file = new File(this->notepadForm, (LPCTSTR)fileName, (LPCTSTR)pathName);
			

			//1.2.4. ��Ʈ���� ���ڿ��� �����´�.
			str = this->notepadForm->note->GetString();
			//1.2.5.���Ͽ��� �����Ѵ�.
			this->notepadForm->file->Save(str);
			this->notepadForm->onIsSaving = true;
			//1.2.5.Ÿ��Ʋ���� ������ �ٲ۴�.
			this->notepadForm->SetWindowText(fileName);
		}
	}