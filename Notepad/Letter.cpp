// Letter.cpp
/*
���ϸ�Ī : Letter.cpp
��� : ���� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.06
*/
#include "Letter.h"

Letter::Letter() {
	this->onIsSelected = false;
}

Letter::~Letter() {
}

void Letter::Select(bool select) {
	this->onIsSelected = select;
}