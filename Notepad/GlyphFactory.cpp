// GlyphFactory.cpp
/*
���ϸ�Ī : GlyphFactory.cpp
��� : ���� ���丮 Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.04.24
*/
#include "GlyphFactory.h"
#include "Glyph.h"
#include "Note.h"
#include "Line.h"
#include "SingleByteLetter.h"
#include "DoubleByteLetter.h"
#include "DummyLine.h"

GlyphFactory::GlyphFactory() {
}

GlyphFactory::~GlyphFactory() {
}

Glyph* GlyphFactory::Create(char(*text), bool onIsLine) {
	Glyph *glyph = 0;
	if (text == 0 || text[0] == '\0') {
		glyph = new Note;
	}
	else if (text[0] == '\r' || text[0] == '\n') {
		if (onIsLine == true) {
			glyph = new Line;
		}
		else {
			glyph = new DummyLine;
		}
	}
	else if (text[0] & 0x80) {
		glyph = new DoubleByteLetter(text);
	}
	else if (!(text[0] & 0x80)) {
		glyph = new SingleByteLetter(text[0]);
	}

	return glyph;
}