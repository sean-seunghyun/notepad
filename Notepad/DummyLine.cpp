// DummyLine.cpp
/*
���ϸ�Ī : DummyLine.cpp
��� : ������ Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.06.18
*/
#include "DummyLine.h"

DummyLine::DummyLine(Long capacity, bool onIsLine)
	: Line(capacity, onIsLine) {
}

DummyLine::DummyLine(const DummyLine& source)
	: Line(source) {
}

DummyLine::~DummyLine() {
}

Glyph* DummyLine::Clone() {
	return new DummyLine(*this);
}

DummyLine& DummyLine::operator =(const DummyLine& source) {
	Line::operator =(source);

	return *this;
}