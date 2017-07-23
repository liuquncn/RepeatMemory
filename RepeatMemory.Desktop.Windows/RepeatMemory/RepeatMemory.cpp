// RepeatMemory.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RepeatMemory.h"
#include "RepeatMemoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryApp

BEGIN_MESSAGE_MAP(CRepeatMemoryApp, CWinApp)
	//{{AFX_MSG_MAP(CRepeatMemoryApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryApp construction

CRepeatMemoryApp::CRepeatMemoryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRepeatMemoryApp object

CRepeatMemoryApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryApp initialization

BOOL CRepeatMemoryApp::InitInstance()
{
	AfxEnableControlContainer();
	AfxInitRichEdit();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}



	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}



	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CRepeatMemoryDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

/*	
CRepeatMemoryModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

LONG CRepeatMemoryModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CRepeatMemoryModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
LPCTSTR CRepeatMemoryModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}
*/

int CRepeatMemoryApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

