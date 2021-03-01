// Clipboard.cpp
/*
���ϸ�Ī : Clipboard.cpp
��� : �ʱ��� Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.07.03
*/
#include "Clipboard.h"
#include <afxole.h>
#include "NotepadForm.h"
#include "Glyph.h"
#pragma warning(disable:4996)

Clipboard::Clipboard(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

Clipboard::~Clipboard() {
}

void Clipboard::Write(CString copyString) {
	HGLOBAL hGlob;
	
	hGlob = GlobalAlloc(GHND | GMEM_SHARE, copyString.GetLength() + 1);
	PSTR pGlobal = (PSTR)GlobalLock(hGlob);
	_tcscpy(pGlobal, (LPCSTR)copyString);
	GlobalUnlock(hGlob);
	
	this->notepadForm->OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hGlob);
	CloseClipboard();
}

CString Clipboard::Read() {
	CString clipboardString;
	HGLOBAL hGlob;
	BOOL isOpen = this->notepadForm->OpenClipboard();
	if (isOpen == TRUE) {
		hGlob = GetClipboardData(CF_TEXT);
		clipboardString = CString((PSTR)GlobalLock(hGlob));
		GlobalUnlock(hGlob);
	}
	CloseClipboard();

	return clipboardString;
}