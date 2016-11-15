// trajectoryDlg.h : header file
// Agung Pambudi <agung.pambudi5595@gmail.com>

#pragma once
#include "tchart1.h"
#include "afxwin.h"
#include "mscomm1.h"

// CtrajectoryDlg dialog
class CtrajectoryDlg : public CDialogEx
{
// Construction
public:
	CtrajectoryDlg(CWnd* pParent = NULL);	// standard constructor
	void ArmDraw(float sdt1, float sdt2, float sdt3);
	void InverseKinematic1(float iqx, float iqy, float iorientasi);
	void slider1(int teta1);
	void slider2(int teta2);
	void slider3(int teta3);
	void origin();
	void cepit(int set);
	void pola(float qx0, float qy0, int orientasi0, float qx1, float qy1, int orientasi1);

// Dialog Data
	enum { IDD = IDD_TRAJECTORY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTchart1 m_chart;
	//afx_msg void OnEnChangeEdit1();
	CListBox m_joint_list;
	CListBox m_work_list;
	CMscomm1 m_comm;

//	int m_teta1_0;
//	int m_teta2_0;
//	int m_teta3_0;
//	int m_teta1_1;
//	int m_teta2_1;
//	int m_teta3_1;

	float m_qx_0;
	float m_qy_0;
	float m_orientasi_0;

	float m_teta1_0;
	float m_teta2_0;
	float m_teta3_0;
	float m_teta1_1;
	float m_teta2_1;
	float m_teta3_1;

	float m_qx_1;
	float m_qy_1;
	float m_orientasi_1;

	float m_a1;
	float m_a2;
	float m_a3;

	int m_n;
	int m_t;

	int m_port;
	int y;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedCancel1();

	afx_msg void OnEnChangeEdit1();

	afx_msg void OnBnClickedOk();
};
