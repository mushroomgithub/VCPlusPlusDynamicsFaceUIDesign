#if !defined(AFX_HOVERBUTTON_H__1155737E_628E_11D2_81B5_0020AFC24C58__INCLUDED_)
#define AFX_HOVERBUTTON_H__1155737E_628E_11D2_81B5_0020AFC24C58__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HoverButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHoverButton window
enum BUTTON_STATE{ BUTTON_OFF, BUTTON_ON, BUTTON_OVER, BUTTON_GREYED};

class CHoverButton : public CBitmapButton
{
// Construction
public:
	// Constructor: default is to use buttons defined in our resources
	CHoverButton();
// Attributes
public:
	// The only way of accessing data from outside this class is to call these 2 functions
	BUTTON_STATE GetButtonState(void) {	return(m_ButtonState);};//返回按钮状态
	BUTTON_STATE SetButtonState(BUTTON_STATE nState);           //设置按钮状态

private:
	BOOL			m_bMouseTracking;	//鼠标跟踪标志
	BUTTON_STATE	m_ButtonState;		//按钮状态
	CBitmap			m_bmpButtonDown;	//四个位图对象，对应不同状态
	CBitmap			m_bmpButtonFocussed;
	CBitmap			m_bmpButtonUp;
	CBitmap			m_bmpButtonDisabled;
	HWND			m_hWndOld;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHoverButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL
private:
	// Called by OnMouseMove() when entering/leaving the button
	void OnMouseLeave(void);		//鼠标离开时调用
	void OnMouseEnter(void);		//鼠标进入时调用

// Implementation
public:
	void SetTextColorOn(COLORREF cr);
	COLORREF crColorOn;
	int b;
	int g;
	int r;
	void SetTextColor(int R,int G,int B);
	void SetFormat(UINT nFormat);
	UINT m_nFormat;
	void InitOffset(int x,int y);
	int m_iOffsetY;
	int m_iOffsetX;
	virtual ~CHoverButton();
	BOOL LoadBitmaps(UINT nBitmapUp, UINT nBitmapDown, UINT nBitmapFocus, UINT nBitmapDisabled);
	BOOL LoadBitmaps(LPCSTR lpszBitmapUp, LPCSTR lpszBitmapDown, LPCSTR lpszBitmapFocus, LPCSTR lpszBitmapDisabled);
	CString Tooltip;
	int m_Tooltip_Y;
	int m_Tooltip_X;
	// Generated message map functions
protected:
	//{{AFX_MSG(CHoverButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVERBUTTON_H__1155737E_628E_11D2_81B5_0020AFC24C58__INCLUDED_)

