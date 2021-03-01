// KeyActionFactory.cpp
/*
���ϸ�Ī : KeyActionFactory.cpp
��� : Ű ��ư�� ������ ���� �߻� ���丮 Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.08
�߰��� ���� : ��Ʈ�� �������� ���η� �������ֱ� Home, End, Left, Right
*/
#include "KeyActionFactory.h"
#include "PageUpKeyAction.h"
#include "PageDownKeyAction.h"
#include "EndKeyAction.h"
#include "CtrlEndKeyAction.h"
#include "HomeKeyAction.h"
#include "CtrlHomeKeyAction.h"
#include "LeftKeyAction.h"
#include "CtrlLeftKeyAction.h"
#include "SelectedLeftKeyAction.h"
#include "UpKeyAction.h"
#include "RightKeyAction.h"
#include "CtrlRightKeyAction.h"
#include "SelectedRightKeyAction.h"
#include "DownKeyAction.h"
#include "Glyph.h"

KeyActionFactory::KeyActionFactory() {
	this->notepadForm = 0;
}

KeyActionFactory::KeyActionFactory(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

KeyActionFactory::~KeyActionFactory() {
}

KeyAction* KeyActionFactory::Create(UINT nChar) {
	KeyAction *keyAction = 0;
	bool onIsSelected = this->notepadForm->note->GetOnIsSelected();
	switch (nChar) {
	case VK_PRIOR:
		keyAction = new PageUpKeyAction(this->notepadForm);
		break;

	case VK_NEXT:
		keyAction = new PageDownKeyAction(this->notepadForm);
		break;

	case VK_END:
		if (!(GetKeyState(VK_CONTROL) & 0x8000)) {
			keyAction = new EndKeyAction(this->notepadForm);
		}
		else {
			keyAction = new CtrlEndKeyAction(this->notepadForm);
		}
		break;

	case VK_HOME:
		if (!(GetKeyState(VK_CONTROL) & 0x8000)) {
			keyAction = new HomeKeyAction(this->notepadForm);
		}
		else {
			keyAction = new CtrlHomeKeyAction(this->notepadForm);
		}
		break;

	case VK_LEFT:
		if (!(GetKeyState(VK_CONTROL) & 0x8000) && ((GetKeyState(VK_SHIFT) & 0x8000) || onIsSelected != true)) {
			keyAction = new LeftKeyAction(this->notepadForm);
		}
		else if((GetKeyState(VK_CONTROL) & 0x8000) && ((GetKeyState(VK_SHIFT) & 0x8000) || onIsSelected != true)) {
			keyAction = new CtrlLeftKeyAction(this->notepadForm);
		}
		else {
			keyAction = new SelectedLeftKeyAction(this->notepadForm);
		}
		break;

	case VK_UP:
		keyAction = new UpKeyAction(this->notepadForm);
		break;

	case VK_RIGHT:
		if (!(GetKeyState(VK_CONTROL) & 0x8000) && ((GetKeyState(VK_SHIFT) & 0x8000) || onIsSelected != true)) {
			keyAction = new RightKeyAction(this->notepadForm);
		}
		else if ((GetKeyState(VK_CONTROL) & 0x8000) && ((GetKeyState(VK_SHIFT) & 0x8000) || onIsSelected != true)) {
			keyAction = new CtrlRightKeyAction(this->notepadForm);
		}
		else {
			keyAction = new SelectedRightKeyAction(this->notepadForm);
		}
		break;

	case VK_DOWN:
		keyAction = new DownKeyAction(this->notepadForm);
		break;

	default:
		break;
	}

	return keyAction;
}