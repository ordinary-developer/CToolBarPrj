
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

class CMyToolBar : public CToolBar
{
public:
	CMyToolBar();

protected:
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg LONG OnCheckUpdate(UINT uParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};

class CMainFrame : public CMDIFrameWnd
{
	friend CMyToolBar;

	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame() noexcept;

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMyToolBar        m_wndToolBar;
	CComboBox         m_comboBox;
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


