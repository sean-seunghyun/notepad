// Observer.cpp
/*
���ϸ�Ī : Observer.cpp
��� : ������ Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.07
*/
#include "Observer.h"
#include "Subject.h"

Observer::Observer(Subject *subject) {
	this->subject = subject;
}

Observer::~Observer() {
}