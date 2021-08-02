// BCGPAppWizard1Dlg.h : header file
//

#pragma once


// CBCGPAppWizard1Dlg dialog
class CBCGPAppWizard1Dlg : public CBCGPDialog
{
// Construction
public:
	CBCGPAppWizard1Dlg(CWnd * pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BCGPAPPWIZARD1_DIALOG };
#endif
	CBCGPThemeSelectorComboBox	m_wndVisualTheme;


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
private:
	CBCGPChartCtrl m_chartControl;
public:
	afx_msg void OnBnClickedOk();
	void OnUpdateChart();
	inline double Rand(double dblStart, double dblFinish)
	{


		//
		double minVal = min(dblStart, dblFinish);
		double maxVal = max(dblStart, dblFinish);

		return (maxVal - minVal) * (double)rand() / (RAND_MAX + 1) + minVal;
	}
};
