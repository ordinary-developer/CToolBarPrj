# Steps for creating a project with CToolBar (under Visual Studio 2019 Community Edition)

1.  Start Visual Studio, click on the "Create a new project" button.

2.  Select the "MFC App" template in the project template selection dialog and click the "Next" button.

3.  Set the "Project name" field to "CToolBarPrj";
    set the "Location" field to where you want to create the project;
    set the flag "Place solution and project in the same directory";
    click the "Create" button.
    
4.  In the "MFC Application - Application Type Options" dialog set the next options:
    in the "Application type" tab set the "Project style" field to "MFC standard" (the "Visual style and colors" field must be automatically set to "Windows Native/Default"; click the "Finish" button.
    (Such settings are necessary for the following:
    The project's "App" class must be inherited from CWinApp (not CWinAppEx), the project's "MainFrame" class must be inherited from CFrameWnd (not CMDIFrameWndEx)).
    
5.  In the opened Visual Studio open the "MainFrm.h" and add at the beginning of the file (just after the line "pragma once") the next code:
    ```
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
    ```
   
6.  Then in MainFrm.h just after the beginning of declaration (just after the opening curly brace) add the next line:
    ```
    friend CMyToolBar;
    ```
    
7.  Then in MainFrm.h instead of the line: 
    ```
    CToolBar          m_wndToolBar;
    ```
    add the line:
    ```
    CMyToolBar        m_wndToolBar;
    ```
 
8.  Then in the MainFrm.h just under the 'CMyToolBar        m_wndToolBar' line add the next line:
    ```
    CComboBox         m_comboBox;
    ```
   
9.  Then open the MainFrm.cpp file in Visual Studio and at the beginning of the file
    just after the next code:
    ```
    #ifdef _DEBUG
    #define new DEBUG_NEW
    #endif
    ```
   
    add the next code:
    ```
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

	    if (pMainFrame != NULL && ::IsWindow(pMainFrame->m_combBox.m_hWnd))
	    {
		    PostMessage(WM_USER + 3, 1);
	    }
    }
    ```
   
10. Then in CMainFrame::OnCreate after the line:
    ```
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
    ```
    
    add the next lines:
    ```
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
    ```
    
11. Save all and close Visual Studio.

12. Open the "Resource.h" file in an ordinary text editor (Notepad, Notepad++, etc.) and after all lines with ID add the next line:
    ```
    #define ID_COMBOBOX                 132
    ```
    (The actual ID can be another, but it must be unique across Resource.h).
    Save changes and close the file.

13. Open the project .rc file in an ordinary text editor and change the lines:
    ```
    IDR_MAINFRAME TOOLBAR 16, 15
    BEGIN
        BUTTON      ID_FILE_NEW
        BUTTON      ID_FILE_OPEN
        BUTTON      ID_FILE_SAVE
        SEPARATOR
        BUTTON      ID_EDIT_CUT
        BUTTON      ID_EDIT_COPY
        BUTTON      ID_EDIT_PASTE
        SEPARATOR
        BUTTON      ID_FILE_PRINT
        BUTTON      ID_APP_ABOUT
    END
    ```
    
    to the next lines (the order of elements in important):
    ```
    IDR_MAINFRAME TOOLBAR 16, 15
    BEGIN
        BUTTON      ID_FILE_NEW
        BUTTON      ID_FILE_OPEN
        BUTTON      ID_FILE_SAVE
        SEPARATOR
        BUTTON      ID_EDIT_CUT
        BUTTON      ID_EDIT_COPY
        BUTTON      ID_EDIT_PASTE
        SEPARATOR
        BUTTON      ID_COMBOBOX
        BUTTON      ID_FILE_PRINT
        BUTTON      ID_APP_ABOUT
    END
    ```
    Save changes and close the file.
    
14. Open the "res\Toolbar.bmp" file in any graphic editor (Paint, Paint.NET, etc.)
    and insert an arbitrary pictogram (with size of 16 px by width and 15 px by height) (with arbitrary contents (for example a black rectangle)) between the 6-th and 7-th element (pictogram), so the whole bar image will be wider by 16 px.
    Save changes and close the file.
    
15. Open Visual Studio with the current project and build the project.
