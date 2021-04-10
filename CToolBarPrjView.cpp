
// CToolBarPrjView.cpp : implementation of the CCToolBarPrjView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CToolBarPrj.h"
#endif

#include "CToolBarPrjDoc.h"
#include "CToolBarPrjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCToolBarPrjView

IMPLEMENT_DYNCREATE(CCToolBarPrjView, CView)

BEGIN_MESSAGE_MAP(CCToolBarPrjView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCToolBarPrjView construction/destruction

CCToolBarPrjView::CCToolBarPrjView() noexcept
{
	// TODO: add construction code here

}

CCToolBarPrjView::~CCToolBarPrjView()
{
}

BOOL CCToolBarPrjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCToolBarPrjView drawing

void CCToolBarPrjView::OnDraw(CDC* /*pDC*/)
{
	CCToolBarPrjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCToolBarPrjView printing

BOOL CCToolBarPrjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCToolBarPrjView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCToolBarPrjView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCToolBarPrjView diagnostics

#ifdef _DEBUG
void CCToolBarPrjView::AssertValid() const
{
	CView::AssertValid();
}

void CCToolBarPrjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCToolBarPrjDoc* CCToolBarPrjView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCToolBarPrjDoc)));
	return (CCToolBarPrjDoc*)m_pDocument;
}
#endif //_DEBUG


// CCToolBarPrjView message handlers
