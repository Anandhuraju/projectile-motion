// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// patterngeneratorView.cpp : implementation of the CpatterngeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "patterngenerator.h"
#endif

#include "patterngeneratorDoc.h"
#include "patterngeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpatterngeneratorView

IMPLEMENT_DYNCREATE(CpatterngeneratorView, CView)

BEGIN_MESSAGE_MAP(CpatterngeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CpatterngeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CpatterngeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON3_STOP, &CpatterngeneratorView::OnButton3Stop)
	ON_COMMAND(ID_BUTTON_RESUME, &CpatterngeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CpatterngeneratorView construction/destruction

CpatterngeneratorView::CpatterngeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;

}

CpatterngeneratorView::~CpatterngeneratorView()
{
}

BOOL CpatterngeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CpatterngeneratorView drawing

void CpatterngeneratorView::OnDraw(CDC* pDC)
{
	CpatterngeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString strCounter;
	//strCounter.Format(L"The Counter is %d", m_iCounter);
	pDC->TextOut(100, 100, strCounter);
	pDC->MoveTo(100, 50);
	pDC->LineTo(100, 200);
	pDC->MoveTo(700, 200);
	pDC->LineTo(100, 200);
	if (m_iCounter < 900)
	{
		for (int i = 0; i < m_PointArray.GetSize() - 2; i++)

		{

			pDC->MoveTo(m_PointArray[i].x, m_PointArray[i].y);
			pDC->LineTo(m_PointArray[i + 1].x, m_PointArray[i + 1].y);

		}
	}

	// TODO: add draw code for native data here
}


// CpatterngeneratorView printing


void CpatterngeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CpatterngeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CpatterngeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CpatterngeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CpatterngeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CpatterngeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CpatterngeneratorView diagnostics

#ifdef _DEBUG
void CpatterngeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CpatterngeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpatterngeneratorDoc* CpatterngeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpatterngeneratorDoc)));
	return (CpatterngeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CpatterngeneratorView message handlers


void CpatterngeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	
	m_pCurrentThread = AfxBeginThread(CpatterngeneratorView::StartTread, this);
}


void CpatterngeneratorView::OnButton3Stop()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->SuspendThread();

}


void CpatterngeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CpatterngeneratorView::StartTread(LPVOID Para)
{
	// TODO: Add your implementation code here.
	CpatterngeneratorView* pview = (CpatterngeneratorView*)Para;
	CPoint mypoint(0, 0);
	while (1)
	{
		mypoint.y = 200 + 50 * sin(pview->m_iCounter);
		mypoint.x = 100 + pview->m_iCounter;
		pview->m_PointArray.Add(mypoint);
		pview -> m_iCounter = pview -> m_iCounter + 100 ;
		pview->Invalidate();
		Sleep(1000);
	}
	

	return 0;
}
