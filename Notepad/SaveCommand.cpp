//SaveCommand.cpp
#include"SaveCommand.h"
#include"File.h"
#include"NotepadForm.h"
#include"Glyph.h"

#include<afxdlgs.h>
#include<string>
using namespace std;

SaveCommand::SaveCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SaveCommand::~SaveCommand() {

}

void SaveCommand::Execute() {// ret �ʱ�ȭ
	CFileStatus status;

	CString windowText;
	CString pathName;
	CString fileName;
	string str;
	bool onIsSaving = false;
	INT_PTR ret = IDCANCEL;
	
	TCHAR szFilters[] = _T("�ؽ�Ʈ���� (*.txt)|*.txt|All Files (*.*)|*.*||");
	/*2021.01.17
	1. �����ϱ� �޴��� ������ ��
		1.1 Ÿ��Ʋ ���� ������ �д´�.
		1.2 �޶����� ������(*ǥ�� ������) �Ǵ� ��������̸�
			1.2.1.���� ������ �Ǿ��ִ� ���°� �ƴϸ�
				1.2.1.1.���� ���� ���̾�α׸� ����.
				1.2.1.2.Ȯ���� ��������
					1.2.2.1.2.1 ������ ���� �̸�, ��θ� �д´�.
					1.2.2.1.2.2.���� ������ ���ش�.
					1.2.2.1.2.3.������ ���� �����.
			1.2.2.���� ������ �Ǿ��ִ� �����̸�
				1.2.2.1.���Ͽ��� �����̸��� ��θ� �д´�.
			1.2.3.��Ʈ���� ���ڿ��� �����´�.
			1.2.4.���Ͽ��� �����Ѵ�.
			1.2.5.Ÿ��Ʋ���� ������ �ٲ۴�.
		*/

		//1.1 Ÿ��Ʋ ���� ������ �д´�.
	this->notepadForm->GetWindowText(windowText);

	//1.2 �޶����� ������(*ǥ�� ������) �Ǵ� ��������̸�
	if (windowText.GetAt(0) == '*' || windowText.Compare("���� ���� - �޸���") == 0) {
		//1.2.1.���� ������ �Ǿ��ִ� ���°� �ƴϸ�
		if (this->notepadForm->onIsSaving != TRUE) {
			//1.2.1.1.���� ���� ���̾�α׸� ����.
			CFileDialog fileDlg(FALSE, _T("txt"), _T("*.txt"), NULL, szFilters);
			ret = fileDlg.DoModal();

			this->notepadForm->onIsSaveCanceled = TRUE;
			if (ret == IDOK) {
				fileName = fileDlg.GetFileName();
				pathName = fileDlg.GetFolderPath();
				//1.2.2.1.2.2.���� ������ ���ش�.					
				if (this->notepadForm->file != NULL) {
					delete this->notepadForm->file;
				}
				//1.2.2.1.2.3.������ ���� �����.
				this->notepadForm->file = new File(this->notepadForm, (LPCTSTR)fileName, (LPCTSTR)pathName);
				this->notepadForm->onIsSaving = TRUE;
				this->notepadForm->onIsSaveCanceled = FALSE;
			}
		}
		//1.2.2.���� ������ �Ǿ��ִ� �����̸�
		else {
			//1.2.2.1.���Ͽ��� �����̸��� ��θ� �д´�.
			ret = IDYES;
			fileName = CString(this->notepadForm->file->GetTitle().c_str());
			pathName = CString(this->notepadForm->file->GetPath().c_str());
		}

		if (ret != IDCANCEL) {//��Ҹ� �ȴ�������
			//1.2.3.��Ʈ���� ���ڿ��� �����´�.	
			str = this->notepadForm->note->GetString();
			//1.2.4.���Ͽ��� �����Ѵ�.
			this->notepadForm->file->Save(str);
			
			//1.2.5.Ÿ��Ʋ���� ������ �ٲ۴�.
			this->notepadForm->SetWindowText(fileName);
		}
	}
}