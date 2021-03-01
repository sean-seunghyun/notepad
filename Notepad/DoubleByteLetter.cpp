// DoubleByteLetter.cpp
/*
���ϸ�Ī : DoubleByteLetter.cpp
��� : 2����Ʈ ���� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.06
*/
#include "DoubleByteLetter.h"

DoubleByteLetter::DoubleByteLetter(){
	this->script[0] = '\0';
	this->script[1] = '\0';
}

DoubleByteLetter::DoubleByteLetter(char(*script)) {
	this->script[0] = script[0];
	this->script[1] = script[1];
}

DoubleByteLetter::DoubleByteLetter(const DoubleByteLetter& source) {
	this->script[0] = source.script[0];
	this->script[1] = source.script[1];
	this->onIsSelected = source.onIsSelected;
}

DoubleByteLetter::~DoubleByteLetter() {
}

Glyph* DoubleByteLetter::Clone() {
	return new DoubleByteLetter(*this);
}

string DoubleByteLetter::GetString() {
	string str;
	str.push_back(this->script[0]);
	str.push_back(this->script[1]);

	return str;
}

DoubleByteLetter& DoubleByteLetter::operator =(const DoubleByteLetter& source) {
	this->script[0] = source.script[0];
	this->script[1] = source.script[1];
	this->onIsSelected = source.onIsSelected;

	return *this;
}