// PrintCommand.cpp
/*
���ϸ�Ī : PrintCommand.cpp
��� : �μ� ��� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.29
*/
#include"PrintCommand.h"
#include"NotepadForm.h"
#include"Glyph.h"
#include"Matrix.h"
#include"Font.h"
#include"PageInfo.h"
#include<afxdlgs.h>
#include"File.h"
#include<afxpriv.h>

PrintCommand::PrintCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PrintCommand::~PrintCommand() {

}

void PrintCommand::Execute() {
	CPrintDialog dlg(FALSE);
	DOCINFO di;
	CDC *cdc;
	Long printWidth;
	Long printHeight;

	Long j;
	Long i = 0;

	bool onIsKorean = false;

	string linestr;

	CFont font;
	LOGFONT logFont;

	RECT margin;
	CString header;
	CString footer;
	Long devMode;
	string fileTitle;


	if (dlg.DoModal() == IDOK) {
		//docInfo �ۼ�
		memset(&di, 0, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		fileTitle = this->notepadForm->file->GetTitle();
		di.lpszDocName = fileTitle.c_str();

		//dc�����б�
		cdc = CDC::FromHandle(dlg.GetPrinterDC());

		//���μ��� ���� ����
		devMode = this->notepadForm->pageInfo->GetDevMode();
		if (devMode != 1) {//���θ��� ������ �Ǿ�������
			DEVMODE *pDevMode = dlg.GetDevMode();
			pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
			cdc->ResetDCA(pDevMode);
		}

#if 0
		//���� ����
		paperSize = this->notepadForm->pageInfo->GetPaperSize();
		printWidth = paperSize.x;
		printHeight = paperSize.y;
#endif
		printWidth = cdc->GetDeviceCaps(HORZRES);
		printHeight = cdc->GetDeviceCaps(VERTRES);

		//��Ʈ ����
		logFont = this->notepadForm->font->GetLogFont();
		logFont.lfHeight = -((logFont.lfHeight * cdc->GetDeviceCaps(LOGPIXELSY)) / 96);
		font.CreateFontIndirectA(&logFont);
		TEXTMETRIC metric;
		CFont *def_font = cdc->SelectObject(&font);
		cdc->GetTextMetrics(&metric);

		//������ ���鼳��
		margin = this->notepadForm->pageInfo->GetMargin();
		header = this->notepadForm->pageInfo->GetHeader();
		footer = this->notepadForm->pageInfo->GetFooter();


		CRect writeRect(0 + (int)(margin.left*0.24), 0 + (int)(margin.top*0.24),
			printWidth - (int)(margin.right*0.24), printHeight - (int)(margin.bottom*0.24));

		if (header.Compare("") != 0) {
			writeRect.top += (metric.tmHeight);
		}
		if (footer.Compare("") != 0) {
			writeRect.bottom -= (metric.tmHeight);
		}



		CRect headerRect(0, 0, printWidth, printHeight + (metric.tmHeight));
		CRect footerRect(0, printHeight - (metric.tmHeight), printWidth, printHeight);
		cdc->SetMapMode(MM_TEXT);
		CString noteString = CString(this->notepadForm->note->GetString().c_str());
		char *p = noteString.GetBuffer(noteString.GetLength());
		char *startAt = p;

		//�μ� ����
		CRect           r;
		int             nHeight;
		CPrintInfo info;
		info.m_rectDraw.SetRect(writeRect.left, writeRect.top, writeRect.right, writeRect.bottom);


		int totalDone = 0;
		int lengthToGo = noteString.GetLength();



		// ��ť��Ʈ �μ� ����
		BOOL bPrintingOK = cdc->StartDoc(&di);

		// �������� �μ��ϴ� ����
		for (UINT page = info.GetMinPage(); bPrintingOK && totalDone < lengthToGo; page++) {
			// ������ �μ� ����
			cdc->StartPage();
			info.m_nCurPage = page;
			// calc how much text fits on one page
			r = info.m_rectDraw;
			r.bottom = r.top;
			j = 0;
			while (r.bottom < info.m_rectDraw.bottom && totalDone + j < lengthToGo) {
				r.right = info.m_rectDraw.right;

				if ((startAt[j] & 0x80) == 0) {//�����̸�
					j = j + 1;
					onIsKorean = false;
				}
				else if ((startAt[j] & 0x80) != 0) {//�ѱ��̸�
					j = j + 2;
					onIsKorean = true;
				}

				nHeight = cdc->DrawText(startAt, j, r, DT_CALCRECT | DT_WORDBREAK | DT_EDITCONTROL | DT_EXPANDTABS);
			}

			// go one back to assure correct height
			if (r.bottom >= info.m_rectDraw.bottom && onIsKorean == true) {
				j -= 2;
			}
			else if (r.bottom >= info.m_rectDraw.bottom) {
				j--;
			}

			//�Ӹ��� ������ �μ�
			cdc->DrawText(header, &headerRect, DT_CENTER);
			cdc->DrawText(footer, &footerRect, DT_CENTER);

			// print that text
			cdc->DrawText(startAt, j, info.m_rectDraw, DT_WORDBREAK | DT_EDITCONTROL | DT_EXPANDTABS);

			// go to next page


			startAt += j;
			totalDone += j;

			// ������ �μ� �Ϸ�
			bPrintingOK = (cdc->EndPage() > 0);
		}
		noteString.ReleaseBuffer();

		// ��ť��Ʈ �μ� ����
		if (bPrintingOK) cdc->EndDoc();
		else cdc->AbortDoc();
		cdc->SelectObject(def_font);

		font.DeleteObject();
		//dc�Ҵ�����
		cdc->DeleteDC();
	}
}