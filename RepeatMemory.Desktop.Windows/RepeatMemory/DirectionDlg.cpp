// DirectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepeatMemory.h"
#include "DirectionDlg.h"
#include "..\\BasicModule\\function.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectionDlg dialog


CDirectionDlg::CDirectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirectionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	*SrcTitle=*TgtTitle=0;
}


void CDirectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectionDlg)
	DDX_Control(pDX, IDC_GROUPSET, m_GroupSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirectionDlg, CDialog)
	//{{AFX_MSG_MAP(CDirectionDlg)
	ON_BN_CLICKED(IDC_BACKWARD, OnBackward)
	ON_BN_CLICKED(IDC_FORWARD, OnForward)
	ON_CBN_SELCHANGE(IDC_GROUPSET, OnSelchangeGroupset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectionDlg message handlers

void CDirectionDlg::OnBackward() 
{
	// TODO: Add your control notification handler code here
	Forward=false;
}

void CDirectionDlg::OnForward() 
{
	// TODO: Add your control notification handler code here
	Forward=true;
}

BOOL CDirectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton *)GetDescendantWindow(IDC_FORWARD))->SetCheck(1);
	char forward[LINELENGTH];
	char backward[LINELENGTH];
	if (*SrcTitle && *TgtTitle)
	{
		sprintf(forward,"%s -> %s",SrcTitle,TgtTitle);
		sprintf(backward,"%s -> %s",TgtTitle,SrcTitle);
	}
	GetDescendantWindow(IDC_FORWARD)->SetWindowText(forward);
	GetDescendantWindow(IDC_BACKWARD)->SetWindowText(backward);
	GetDescendantWindow(IDC_GRPTITLE)->SetWindowText(GrpTitle);
	((CButton *)GetDescendantWindow(IDC_FORWARD))->SetCheck(Forward==true);
	((CButton *)GetDescendantWindow(IDC_BACKWARD))->SetCheck(Forward==false);
	set<string>::iterator iter;
	for (iter=GroupSet->begin();iter!=GroupSet->end();iter++)
	{
		m_GroupSet.AddString(iter->data());
	}
	m_GroupSet.SetCurSel(m_GroupSet.FindString(-1,GroupName));	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDirectionDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (*GroupName==0)
	{
		message("请选择一组记录。");
		return;
	}
	CDialog::OnOK();
}

void CDirectionDlg::OnSelchangeGroupset() 
{
	// TODO: Add your control notification handler code here
	m_GroupSet.GetLBText(m_GroupSet.GetCurSel(),GroupName);	
}

void CDirectionDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (*GroupName==0)
		strcpy(GroupName,(*GroupSet->begin()).data());
	CDialog::OnCancel();
}
