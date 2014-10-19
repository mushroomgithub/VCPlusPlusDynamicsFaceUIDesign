// MFCDlg.h : header file
//
//{{AFX_INCLUDES()
#include "shockwaveflash1.h"
//}}AFX_INCLUDES

#if !defined(AFX_MFCDLG_H__B757BE68_4D9D_4CBC_9AB3_49C8D05A0BCA__INCLUDED_)
#define AFX_MFCDLG_H__B757BE68_4D9D_4CBC_9AB3_49C8D05A0BCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "HoverButton.h"
/////////////////////////////////////////////////////////////////////////////
// CMFCDlg dialog

class CMFCDlg : public CDialog
{
// Construction
public:
	CImageList Cil2;
	CImageList Cil1;
//	CTreeCtrl m_treeCtrl;
	CMFCDlg(CWnd* pParent = NULL);	// standard constructor
	~CMFCDlg();
// Dialog Data
	//{{AFX_DATA(CMFCDlg)
	enum { IDD = IDD_MFC_DIALOG };
	CTreeCtrl	m_treeCtrl;
	CListCtrl	m_listCtrlView;
	CSliderCtrl	m_Slider;
	CListBox	m_List;
	int		m_Radio;
	BOOL	m_Distribute;
	BOOL	m_Shuxue;
	BOOL	m_English;
	BOOL	m_Network;
	CShockwaveFlash	m_ShockwaveFlash;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOk();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCancelMode();
	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOpenswf();
	afx_msg void OnCloseswf();
	afx_msg void OnPlayswf2();
	//}}AFX_MSG
	afx_msg void OnExit();
	afx_msg void OnHelp();
	afx_msg void OnMinimize();
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTitle;
	char title[255];
	HTREEITEM m_CurItem;
	//HTREEITEM m_NextItem;
	//HTREEITEM m_PreItem;
	BOOL m_bOK;
	int m_int;
	CString m_strIT;
	CString m_strWuli;
	CString m_strNetwork;
	CString m_strEnglish;
	CString m_strDistribute;
	CString m_strShuxue;
	CString m_strRadio;
	CToolTipCtrl *m_pToolTipCtrl;
	CBitmap m_bg;
public:
	CBrush m_Brush;
	CHoverButton m_Minimize;
	CHoverButton m_Exit;
	CHoverButton m_Help;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDLG_H__B757BE68_4D9D_4CBC_9AB3_49C8D05A0BCA__INCLUDED_)
