
// SPDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SPDialog.h"
#include "SPDialogDlg.h"
#include "afxdialogex.h"
#include <math.h> 
#include <iomanip>
#include <locale>
#include <sstream>
#include <string> 
#include <sstream>

#ifdef UNICODE
typedef std::wostringstream tstringstream;
#else
typedef std::ostringstream tstringstream;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CSPDialogDlg dialog

int CSPDialogDlg::vrednosti[7] = { 0, 1, 3, 7, 5000, 5000, 5000 };
int CSPDialogDlg::redosled[7] = { 3, 4, 2, 5, 1, 6, 0 };

CSPDialogDlg::CSPDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSPDialogDlg::IDD, pParent)

	
{
	long lrand(time(0));
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			for (int z = 0; z < 2; z++)
				ran[i][j][z] = rand()*65535+rand();
	kljuc = 0;

	
	boje[0].CreateSolidBrush(RGB(0, 255, 0));

	boje[1].CreateSolidBrush(RGB(255, 0, 0));
	brojac = 1;
	
	for (int i = 0; i < 7; i++)
	{
		niz[i] = 0;
	}
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	izbor = 1;
	drawOnClick = false;
}

void CSPDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CSPDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()

	
	ON_BN_CLICKED(IDC_NEW, &CSPDialogDlg::OnBnClickedNew)

	ON_BN_CLICKED(IDC_BOT, &CSPDialogDlg::OnBnClickedBot)
	
END_MESSAGE_MAP()


// CSPDialogDlg message handlers

BOOL CSPDialogDlg::OnInitDialog()
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

	



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSPDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSPDialogDlg::OnPaint()
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
		CPaintDC dc(this); // device context for painting
		// horizontalne linije
		CBrush* pTempBrush = NULL;
		pTempBrush = (CBrush*)dc.SelectObject(CreateSolidBrush(RGB(140, 140, 140)));
		dc.Rectangle(20, 20, 720, 620);
		pTempBrush = (CBrush*)dc.SelectObject(CreateSolidBrush(RGB(255, 255, 255)));
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 6; j++)
				dc.Ellipse(i * 100 + 23, j * 100 + 23, i * 100 + 117, j * 100 + 117);
	/*	dc.MoveTo(20, 20); dc.LineTo(20, 620);
		dc.MoveTo(120, 20); dc.LineTo(120, 620);
		dc.MoveTo(220, 20); dc.LineTo(220, 620);
		dc.MoveTo(320, 20); dc.LineTo(320, 620);
		dc.MoveTo(420, 20); dc.LineTo(420, 620);
		dc.MoveTo(520, 20); dc.LineTo(520, 620);
		dc.MoveTo(620, 20); dc.LineTo(620, 620);
		dc.MoveTo(720, 20); dc.LineTo(720, 620);

		dc.MoveTo(20, 20); dc.LineTo(720, 20);
		dc.MoveTo(20, 120); dc.LineTo(720, 120);
		dc.MoveTo(20, 220); dc.LineTo(720, 220);
		dc.MoveTo(20, 320); dc.LineTo(720, 320);
		dc.MoveTo(20, 420); dc.LineTo(720, 420);
		dc.MoveTo(20, 520); dc.LineTo(720, 520);
		dc.MoveTo(20, 620); dc.LineTo(720, 620);
		*/
		
		pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);
		dc.Ellipse(780, 20, 880, 120);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSPDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}








void CSPDialogDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (gotovo==false)
	if (20 < point.x && point.x < 720 && 20 < point.y && point.y < 620)
	{

		if (niz[(int)floor(((double)point.x - 20) / 100)] < 6){

			CClientDC dc(this);
			CBrush* pTempBrush = NULL;
			pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);
			brojac = -brojac + 1;

			dc.Ellipse((int)floor(((double)point.x - 20) / 100) * 100 + 23, (5 - niz[(int)floor(((double)point.x - 20) / 100)]) * 100 + 23,
				(int)floor(((double)point.x - 20) / 100) * 100 + 117, (5 - niz[(int)floor(((double)point.x - 20) / 100)]) * 100 + 117);
			mat[niz[(int)floor(((double)point.x - 20) / 100)]][(int)floor(((double)point.x - 20) / 100)] = -(brojac == 0) + (brojac == 1);
		
			gotovo = gg((int)floor(((double)point.x - 20) / 100));
			niz[(int)floor(((double)point.x - 20) / 100)] = niz[(int)floor(((double)point.x - 20) / 100)] + 1;
			
			//	bmDC.SelectObject(pOldbmp);
			//AfxMessageBox(_T("Ocitano je    "));
			pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);
			dc.Ellipse(780, 20, 880, 120);
			
			int alpha1 = -45000;
			int beta1 = 45000;
			if (gotovo==true)
				if (brojac==1)
			SetDlgItemText(IDC_REZULTAT,_T( "Pobedio je ZELENI"));
				else 
					SetDlgItemText(IDC_REZULTAT, _T("Pobedio je CRVENI"));
			if (bot)
			if (gotovo == false)
			{
				pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);

				int pomniz[7];
				for (int i = 0; i < 7; i++)
					if (niz[redosled[i]]<6)
						pomniz[redosled[i]] = minmax(redosled[i], 9, true, alpha1, beta1,13);
					else pomniz[redosled[i]] = -50000;
					int maxpom = -50000;
					int pomkof = 0;
					for (int i = 0; i < 7; i++)
						if (pomniz[i]>maxpom){ maxpom = pomniz[i]; pomkof = i; }

					dc.Ellipse(pomkof * 100 + 23, (5 - niz[pomkof]) * 100 + 23,
						pomkof * 100 + 117, (5 - niz[pomkof]) * 100 + 117);
					brojac = -brojac + 1;
					mat[niz[pomkof]][pomkof] = -(brojac == 0) + (brojac == 1);
					gotovo = gg(pomkof);
					int volumeLevel = (-(brojac == 0) + (brojac == 1))*ocena(-(brojac == 0) + (brojac == 1));
					volumeLevel += -(-(brojac == 0) + (brojac == 1))*ocena(-(-(brojac == 0) + (brojac == 1)));
					helper = 0;
					nothelper = 0;
					//table.clear();
					niz[pomkof] = niz[pomkof] + 1;
					//	bmDC.SelectObject(pOldbmp);
					//AfxMessageBox(_T("Ocitano je    "));
					pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);
					dc.Ellipse(780, 20, 880, 120);


					if (gotovo == true)
						SetDlgItemText(IDC_REZULTAT, _T("Pobedio je BOT"));



			}
		}

		
		
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}




void CSPDialogDlg::OnBnClickedNew()
{
	CClientDC dc(this);
	CBrush* pTempBrush = NULL;
	pTempBrush = (CBrush*)dc.SelectObject(CreateSolidBrush(RGB(140, 140, 140)));
	dc.Rectangle(20, 20, 720, 620);
	pTempBrush = (CBrush*)dc.SelectObject(CreateSolidBrush(RGB(255, 255, 255)));

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 6; j++)
			dc.Ellipse(i * 100 + 23, j * 100 + 23, i * 100 + 117, j * 100 + 117);
	brojac = 1;
	for (int i = 0; i < 7; i++)
	{
		niz[i] = 1;
	}

	pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);
	dc.Ellipse(780, 20, 880, 120);


	ocenat = 0;
	gotovo = false;
	int volumeLevel = ocenat;
	tstringstream stros;
	stros << volumeLevel;
	for (int i = 0; i < 7; i++)
		niz[i] = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			mat[i][j] = 0;
	bot = 0;
	/*tstringstream stros1;
	volumeLevel = pomoc;
	stros1 << volumeLevel;*/
	//table.clear();
	SetDlgItemText(IDC_REZULTAT, _T(" "));

}





void CSPDialogDlg::OnBnClickedBot()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	CBrush* pTempBrush = NULL;
	pTempBrush = (CBrush*)dc.SelectObject(CreateSolidBrush(RGB(140, 140, 140)));
	dc.Rectangle(20, 20, 720, 620);
	pTempBrush = (CBrush*)dc.SelectObject(CreateSolidBrush(RGB(255, 255, 255)));
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 6; j++)
			dc.Ellipse(i * 100 + 23, j * 100 + 23, i * 100 + 117, j * 100 + 117);
		brojac = 1;
		for (int i = 0; i < 7; i++)
		{
			niz[i] = 1;
		}
		
		pTempBrush = (CBrush*)dc.SelectObject(&boje[brojac]);
		dc.Ellipse(780, 20, 880, 120);


		ocenat = 0;
		gotovo = false;
		int volumeLevel = ocenat;
		tstringstream stros;
		stros << volumeLevel;
		for (int i = 0; i < 7; i++)
			niz[i] = 0;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 7; j++)
				mat[i][j] = 0;
		bot = 1;
		//table.clear();
		SetDlgItemText(IDC_REZULTAT, _T(" "));
}


