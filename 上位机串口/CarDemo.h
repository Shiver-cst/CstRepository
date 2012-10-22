// CarDemo.h : main header file for the CARDEMO application
//

#if !defined(AFX_CARDEMO_H__123AE72A_1DDE_4C75_9835_4769D899F562__INCLUDED_)
#define AFX_CARDEMO_H__123AE72A_1DDE_4C75_9835_4769D899F562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCarDemoApp:
// See CarDemo.cpp for the implementation of this class
//

class CCarDemoApp : public CWinApp
{
public:
	CCarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCarDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDEMO_H__123AE72A_1DDE_4C75_9835_4769D899F562__INCLUDED_)
