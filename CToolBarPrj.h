
// CToolBarPrj.h : main header file for the CToolBarPrj application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCToolBarPrjApp:
// See CToolBarPrj.cpp for the implementation of this class
//

class CCToolBarPrjApp : public CWinApp
{
public:
	CCToolBarPrjApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCToolBarPrjApp theApp;
