// RepeatMemoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RepeatMemory.h"
#include "RepeatMemoryDlg.h"
#include "DirectionDlg.h"
#include "RecordDlg.h"
#include "..\\BasicModule\function.h"

#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\\BasicModule\\code.h"
#include "..\\BasicModule\\error.h"

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryDlg dialog

CRepeatMemoryDlg::CRepeatMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRepeatMemoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRepeatMemoryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRepeatMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRepeatMemoryDlg)
	DDX_Control(pDX, IDC_TARGET, TargetCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRepeatMemoryDlg, CDialog)
	//{{AFX_MSG_MAP(CRepeatMemoryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_HINT, OnChangeHint)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_SHOWHINT, OnShowhint)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_RECORD, OnRecord)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_ANSWER, OnAnswer)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_END, OnEnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepeatMemoryDlg message handlers

BOOL CRepeatMemoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	Forward=true;
	Group="";

	Working=false;

	CHARFORMAT cf;
	TargetCtrl.GetDefaultCharFormat(cf);
	cf.bCharSet=GB2312_CHARSET;
	cf.cbSize=sizeof(cf);
	cf.yHeight=20*14;
	strcpy(cf.szFaceName,"宋体");
	TargetCtrl.SetDefaultCharFormat(cf);

	display();
	GetDescendantWindow(IDC_PATH)->SetWindowText("请选择一个文件");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRepeatMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRepeatMemoryDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRepeatMemoryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRepeatMemoryDlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(true);
	dialog.m_ofn.lpstrFilter="CSV Files\0*.csv\0";
	dialog.m_ofn.lpstrInitialDir=".";
	dialog.DoModal();
	CString filename=dialog.GetPathName();
	if (filename.IsEmpty()) return;

    char drive[FILENAMELENGTH];
    char dir[FILENAMELENGTH];
    char name[FILENAMELENGTH];
    char ext[FILENAMELENGTH];
    _splitpath(filename,drive,dir,name,ext );

	GetDescendantWindow(IDC_PATH)->SetWindowText(name);
	strcpy(DataPath,filename);
	_makepath(RecordPath,drive,dir,name,".rcd");

	readData();

	char namedirection[FILENAMELENGTH];
	sprintf(namedirection,"%s / 共%d项",name,Data.size());
	GetDescendantWindow(IDC_PATH)->SetWindowText(namedirection);

	OnSelect();
}

void CRepeatMemoryDlg::OnSelect() 
{
	// TODO: Add your control notification handler code here
	CDirectionDlg directiondlg;
	directiondlg.SetTitle(Title[1].data(),Title[2].data());
	directiondlg.SetGroupSet(Title[0].data(),GroupSet);
	directiondlg.Forward=Forward;
	strcpy(directiondlg.GroupName,Group.data());
	directiondlg.DoModal();
	Forward=directiondlg.Forward;
	Group=directiondlg.GroupName;

	readRecord();

	int size=0;
	CSVData::iterator iter;
	for (iter=Data.begin();iter!=Data.end();iter++)
	{
		if (iter->size()<3) continue;
		if ((*iter)[0]==Group) size++;
	}
	if (size==0)
		error("CRepeatMemoryDlg::OnBrowse(): 该组记录为空。");

	char namedirection[FILENAMELENGTH];
	sprintf(namedirection,"组别：%s 共%d项",Group.data(),size);

	GetDescendantWindow(IDC_GROUP)->SetWindowText(namedirection);

	GetDescendantWindow(IDC_STATIC_SOURCE)->SetWindowText((Title[Forward?1:2]+"：").data());
	GetDescendantWindow(IDC_STATIC_TARGET)->SetWindowText((Title[Forward?2:1]+"：").data());
	GetDescendantWindow(IDC_HINT)->SetWindowText("");
	display();

	Retry=false;
}

void CRepeatMemoryDlg::OnChangeHint() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRepeatMemoryDlg::readData()
{
	DataFile.clear();
	DataFile.open(DataPath,ios::in|ios::binary);
	if (!DataFile) error("CRepeatMemoryDlg::readData(): DataFile cannot open.");
	Title.read(DataFile);
	Data.read(DataFile);
	DataFile.close();

	GroupSet.clear();
	CSVData::iterator dataiter;
	for (dataiter=Data.begin();dataiter!=Data.end();dataiter++)
	{
		if (!(*dataiter)[1].empty() && !(*dataiter)[2].empty())
			GroupSet.insert((*dataiter)[0]);
	}

	Pass.resize(Data.size());
	for (PassIter=Pass.begin();PassIter!=Pass.end();PassIter++) *PassIter=false;
}

void CRepeatMemoryDlg::readRecord()
{
	FailNumber=0;
	time(&Timer);
	struct tm * timestruct;
	timestruct=localtime(&Timer);
	char datetext[LINELENGTH];
	sprintf(datetext,"%04d-%02d-%02d",
			timestruct->tm_year+1900,
			timestruct->tm_mon+1,
			timestruct->tm_mday);

	RecordFile.clear();
	RecordFile.open(RecordPath,ios::in|ios::binary);
	if (!RecordFile)
	{
		Record.clear();
	}
	else
	{
		Record.read(RecordFile);
	}
	RecordFile.close();
	for (RecordIter=Record.begin();RecordIter!=Record.end();RecordIter++)
	{
		if ((*RecordIter)[0]==Group && (*RecordIter)[1]==datetext) break;
	}
	if (RecordIter==Record.end())
	{
		CSVLine line;
		line.resize(6);
		line[0]=Group;
		line[1]=datetext;
		Record.push_back(line);
		RecordIter=Record.end();
		RecordIter--;
	}
	else RecordIter->resize(6);

	PassIter=Pass.begin();
	DataIter=Data.begin();
	while ((*DataIter)[0]!=Group)
	{
		DataIter++;
		PassIter++;
	}
}

void CRepeatMemoryDlg::writeRecord()
{
	if (Record.size()>RECORDSIZE)
		error("CRepeatMemoryDlg::writeRecord(): the size of history records is too long.");
	RecordFile.clear();
	RecordFile.open(RecordPath,ios::out|ios::trunc|ios::binary);
	Record.write(RecordFile);
	RecordFile.close();
}

void CRepeatMemoryDlg::display()
{
	if (Data.empty())
	{
		GetDescendantWindow(IDC_SELECT)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_SHOWHINT)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_NEXT)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_START)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_RECORD)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_EDIT)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_ANSWER)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_END)->EnableWindow(FALSE);
		GetDescendantWindow(IDC_SOURCE)->SetWindowText("");
		GetDescendantWindow(IDC_PATH)->SetWindowText("");
	}
	else
	{
		CSVLine::iterator iter=DataIter->begin();
		iter++;
		if (Forward) strcpy(Source,iter->data());
		else strcpy(Target,iter->data());
		iter++;
		if (Forward) strcpy(Target,iter->data());
		else strcpy(Source,iter->data());
		strcpy(Answer,Target);
		normalize(Answer);
		GetDescendantWindow(IDC_SOURCE)->SetWindowText(Source);
		GetDescendantWindow(IDC_TARGET)->SetWindowText("");
		GetDescendantWindow(IDC_SHOWHINT)->EnableWindow(TRUE);
		GetDescendantWindow(IDC_TARGET)->EnableWindow(TRUE);
		GetDescendantWindow(IDC_NEXT)->EnableWindow(TRUE);
		GetDescendantWindow(IDC_END)->EnableWindow(TRUE);
		if (Working)
		{
			GetDescendantWindow(IDC_SELECT)->EnableWindow(FALSE);
			TargetCtrl.SetReadOnly(FALSE);
			GetDescendantWindow(IDC_TARGET)->SetFocus();
			GetDescendantWindow(IDC_START)->EnableWindow(FALSE);
			GetDescendantWindow(IDC_RECORD)->EnableWindow(FALSE);
			GetDescendantWindow(IDC_EDIT)->EnableWindow(FALSE);
			GetDescendantWindow(IDC_ANSWER)->EnableWindow(FALSE);
		}
		else
		{
			GetDescendantWindow(IDC_SELECT)->EnableWindow(TRUE);
			TargetCtrl.SetReadOnly(TRUE);
			GetDescendantWindow(IDC_START)->EnableWindow(TRUE);
			GetDescendantWindow(IDC_RECORD)->EnableWindow(TRUE);
			GetDescendantWindow(IDC_EDIT)->EnableWindow(TRUE);
			GetDescendantWindow(IDC_ANSWER)->EnableWindow(TRUE);
		}
	}
}

void CRepeatMemoryDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	char target[LINELENGTH],answer[LINELENGTH];
	TargetCtrl.SetSel(0,-1);
	int length=TargetCtrl.GetSelText(target);
	target[length]=0;
	strcpy(answer,target);
	normalize(answer);
	if (strcmp(answer,Answer)==0)
	{
		if (Retry==false )
		{
			GetDescendantWindow(IDC_HINT)->SetWindowText("对了！");
			*PassIter=true;
		}
		else
		{
			GetDescendantWindow(IDC_HINT)->SetWindowText("记住了吧？");
			Retry=false;
		}
	}
	else
	{
		char hint[LINELENGTH];
		sprintf(hint,"%s%s\x0d\x0a%s%s\x0d\x0a%s%s\x0d\x0a请再试一遍！","错了：",target,"答案：",Target,"题目：",Source);
		GetDescendantWindow(IDC_HINT)->SetWindowText(hint);
		if (Retry==false) FailNumber++;
		Retry=true; 
	}
	if (!Retry)
	{
		CSVData::iterator DataLast=DataIter;
		do
		{
			DataIter++;
			PassIter++;
			if (DataIter==Data.end())
			{
				DataIter=Data.begin();
				PassIter=Pass.begin();
			}
			if (Working && DataIter==DataLast && *PassIter==true)
			{
				time_t timer;
				time(&timer);
				time_t timespan=timer-Timer;
				int timeminite=timespan / 60;
				int timesecond=timespan % 60;
				char timetext[LINELENGTH];
				sprintf(timetext,"%4d分%02d秒",timeminite,timesecond);
				(*RecordIter)[Forward?2:4]=timetext;
				char failtext[LINELENGTH];
				sprintf(failtext,"%4d",FailNumber);
				(*RecordIter)[Forward?3:5]=failtext;
				writeRecord();
				message("恭喜！本次记忆全部结束。");
				char hinttext[LINELENGTH];
				sprintf(hinttext,
						"当前日期：%s\x0d\x0a花费时间：%s\x0d\x0a失败次数：%s",
						(*RecordIter)[1].data(),timetext,failtext);
				GetDescendantWindow(IDC_HINT)->SetWindowText(hinttext);
				Working=false;
				display();
				return;
			}
		}
		while (DataIter->size()<3 || 
				(Working && *PassIter==true) ||
				((*DataIter)[0]!=Group));
	}
	display();
}

void CRepeatMemoryDlg::normalize(char * text) 
{
	if (*text==0) return;
	char * p=text, * q=text;
	while (*p)
	{
		if (isEqual(p,"("))
		{
			while (*p && !isEqual(p,")")) goNext(p);
			goNext(p);
		}
		else if (isEqual(p,"["))
		{
			while (*p && !isEqual(p,"]")) goNext(p);
			goNext(p);
		}
		else if (isEqual(p,"{"))
		{
			while (*p && !isEqual(p,"}")) goNext(p);
			goNext(p);
		}
		else if (isEqual(p,"（"))
		{
			while (*p && !isEqual(p,"）")) goNext(p);
			goNext(p);
		}
		else if (isEqual(p,"［"))
		{
			while (*p && !isEqual(p,"］")) goNext(p);
			goNext(p);
		}
		else if (isEqual(p,"｛"))
		{
			while (*p && !isEqual(p,"｝")) goNext(p);
			goNext(p);
		}
		else if (isEqual(p,"【"))
		{
			while (*p && !isEqual(p,"】")) goNext(p);
			goNext(p);
		}
		else if (isPctChar(p))
		{
			goNext(p);
		}
		else setCharNext(q,p);
	}
	*q=0;
}

void CRepeatMemoryDlg::OnShowhint() 
{
	// TODO: Add your control notification handler code here
	CSVLine::iterator iter=DataIter->begin();
	iter++;
	iter++;
	iter++;
	char hint[LINELENGTH];
	*hint=0;
	while (iter!=DataIter->end())
	{
		strcat(hint,iter->data());
		strcat(hint,"\x0d\x0a");
		iter++;
	}
	GetDescendantWindow(IDC_HINT)->SetWindowText(hint);
}

void CRepeatMemoryDlg::OnAnswer() 
{
	// TODO: Add your control notification handler code here
	CSVLine::iterator iter=DataIter->begin();
	iter++;
	if (Forward) iter++;
	TargetCtrl.SetWindowText(iter->data());
}

void CRepeatMemoryDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	Working=true;
	FailNumber=0;
	vector<bool>::iterator iter;
	for (iter=Pass.begin();iter!=Pass.end();iter++)
	{
		*iter=false;
	}
	time(&Timer);

	PassIter=Pass.begin();
	DataIter=Data.begin();
	while ((*DataIter)[0]!=Group)
	{
		DataIter++;
		PassIter++;
	}

	GetDescendantWindow(IDC_HINT)->SetWindowText("");
	display();
}

#include <strstream>

void CRepeatMemoryDlg::OnRecord() 
{
	// TODO: Add your control notification handler code here
	char history[RECORDSIZE*100];
	strstream histream(history,RECORDSIZE*100);
	histream << "日      期";
	histream << "  正向记忆时间";
	histream << "  正向失败次数";
	histream << "  逆向记忆时间";
	histream << "  逆向失败次数";
	histream << "\x0d\x0a";
	histream << "\x0d\x0a";
	for (CSVData::iterator iter=Record.begin();iter!=Record.end();iter++)
	{
		if (iter->size()==0) continue;
		if ((*iter)[0]!=Group) continue;
		if (iter->size()>=2) histream << (*iter)[1];
		if (iter->size()>=3) histream << "  " << (*iter)[2] << "  ";
		if (iter->size()>=4) histream << "     " << (*iter)[3] << "     ";
		if (iter->size()>=5) histream << "  " << (*iter)[4] << "  ";
		if (iter->size()>=6) histream << "     " << (*iter)[5] << "     ";
		histream << "\x0d\x0a";
	}
	histream.put(0);
	CRecordDlg recorddlg;
	recorddlg.SetRecord(history);
	recorddlg.DoModal();
}


void CRepeatMemoryDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	ShellOpen(DataPath);
}

void CRepeatMemoryDlg::OnCancel() 
{
}

void CRepeatMemoryDlg::OnClose() 
{
}

void CRepeatMemoryDlg::OnEnd() 
{
	// TODO: Add your control notification handler code here
	Working=false;
	display();	
}
