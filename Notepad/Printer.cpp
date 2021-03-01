// Printer.cpp
/*
���ϸ�Ī : Printer.cpp
��� : �μ�� Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.08.21
*/
#include "Printer.h"
#include "PageInfo.h"
#include "NotepadForm.h"
#include "Font.h"
#if _MFC_VER < 0x0700
#include <..\src\afximpl.h>
#else
#include <..\src\mfc\afximpl.h>
#endif
//#include "PrintPreviewForm.h"

Printer::Printer(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->printerDC = 0;
	this->notepadPage = 0;
	this->previewPage = 0;
}

Printer::~Printer() {
	if (this->printerDC != 0) {
		DeleteDC(this->printerDC);
	}
	if (this->notepadPage != 0) {
		delete this->notepadPage;
	}
	if (this->previewPage != 0) {
		delete this->previewPage;
	}
}
/*
1. �μ� ���� ũ�⸦ ���Ѵ�.
dc���� ���Ѵ�.
2. ���� ������ ĭ�� ������ ���Ѵ�.
GetTextMetric
3. ������ ���Ѵ�.
4. �̸����� ���� ũ�⸦ ���Ѵ�.
5. ���� ũ�⸦ ���Ѵ�.
6. ���� ũ��� ��Ʈ�� �����Ѵ�.
7. �̸����� ������ ������ ���Ѵ�.
*/
void Printer::CreatePageInfo(CWnd *previewForm) {// ���⿡�� ���鶧 �μ�, �̸����⸦ ��� �����Ѵ�.
	CRect printRect;
	CRect previewRect;
	CRect printMargin;
	CRect previewMargin;
	CRect printWriteRect;
	CRect previewWriteRect;
	CRect previewScreenRect;

	HFONT hFont;
	HFONT oldFont;

	CSize ratio;
	CSize previewSize;

	LOGFONT notepadFont;
	LOGFONT printerLogFont;
	LOGFONT previewLogFont;

	TEXTMETRIC metric;

	LONG rowCount = 0;
	LONG columnCount = 0;
	LONG letterWidth;
	LONG letterHeight;

	int nNum;
	int nDen;

	CDC *dc = CDC::FromHandle(this->printerDC);

	// 1. �μ� ���� ũ�⸦ ���Ѵ�.
	printRect.left = 0;
	printRect.top = 0;
	printRect.right = dc->GetDeviceCaps(HORZRES);
	printRect.bottom = dc->GetDeviceCaps(VERTRES);

	dc->DPtoLP(&printRect);

	// 2. �μ� ������ ��Ʈ�� ���Ѵ�.
	notepadFont = this->notepadForm->font->GetLogFont();
	printerLogFont = notepadFont;
	printerLogFont.lfHeight = -MulDiv(printerLogFont.lfHeight, GetDeviceCaps(this->printerDC, LOGPIXELSY), 72);
	printerLogFont.lfWidth = 0;

	// 3. ���� ũ�⸦ ���Ѵ�.
	hFont = CreateFontIndirect(&printerLogFont);
	oldFont = (HFONT)dc->SelectObject(hFont);
	dc->SetTextColor(this->notepadForm->font->GetColorRef());
	dc->GetTextMetrics(&metric);

	// 4. ���� ������ ĭ�� ������ ���Ѵ�.
	columnCount = printRect.right / metric.tmAveCharWidth;
	rowCount = printRect.bottom / metric.tmHeight;

	// 5. ������ ���Ѵ�.
	printMargin.left = AfxGetApp()->GetProfileInt("NotepadSection", "LEFT", 20) * 240;
	printMargin.top = AfxGetApp()->GetProfileInt("NotepadSection", "TOP", 20) * 240;
	printMargin.right = AfxGetApp()->GetProfileInt("NotepadSection", "RIGHT", 20) * 240;
	printMargin.bottom = AfxGetApp()->GetProfileInt("NotepadSection", "BOTTOM", 20) * 240;

	// 6. �μ� ������ ���� ������ ���Ѵ�.
	printWriteRect = printRect;
	printWriteRect.left += printMargin.left;
	printWriteRect.top += printMargin.top;
	printWriteRect.right -= printMargin.right;
	printWriteRect.bottom -= printMargin.bottom;

	// 7. �̸����� ���� ũ�⸦ ���Ѵ�.
	previewRect = printRect;
	dc->DPtoLP(&previewRect);

	previewMargin = printMargin;
	dc->DPtoLP(&previewMargin);

	previewForm->GetClientRect(&previewScreenRect);

	previewSize.cx = MulDiv(printRect.right, afxData.cxPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSX));
	previewSize.cy = MulDiv(printRect.bottom, afxData.cyPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSY));

	previewMargin.left = MulDiv(printMargin.left, afxData.cxPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSX));
	previewMargin.top = MulDiv(printMargin.top, afxData.cyPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSY));
	previewMargin.right = MulDiv(printMargin.right, afxData.cxPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSX));
	previewMargin.bottom = MulDiv(printMargin.bottom, afxData.cyPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSY));

	// ���� ġ���� �������� ������ ����� ������ Ȯ��
	nNum = previewScreenRect.bottom;
	nDen = previewSize.cy;

	// ������ �ʺ� �� ū ��� �ʺ� �������� ���� ����
	if (MulDiv(previewScreenRect.right, nNum, nDen) > previewSize.cx) {
		nNum = previewScreenRect.right;
		nDen = previewSize.cx;
	}

	ratio.cx = nNum;
	ratio.cy = nDen;

	// ������ �̸����� ���� ũ�� ���δ�.
	previewSize.cx = MulDiv(previewSize.cx, ratio.cx, ratio.cy);
	previewSize.cy = MulDiv(previewSize.cy, ratio.cx, ratio.cy);

	// ������ ������ ���δ�.
	previewMargin.left = MulDiv(previewMargin.left, ratio.cx, ratio.cy);
	previewMargin.top = MulDiv(previewMargin.top, ratio.cx, ratio.cy);
	previewMargin.right = MulDiv(previewMargin.right, ratio.cx, ratio.cy);
	previewMargin.bottom = MulDiv(previewMargin.bottom, ratio.cx, ratio.cy);

	// �̸����� ���� ũ�⸦ ���Ѵ�.
	previewRect.SetRect(3, 3, previewSize.cx - 3, previewSize.cy - 3);

	// ������ �߾����� �̵�
	previewRect.OffsetRect((previewScreenRect.right - previewRect.Size().cx) / 2 - 1,
		(previewScreenRect.bottom - previewRect.Size().cy) / 2 - 1);

	// 8. �̸������� ���� ������ ���Ѵ�. ���� �������� ���黩��.
	previewWriteRect = previewRect;
	previewRect.left += previewMargin.left;
	previewRect.top += previewMargin.top;
	previewRect.right -= previewMargin.right;
	previewRect.bottom -= previewMargin.bottom;

	// 9. ���� ũ�⸦ ���Ѵ�.
	letterWidth = previewSize.cx / columnCount;
	letterHeight = previewSize.cy / rowCount;

	// 10. �̸����� ������ ��Ʈ�� ���Ѵ�.
	CFont font;
	font.CreateFontA(letterHeight, letterWidth, notepadFont.lfEscapement, notepadFont.lfOrientation, notepadFont.lfWeight,
		notepadFont.lfItalic, notepadFont.lfUnderline, notepadFont.lfStrikeOut, notepadFont.lfCharSet, notepadFont.lfOutPrecision, 
		notepadFont.lfClipPrecision, notepadFont.lfQuality, notepadFont.lfPitchAndFamily, notepadFont.lfFaceName);

	font.GetLogFont(&previewLogFont);

	if (this->notepadPage != 0) {
		delete this->notepadPage;
	}
	//this->notepadPage = new PageInfo(printRect, printMargin, printWriteRect, printerLogFont);

	if (this->previewPage != 0) {
		delete this->previewPage;
	}
	//this->previewPage = new PageInfo(previewRect, previewMargin, previewWriteRect, previewLogFont);

	dc->SelectObject(oldFont);
	DeleteObject(hFont);
}
#if 0
CRect Printer::GetPrintPageRect() {
	//int nPageWidth = GetDeviceCaps(this->printerDC, HORZRES);
	// PHYSICALOFFSETX : �μ� ������ ������ �������� �Ÿ��� ��ġ ������ ����, PHYSICALWIDTH : ������ ������ �߾� �κ�
	//�μ��� ���̸� �ȼ������� ��´�. PHYSICALWIDTH, PHYSICALHEIGHT
	//int nPageHeight = GetDeviceCaps(this->printerDC, VERTRES);
	// PHYSICALOFFSETY : �μ� ������ ������ �������� �Ÿ��� ��ġ ������ ����, PHYSICALHEIGHT : ������ ������ �߾� �κ�
	return this->notepadPage->GetPageRect();
}

CRect Printer::GetPreviewPageRect() {
	return this->previewPage->GetPageRect();
}
#endif
CRect Printer::GetPrintPageMargin() {
	return this->notepadPage->GetMargin();
}

CRect Printer::GetPreviewPageMargin() {
	return this->previewPage->GetMargin();
}
#if 0
CRect Printer::GetPrintWriteRect() {
	return this->notepadPage->GetWriteRect();
}

CRect Printer::GetPreviewWriteRect() {
	return this->previewPage->GetWriteRect();
}

LOGFONT Printer::GetPrintLogFont() {
	return this->notepadPage->GetLogFont();
}

LOGFONT Printer::GetPreviewLogFont() { // ��Ʈ�� ����� ���߰� ������ ����. ������ �����ؼ� ������.
	return this->previewPage->GetLogFont();
}
#endif
void Printer::SetDC(HDC printerDC) {
	if (this->printerDC != 0) {
		DeleteDC(this->printerDC);
	}
	this->printerDC = printerDC;
}