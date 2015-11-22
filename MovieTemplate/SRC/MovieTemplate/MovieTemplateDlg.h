
// MovieTemplateDlg.h : header file
//

#pragma once
#include "OpenCVTemplate.h"
#include "afxwin.h"
#include "opencv/cv.h"
#include "CvvImage.h"

// CMovieTemplateDlg dialog
class CMovieTemplateDlg : public CDialogEx
{
// Construction
public:
	CMovieTemplateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MOVIETEMPLATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	//OpenCV
	OpenCVTemplate opencv;
	void DrawImage(IplImage* src, CStatic* m_video);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CStatic m_video_input;
	CStatic m_video_output;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
