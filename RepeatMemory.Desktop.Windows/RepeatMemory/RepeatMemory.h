// RepeatMemory.h : main header file for the REPEATMEMORY application
//

#if !defined(AFX_REPEATMEMORY_H__0709BCA8_3DA1_465A_8F84_8C4D5BCD41F2__INCLUDED_)
#define AFX_REPEATMEMORY_H__0709BCA8_3DA1_465A_8F84_8C4D5BCD41F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryApp:
// See RepeatMemory.cpp for the implementation of this class
//

class CRepeatMemoryApp : public CWinApp
{
public:
	CRepeatMemoryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepeatMemoryApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRepeatMemoryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPEATMEMORY_H__0709BCA8_3DA1_465A_8F84_8C4D5BCD41F2__INCLUDED_)
