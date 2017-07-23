; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRepeatMemoryDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RepeatMemory.h"

ClassCount=5
Class1=CRepeatMemoryApp
Class2=CRepeatMemoryDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIRECTION
Class4=CDirectionDlg
Resource4=IDD_REPEATMEMORY_DIALOG
Class5=CRecordDlg
Resource5=IDD_RECORD

[CLS:CRepeatMemoryApp]
Type=0
HeaderFile=RepeatMemory.h
ImplementationFile=RepeatMemory.cpp
Filter=N

[CLS:CRepeatMemoryDlg]
Type=0
HeaderFile=RepeatMemoryDlg.h
ImplementationFile=RepeatMemoryDlg.cpp
Filter=D
LastObject=CRepeatMemoryDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=RepeatMemoryDlg.h
ImplementationFile=RepeatMemoryDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_RICHEDIT1,RICHEDIT,1350631552

[DLG:IDD_REPEATMEMORY_DIALOG]
Type=1
Class=CRepeatMemoryDlg
ControlCount=20
Control1=IDOK,button,1342242816
Control2=IDC_END,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PATH,edit,1350633600
Control5=IDC_BROWSE,button,1342242816
Control6=IDC_STATIC_SOURCE,static,1342308352
Control7=IDC_SOURCE,edit,1350633540
Control8=IDC_STATIC_TARGET,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_HINT,edit,1350633540
Control11=IDC_NEXT,button,1342242817
Control12=IDC_SHOWHINT,button,1342242816
Control13=IDC_RECORD,button,1342242816
Control14=IDC_START,button,1342242816
Control15=IDC_TARGET,RICHEDIT,1350631492
Control16=IDC_EDIT,button,1342242816
Control17=IDC_ANSWER,button,1342242816
Control18=IDC_STATIC,static,1342308352
Control19=IDC_GROUP,edit,1350633600
Control20=IDC_SELECT,button,1342242816

[DLG:IDD_DIRECTION]
Type=1
Class=CDirectionDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_FORWARD,button,1342177289
Control3=IDC_BACKWARD,button,1342177289
Control4=IDC_GROUPSET,combobox,1344340227
Control5=IDC_GRPTITLE,static,1342308352
Control6=IDCANCEL,button,1342242817

[CLS:CDirectionDlg]
Type=0
HeaderFile=DirectionDlg.h
ImplementationFile=DirectionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_GROUPSET

[DLG:IDD_RECORD]
Type=1
Class=CRecordDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RECORD,edit,1352730756
Control4=IDC_STATIC,static,1342308352

[CLS:CRecordDlg]
Type=0
HeaderFile=RecordDlg.h
ImplementationFile=RecordDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CRecordDlg
VirtualFilter=dWC

