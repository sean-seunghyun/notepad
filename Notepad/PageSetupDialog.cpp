// PageSetupDialog.cpp
/*
���ϸ�Ī : PageSetupDialog.cpp
��� : ������ ���� ��ȭ���� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.29
*/

#include"PageSetupDialog.h"
#include"PageInfo.h"
#include"NotepadForm.h"

BEGIN_MESSAGE_MAP(PageSetupDialog, CPageSetupDialog)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()

PageSetupDialog::PageSetupDialog(DWORD dwFlags, CWnd *parent)
	:CPageSetupDialog(dwFlags, parent) {
	this->notepadForm = dynamic_cast<NotepadForm*>(parent);

	this->m_psd.Flags |= PSD_ENABLEPAGESETUPTEMPLATE | PSD_MARGINS;
	this->m_psd.hInstance = AfxGetResourceHandle();
	this->m_psd.lpPageSetupTemplateName = MAKEINTRESOURCE(PageSetupDialog::IDD);

}

BOOL PageSetupDialog::OnInitDialog() {
	CDialog::OnInitDialog();
	CString header;
	CString footer;

	header = this->notepadForm->pageInfo->GetHeader();
	footer = this->notepadForm->pageInfo->GetFooter();

	if (header.Compare("") != 0) {
		this->GetDlgItem(IDC_EDIT_HEADER)->SetWindowTextA((LPCTSTR)header);
	}
	if (footer.Compare("") != 0) {
		this->GetDlgItem(IDC_EDIT_FOOTER)->SetWindowTextA((LPCTSTR)footer);
	}

	return FALSE;
}


void PageSetupDialog::OnOK() {
	//Ŭ������ ������ �����Ѵ�.
	CString header;
	CString footer;
	Long devMode=1;

	POINT paperSize;


	
	this->GetDlgItem(IDC_EDIT_HEADER)->GetWindowTextA(header);
	this->GetDlgItem(IDC_EDIT_FOOTER)->GetWindowTextA(footer);

	
	LPDEVMODE pDevMode = (LPDEVMODE)::GlobalLock(this->m_psd.hDevMode);
	if (pDevMode->dmOrientation == DMORIENT_LANDSCAPE) {
		devMode = 2;
	}

	if (this->notepadForm->pageInfo != NULL) {
		delete this->notepadForm->pageInfo;
	}
	
	paperSize.x = this->m_psd.ptPaperSize.x;
	paperSize.y = this->m_psd.ptPaperSize.y;


	this->notepadForm->pageInfo = new PageInfo(paperSize, devMode, this->m_psd.rtMargin, header, footer);

	this->EndDialog(0);

}

