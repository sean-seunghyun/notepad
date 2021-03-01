// HorizontalScroll.cpp
/*
���ϸ�Ī : HorizontalScroll.cpp
��� : ���� ��ũ�� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.11
*/
#include "HorizontalScroll.h"

HorizontalScroll::HorizontalScroll() {
}

HorizontalScroll::HorizontalScroll(Long min, Long max, Long unit, Long page, Long current)
	: Scroll(min, max, unit, page, current) {
}

HorizontalScroll::HorizontalScroll(const HorizontalScroll& source)
	: Scroll(source.min, source.max, source.unit, source.page, source.current) {
}

HorizontalScroll::~HorizontalScroll() {
}

Scroll* HorizontalScroll::Clone(Long min, Long max, Long unit, Long page, Long current) {
	return new HorizontalScroll(min, max, unit, page, current);
}

HorizontalScroll& HorizontalScroll::operator =(const HorizontalScroll& source) {
	*static_cast<Scroll*>(this) = source;

	return *this;
}