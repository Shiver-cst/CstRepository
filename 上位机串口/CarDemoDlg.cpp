// CarDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CarDemo.h"
#include "CarDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CCarDemoDlg dialog

CCarDemoDlg::CCarDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCarDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCarDemoDlg)
	m_strSendSpeed = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCarDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCarDemoDlg)
	DDX_Control(pDX, IDC_COMBO1, m_ctrlComboComPort);
	DDX_Text(pDX, IDC_EDIT1, m_strSendSpeed);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCarDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCarDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM, OnButtonOpenCom)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECOM, OnButtonCloseCom)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, OnButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SPEEDUP, OnButtonSpeedUp)
	ON_BN_CLICKED(IDC_BUTTON_SLOWDOWN, OnButtonSlowDown)
	ON_BN_CLICKED(IDC_BUTTON_BACK, OnButtonBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarDemoDlg message handlers

BOOL CCarDemoDlg::OnInitDialog()
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
	m_ctrlComboComPort.SetCurSel(0); //初始串口选择框显示"COM1"
	//以下语句分别设置“打开串口”、“关闭串口”两个按状态的使能状态
	m_bSerialPortOpened=FALSE;
	m_dwSpeed = 0 ;   //表示速度
	m_bDirection = 0 ;  //表示方向,0表示停，1表示前进，-1表示后退
	GetDlgItem(IDC_BUTTON_OPENCOM)->EnableWindow(!m_bSerialPortOpened);//"打开串口"按钮有效
	GetDlgItem(IDC_BUTTON_CLOSECOM)->EnableWindow(m_bSerialPortOpened);//"关闭串口"按钮无效
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCarDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCarDemoDlg::OnPaint() 
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
HCURSOR CCarDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LONG CCarDemoDlg::OnComm(WPARAM ch, LPARAM port)
{
//	m_strEditReceiveMsg += ch;
	UpdateData(FALSE); //将接收到的字符显示在接收编辑框中
	return 0;
}

void CCarDemoDlg::OnButtonOpenCom() 
{
	// TODO: Add your control notification handler code here
	int nPort=m_ctrlComboComPort.GetCurSel()+1; //得到串口号，想想为什么要加1
	if(m_SerialPort.InitPort(this, nPort, 9600,'N',8,1,EV_RXFLAG | EV_RXCHAR,512))
	{
		m_SerialPort.StartMonitoring();
		m_bSerialPortOpened=TRUE;
		OnButtonStop() ;
	}
	else
	{
		AfxMessageBox("没有发现此串口或被占用");
		m_bSerialPortOpened=FALSE;
	}
	GetDlgItem(IDC_BUTTON_OPENCOM)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSECOM)->EnableWindow(m_bSerialPortOpened);
	
}

void CCarDemoDlg::OnButtonCloseCom() 
{
	// TODO: Add your control notification handler code here
	m_SerialPort.ClosePort();//关闭串口
    m_bSerialPortOpened=FALSE;
	GetDlgItem(IDC_BUTTON_OPENCOM)->EnableWindow(!m_bSerialPortOpened);
	GetDlgItem(IDC_BUTTON_CLOSECOM)->EnableWindow(m_bSerialPortOpened);
}

void CCarDemoDlg::OnButtonForward() 
{
	// TODO: Add your control notification handler code here
	if(!m_bSerialPortOpened) return; //检查串口是否打开
	m_bDirection = TRUE ;
	m_dwSpeed = 1 ;
	CString m_strForward = "11" ;
	m_SerialPort.WriteToPort((LPCTSTR)m_strForward);//发送数据
	m_strSendSpeed = "1" ;
	UpdateData(FALSE) ;
}

void CCarDemoDlg::OnButtonBack() 
{
	// TODO: Add your control notification handler code here
	if(!m_bSerialPortOpened) return; //检查串口是否打开
	m_bDirection = FALSE ;
	m_dwSpeed = 1 ;
	CString m_strBack = "21" ;
	m_SerialPort.WriteToPort((LPCTSTR)m_strBack);//发送数据
	m_strSendSpeed = "1" ;
	UpdateData(FALSE) ;
}

void CCarDemoDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if(!m_bSerialPortOpened) return; //检查串口是否打开
	CString m_strStop = "00" ;
	m_SerialPort.WriteToPort((LPCTSTR)m_strStop);//发送数据	
	m_strSendSpeed = "0" ;
	UpdateData(FALSE) ;
}

void CCarDemoDlg::OnButtonSpeedUp() 
{
	// TODO: Add your control notification handler code here
	if(!m_bSerialPortOpened) return; //检查串口是否打开
	m_dwSpeed++ ;
	DWORD dwDir = 1 ;

	if(m_dwSpeed > 6)
	{
		m_dwSpeed = 6 ;
	}
	if(m_bDirection == FALSE)
	{
		dwDir = 2 ;
	}
	m_strSendSpeed.Format("%d%d",dwDir,m_dwSpeed) ;
	m_SerialPort.WriteToPort((LPCTSTR)m_strSendSpeed) ;
	m_strSendSpeed.Format("%d",m_dwSpeed) ;
	UpdateData(FALSE);
}

void CCarDemoDlg::OnButtonSlowDown() 
{
	// TODO: Add your control notification handler code here
	if(!m_bSerialPortOpened) return; //检查串口是否打开
	m_dwSpeed-- ;

	DWORD dwDir = 1 ;

	if(m_dwSpeed <= 0)
	{
		m_dwSpeed = 1 ;
	}
	if(m_bDirection == FALSE)
	{
		dwDir = 2 ;
	}
	m_strSendSpeed.Format("%d%d",dwDir,m_dwSpeed) ;
	m_SerialPort.WriteToPort((LPCTSTR)m_strSendSpeed) ;
	m_strSendSpeed.Format("%d",m_dwSpeed) ;
	UpdateData(FALSE);
}


