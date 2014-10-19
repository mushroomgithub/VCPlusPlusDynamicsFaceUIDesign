// HoverButton.cpp : implementation file
//

#include "stdafx.h"
#include "HoverButton.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHoverButton

BEGIN_MESSAGE_MAP(CHoverButton, CBitmapButton)
	//{{AFX_MSG_MAP(CHoverButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHoverButton construction / destruction

CHoverButton::CHoverButton()
{
	// To start with, the button is switched off and we are NOT tracking the mouse
	//缺省状态为OFF，不跟踪鼠标
	m_ButtonState		= BUTTON_OFF;
	m_bMouseTracking	= FALSE;
	m_iOffsetX=0;
	m_iOffsetY=10;
	m_nFormat=DT_CENTER;
	r=g=b=0;
	crColorOn =  RGB(0xFF,0xFF,0xFF);
}

CHoverButton::~CHoverButton()
{
}

/////////////////////////////////////////////////////////////////////////////
// CHoverButton message handlers

void CHoverButton::OnMouseMove(UINT nFlags, CPoint point) //鼠标移动事件
{
	CBitmapButton::OnMouseMove(nFlags, point);

	// 1. Mouse has moved and we are not tracking this button, or 
	// 2. mouse has moved and the cursor was not above this window
	// == Is equivalent to WM_MOUSEENTER (for which there is no message)
	if((!m_bMouseTracking || GetCapture()!=this) && (m_ButtonState == BUTTON_OFF))
	{
		OnMouseEnter();
	}
	else 
	{
		if(m_ButtonState == BUTTON_OVER)
		{
			CRect rc;
			GetClientRect(&rc);
			if(!rc.PtInRect(point))	// The mouse cursor is no longer above this button
				OnMouseLeave();
		}
	}
//	::SetCursor(AfxGetApp()->LoadCursor(IDC_MYCURSOR));
}

void CHoverButton::OnMouseEnter(void)
{
	// We are now tracking the mouse, OVER this button
	m_bMouseTracking = TRUE;
	m_ButtonState = BUTTON_OVER;
	
	SetCapture();
	Invalidate();
	UpdateWindow();
}

void CHoverButton::OnMouseLeave(void)
{
	// We are not tracking the mouse, this button is OFF.
	m_ButtonState = BUTTON_OFF;
	m_bMouseTracking = FALSE;

	// Release mouse capture from the button and restore normal mouse input
	Invalidate();
	UpdateWindow();
	ReleaseCapture();
}

void CHoverButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	HMODULE hmod=AfxGetResourceHandle(); 
//	HRSRC hSndResource=FindResource(hmod,MAKEINTRESOURCE(IDR_CLICKBUTTON),_T("WAVE"));
//	HGLOBAL hGlobalMem=LoadResource(hmod,hSndResource);
//	LPCTSTR lpMemSound=(LPCSTR)LockResource(hGlobalMem);
//	sndPlaySound(lpMemSound,SND_MEMORY|SND_SYNC);
//	FreeResource(hGlobalMem);

	SetButtonState(BUTTON_OFF);			// Highlight button
	CBitmapButton::OnLButtonUp(nFlags, point);
}

// Purpose:		Set the new state of the button 
// Return:		Returns the old state of the button
// Parameters:	nState = Either ON or OFF. The default is OFF. This is NOT tri-state button!
BUTTON_STATE CHoverButton::SetButtonState(BUTTON_STATE nState) 
{
	BUTTON_STATE nOldState = (BUTTON_STATE)GetCheck();
	
	m_ButtonState = nState;
	switch(m_ButtonState)
	{
	case BUTTON_ON:
		EnableWindow(TRUE);
		SetState(BUTTON_ON);
		break;
	case BUTTON_GREYED:
		EnableWindow(FALSE);
		break;
	case BUTTON_OVER:
		EnableWindow(TRUE);
		SetState(BUTTON_OVER);
		break;
	default:
		EnableWindow(TRUE);
		SetState(BUTTON_ON);
		m_ButtonState =nOldState;			//BUTTON_OFF;
		break;
	}
	return(nOldState);
}

// Draws the buttons in their relevant state, and text labels
void CHoverButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC			memDC;
	CBitmap*	pOld=NULL;
	CBitmap*	pBitmap=NULL;
	CDC*		pDC;
	CRect		rc;
	int			iSaveDC;

	pDC= CDC::FromHandle(lpDrawItemStruct->hDC);
	memDC.CreateCompatibleDC(pDC);
	VERIFY(pDC);
	iSaveDC=pDC->SaveDC();
	rc.CopyRect(&lpDrawItemStruct->rcItem);
	pDC->SetBkMode(TRANSPARENT);	//设置背景模式为透明
	pDC->SetTextColor(GetSysColor(COLOR_WINDOWFRAME));// 黑色文本
	switch(m_ButtonState)	//判断按钮状态
	{
	case BUTTON_ON:		//选中按钮
		pDC->SetTextColor(crColorOn);
		pBitmap=&m_bmpButtonDown;
		break;
	case BUTTON_OVER:	//鼠标滑过
		pDC->SetTextColor(crColorOn);
		pBitmap=&m_bmpButtonFocussed;
		break;
	case BUTTON_GREYED:	//禁止
		pBitmap=&m_bmpButtonDisabled;
		break;
	default:
		pDC->SetTextColor(RGB(r,g,b));
		pBitmap=&m_bmpButtonUp;
		break;
	}

	CString		strTitle;
	GetWindowText(strTitle);	//取得按钮文本

	if (pBitmap->m_hObject)
	{
		CRect	rcBitmap(rc);
		BITMAP	bmpInfo;			
		CSize	size;

		// 文本
		size = pDC->GetTextExtent(strTitle);
		rcBitmap.OffsetRect(size.cx+5,0);

		// 绘制位图
		if(!pBitmap->GetBitmap(&bmpInfo))
			return;
		pOld=memDC.SelectObject((CBitmap*) pBitmap);  //恢复现场
		if (pOld==NULL) 
			return; //Destructors will clean up

		if(!pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY))
			return;
		memDC.SelectObject(pOld);	
		if(memDC==NULL)
			return;
	}

	CRect	rcText(rc);			//绘图区域
	UINT nFormat = m_nFormat;	//居中LEFT;//

	if(m_ButtonState == BUTTON_GREYED)
	{							//如果为禁止状态则分两次绘制文本，显示立体状态
		rcText.OffsetRect(1,1);
		pDC->SetTextColor(GetSysColor(COLOR_BTNHIGHLIGHT));
		pDC->DrawText(strTitle,rcText,nFormat);
		rcText.OffsetRect(-1,-1);
		pDC->SetTextColor(GetSysColor(COLOR_BTNSHADOW));	//阴影色
		pDC->DrawText(strTitle,rcText,nFormat);
	} 
	else
	{
		//pDC->SetTextColor(RGB(255,255,255));
		rcText.OffsetRect(m_iOffsetX,m_iOffsetY);
		//rcText.OffsetRect(2,9);
		pDC->DrawText(strTitle,rcText,nFormat);		//其他状态直接绘制文本
		
	}
	pDC->RestoreDC(iSaveDC);
}

BOOL CHoverButton::LoadBitmaps(UINT nBitmapUp, UINT nBitmapDown, 
							   UINT nBitmapFocus, UINT nBitmapDisabled)
{
	return LoadBitmaps(MAKEINTRESOURCE(nBitmapUp),
						MAKEINTRESOURCE(nBitmapDown),
						MAKEINTRESOURCE(nBitmapFocus),
						MAKEINTRESOURCE(nBitmapDisabled));
}

BOOL CHoverButton::LoadBitmaps(LPCSTR lpszBitmapUp, LPCSTR lpszBitmapDown, 
							   LPCSTR lpszBitmapFocus, LPCSTR lpszBitmapDisabled)
{
	BOOL bAllLoaded=TRUE;

	//Delete old ones
	m_bmpButtonDown.DeleteObject();
	m_bmpButtonFocussed.DeleteObject();
	m_bmpButtonUp.DeleteObject();
	m_bmpButtonDisabled.DeleteObject();
	
	if (!m_bmpButtonUp.LoadBitmap(lpszBitmapUp))
	{
		TRACE0("Failed to load up bitmap of bitmap button\n");
		return FALSE;
	}

	if (lpszBitmapDown!=NULL)
	{
		if (!m_bmpButtonDown.LoadBitmap(lpszBitmapDown))
		{
			TRACE0("Failed to load down bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (lpszBitmapFocus!=NULL)
	{
		if (!m_bmpButtonFocussed.LoadBitmap(lpszBitmapFocus))
		{
			TRACE0("Failed to load focussed bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (lpszBitmapDisabled!=NULL)
	{
		if (!m_bmpButtonDisabled.LoadBitmap(lpszBitmapDisabled))
		{
			TRACE0("Failed to load disabled bitmap of bitmap button\n");
			return bAllLoaded=FALSE;
		}
	}
	return bAllLoaded;
}

void CHoverButton::InitOffset(int x, int y)
{
	m_iOffsetX=x;
	m_iOffsetY=y;
}

void CHoverButton::SetFormat(UINT nFormat)
{
	m_nFormat=nFormat;
}

void CHoverButton::SetTextColor(int R, int G, int B)
{
	r=R;
	g=G;
	b=B;
}

void CHoverButton::SetTextColorOn(COLORREF cr)
{
	crColorOn = cr;
}

