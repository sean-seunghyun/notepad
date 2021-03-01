// HelpCommand.cpp
/*
���ϸ�Ī : HelpCommand.cpp
��� : ���� ���� ��� Ŭ������ �����.
�ۼ��� : ������
�ۼ����� : 2020.09.25
*/
#include "HelpCommand.h"
#include "NotepadForm.h"
#include "resource.h"
#include <htmlhelp.h>
#pragma comment(lib, "htmlhelp")

HelpCommand::HelpCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

HelpCommand::~HelpCommand() {
}

void HelpCommand::Execute() {//GetHelpFile().c_str()//"C:\\Users\\jeong\\Downloads\\helpdocs\\Notepad User Manual.chm::/Intro.htm>Mainwin"
	HWND hwnd = HtmlHelpA(GetDesktopWindow(), "notepad.chm", HH_DISPLAY_TOPIC, NULL);
}