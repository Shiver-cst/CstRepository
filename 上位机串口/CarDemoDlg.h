// CarDemoDlg.h : header file
//

#if !defined(AFX_CARDEMODLG_H__29B9173A_16F7_43F1_B76F_C854B14C0125__INCLUDED_)
#define AFX_CARDEMODLG_H__29B9173A_16F7_43F1_B76F_C854B14C0125__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SerialPort.h"  //添加CSerailPort类的头文件

/////////////////////////////////////////////////////////////////////////////
// CCarDemoDlg dialog

class CCarDemoDlg : public CDialog
{
// Construction
public:
	CCarDemoDlg(CWnd* pParent = NULL);	// standard constructor

	CSerialPort m_SerialPort; //CSerailPort类对象
	BOOL m_bSerialPortOpened; //标志串口是否打开
	DWORD m_dwSpeed ;
	BOOL m_bDirection ;
// Dialog Data
	//{{AFX_DATA(CCarDemoDlg)
	enum { IDD = IDD_CARDEMO_DIALOG };
	CComboBox	m_ctrlComboComPort;
	CString	m_strSendSpeed;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCarDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg LONG OnComm(WPARAM ch, LPARAM port);   //添加控件响应函数
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpenCom();
	afx_msg void OnButtonCloseCom();
	afx_msg void OnButtonForward();
	afx_msg void OnButtonBack();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonSpeedUp();
	afx_msg void OnButtonSlowDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDEMODLG_H__29B9173A_16F7_43F1_B76F_C854B14C0125__INCLUDED_)
