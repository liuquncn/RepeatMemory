// RepeatMemoryDlg.h : header file
//

#if !defined(AFX_REPEATMEMORYDLG_H__ED504BA1_65A7_488F_AAC1_0FFE0F1D7C81__INCLUDED_)
#define AFX_REPEATMEMORYDLG_H__ED504BA1_65A7_488F_AAC1_0FFE0F1D7C81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\CSVProcessor\\CSVProcessor.h"
#include <set>

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryDlg dialog

const int RECORDSIZE=100;

class CRepeatMemoryDlg : public CDialog
{
// Construction
public:
	CRepeatMemoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRepeatMemoryDlg)
	enum { IDD = IDD_REPEATMEMORY_DIALOG };
	CRichEditCtrl	TargetCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepeatMemoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRepeatMemoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnChangeHint();
	afx_msg void OnNext();
	afx_msg void OnShowhint();
	afx_msg void OnStart();
	afx_msg void OnRecord();
	afx_msg void OnEdit();
	afx_msg void OnAnswer();
	afx_msg void OnSelect();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnEnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CSVLine Title;
	CSVData Data;
	CSVData Record;

	char RecordPath[PATHLENGTH];
	fstream RecordFile;
	CSVData::iterator RecordIter;

	char DataPath[PATHLENGTH];
	fstream DataFile;
	CSVData::iterator DataIter;

	vector<bool> Pass;
	vector<bool>::iterator PassIter;

	set<string> GroupSet;
	string Group;

	char Source[LINELENGTH];
	char Target[LINELENGTH];
	char Answer[LINELENGTH];
	bool Forward;
	bool Retry;

	time_t Timer;
	int FailNumber;

	bool Working;

public:
	void readData();
	void readRecord();
	void writeRecord();
	void display();
	void normalize(char * text);
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPEATMEMORYDLG_H__ED504BA1_65A7_488F_AAC1_0FFE0F1D7C81__INCLUDED_)
