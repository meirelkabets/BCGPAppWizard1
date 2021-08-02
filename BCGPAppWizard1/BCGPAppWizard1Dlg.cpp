// BCGPAppWizard1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "BCGPAppWizard1.h"
#include "BCGPAppWizard1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(IDD_ABOUTBOX)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CBCGPAppWizard1Dlg dialog


CBCGPAppWizard1Dlg::CBCGPAppWizard1Dlg(CWnd* pParent /*=NULL*/)
: CBCGPDialog(IDD_BCGPAPPWIZARD1_DIALOG, pParent), m_wndVisualTheme(BCGP_THEMES_LIST_ALL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	EnableVisualManagerStyle(TRUE, TRUE);

}

void CBCGPAppWizard1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_VISUAL_MNGR, m_wndVisualTheme);
	DDX_Control(pDX, IDC_CHART, m_chartControl);
}

BEGIN_MESSAGE_MAP(CBCGPAppWizard1Dlg, CBCGPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBCGPAppWizard1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBCGPAppWizard1Dlg message handlers

BOOL CBCGPAppWizard1Dlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//m_wndVisualTheme.SelectTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2019_BLACK);
	
	

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

	// TODO: add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBCGPAppWizard1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CBCGPDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBCGPAppWizard1Dlg::OnPaint()
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
		CBCGPDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBCGPAppWizard1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBCGPAppWizard1Dlg::OnBnClickedOk()
{
	CBCGPChartVisualObject* pChart = m_chartControl.GetChart();
	ASSERT_VALID(pChart);

	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE);
	pChart->SetThemeOpacity(70);
	pChart->SetZoomScrollConfig(BCGPChartMouseConfig::ZSO_WHEEL_PAN);

	OnUpdateChart();


}

void CBCGPAppWizard1Dlg::OnUpdateChart()
{
	CWaitCursor wait;

	UpdateData();

	typedef struct MERGE_DTM_HDR
	{
		unsigned long hdr[15];
		unsigned long dwcrc;

	}MERGE_DTM_HDR;

	unsigned long nDataPoints = 40000000;
	unsigned long buff[40000] = { 0 };

	FILE* fp = fopen("bin.bin", "w+b");
		   
	for (int j = 0; j < 4 ; j++)
	{
		fwrite(buff, sizeof(buff), 1, fp);

	}

	fclose(fp);
	

	CBCGPChartVisualObject* pChart = m_chartControl.GetChart();
	ASSERT_VALID(pChart);

	pChart->CleanUpChartData();

	double dblMaxVal = 0;
	double dblVal = 0;

	CBCGPDoubleArray arValues;
	arValues.SetSize(nDataPoints,10);

	for (unsigned long i = 0; i < nDataPoints; i++)
	{
		double dblDelta = dblVal > 500 ? Rand(-500, 500) : Rand(0, 1000);
		dblVal += dblDelta;

		arValues[i] = dblVal;

		dblMaxVal = max(dblMaxVal, dblVal);
	}

	CBCGPChartAxis* pAxisX = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	CBCGPChartAxis* pAxisY = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);

	CString strLabel;
	pAxisY->GetDisplayedLabel(dblMaxVal, strLabel);
	pAxisY->m_strMaxDisplayedLabel = strLabel;

	pAxisX->GetDisplayedLabel(nDataPoints, strLabel);
	pAxisX->m_strMaxDisplayedLabel = strLabel;

	pChart->AddDataPointsOptimized(arValues);
	pChart->AddDataPointsOptimized(arValues,1);

	pChart->GetSeries(0)->SetCurveType(BCGPChartFormatSeries::CCT_SPLINE);	
	pChart->GetSeries(1)->SetCurveType(BCGPChartFormatSeries::CCT_STEP);


	pChart->SetDirty(TRUE, TRUE);



	//UpdateScrollBars();

	m_chartControl.SetFocus();
}