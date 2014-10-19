// MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "HoverButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDlg dialog

CMFCDlg::CMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCDlg::IDD, pParent)
{
	m_bOK=FALSE;
	//{{AFX_DATA_INIT(CMFCDlg)
	m_Radio = -1;
	m_Distribute = FALSE;
	m_Shuxue = FALSE;
	m_English = FALSE;
	m_Network = FALSE;
	m_int=0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CMFCDlg::~CMFCDlg()
{
		delete m_pToolTipCtrl;

}
void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCDlg)
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
	DDX_Control(pDX, IDC_LIST1, m_listCtrlView);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Radio(pDX, IDC_WULI_RADIO, m_Radio);
	DDX_Check(pDX, IDC_CK_DISTRIBUTE, m_Distribute);
	DDX_Check(pDX, IDC_CK_SHUXUE, m_Shuxue);
	DDX_Check(pDX, IDC_CK_ENGLISH, m_English);
	DDX_Check(pDX, IDC_CK_NETWORK, m_Network);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH, m_ShockwaveFlash);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_WM_HSCROLL()
	ON_WM_CANCELMODE()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, OnClickTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENSWF, OnOpenswf)
	ON_BN_CLICKED(IDC_CLOSESWF, OnCloseswf)
	ON_BN_CLICKED(IDC_PLAYSWF2, OnPlayswf2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_EXIT,OnExit)
	ON_BN_CLICKED(IDB_HELP,OnHelp)
	ON_BN_CLICKED(IDB_MINIMIZE,OnMinimize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDlg message handlers

BOOL CMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ShowWindow(SW_SHOWMAXIMIZED);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
//	SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_bg.LoadBitmap(IDB_BITMAP1);//加载背景图片
	//m_bg.LoadBitmap(IDB_BACKGROUND1);
	//m_pToolTipCtrl->EnableToolTips(TRUE);
//	m_pToolTipCtrl->Activate(TRUE);

	m_ShockwaveFlash.SetBackgroundColor((long)RGB(100,255,100));//为Flash插件设置背景色

	CBitmap m_tmp;
	BITMAP Bmp;
	m_tmp.LoadBitmap(IDB_EXIT1);
	m_tmp.GetBitmap(&Bmp);
	m_Exit.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_EXIT);
	m_Exit.ShowWindow(SW_SHOW);
	m_Exit.MoveWindow(1400,0,Bmp.bmWidth,Bmp.bmHeight);
	m_Exit.LoadBitmaps(IDB_EXIT1,
		NULL,
		IDB_EXIT2,
		IDB_EXIT1);
	m_tmp.DeleteObject();
//	m_pToolTipCtrl->AddTool(&m_Exit,"关闭");

	m_tmp.LoadBitmap(IDB_HELP1);
	m_tmp.GetBitmap(&Bmp);
	m_Help.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_HELP);
	m_Help.ShowWindow(SW_SHOW);
	m_Help.MoveWindow(1375,0,Bmp.bmWidth,Bmp.bmWidth,Bmp.bmHeight);
	m_Help.LoadBitmaps(IDB_HELP1,
		NULL,
		IDB_HELP2,
		IDB_HELP1);
	m_tmp.DeleteObject();
	//m_pToolTipCtrl->AddTool(&m_Help,"关于");

	m_tmp.LoadBitmap(IDB_MINIMIZE1);
	m_tmp.GetBitmap(&Bmp);
	m_Minimize.Create(NULL,BS_OWNERDRAW,CRect(0,0,Bmp.bmWidth,Bmp.bmHeight),this,IDB_MINIMIZE);
	m_Minimize.ShowWindow(SW_SHOW);
	m_Minimize.MoveWindow(1346,0,Bmp.bmWidth,Bmp.bmHeight);
	m_Minimize.LoadBitmaps(IDB_MINIMIZE1,
		NULL,
		IDB_MINIMIZE2,
		IDB_MINIMIZE1);
	m_tmp.DeleteObject();
//	m_pToolTipCtrl->AddTool(&m_Minimize,"最小化");

	m_Slider.SetRange(0,100);//设置滑块的范围
	m_Slider.SetTicFreq(10);//设置滑块每对少单位画一个刻度
	m_Slider.SetPageSize(30);//设置按下PageDown和PageUp按钮时滑动间隔
	m_Slider.SetLineSize(20);//设置滑块左右箭头滑动间隔
	m_Slider.SetPos(50);//设置滑块当前位置
	m_int=m_Slider.GetPos();//获得程序刚开始运行时，滑块所在的位置

	m_listCtrlView.ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING,0);
	m_listCtrlView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
    /*LV_COLUMN comn;//LV_COLUMN结构体与LVCOLUMN结构体是一样的，可以相互替换
	comn.pszText ="匹配规则";
	comn.mask =LVCF_TEXT;//此时pszText有效
	m_listCtrlView.InsertColumn(0,&comn);
	m_listCtrlView.SetColumnWidth(0,80);
    
	comn.pszText ="级别";
	comn.mask = LVCF_TEXT;
	m_listCtrlView.InsertColumn(1,&comn);
	m_listCtrlView.SetColumnWidth(1,80);*/
	LVCOLUMN lvColumn;//需要设置列表控件列的属性；即属性-样式-查看，将查看项修改为报告样式
	char Header[5][10]={"匹配规则","级别","大小","修改日期","详细信息"};
	for(int i=0;i<5;i++)
		
	{
		lvColumn.mask=LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH|LVCF_FMT;
		lvColumn.fmt=LVCFMT_LEFT;//对齐方式
		lvColumn.iSubItem=i;//列索引
		lvColumn.pszText=Header[i];//表头文本
		lvColumn.cx=100;//设置列宽
		m_listCtrlView.InsertColumn(i,&lvColumn);//将新列插入到列表控件中
	}
	m_listCtrlView.SetColumnWidth(3,200);//将第四列宽度增大一倍
	
	CTime time=::GetCurrentTime();
	CString strTime=time.Format("%Y/%m/%d");
	
	m_listCtrlView.InsertItem(0,"北京");//插入新行
	m_listCtrlView.SetItemText(0,1,"长城");
	m_listCtrlView.SetItemText(0,2,"4KB");
	m_listCtrlView.SetItemText(0,3,strTime);
	m_listCtrlView.SetItemText(0,4,"首都北京");

	m_listCtrlView.InsertItem(1,"上海");
	m_listCtrlView.SetItemText(1,1,"发展");
	m_listCtrlView.SetItemText(1,2,"2MB");
	m_listCtrlView.SetItemText(1,3,strTime);
	m_listCtrlView.SetItemText(1,4,"上海金融中心");

	m_listCtrlView.InsertItem(2,"深圳");
	m_listCtrlView.SetItemText(2,1,"花期");
	m_listCtrlView.SetItemText(2,2,"2KB");
	m_listCtrlView.SetItemText(2,3,strTime);
	m_listCtrlView.SetItemText(2,4,"深圳就业服务部");

	m_listCtrlView.InsertItem(3,"广州");
	m_listCtrlView.SetItemText(3,1,"东莞");
	m_listCtrlView.SetItemText(3,2,"6KB");
	m_listCtrlView.SetItemText(3,3,strTime);
	m_listCtrlView.SetItemText(3,4,"东莞回来的你懂得");
	
	m_listCtrlView.InsertItem(4,"湖南");
	m_listCtrlView.SetItemText(4,1,"长沙");
	m_listCtrlView.SetItemText(4,2,"4KB");
	m_listCtrlView.SetItemText(4,3,strTime);
	m_listCtrlView.SetItemText(4,4,"湖南湘潭医疗事故");

	m_listCtrlView.InsertItem(5,"江西");
	m_listCtrlView.SetItemText(5,1,"南昌");
	m_listCtrlView.SetItemText(5,2,"12KB");
	m_listCtrlView.SetItemText(5,3,strTime);
	m_listCtrlView.SetItemText(5,4,"江西老乡会");

	m_listCtrlView.InsertItem(6,"江苏");
	m_listCtrlView.SetItemText(6,1,"南京");
	m_listCtrlView.SetItemText(6,2,"1KB");
	m_listCtrlView.SetItemText(6,3,strTime);
	m_listCtrlView.SetItemText(6,4,"南京好地方啊");

	m_listCtrlView.InsertItem(7,"浙江");
	m_listCtrlView.SetItemText(7,1,"杭州");
	m_listCtrlView.SetItemText(7,2,"2KB");
	m_listCtrlView.SetItemText(7,3,strTime);
	m_listCtrlView.SetItemText(7,4,"杭州IT行业发达");

	m_listCtrlView.InsertItem(8,"广西");
	m_listCtrlView.SetItemText(8,1,"南宁");
	m_listCtrlView.SetItemText(8,2,"8KB");
	m_listCtrlView.SetItemText(8,3,strTime);
	m_listCtrlView.SetItemText(8,4,"广西大学欢迎你");
	
	m_listCtrlView.InsertItem(9,"甘肃");
	m_listCtrlView.SetItemText(9,1,"兰州");
	m_listCtrlView.SetItemText(9,2,"16KB");
	m_listCtrlView.SetItemText(9,3,strTime);
	m_listCtrlView.SetItemText(9,4,"兰州大学时985啊");
	m_listCtrlView.ShowWindow(TRUE);
	
	m_List.ModifyStyle(LVS_SORTDESCENDING | LVS_SORTASCENDING,0);
	m_List.AddString("hello");
	m_List.AddString("world");
	m_List.AddString("birthday");
	m_List.AddString("success");
	m_List.AddString("come on");
	m_List.SetCurSel(0);//设置列表框开始第一顶处于选中状态

	m_pToolTipCtrl=new CToolTipCtrl;//给树控件创建提示控件，显示提示信息
	if(!m_pToolTipCtrl->Create(this,TTS_ALWAYSTIP))
	{
		TRACE("Uable to Create ToolTip\n");
		return FALSE;
	}
	CMFCApp *pApp=(CMFCApp *)AfxGetApp();//创建图象列表
	Cil1.Create(16,16,ILC_COLOR,2,2);
	
	Cil1.Add(pApp->LoadIcon(IDI_ICON1));
	Cil1.Add(pApp->LoadIcon(IDI_ICON2));
	  
	m_treeCtrl.SetImageList(&Cil1,TVSIL_NORMAL); //设置图象列表
	//m_treeCtrl.SetImageList(&Cil2,TVSIL_NORMAL);//此程序中Cil2没有用到

	DWORD dwStyles=GetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE);//获取树控制原风格
	dwStyles|=TVS_EDITLABELS|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	SetWindowLong(m_treeCtrl.m_hWnd,GWL_STYLE,dwStyles);//设置风格
	m_treeCtrl.ModifyStyle(LVS_SORTASCENDING|LVS_SORTDESCENDING,0);
	HTREEITEM hRoot,hRoot1,hItem,hItem1,hSubItem,hSubItem1;
	//hItem = m_treeCtrl.InsertItem("Parent1",0,1,TVI_ROOT);
	hItem = m_treeCtrl.InsertItem("IT论坛",0,1,TVI_ROOT);
	
	hRoot = hItem;//保存根节点句柄
	//hSubItem = m_treeCtrl.InsertItem("child1",0,1,hItem);

		hSubItem = m_treeCtrl.InsertItem("版主模块",0,1,hItem);

	//hSubItem = m_treeCtrl.InsertItem("child2",0,1,hItem,hSubItem);//在child1后添加child2

		hSubItem = m_treeCtrl.InsertItem("游客模块",0,1,hItem,hSubItem);

	//hSubItem = m_treeCtrl.InsertItem("child3",0,1,hItem,hSubItem);//在child2后面添加child3

		hSubItem = m_treeCtrl.InsertItem("新用户注册",0,1,hItem,hSubItem);
	
	//hItem = m_treeCtrl.InsertItem("Parent2",0,1,TVI_ROOT,hItem);//新的父节点与根节点同级

		hItem = m_treeCtrl.InsertItem("后台维护",0,1,TVI_ROOT,hItem);//新的父节点与根节点同级

	//hItem = m_treeCtrl.InsertItem("Parent3",0,1,TVI_ROOT,hItem);//新的父节点
	
		hItem = m_treeCtrl.InsertItem("评论",0,1,TVI_ROOT,hItem);//新的父节点与根节点同级

	
		hItem1=m_treeCtrl.InsertItem("程序员模块",1,0,TVI_ROOT);
		hRoot1=hItem1;
		hSubItem1=m_treeCtrl.InsertItem("C++/MFC模块",1,0,hItem1);
		hSubItem1=m_treeCtrl.InsertItem("C程序模块",1,0,hItem1,hSubItem1);

		hItem1=m_treeCtrl.InsertItem("招聘信息",1,0,TVI_ROOT,hItem1);
		hItem1=m_treeCtrl.InsertItem("论坛下载服务区",1,0,TVI_ROOT,hItem1);
		m_treeCtrl.Expand(hRoot1,TVE_EXPAND);
		
	m_treeCtrl.Expand(hRoot,TVE_EXPAND);//展开树状控件所有节点
	CRect r;
	m_treeCtrl.GetItemRect(hRoot,&r,TRUE);
	m_pToolTipCtrl->AddTool(&m_treeCtrl,"TreeCtrl Item Info",&r,IDC_TREE1);
	
	memset(title,0,255);
	//GetPrivateProfileString("参数设置","主界面标题","蘑菇控件测试程序",m_strTitle.GetBuffer(255),255,".\\Mogu.ini");//输出标题不适合用CString对象，应用char数组
	GetPrivateProfileString("参数设置","主界面标题","蘑菇控件测试程序",title,255,".\\Mogu.ini");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
	////////////////////////////////////////给对话框创建背景图片
	CDC *hDC=GetDC();
	CDC m_DC;
	CRect rect;
	m_DC.CreateCompatibleDC(hDC);
	m_DC.SelectObject(&m_bg);
	GetClientRect(rect);
	hDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_DC,0,0,SRCCOPY);
	//hDC->StretchBlt(0,0,rect.Width(),rect.Height(),&m_DC,0,0,rect.Width(),rect.Height(),SRCCOPY);
	ReleaseDC(hDC);
	/////////////////////////////////////////从配置文件中读取程序标题内容，并显示在应用程序主窗口的左上角位置
	CClientDC dc(this);
	CFont font;
	font.CreatePointFont(120,"楷体",NULL);
	CFont *pOldFont=dc.SelectObject(&font);
	dc.SetTextColor(RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);
	//MessageBox(m_strTitle);
	//dc.TextOut(5,5,m_strTitle);
	dc.TextOut(5,5,title);
	dc.SelectObject(pOldFont);
	
	m_Exit.RedrawWindow();
	m_Help.RedrawWindow();
	m_Minimize.RedrawWindow();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCDlg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	if(!m_bOK)
	{
		
		UpdateData(TRUE);//自己总是忘记获得控件变量值，注意不要忘记UpdateData(TRUE)函数
		if(m_Shuxue)
		{
			GetDlgItem(IDC_CK_SHUXUE)->GetWindowText(m_strShuxue);
			//	MessageBox(m_strShuxue,"选课信息",MB_OKCANCEL);
			m_List.AddString(m_strShuxue);
		}
		if(m_Distribute)
		{
			GetDlgItem(IDC_CK_DISTRIBUTE)->GetWindowText(m_strDistribute);
			//	MessageBox(m_strDistribute,"选课信息",MB_OKCANCEL);
			m_List.AddString(m_strDistribute);
		}
		if(m_English)
		{
			GetDlgItem(IDC_CK_ENGLISH)->GetWindowText(m_strEnglish);
			//	MessageBox(m_strEnglish,"选课信息",MB_OKCANCEL);
			m_List.AddString(m_strEnglish);
		}
		if(m_Network)
		{
			GetDlgItem(IDC_CK_NETWORK)->GetWindowText(m_strNetwork);
			//	MessageBox(m_strNetwork,"选课信息",MB_OKCANCEL);
			m_List.AddString(m_strNetwork);
		}
		switch(m_Radio)
		{
		case 0:
			GetDlgItemText(IDC_WULI_RADIO,m_strRadio);
			//	MessageBox(m_strRadio,"专业信息",MB_OKCANCEL);
			break;
		case 1:
			GetDlgItemText(IDC_IT_RADIO,m_strRadio);
			//	MessageBox(m_strRadio,"专业信息",MB_OKCANCEL);
			break;
		case 2:
			GetDlgItemText(IDC_DIANQI_RADIO,m_strRadio);
			//	MessageBox(m_strRadio,"专业信息",MB_OKCANCEL);
			break;
		default:
			break;
		}
		m_List.AddString(m_strRadio);
		CString m_strSlider;
		m_strSlider.Format("当前Slider值为:%d",m_int);
		m_List.AddString(m_strSlider);
		m_bOK=TRUE;
	}

}

void CMFCDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) //用于获得当前滑块的值，对于滑块是没有响应滑块滑动的消息响应函数的，但是我们可以再煮窗体中添加WM_HSCROLL消息，在此函数中处理以下代码获得滑块的当前位置
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl *pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	m_int=pSlider->GetPos();//获得鼠标滑动滑块之后的滑块所在位置的值
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMFCDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

BOOL CMFCDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pToolTipCtrl)
	{
		m_pToolTipCtrl->RelayEvent(pMsg);
	}

	if(pMsg->message==WM_KEYDOWN)//创建热键组合
	{
		switch(pMsg->wParam)
		{
		case 'L':
			if(::GetKeyState(VK_CONTROL)<0)
			{
				MessageBox("组合键 Ctrl+L 被按下");
			}
			break;
		case 'K':
			if(::GetKeyState(VK_SHIFT)<0)
			{
				MessageBox("组合键 Shift+K 被按下");
			}
			break;
		case VK_RETURN:
			OnExit();
			return 0;
			break;
		case VK_ESCAPE:
			OnExit();
			return 0;
			break;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMFCDlg::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult) //树控件鼠标左键单击事件响应函数
{
	// TODO: Add your control notification handler code here
	
	CPoint curPoint;
    UINT nFlags;//获取坐标所在处item的标记
    HTREEITEM hItem;
	CString strItem;
    GetCursorPos(&curPoint); //当前点坐标
    m_treeCtrl.ScreenToClient(&curPoint); //屏幕坐标转换为TREE内坐标
    hItem = m_treeCtrl.HitTest(curPoint, &nFlags); //坐标是否有ITEM

    if(hItem && (TVHT_ONITEM & nFlags)) //判断是否有HTREEITEM
    {
		MessageBox("树控件节点响应鼠标左键单击事件");
		//m_CurItem=m_treeCtrl.GetSelectedItem();
    }

	*pResult = 0;
}

void CMFCDlg::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult) //树控件鼠标右键单击事件响应函数
{
	// TODO: Add your control notification handler code here
	CPoint curPoint;
	UINT nFlags;
	HTREEITEM hItem;
	GetCursorPos(&curPoint);
	m_treeCtrl.ScreenToClient(&curPoint);//将屏幕坐标转换为TREE内坐标
	hItem=m_treeCtrl.HitTest(curPoint,&nFlags);
	if(hItem&&(TVHT_ONITEM&nFlags))
	{
		MessageBox("树控件节点鼠标右键单击事件");
	//	m_CurItem=m_treeCtrl.GetSelectedItem();
		
	}
	*pResult = 0;
}

void CMFCDlg::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)//
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	
	
	pNMTreeView->itemNew.iImage;
	pNMTreeView->itemOld.iImage;
	if(pNMTreeView->itemOld.iImage)
	{
		MessageBox("鼠标从一个节点转移到另外一个节点");
	}
	*pResult = 0;
}
void CMFCDlg::OnExit()
{
	DestroyWindow();
}
void CMFCDlg::OnHelp()
{
	MessageBox("本程序由小蘑菇测试完成\n\n联系方式:13547946476646\n\n现就读于辽宁大学信息学院","树形控件测试",MB_OK);
}
void CMFCDlg::OnMinimize()
{
	ShowWindow(SW_SHOWMINIMIZED);
}

void CMFCDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) //响应列表控件单击事件
{
	// TODO: Add your control notification handler code here
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//MessageBox(pNMTreeView->itemNew.pszText);
	char Text[255];
	m_listCtrlView.GetItemText(0,0,Text,255);
	MessageBox(Text);
	*pResult = 0;
}

void CMFCDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

HBRUSH CMFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd==this)//重画背景
	{
		
		//return m_Brush;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMFCDlg::OnOpenswf() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE,"*.txt","MFC",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"SWF Files(*.swf)|*.swf|All Files(*.*)|*.*||",this);
	if(IDOK==fileDlg.DoModal())
	{
		CString fullPath=fileDlg.GetPathName();
		m_ShockwaveFlash.LoadMovie(0,fullPath);
		m_ShockwaveFlash.StopPlay();
	}
}

void CMFCDlg::OnCloseswf() 
{
	// TODO: Add your control notification handler code here
	m_ShockwaveFlash.SetFrameNum(0);
	m_ShockwaveFlash.StopPlay();
	//m_ShockwaveFlash.Rewind();//倒带，返回到影片的第一帧，并停止播放
	//m_ShockwaveFlash.Back();//影片后退一帧，并且停止播放
}

void CMFCDlg::OnPlayswf2() 
{
	// TODO: Add your control notification handler code here
	m_ShockwaveFlash.SetLoop(TRUE);//设置为循环播放
	m_ShockwaveFlash.SetWMode("TRANSPARENT");//设置透明播放模式，如果影片中有透明的片段，放到这里时，就可以看到控件下面的背景
	m_ShockwaveFlash.Play();
}
