// BCGPAppWizard1.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BCGPAppWizard1.h"
#include "BCGPAppWizard1Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBCGPAppWizard1App

BEGIN_MESSAGE_MAP(CBCGPAppWizard1App, CBCGPWinApp)
	ON_COMMAND(ID_HELP, CBCGPWinApp::OnHelp)
END_MESSAGE_MAP()


// CBCGPAppWizard1App construction

CBCGPAppWizard1App::CBCGPAppWizard1App()
{
	// Support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// Enable VS 2019 look (Blue theme)
	SetVisualTheme(BCGP_VISUAL_THEME_OFFICE_2019_BLACK);

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
//

// The one and only CBCGPAppWizard1App object

CBCGPAppWizard1App theApp;


// CBCGPAppWizard1App initialization

BOOL CBCGPAppWizard1App::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	CBCGPAppWizard1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
