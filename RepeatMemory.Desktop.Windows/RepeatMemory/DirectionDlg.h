#if !defined(AFX_DIRECTIONDLG_H__6FE9C3D6_7221_4049_85C8_80059E289948__INCLUDED_)
#define AFX_DIRECTIONDLG_H__6FE9C3D6_7221_4049_85C8_80059E289948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\BasicModule\\constant.h"
#include <set>
#include <string>
using namespace std;

// DirectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirectionDlg dialog

class CDirectionDlg : public CDialog
{
// Construction
public:
	CDirectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirectionDlg)
	enum { IDD = IDD_DIRECTION };
	CComboBox	m_GroupSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirectionDlg)
	afx_msg void OnBackward();
	afx_msg void OnForward();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeGroupset();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	char SrcTitle[WORDLENGTH];
	char TgtTitle[WORDLENGTH];
	char GrpTitle[WORDLENGTH];
	set<string> * GroupSet;
public:
	bool Forward;
	char GroupName[WORDLENGTH];
	void SetTitle(const char * source, const char * target)
	{
		strcpy(SrcTitle,source);
		strcpy(TgtTitle,target);
	}
	void SetGroupSet(const char * grptitle,set<string> & groupset)
	{
		strcpy(GrpTitle,grptitle);
		GroupSet=&groupset;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTIONDLG_H__6FE9C3D6_7221_4049_85C8_80059E289948__INCLUDED_)
