// CaretController.cpp
/*
���ϸ�Ī : CaretController.cpp
��� : ������(������)�� ĳ�� ������ Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.07
*/
#include "CaretController.h"
#include "Caret.h"
#include "Subject.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "Scroll.h"
#include "ScrollController.h"

CaretController::CaretController() {
	this->notepadForm = 0;
	this->caret = 0;
	this->onIsCaret = false;
}

CaretController::CaretController(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->caret = new Caret(this);
	dynamic_cast<Subject*>(this->notepadForm)->Attach(this);
}

CaretController::~CaretController() {
	if (this->caret != 0) {
		delete this->caret;
	}
}

void CaretController::Update() {
	Long vScrollBarWidth = 0;
	Long hScrollBarHeight = 0;
	Long statusHeight = 0;
	Long hideCaretRight;
	Long hideCaretBottom;
	Long x;
	Long y;
	Long textWidth = 2;
	if (this->notepadForm->onIsComposing == TRUE) {
		textWidth = this->notepadForm->matrix->GetWidth(128);
	}

	x = this->notepadForm->matrix->GetX(this->notepadForm->current->GetCurrent());
	y = this->notepadForm->matrix->GetY(this->notepadForm->note->GetCurrent());

	// ��ũ�ѹ� ��ġ�� ĳ���� ���� �� ������ ���� �߰� (2021.01.13)
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		vScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL);
	}

	if (this->notepadForm->onIsHorizontalScrollBar == TRUE) {
		hScrollBarHeight = GetSystemMetrics(SM_CYHSCROLL);
	}

	if (this->notepadForm->onIsStatusBar == TRUE) {
		statusHeight = GetSystemMetrics(SM_CYHSCROLL);
	}

	hideCaretRight = this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent() +
		this->notepadForm->scrollController->GetHorizontalScroll()->GetPage();
	hideCaretBottom = this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent() +
		this->notepadForm->scrollController->GetVerticalScroll()->GetPage() - this->notepadForm->matrix->GetHeight();

	this->onIsCaret = true;
	if (this->notepadForm->onIsScrolling == TRUE && ((statusHeight > 0 || hScrollBarHeight > 0) && y > hideCaretBottom)) {
		this->onIsCaret = false;
	}
	else if (this->notepadForm->onIsScrolling == TRUE && vScrollBarWidth > 0 && x > hideCaretRight) {
		this->onIsCaret = false;
	}

	if (this->notepadForm->onIsScrolling != TRUE && (this->notepadForm->onIsMoving == TRUE || !(GetKeyState(VK_CONTROL) & 0x8000)) &&
		(this->notepadForm->onIsMoving == TRUE || !(GetKeyState(VK_SHIFT) & 0x8000))) {
		if (y < this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent()) {// 1. ĳ���� ���� ������
			this->notepadForm->scrollController->GetVerticalScroll()->Move(y);
			this->notepadForm->verticalScrollBar->SetScrollPos(this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent());
		}// 2. ĳ���� �Ʒ��� ������
		else if (y + this->notepadForm->matrix->GetHeight() > this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent() + this->notepadForm->scrollController->GetVerticalScroll()->GetPage()) {
			this->notepadForm->scrollController->GetVerticalScroll()->Move(
				y - this->notepadForm->scrollController->GetVerticalScroll()->GetPage() + this->notepadForm->matrix->GetHeight()
			);
			this->notepadForm->verticalScrollBar->SetScrollPos(this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent());
		}// 3. ĳ���� ���ʿ� ������
		if (x < this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent() &&	this->notepadForm->onIsLineWrapping != TRUE) {
			this->notepadForm->scrollController->GetHorizontalScroll()->Move(
				x - this->notepadForm->scrollController->GetHorizontalScroll()->GetPage() / 5
			);
			this->notepadForm->horizontalScrollBar->SetScrollPos(this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent());
		}// 4. ĳ���� �����ʿ� ������
		else if (x > this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent() + this->notepadForm->scrollController->GetHorizontalScroll()->GetPage() &&
			this->notepadForm->onIsLineWrapping != TRUE) {
			this->notepadForm->scrollController->GetHorizontalScroll()->Move(
				x - this->notepadForm->scrollController->GetHorizontalScroll()->GetPage() + this->notepadForm->scrollController->GetHorizontalScroll()->GetPage() / 5
			);
			this->notepadForm->horizontalScrollBar->SetScrollPos(this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent());
		}
	}
	this->notepadForm->onIsMoving = FALSE;

	if (this->notepadForm->onIsComposing == TRUE) {
		x -= textWidth;
	}

	if (this->onIsCaret == true) {
		this->caret->Create(textWidth, this->notepadForm->matrix->GetHeight());
		this->caret->Move(x - this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent(),
			y - this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent());
	}
	else {
		this->caret->Hide();
	}
}

Observer* CaretController::Clone() {
	return new CaretController(*this);
}