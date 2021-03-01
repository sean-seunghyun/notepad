// Font.cpp
/*
���ϸ�Ī : Font.cpp
��� : �۲� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.07
*/
#include "Font.h"

Font::Font() {
	memset(&this->logFont, 0, sizeof(LOGFONT));
	memset(&this->color, 0, sizeof(COLORREF));
}

Font::Font(LOGFONT logFont, COLORREF color) {
	this->logFont = logFont;
	this->color = color;
}

Font::Font(const Font& source) {
	this->logFont = source.logFont;
	this->color = source.color;
}

Font::~Font() {
}

Font& Font::operator =(const Font& source) {
	this->logFont = source.logFont;
	this->color = source.color;

	return *this;
}