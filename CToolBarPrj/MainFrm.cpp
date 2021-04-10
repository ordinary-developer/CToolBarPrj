
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "CToolBarPrj.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyToolBar
const int COMBOBOX_POS = 8;
const int COMBOBOX_WIDTH = 180;

BEGIN_MESSAGE_MAP(CMyToolBar, CToolBar)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_MESSAGE(WM_USER + 3, OnCheckUpdate)
END_MESSAGE_MAP()

CMyToolBar::CMyToolBar() {}

void CMyToolBar::OnPaint()
{
	Default();

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame != NULL && ::IsWindow(pMainFrame->m_comboBox.m_hWnd))
	{
		PostMessage(WM_USER + 3, 0);
	}

}

LONG CMyToolBar::OnCheckUpdate(UINT uParam, LONG lParam)
{
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	if (pMainFrame != NULL && ::IsWindow(pMainFrame->m_comboBox.m_hWnd))
	{
		CRect toolBarRect, comboBoxRect;
		GetClientRect(&toolBarRect);
		GetItemRect(COMBOBOX_POS, &comboBoxRect);

		bool bChanged = false;
		if (toolBarRect.Height() > comboBoxRect.Height() * 2)
		{
			if (comboBoxRect.Width() != COMBOBOX_WIDTH)
			{
				SetButtonInfo(COMBOBOX_POS, ID_COMBOBOX, TBBS_SEPARATOR, COMBOBOX_WIDTH);

				CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
				bChanged = true;
			}
		}
		else
		{
			if (comboBoxRect.Width() != COMBOBOX_WIDTH)
			{
				SetButtonInfo(COMBOBOX_POS, ID_COMBOBOX, TBBS_SEPARATOR, COMBOBOX_WIDTH);
				CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
				bChanged = true;
			}
		}

		if (bChanged || uParam == 1)
		{
			CRect newComboBoxRect;
			GetItemRect(COMBOBOX_POS, &newComboBoxRect);
			pMainFrame->m_comboBox.MoveWindow(newComboBoxRect, FALSE);
			pMainFrame->ShowControlBar(this, FALSE, FALSE);
			pMainFrame->ShowControlBar(this, TRUE, FALSE);
		}
	}

	return 0L;
}

void CMyToolBar::OnMove(int x, int y)
{
	CToolBar::OnMove(x, y);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame != NULL && ::IsWindow(pMainFrame->m_comboBox.m_hWnd))
	{
		PostMessage(WM_USER + 3, 1);
	}
}

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	m_wndToolBar.SetButtonInfo(COMBOBOX_POS, ID_COMBOBOX, TBBS_SEPARATOR, COMBOBOX_WIDTH);

	CRect comboBoxRect;
	m_wndToolBar.GetItemRect(COMBOBOX_POS, &comboBoxRect);
	comboBoxRect.bottom = comboBoxRect.top + comboBoxRect.Height() * 10;

	if (!m_comboBox.Create(CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		comboBoxRect, &m_wndToolBar, ID_COMBOBOX)
		)
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

	m_comboBox.AddString(_T("Item 01"));
	m_comboBox.AddString(_T("Item 02"));
	m_comboBox.AddString(_T("Item 02"));
	m_comboBox.SetCurSel(0);

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

