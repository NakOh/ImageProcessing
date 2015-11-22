
// MovieTemplateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MovieTemplate.h"
#include "MovieTemplateDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _DEF_VIDEO	1000

// CMovieTemplateDlg dialog



CMovieTemplateDlg::CMovieTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMovieTemplateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMovieTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO_INPUT, m_video_input);
	DDX_Control(pDX, IDC_VIDEO_OUTPUT, m_video_output);
}

BEGIN_MESSAGE_MAP(CMovieTemplateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMovieTemplateDlg message handlers

BOOL CMovieTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMovieTemplateDlg::OnPaint()
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


int CMovieTemplateDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//video file open
	
	opencv = OpenCVTemplate("V0206-cinepak.avi");


	if (!opencv.isOpened()){
		AfxMessageBox(_T("Can't open video file!!!"));
	}
	else{
		this->SetTimer(_DEF_VIDEO, 33, NULL);
	}
	return 0;
}


void CMovieTemplateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == _DEF_VIDEO){
		if (opencv.getImage()){
			DrawImage(new IplImage(opencv.getOriginal()), &m_video_input);
			DrawImage(new IplImage(opencv.EdgeDetection(opencv.getOriginal())), &m_video_output);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
void CMovieTemplateDlg::DrawImage(IplImage* src, CStatic* m_video){
	CDC * pDC;
	CRect rect;

	pDC = m_video->GetDC();
	m_video->GetClientRect(rect);

	CvvImage m_cImage;
	m_cImage.CopyOf(src);
	m_cImage.DrawToHDC(pDC->m_hDC, rect);

	ReleaseDC(pDC);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMovieTemplateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
