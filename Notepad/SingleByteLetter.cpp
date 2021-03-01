// SingleByteLetter.cpp
/*
���ϸ�Ī : SingleByteLetter.cpp
��� : 1����Ʈ ���� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.06
*/
#include "SingleByteLetter.h"

SingleByteLetter::SingleByteLetter() {
	this->script = '\0';
}

SingleByteLetter::SingleByteLetter(char script) {
	this->script = script;
}

SingleByteLetter::SingleByteLetter(const SingleByteLetter& source) {
	this->script = source.script;
	this->onIsSelected = source.onIsSelected;
}

SingleByteLetter::~SingleByteLetter() {
}

Glyph* SingleByteLetter::Clone() {
	return new SingleByteLetter(*this);
}

string SingleByteLetter::GetString() {
	string str;
	str.push_back(this->script);

	return str;
}

SingleByteLetter& SingleByteLetter::operator =(const SingleByteLetter& source) {
	this->script = source.script;
	this->onIsSelected = source.onIsSelected;

	return *this;
}