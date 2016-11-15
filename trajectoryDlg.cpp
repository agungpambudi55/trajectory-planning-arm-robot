// trajectoryDlg.cpp : implementation file
// Agung Pambudi <agung.pambudi5595@gmail.com>

#include "stdafx.h"
#include "trajectory.h"
#include "trajectoryDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "CAxes.h"
#include "CAxis.h"
#include "CSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int n, space, jenis, flag=0;
float teta1[1000], teta2[1000], teta3[1000];
float qx[1000], qy[1000], orientasi[1000];

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CtrajectoryDlg dialog
CtrajectoryDlg::CtrajectoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtrajectoryDlg::IDD, pParent)
	//, m_chart(0)
	, m_port(0)
	, y(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_qx_0 = 0.0f;
	m_qy_0 = 0.0f;
	m_orientasi_0 = 0.0f;

	m_teta1_0 = 0.0f;
	m_teta2_0 = 0.0f;
	m_teta3_0 = 0.0f;
	m_teta1_1 = 0.0f;
	m_teta2_1 = 0.0f;
	m_teta3_1 = 0.0f;

	m_qx_1 = 0.0f;
	m_qy_1 = 0.0f;
	m_orientasi_1 = 0.0f;

	m_a1 = 0;
	m_a2 = 0;
	m_a3 = 0;

	m_n = 0;
	m_t = 0;
}

void CtrajectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chart);
	DDX_Control(pDX, IDC_LIST2, m_joint_list);

	DDX_Text(pDX, IDC_EDIT7, m_qx_0);
	DDX_Text(pDX, IDC_EDIT8, m_qy_0);
	DDX_Text(pDX, IDC_EDIT9, m_orientasi_0);

	DDX_Text(pDX, IDC_EDIT1, m_teta1_0);
	DDX_Text(pDX, IDC_EDIT2, m_teta2_0);
	DDX_Text(pDX, IDC_EDIT3, m_teta3_0);
	DDX_Text(pDX, IDC_EDIT4, m_teta1_1);
	DDX_Text(pDX, IDC_EDIT5, m_teta2_1);
	DDX_Text(pDX, IDC_EDIT6, m_teta3_1);

	DDX_Text(pDX, IDC_EDIT10, m_qx_1);
	DDX_Text(pDX, IDC_EDIT11, m_qy_1);
	DDX_Text(pDX, IDC_EDIT12, m_orientasi_1);

	DDX_Text(pDX, IDC_EDIT13, m_a1);
	DDX_Text(pDX, IDC_EDIT14, m_a2);
	DDX_Text(pDX, IDC_EDIT15, m_a3);

	DDX_Text(pDX, IDC_EDIT16, m_n);
	DDX_Text(pDX, IDC_EDIT17, m_t);

	DDX_Control(pDX, IDC_LIST3, m_work_list);
	DDX_Control(pDX, IDC_MSCOMM1, m_comm);
	DDX_Text(pDX, IDC_EDIT18, m_port);
}

BEGIN_MESSAGE_MAP(CtrajectoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtrajectoryDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtrajectoryDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CtrajectoryDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CtrajectoryDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CtrajectoryDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CtrajectoryDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CtrajectoryDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CtrajectoryDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CtrajectoryDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CtrajectoryDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CtrajectoryDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CtrajectoryDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CtrajectoryDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CtrajectoryDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CtrajectoryDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CtrajectoryDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CtrajectoryDlg::OnBnClickedButton18)

	ON_BN_CLICKED(IDOK, &CtrajectoryDlg::OnBnClickedOk)

	ON_BN_CLICKED(IDC_RADIO1, &CtrajectoryDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CtrajectoryDlg::OnBnClickedRadio2)
	ON_WM_TIMER()

END_MESSAGE_MAP()


// CtrajectoryDlg message handlers

BOOL CtrajectoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	UpdateData(1);
		m_a1 = (float)12;
		m_a2 = (float)12.8;
		m_a3 = (float)5.7;

		m_port = 5;

		m_n = 25;
		m_t = 100;
	UpdateData(0);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtrajectoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtrajectoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtrajectoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtrajectoryDlg::ArmDraw(float sdt1, float sdt2, float sdt3)
{
	float kx,ky,px,py,qx,qy;
	sdt1=sdt1 * (float)(3.14/180);
	sdt2=sdt2 * (float)(3.14/180);
	sdt3=sdt3 * (float)(3.14/180);

	UpdateData(1);

	kx=m_a1*cos(sdt1);
	ky=m_a1*sin(sdt1);
	px=m_a2*cos(sdt1+sdt2) + kx;
	py=m_a2*sin(sdt1+sdt2) + ky;
	qx=m_a3*cos(sdt1+sdt2+sdt3) + px;
	qy=m_a3*sin(sdt1+sdt2+sdt3) + py;

	UpdateData(0);

	((CSeries)m_chart.Series(0)).Clear();
	((CSeries)m_chart.Series(1)).Clear();
	((CSeries)m_chart.Series(2)).Clear();

	((CSeries)m_chart.Series(0)).AddXY(0,0,NULL,RGB(100,100,100));
	((CSeries)m_chart.Series(0)).AddXY(kx,ky,NULL,RGB(100,100,100));

	((CSeries)m_chart.Series(1)).AddXY(kx,ky,NULL,RGB(100,100,100));
	((CSeries)m_chart.Series(1)).AddXY(px,py,NULL,RGB(100,100,100));

	((CSeries)m_chart.Series(2)).AddXY(px,py,NULL,RGB(100,100,100));
	((CSeries)m_chart.Series(2)).AddXY(qx,qy,NULL,RGB(100,100,100));

	((CSeries)m_chart.Series(3)).AddXY(qx,qy,NULL,RGB(100,100,100));
}

void CtrajectoryDlg::InverseKinematic1(float iqx, float iqy, float iorientasi)
{
	float teta1,teta2,teta3,ipx,ipy, mteta1,mteta2;

	UpdateData(1);

	ipx = iqx - m_a3*(float)cos(iorientasi*3.14/180);
	ipy = iqy - m_a3*(float)sin(iorientasi*3.14/180);
	teta2 = (pow(ipx,2)+pow(ipy,2)-pow((float)m_a1,2)-pow((float)m_a2,2)) / (2*(float)m_a1*(float)m_a2);
	
	if(teta2>=1.0) teta2=1.0;
	else if(teta2<=-1.0) teta2=-1.0;
	
	teta2=acos(teta2);
	teta1=((float)m_a2*sin(teta2)) / ((float)m_a1+(float)m_a2*cos(teta2));
	teta1=atan2(ipy,ipx) - atan(teta1);
	mteta2=(float)(teta2*(180/3.14));
	mteta1=teta1*(float)(180/3.14);
	teta3=iorientasi - mteta2 - mteta1;

	/*if(teta1<0) teta1=0;
	else if(teta1>180) teta1=180;
	if(teta2<0) teta2=0;
	else if(teta2>180) teta2=180;
	if(teta3<0) teta3=0;
	else if(teta3>180) teta3=180;*/

	ArmDraw(mteta1,mteta2,teta3);

	slider1((int)mteta1);
	slider2((int)mteta2);
	slider3((int)teta3);

	UpdateData(0);
}


void CtrajectoryDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString dt;
	int i;
	
	m_joint_list.ResetContent();
	
	UpdateData(1);
	
	for(i=0;i<=m_n;i++){
		teta1[i]=m_teta1_0 + ((m_teta1_1-m_teta1_0)/(float)(m_n)*(float)i);
		teta2[i]=m_teta2_0 + ((m_teta2_1-m_teta2_0)/(float)(m_n)*(float)i);
		teta3[i]=m_teta3_0 + ((m_teta3_1-m_teta3_0)/(float)(m_n)*(float)i);

		dt.Format(_T("%3d %3.1f %3.1f %3.1f"),i,teta1[i],teta2[i],teta3[i]);
		
		m_joint_list.AddString(dt);
	}
	
	UpdateData(0);
	
	n=0; space=0;
}


void CtrajectoryDlg::OnBnClickedButton2()
{
	OnBnClickedButton12();
	// TODO: Add your control notification handler code here
	int time;

	n=0; space=0;

	UpdateData(1);

	if(jenis==0) time=m_t;
	else time=m_t/m_n;

	UpdateData(0);

	SetTimer(0,time,NULL);
}


void CtrajectoryDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString dt;
	int i;

	m_work_list.ResetContent();

	UpdateData(1);

	for(i=0;i<=m_n;i++){
		qx[i]=m_qx_0 + ((m_qx_1-m_qx_0)/(float)(m_n)*(float)i);
		qy[i]=m_qy_0 + ((m_qy_1-m_qy_0)/(float)(m_n)*(float)i);
		orientasi[i]=m_orientasi_0 + ((m_orientasi_1-m_orientasi_0)/(float)(m_n)*(float)i);
		
		dt.Format(_T("%3d %3.1f %3.1f %3.1f"),i,qx[i],qy[i],orientasi[i]);
		
		m_work_list.AddString(dt);
	}

	UpdateData(0);

	n=0; space=1;
}


void CtrajectoryDlg::OnBnClickedButton5()
{
	OnBnClickedButton12();
	// TODO: Add your control notification handler code here
	int time;
	n=0; space=1;

	UpdateData(1);

	if(jenis==0) time=m_t;
	else time=m_t/m_n;

	UpdateData(0);

	SetTimer(0,time,NULL);
}


void CtrajectoryDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	OnBnClickedButton12();
}


void CtrajectoryDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	jenis=0;
}


void CtrajectoryDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	jenis=1;
}


void CtrajectoryDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(space==0) 
		{ArmDraw(teta1[n],teta2[n],teta3[n]);
		slider1((int)teta1[n]);
		slider2((int)teta2[n]);
		slider3((int)teta3[n]);}
	else if(space==1)
		{InverseKinematic1(qx[n],qy[n],orientasi[n]);}

	UpdateData(1);

	n++;

	if(flag!=0)
	{
		if(n>m_n*4) KillTimer(0);
	}
	else
	{
		if(n>m_n) KillTimer(0);
	}

	UpdateData(0);

	CDialogEx::OnTimer(nIDEvent);
}


void CtrajectoryDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	UpdateData(1);

	m_comm.put_CommPort(m_port);

	UpdateData(0);

	m_comm.put_Settings(_T("9600,N,8,1"));
	m_comm.put_InputMode(0);
	m_comm.put_InputLen(1);
	m_comm.put_RTSEnable(TRUE);
	m_comm.put_RThreshold(1);
	m_comm.put_PortOpen(TRUE);

}

void CtrajectoryDlg::slider1(int teta1)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);

	y=2401 + (592-2401)*(teta1)/(180-0);

	UpdateData(0);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0]=0x0D;
	header[1]=0x0A;
	hexdata[0]='#';
	hexdata[1]='0';
	hexdata[2]=' ';
	hexdata[3]='P';
	hexdata[4]=0x30+((y/1000)%10);
	hexdata[5]=0x30+((y/100)%10);
	hexdata[6]=0x30+((y/10)%10);
	hexdata[7]=0x30+(y%10);
	hexdata[8]=' ';
	hexdata[9]='S';
	hexdata[10]='1';
	hexdata[11]='0';
	hexdata[12]='0';
	hexdata[13]='0';
	hexdata[14]=' ';
	hexdata[15]='<';
	hexdata[16]='c';
	hexdata[17]='r';
	hexdata[18]='>';

	tail[0]=0x0D;
	tail[1]=0x0A;
	tail[2]=0x00;

	if(m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
}

void CtrajectoryDlg::slider2(int teta2)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);

	y= 2419 + (591-2419)*(teta2+90)/(180-0);

	UpdateData(0);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0]=0x0D;
	header[1]=0x0A;
	hexdata[0]='#';
	hexdata[1]='2';
	hexdata[2]=' ';
	hexdata[3]='P';
	hexdata[4]=0x30+((y/1000)%10);
	hexdata[5]=0x30+((y/100)%10);
	hexdata[6]=0x30+((y/10)%10);
	hexdata[7]=0x30+(y%10);
	hexdata[8]=' ';
	hexdata[9]='S';
	hexdata[10]='1';
	hexdata[11]='0';
	hexdata[12]='0';
	hexdata[13]='0';
	hexdata[14]=' ';
	hexdata[15]='<';
	hexdata[16]='c';
	hexdata[17]='r';
	hexdata[18]='>';

	tail[0]=0x0D;
	tail[1]=0x0A;
	tail[2]=0x00;

	if(m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
}

void CtrajectoryDlg::slider3(int teta3)
{
	// TODO: Add your control notification handler code here
	UpdateData(1);

	y= 2391 + (626-2391)*(teta3+90)/(180-0);

	UpdateData(0);

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	header[0]=0x0D;
	header[1]=0x0A;
	hexdata[0]='#';
	hexdata[1]='3';
	hexdata[2]=' ';
	hexdata[3]='P';
	hexdata[4]=0x30+((y/1000)%10);
	hexdata[5]=0x30+((y/100)%10);
	hexdata[6]=0x30+((y/10)%10);
	hexdata[7]=0x30+(y%10);
	hexdata[8]=' ';
	hexdata[9]='S';
	hexdata[10]='1';
	hexdata[11]='0';
	hexdata[12]='0';
	hexdata[13]='0';
	hexdata[14]=' ';
	hexdata[15]='<';
	hexdata[16]='c';
	hexdata[17]='r';
	hexdata[18]='>';

	tail[0]=0x0D;
	tail[1]=0x0A;
	tail[2]=0x00;

	if(m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
}
void CtrajectoryDlg::origin()
{
	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	// rata air start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '1';
	hexdata[2] = ' ';
	hexdata[3] = ' ';
	hexdata[4] = 'P';
	hexdata[5] = '7';
	hexdata[6] = '4';
	hexdata[7] = '8';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// rata air end

	// servo 0 start		
	UpdateData(0);
	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '0';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '4';
	hexdata[6] = '9';
	hexdata[7] = '7';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 0 end

	// servo 2 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '2';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '5';
	hexdata[6] = '0';
	hexdata[7] = '5';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 2 end

	// servo 3 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '3';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '5';
	hexdata[6] = '0';
	hexdata[7] = '9';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 3 end
}

void CtrajectoryDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	origin();
}

void CtrajectoryDlg::cepit(int set){
	int y;
	if(set==0){
		y=2350;
	}else if(set==1){
		y=1010;
	}

	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);
 
	header[0]=0x0D;
	header[1]=0x0A;
	hexdata[0]='#';
	hexdata[1]='4';
	hexdata[2]=' ';
	hexdata[3]='P';  
	hexdata[4]=0x30+((y/1000)%10);
	hexdata[5]=0x30+((y/100)%10);
	hexdata[6]=0x30+((y/10)%10);
	hexdata[7]=0x30+(y%10);
	hexdata[8]=' ';
	hexdata[9]='S';
	hexdata[10]='2';
	hexdata[11]='5';
	hexdata[12]='0';
	hexdata[13]='0';
	hexdata[14]=' ';
	hexdata[15]='<';
	hexdata[16]='c';
	hexdata[17]='r';
	hexdata[18]='>';

	tail[0]=0x0D;
	tail[1]=0x0A;
	tail[2]=0x00;

	if(m_comm.get_PortOpen()){
		UpdateData(TRUE);
			m_comm.put_Output(COleVariant(header));
			m_comm.put_Output(COleVariant(hexdata));
			m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
}

void CtrajectoryDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	cepit(0);

}


void CtrajectoryDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	cepit(1);
}


void CtrajectoryDlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	if(space==0) 
		{ArmDraw(teta1[n],teta2[n],teta3[n]);
		slider1((int)teta1[n]);
		slider2((int)teta2[n]);
		slider3((int)teta3[n]);}
	else if(space==1)
		{InverseKinematic1(qx[n],qy[n],orientasi[n]);
		}
	n++;
	UpdateData(1);
	if(n>m_n) n = m_n;
	UpdateData(0);
}


void CtrajectoryDlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	m_comm.put_PortOpen(FALSE);
}



void CtrajectoryDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CtrajectoryDlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
	((CSeries)m_chart.Series(0)).Clear();
	((CSeries)m_chart.Series(1)).Clear();
	((CSeries)m_chart.Series(2)).Clear();
	((CSeries)m_chart.Series(3)).Clear();
}


void CtrajectoryDlg::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	// rata air start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '1';
	hexdata[2] = ' ';
	hexdata[3] = ' ';
	hexdata[4] = 'P';
	hexdata[5] = '7';
	hexdata[6] = '4';
	hexdata[7] = '8';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// rata air end

	// servo 0 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '0';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '2';
	hexdata[5] = '4';
	hexdata[6] = '0';
	hexdata[7] = '1';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '0';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 0 end

	// servo 2 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '2';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '5';
	hexdata[6] = '0';
	hexdata[7] = '5';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '0';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 2 end

	// servo 3 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '3';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '5';
	hexdata[6] = '0';
	hexdata[7] = '9';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 3 end
}


void CtrajectoryDlg::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CByteArray hexdata; hexdata.SetSize(19);
	CByteArray header; header.SetSize(2);
	CByteArray tail; tail.SetSize(3);

	// rata air start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '1';
	hexdata[2] = ' ';
	hexdata[3] = ' ';
	hexdata[4] = 'P';
	hexdata[5] = '7';
	hexdata[6] = '4';
	hexdata[7] = '8';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// rata air end

	// servo 0 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '0';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '5';
	hexdata[5] = '9';
	hexdata[6] = '2';
	hexdata[7] = ' ';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '0';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 0 end

	// servo 2 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '2';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '5';
	hexdata[6] = '0';
	hexdata[7] = '5';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '0';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 2 end

	// servo 3 start		
	UpdateData(0);

	header[0] = 0x0D;
	header[1] = 0x0A;
	hexdata[0] = '#';
	hexdata[1] = '3';
	hexdata[2] = ' ';
	hexdata[3] = 'P';
	hexdata[4] = '1';
	hexdata[5] = '5';
	hexdata[6] = '0';
	hexdata[7] = '9';
	hexdata[8] = ' ';
	hexdata[9] = 'S';
	hexdata[10] = '1';
	hexdata[11] = '5';
	hexdata[12] = '0';
	hexdata[13] = '0';
	hexdata[14] = ' ';
	hexdata[15] = '<';
	hexdata[16] = 'c';
	hexdata[17] = 'r';
	hexdata[18] = '>';

	tail[0] = 0x0D;
	tail[1] = 0x0A;
	tail[2] = 0x00;

	UpdateData(0);

	if (m_comm.get_PortOpen()){
		UpdateData(TRUE);
		m_comm.put_Output(COleVariant(header));
		m_comm.put_Output(COleVariant(hexdata));
		m_comm.put_Output(COleVariant(tail));
		UpdateData(FALSE);
	}
	// servo 3 end
}

int n_pola=0;
void CtrajectoryDlg::pola(float qx0, float qy0, int o0, float qx1, float qy1, int o1){
	CString dt;
	UpdateData(1);
		m_work_list.ResetContent();
		for(int i=0;i<=m_n;i++){
			qx[i] = qx0 + ((qx1-qx0)/(float)(m_n)*(float)i);
			qy[i] = qy0 + ((qy1-qy0)/(float)(m_n)*(float)i);
			orientasi[i] = o0 + ((o1-o0)/(float)(m_n)*(float)i);

			dt.Format(_T("%3d %3.1f %3.1f %3.1f"), i, qx[i], qy[i], orientasi[i]);
			m_work_list.AddString(dt);
		}
	UpdateData(0);

	n=0; space=1;

	SetTimer(0,((jenis==0)?m_t:(m_t/m_n)),NULL);
}

void CtrajectoryDlg::OnBnClickedButton15(){flag=0;
	n_pola++;
	switch (n_pola) {
		case 1 : pola(-27.5,5,203,  -27.5,10,186); break;
		case 2 : pola(-27.5,10,186, -25,7.5,207); break;
		case 3 : pola(-25,7.5,207,  -22.5,10,210); break;
		case 4 : pola(-22.5,10,210, -22.5,5,228); n_pola=0; break;
	}
}

void CtrajectoryDlg::OnBnClickedButton17(){flag=1;n_pola=0;
	CString dt;
	int i, ii, iii, iiii, o0, o1;
	float qx0, qx1, qy0, qy1;
	
	m_work_list.ResetContent();
	UpdateData(1);
		qx0 = -27.5; qy0 = 5; o0 = 203;
		qx1 = -27.5; qy1 = 10; o1 =186;
		for (i = 0; i <= m_n; i++){
			qx[i] = qx0 + ((qx1 - qx0) / (float)(m_n)*(float)i);
			qy[i] = qy0 + ((qy1 - qy0) / (float)(m_n)*(float)i);
			orientasi[i] = o0 + ((o1 - o0) / (float)(m_n)*(float)i);

			dt.Format(_T("%3d %3.1f %3.1f %3.1f"), i, qx[i], qy[i], orientasi[i]);
			m_work_list.AddString(dt);
		}
		qx0 = -27.5; qy0 = 10; o0 =186;
		qx1 = -25; qy1 = 7.5; o1 = 207;
		for (i = 0; i<=m_n; i++){
			ii = i + m_n;
			qx[ii] = qx0 + ((qx1 - qx0) / (float)(m_n)*(float)i);
			qy[ii] = qy0 + ((qy1 - qy0) / (float)(m_n)*(float)i);
			orientasi[ii] = o0 + ((o1 - o0) / (float)(m_n)*(float)i);

			dt.Format(_T("%3d %3.1f %3.1f %3.1f"), ii, qx[ii], qy[ii], orientasi[ii]);
			m_work_list.AddString(dt);
		}
		qx0 = -25; qy0 = 7.5; o0 = 207;
		qx1 = -22.5; qy1 = 10; o1 = 210;
		for (i = 0; i<=m_n; i++){
			iii = ii + i;
			qx[iii] = qx0 + ((qx1 - qx0) / (float)(m_n)*(float)i);
			qy[iii] = qy0 + ((qy1 - qy0) / (float)(m_n)*(float)i);
			orientasi[iii] = o0 + ((o1 - o0) / (float)(m_n)*(float)i);

			dt.Format(_T("%3d %3.1f %3.1f %3.1f"), iii, qx[iii], qy[iii], orientasi[iii]);
			m_work_list.AddString(dt);
		}
		qx0 = -22.5; qy0 = 10; o0 = 210;
		qx1 = -22.5; qy1 = 5; o1 = 228;
		for (i = 0; i<=m_n; i++){
			iiii = iii + i;
			qx[iiii] = qx0 + ((qx1 - qx0) / (float)(m_n)*(float)i);
			qy[iiii] = qy0 + ((qy1 - qy0) / (float)(m_n)*(float)i);
			orientasi[iiii] = o0 + ((o1 - o0) / (float)(m_n)*(float)i);

			dt.Format(_T("%3d %3.1f %3.1f %3.1f"), iiii, qx[iiii], qy[iiii], orientasi[iiii]);
			m_work_list.AddString(dt);
		}
	UpdateData(0);

	n = 0; space = 1;

	SetTimer(0,((jenis==0)?m_t:(m_t/m_n)),NULL);
}

void CtrajectoryDlg::OnBnClickedButton18(){
	flag=1;
}