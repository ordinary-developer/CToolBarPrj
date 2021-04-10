
// CToolBarPrjView.h : interface of the CCToolBarPrjView class
//

#pragma once


class CCToolBarPrjView : public CView
{
protected: // create from serialization only
	CCToolBarPrjView() noexcept;
	DECLARE_DYNCREATE(CCToolBarPrjView)

// Attributes
public:
	CCToolBarPrjDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCToolBarPrjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CToolBarPrjView.cpp
inline CCToolBarPrjDoc* CCToolBarPrjView::GetDocument() const
   { return reinterpret_cast<CCToolBarPrjDoc*>(m_pDocument); }
#endif

