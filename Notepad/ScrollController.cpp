//ScrollController.cpp
#include"ScrollController.h"
#include"VerticalScroll.h"
#include"HorizontalScroll.h"
#include"Scroll.h"
#include"NotepadForm.h"
#include"Matrix.h"
#include"Glyph.h"
#include<afxext.h>


ScrollController::ScrollController(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	
	Long horizontalMax;
	Long verticalMax;
	Long horizontalPage;
	Long verticalPage;
	Long horizontalUnit;
	Long verticalUnit;
	RECT rect = { 0, };
	this->notepadForm->GetClientRect(&rect);

	horizontalMax = this->notepadForm->matrix->GetMaxX();
	verticalMax = this->notepadForm->matrix->GetMaxY();
	horizontalPage = rect.right;
	verticalPage = rect.bottom;
	horizontalUnit = this->notepadForm->matrix->GetWidth(128) / 2;
	verticalUnit = this->notepadForm->matrix->GetHeight();

	this->horizontalScroll = new HorizontalScroll(0,horizontalMax,horizontalUnit,horizontalPage,0);
	this->verticalScroll = new VerticalScroll(0, verticalMax, verticalUnit, verticalPage, 0);

	dynamic_cast<Subject*>(this->notepadForm)->Attach(this);
}

ScrollController::~ScrollController() {
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}
	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}
}

void ScrollController::Update() {
	
	Long box;
	RECT rect = { 0, };
	Long verticalMax;
	Long horizontalMax;
	Long verticalPage;
	Long horizontalPage;
	Long verticalUnit;
	Long horizontalUnit;
	Long verticalCurrent;
	Long horizontalCurrent;

	Long horizontalScrollBarX;
	Long horizontalScrollBarY;
	Long horizontalScrollBarWidth;
	Long horizontalScrollBarHeight;

	Long verticalScrollBarX;
	Long verticalScrollBarY;
	Long verticalScrollBarWidth;
	Long verticalScrollBarHeight;

	Long statusBarHeight = 0;

	

	SCROLLINFO horizontalScrollInfo;
	SCROLLINFO verticalScrollInfo;

	

	this->notepadForm->onIsHorizontalScrollBar = FALSE;
	this->notepadForm->onIsVerticalScrollBar = FALSE;

	//1. ��ũ�ѹ� �ڽ��� ���̸� ���Ѵ�.
	box = GetSystemMetrics(SM_CYHSCROLL);



	//2. ������ ȭ�� ũ�⸦ ���Ѵ�.
	this->notepadForm->GetClientRect(&rect);
	//CClientDC dc(this->notepadForm);

	//3. ��ũ���� ����, ���� �ִ� ���̸� ���Ѵ�.
	horizontalMax = this->notepadForm->matrix->GetMaxX();
	verticalMax = this->notepadForm->matrix->GetMaxY();
	// ���̴� ĳ���� �� ������ �ƴ϶� �Ʒ��� �������� ��ũ�ѹٰ� ����Ƿ� ���̸� �� �� ����(2021.01.13)

	//4. �������� ����, ���� ���̸� ���Ѵ�.
	horizontalPage = rect.right;
	verticalPage = rect.bottom;

	//5. ����, ���� current ���� �д´�.
	horizontalCurrent = this->horizontalScroll->GetCurrent();
	verticalCurrent = this->verticalScroll->GetCurrent();

	// + ���¹ٰ� ������ ���� ������ ũ�⸦ ���δ�.
	if (this->notepadForm->onIsStatusBar == TRUE) {
		verticalPage -= box;
		statusBarHeight = box;
	}

	//6. ����ũ�ѹٰ� �����(���ν�ũ���� �ִ� ���̰� �������� ���α��̺��� ũ��)
	if (horizontalMax > horizontalPage) {
		//6.1 ����ũ�ѹ��� �÷��׸� �����Ѵ�.
		this->notepadForm->onIsHorizontalScrollBar = TRUE;
		//6.1. �������� ���α��̿��� �ڽ��� ���̸� ����.
		verticalPage -= box;
	}
	//7. ������ũ�ѹٰ� �����(���ν�ũ���� �ִ� ���̰� �������� ���α��̺��� ũ��)
	if (verticalMax > verticalPage) {
		//7.1 ����ũ�ѹ��� �÷��׸� �����Ѵ�.
		this->notepadForm->onIsVerticalScrollBar = TRUE;
		//7.2. �������� ���α��̿��� �ڽ��� ���̸� ����.
		horizontalPage -= box;
	}
	// 8. ���� ��ũ�ѹٰ� �����(�ѹ� �� Ȯ��) (2021.01.13)
	if (horizontalMax > horizontalPage && this->notepadForm->onIsHorizontalScrollBar != TRUE) {
		//6.1 ����ũ�ѹ��� �÷��׸� �����Ѵ�.
		this->notepadForm->onIsHorizontalScrollBar = TRUE;
		//6.1. �������� ���α��̿��� �ڽ��� ���̸� ����.
		verticalPage -= box;
	}

	//8. ����ũ�ѹٰ� �Ȼ������� ����ũ���� ���� ��ġ�� 0���� �����Ѵ�.
	if (this->notepadForm->onIsHorizontalScrollBar != TRUE) {
		horizontalCurrent = 0;
	}
	
	// + �ڵ��������̸� ���� ��ũ�ѹ� 0���� ����.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		horizontalCurrent = 0;
	}

	//9. ������ũ�ѹٰ� �Ȼ������� ������ũ���� ������ġ�� 0���� �����Ѵ�.
	if (this->notepadForm->onIsVerticalScrollBar != TRUE) {
		verticalCurrent = 0;
	}

	//10. ����, ���� ��ũ���� ������ ���Ѵ�.
	horizontalUnit = this->notepadForm->matrix->GetWidth(128) / 2;
	verticalUnit = this->notepadForm->matrix->GetHeight();

	//11. ����ũ�ѹٰ� ������ ��ũ�ѹ��� ��ġ�� �����ش�.
	if (this->notepadForm->onIsHorizontalScrollBar == TRUE) {
		horizontalScrollBarX = 0;
		horizontalScrollBarY = rect.bottom - statusBarHeight - box;
		horizontalScrollBarWidth = horizontalPage;
		horizontalScrollBarHeight = box;
	}

	//12. ������ũ�ѹٰ� ������ ��ũ�ѹ��� ��ġ�� �����ش�.
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		verticalScrollBarX = rect.right - box;
		verticalScrollBarY = 0;
		verticalScrollBarWidth = box;
		verticalScrollBarHeight = verticalPage;
	}

	//14. ������ ��ũ�ѵ��� �����.
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}

	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}

	// + ��ũ���� ���� ��ġ ���� �����Ѵ�.(2021.02.03)
	if (horizontalCurrent >= horizontalMax - horizontalPage && horizontalMax > horizontalPage) {
		horizontalCurrent = horizontalMax - horizontalPage + 2;
	}

	if (verticalCurrent >= verticalMax - verticalPage && verticalMax > verticalPage) {
		verticalCurrent = verticalMax - verticalPage + 2;
	}

	//15. ��ũ���� ������ ���� �����Ѵ�.
	this->horizontalScroll = new HorizontalScroll(0,horizontalMax,horizontalUnit,horizontalPage,horizontalCurrent);
	this->verticalScroll = new VerticalScroll(0,verticalMax,verticalUnit,verticalPage,verticalCurrent);

	//16. ��ũ�ѿ� ������ �����Ѵ�
	horizontalScrollInfo.cbSize = sizeof(SCROLLINFO);
	horizontalScrollInfo.fMask = SIF_ALL;
	horizontalScrollInfo.nMin = this->horizontalScroll->GetMin();
	horizontalScrollInfo.nMax = this->horizontalScroll->GetMax();
	horizontalScrollInfo.nPage = this->horizontalScroll->GetPage();
	horizontalScrollInfo.nPos = this->horizontalScroll->GetCurrent();
	horizontalScrollInfo.nTrackPos = 2;

	verticalScrollInfo.cbSize = sizeof(SCROLLINFO);
	verticalScrollInfo.fMask = SIF_ALL;
	verticalScrollInfo.nMin = this->verticalScroll->GetMin();
	verticalScrollInfo.nMax = this->verticalScroll->GetMax();
	verticalScrollInfo.nPage = this->verticalScroll->GetPage();
	verticalScrollInfo.nPos = this->verticalScroll->GetCurrent();
	verticalScrollInfo.nTrackPos = 2;

	//17. ���� ��ũ�ѹٸ� �����ش�.
	this->notepadForm->horizontalScrollBar->SetScrollInfo(&horizontalScrollInfo, TRUE); // ������ �����ϴ� ������ ���� (2021.01.13)
	if (this->notepadForm->onIsHorizontalScrollBar == TRUE) {
		this->notepadForm->horizontalScrollBar->SetWindowPos(NULL, horizontalScrollBarX, horizontalScrollBarY, horizontalScrollBarWidth, horizontalScrollBarHeight, SWP_DRAWFRAME);
		this->notepadForm->horizontalScrollBar->ShowScrollBar(TRUE);
	}
	else {
		this->notepadForm->horizontalScrollBar->ShowScrollBar(FALSE);
	}
	//18. ���� ��ũ�ѹٸ� �����ش�.
	this->notepadForm->verticalScrollBar->SetScrollInfo(&verticalScrollInfo, TRUE); // ������ �����ϴ� ������ ���� (2021.01.13)
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		this->notepadForm->verticalScrollBar->SetWindowPos(NULL, verticalScrollBarX,verticalScrollBarY, verticalScrollBarWidth,
			verticalScrollBarHeight, SWP_DRAWFRAME);
		this->notepadForm->verticalScrollBar->ShowScrollBar(TRUE);
	}
	else {
		this->notepadForm->verticalScrollBar->ShowScrollBar(FALSE);
	}

	//19. ����, ������ũ�ѹٰ� ���ÿ� ������ ������ �ڽ��� �����ִ´�.
	if (this->notepadForm->onIsHorizontalScrollBar == TRUE && this->notepadForm->onIsVerticalScrollBar == TRUE) {
		// X = VerticalScrollBar�� X, Y = HorizontalScrollBar�� Y������ ����(2021.01.13)
		this->notepadForm->sizeBox->SetWindowPos(NULL, verticalScrollBarX, horizontalScrollBarY, box, box, SWP_DRAWFRAME);
		this->notepadForm->sizeBox->ShowScrollBar(TRUE);
	}
	else {
		this->notepadForm->sizeBox->ShowScrollBar(FALSE);
	}
}

Observer* ScrollController::Clone() {
	return new ScrollController(*this);
}
// Scroll���� �д� ���� �߰� (2021.01.13)
Scroll* ScrollController::GetHorizontalScroll() {
	return this->horizontalScroll;
}

Scroll* ScrollController::GetVerticalScroll() {
	return this->verticalScroll;
}



#if 0
void ScrollController::Update() {


	Long verticalMax;
	Long horizontalMax;
	Long verticalPage;
	Long horizontalPage;
	Long verticalUnit;
	Long horizontalUnit;
	Long verticalCurrent;
	Long horizontalCurrent;
	RECT rect = { 0, };
	RECT statusBarRect = { 0, };
	SCROLLINFO hScrollInfo;
	SCROLLINFO vScrollInfo;
	CRect  hScrollRect = { 0, };
	CRect  vScrollRect = { 0, };
	Long hScrollHeight;
	Long vScrollWidth;






	hScrollHeight = GetSystemMetrics(SM_CYHSCROLL);
	vScrollWidth = GetSystemMetrics(SM_CXHSCROLL);
	this->notepadForm->statusBar->GetItemRect(0, &statusBarRect);
	this->notepadForm->GetClientRect(&rect);
	CClientDC dc(this->notepadForm);

	horizontalMax = this->notepadForm->matrix->GetMaxX();
	horizontalUnit = this->notepadForm->matrix->GetWidth(128) * 5;
	horizontalPage = rect.right;


	//������ũ�ѹٰ� �ָ� ���� page�� ���� �پ���� �Ѵ�.
	verticalMax = this->notepadForm->matrix->GetMaxY();
	verticalPage = rect.bottom;

#if 0
	? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?
		if (verticalMax > verticalPage) {
			horizontalPage -= hScrollHeight;
		}
#endif


	if (this->notepadForm->onIsAutomaticCarriageReturning == TRUE) {
		horizontalCurrent = 0;
		//this->notepadForm->hScrollBar->ShowScrollBar(FALSE);
	}

	else {
		horizontalCurrent = this->horizontalScroll->GetCurrent();
		if (horizontalMax < horizontalPage) {//��ũ�� ������ ��� ó������
			horizontalCurrent = 0;
		}
	}



	//verticalMax = this->notepadForm->matrix->GetMaxY(); ������ ����

	verticalUnit = this->notepadForm->matrix->GetHeight();
	//verticalPage = rect.bottom; ������ ����
	//����ũ�ѹٰ� ����� page�� ���� �پ���� �Ѵ�.
	if (horizontalMax > horizontalPage) {
		verticalPage -= hScrollHeight;
	}
	verticalCurrent = this->verticalScroll->GetCurrent();
	if (verticalMax < verticalPage) {//��ũ�� ������ ��� ó������
		verticalCurrent = 0;
	}

	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}


	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}


	//��ũ�ѹٰ� ����� ��ŭ page�� ���� �پ�����.

	this->horizontalScroll = new HorizontalScroll(this, horizontalCurrent, horizontalUnit, horizontalPage - vScrollWidth, 0, horizontalMax);


	if (this->notepadForm->onIsShowingStatusBar == TRUE) {
		this->verticalScroll = new VerticalScroll(this, verticalCurrent, verticalUnit, verticalPage - hScrollHeight - statusBarRect.bottom, 0, verticalMax);
	}
	else {
		this->verticalScroll = new VerticalScroll(this, verticalCurrent, verticalUnit, verticalPage - hScrollHeight, 0, verticalMax);
	}



	hScrollInfo.cbSize = sizeof(SCROLLINFO);
	hScrollInfo.fMask = SIF_ALL;
	hScrollInfo.nMin = this->horizontalScroll->GetMin();
	hScrollInfo.nMax = this->horizontalScroll->GetMax();
	hScrollInfo.nPage = this->horizontalScroll->GetPage();
	hScrollInfo.nPos = this->horizontalScroll->GetCurrent();

	hScrollInfo.nTrackPos = 2;

	vScrollInfo.cbSize = sizeof(SCROLLINFO);
	vScrollInfo.fMask = SIF_ALL;
	vScrollInfo.nMin = this->verticalScroll->GetMin();
	vScrollInfo.nMax = this->verticalScroll->GetMax();
	vScrollInfo.nPage = this->verticalScroll->GetPage();
	vScrollInfo.nPos = this->verticalScroll->GetCurrent();
	vScrollInfo.nTrackPos = 2;

	if (this->horizontalScroll->GetMax() > this->horizontalScroll->GetPage() && this->notepadForm->onIsAutomaticCarriageReturning != TRUE) {
		this->notepadForm->hOnIsScrolling = TRUE;

		if (this->notepadForm->onIsShowingStatusBar == FALSE) {//����ǥ������ �Ⱥ��̸�
			if (this->notepadForm->vOnIsScrolling == TRUE) {//����ũ�Ѱ� ������ũ���� ���ÿ� �����
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight, rect.right - hScrollHeight, hScrollHeight, SWP_DRAWFRAME);

			}
			else {//����ũ�Ѹ� �����
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight, rect.right, hScrollHeight, SWP_DRAWFRAME);
			}
		}
		else {//����ǥ������ ���̸�

			if (this->notepadForm->vOnIsScrolling == TRUE) {//����ũ�Ѱ� ������ũ���� ���ÿ� �����
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight - statusBarRect.bottom, rect.right - hScrollHeight, hScrollHeight, SWP_DRAWFRAME);



				dc.Rectangle(rect.right - vScrollWidth, rect.bottom - hScrollHeight - statusBarRect.bottom, rect.right, rect.bottom - statusBarRect.bottom);


			}
			else {//����ũ�Ѹ� �����
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight - statusBarRect.bottom, rect.right, hScrollHeight, SWP_DRAWFRAME);
			}


		}
		this->notepadForm->hScrollBar->ShowScrollBar(TRUE);
		this->notepadForm->hScrollBar->SetScrollInfo(&hScrollInfo, TRUE);
	}

	else {
		this->notepadForm->hOnIsScrolling = FALSE;
		this->notepadForm->hScrollBar->ShowScrollBar(FALSE);
		this->notepadForm->hScrollBar->SetScrollInfo(&hScrollInfo, TRUE);//
	}




	if (this->verticalScroll->GetMax() > this->verticalScroll->GetPage()) {
		this->notepadForm->vOnIsScrolling = TRUE;
		this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom, SWP_DRAWFRAME);

		if (this->notepadForm->onIsShowingStatusBar == FALSE) {//����ǥ������ �Ⱥ��̸�
			if (this->notepadForm->hOnIsScrolling == TRUE) {//����, ���� ��ũ���� ���ÿ� �����
				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom - vScrollWidth, SWP_DRAWFRAME);
			}
			else {
				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom, SWP_DRAWFRAME);

			}
		}
		else {//����ǥ������ ���̸�

			if (this->notepadForm->hOnIsScrolling == TRUE) {//����, ���� ��ũ���� ���ÿ� �����

				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom - vScrollWidth - statusBarRect.bottom, SWP_DRAWFRAME);

			}
			else {
				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom, SWP_DRAWFRAME);

			}

		}
		this->notepadForm->vScrollBar->ShowScrollBar(TRUE);
		this->notepadForm->vScrollBar->SetScrollInfo(&vScrollInfo, TRUE);

	}

	else {
		this->notepadForm->vOnIsScrolling = FALSE;
		this->notepadForm->vScrollBar->ShowScrollBar(FALSE);
		this->notepadForm->vScrollBar->SetScrollInfo(&vScrollInfo, TRUE);
	}


}
#endif
