// PreviewCommand.cpp
/*
���ϸ�Ī : PreviewCommand.cpp
��� : �̸����� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.29
*/
#include "PreviewCommand.h"
#include "PrintPreviewForm.h"
#include "NotepadForm.h"
#include "Printer.h"
#include "PageSetupDialog.h"
#include <afxdlgs.h>
#include <afxstat_.h>
#include <afxdisp.h>

PreviewCommand::PreviewCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PreviewCommand::~PreviewCommand() {
}

void PreviewCommand::Execute() {
	PageSetupDialog dlg(PSD_MARGINS | PSD_RETURNDEFAULT, this->notepadForm);
	dlg.DoModal();
	this->notepadForm->printer->SetDC(dlg.CreatePrinterDC());

	PrintPreviewForm *printPreviewForm = new PrintPreviewForm(this->notepadForm);
	printPreviewForm->Create(NULL, "�̸�����");
	printPreviewForm->ShowWindow(SW_SHOW);
	printPreviewForm->UpdateWindow();
}