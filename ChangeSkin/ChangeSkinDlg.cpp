// ChangeSkinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChangeSkin.h"
#include "ChangeSkinDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinDlg dialog



CChangeSkinDlg::CChangeSkinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeSkinDlg::IDD, pParent)
{
	m_FirstShow=FALSE;
	m_IsMax=TRUE;
	m_CaptionColor=RGB(255,255,0);	//设置标题栏颜色
	m_szCaption=_T("珍");	//设置标题栏文本的颜色
	m_bLoadDll=FALSE;				//设置加载标记为未加载皮肤文件

	//{{AFX_DATA_INIT(CChangeSkinDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChangeSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeSkinDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChangeSkinDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeSkinDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_COMMAND(ID_WINDOWSSKIN, OnWindowsskin)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID_LOADFILE, OnLoadfile)
	ON_COMMAND(ID_ABOUTBOX, OnAboutbox)
	ON_WM_NCCALCSIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinDlg message handlers

BOOL CChangeSkinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	//加载菜单并获取保存菜单信息再m_Menu对象中
	HMENU hMenu = GetMenu()->GetSafeHmenu();
	if (hMenu != NULL)
	{
		m_Menu.AttatchMenu(hMenu);//将菜单对象与菜单资源相绑定
		m_Menu.SetMenuItemInfo(&m_Menu);//
	}

	m_BorderHeight = GetSystemMetrics(SM_CYBORDER);		//获取系统边界高度
	m_BorderWidth = GetSystemMetrics(SM_CXBORDER);		//获取系统边界宽度
	m_CaptionHeight = GetSystemMetrics(SM_CYCAPTION);	//获取系统标题栏高度
	SkinApplication();									
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChangeSkinDlg::OnPaint() 
{
	if (IsIconic())		//窗口最小化的绘制
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


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}


	SkinDialog();			//每次刷新都重新绘制对话框个部分
	m_IsDrawForm=TRUE;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChangeSkinDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChangeSkinDlg::DrawDialogText()
{
	if(!m_szCaption.IsEmpty())
	{
		CDC* pDC=GetWindowDC();		//获取窗口设备上下文
		pDC->SetBkMode(TRANSPARENT);//设置透明的背景模式
		pDC->SetTextColor(m_CaptionColor);	//设置标题栏文本颜色
		pDC->SetTextAlign(TA_CENTER);
		CRect rect;
		GetClientRect(rect);
		pDC->SelectObject(&m_CaptionFont);
		//在标题栏中输出文本
		pDC->TextOut(rect.Width()/2,m_CaptionHeight/3,m_szCaption);
		ReleaseDC(pDC);
	}
}


/******************************************************************
* HBRUSH CChangeSkinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
* 功能:消息相应函数，修改窗口背景颜色
* 参数：请参阅MSDN
******************************************************************/
HBRUSH CChangeSkinDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

	// TODO: Change any attributes of the DC here
	//绘制背景,如果是窗口且皮肤文件已加载
	if(nCtlColor==CTLCOLOR_DLG && m_bLoadDll==TRUE)
	{
		if(m_bLoadDll)
		{
			CBrush m_Brush(&m_Bk);//CBrush可以用位图来创建
			CRect rect;
			GetClientRect(rect);
			pDC->SelectObject(&m_Brush);
			pDC->FillRect(rect,&m_Brush);
			return m_Brush;
		}
		else
			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	else if(nCtlColor==CTLCOLOR_STATIC)//如果为静态文本
	{
		pDC->SetBkMode(TRANSPARENT);
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	else
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Return a different brush if the default is not desired
}




/**************************************************
* void CChangeSkinDlg::SkinDialog(UINT Flags)
* 功能：根据参数标记使用位图资源来绘制窗口的各个部分，整个主应用程序的核心，
		实现绘制对话框标题栏，标题栏按钮，对话框边框，对话框背景的功能
* 参数：Flags，需要绘制的部分的编码
****************************************************/
void CChangeSkinDlg::SkinDialog(UINT Flags)
{
	if(m_bLoadDll)
	{
		m_FrameHeight=GetSystemMetrics(SM_CYFIXEDFRAME);		//获取对话框框架高度
		m_BorderHeight=GetSystemMetrics(SM_CYBORDER);			//获取对话框边框的高度
		m_FrameWidth=GetSystemMetrics(SM_CXFIXEDFRAME);			//获取对话框框架的宽度
		m_BorderWidth=GetSystemMetrics(SM_CXBORDER);			//获取对话框边框的宽度
		m_CaptionHeight=GetSystemMetrics(SM_CYCAPTION);			//获取标题栏高度
		CRect ClientRect;
		GetClientRect(ClientRect);
		CRect WinRC,FactRC;
		//获取整个窗口区域，包括非客户区域
		GetWindowRect(WinRC);
		FactRC.CopyRect(CRect(0,0,WinRC.Width(),WinRC.Height()));
		CWindowDC WindowDC(this);
		CBitmap LeftLine,*OldObj;	//定义位图对象
		BITMAPINFO bitInfo;			//定义位图信息对象
		CDC memDC;					//定义内存设备上下文
		memDC.CreateCompatibleDC(&WindowDC);
		LeftLine.Attach(pSkin->GetBitmapRes(2));	//加载右标题位图
		LeftLine.GetObject(sizeof(bitInfo),&bitInfo);//获取右标题位图信息
		m_rightwidth=bitInfo.bmiHeader.biWidth;		//获取右标题位图宽度
		LeftLine.Detach();
		int x,y;

		//绘制对话框的左边框
		if(Flags&fLeftBand)		//绘制左边框
		{
			DeleteObject(LeftLine);		//删除以前加载的位图
			LeftLine.Attach(pSkin->GetBitmapRes(3));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			OldObj=memDC.SelectObject(&LeftLine);
			//判断位图的宽度与窗体边缘的宽度
			m_leftlinewidth=(x>m_FrameWidth+m_BorderWidth)?x:m_FrameWidth+m_BorderWidth;
			m_Menu.m_nMenuLeft=m_leftlinewidth-m_BorderWidth-m_FrameWidth;

			//在窗口中绘制边框位图
			WindowDC.StretchBlt(0,m_CaptionHeight,m_leftlinewidth,
				FactRC.Height()-m_CaptionHeight,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();		//分离位图	
		}

		//绘制对话框的左标题栏，首先从皮肤文件中获取左标题栏位图，然后绘制
		if(Flags&fLeftTitle)
		{
			DeleteObject(LeftLine);		//删除以前加载的位图
			LeftLine.Attach(pSkin->GetBitmapRes(0));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			m_leftwidth=x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//计算标题栏的高度
			m_TitleDrawHeight=(m_CaptionHeight+4)>y?m_CaptionHeight+4:y;

			m_Menu.m_nMenuTop=m_TitleDrawHeight;	//设置菜单的顶部位置

			//定义左标题栏显示区域
			m_LTitleRc.CopyRect(CRect(0,0,x,m_TitleDrawHeight));
			//绘制左标题栏位图
			WindowDC.StretchBlt(m_LTitleRc.left,m_LTitleRc.top,
				m_LTitleRc.Width(),m_LTitleRc.Height(),
				&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//绘制对话框的右标题栏
		if ( Flags & fRightTitle)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(2));
			//获取位图大小
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj = memDC.SelectObject(&LeftLine);
			x = bitInfo.bmiHeader.biWidth;
			y = bitInfo.bmiHeader.biHeight;
			m_TitleDrawHeight = (m_CaptionHeight+4>y)?m_CaptionHeight+4: y;
			
			m_RTitleRc.CopyRect(CRect(FactRC.right-x,0,FactRC.right,m_TitleDrawHeight));

			WindowDC.StretchBlt(m_RTitleRc.left,m_RTitleRc.top,m_RTitleRc.Width(),m_RTitleRc.Height(),&memDC,0,0,x,y,SRCCOPY);
			DeleteObject( memDC.SelectObject(OldObj));
			LeftLine.Detach();
		}



		//绘制对话框的中间标题栏
		if(Flags&fMidTitle)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(1));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//计算标题栏的绘制高度
			m_TitleDrawHeight=(m_CaptionHeight+4>y)?m_CaptionHeight+4:y;

			//定义中间标题栏的显示区域
			m_MTitleRc.CopyRect(CRect(m_LTitleRc.right,0,m_RTitleRc.left,m_TitleDrawHeight));
			//绘制中间标题栏位图
			WindowDC.StretchBlt(m_MTitleRc.left,m_MTitleRc.top,
				m_MTitleRc.Width(),m_MTitleRc.Height(),&memDC,
				0,0,x,y,SRCCOPY);
			LeftLine.Detach();
			memDC.SelectObject(OldObj);
		}

		//绘制对话框的右边框
		if(Flags&fRightBand)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(5));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//计算右边框的宽度
			m_rLineWidth=m_FrameWidth+m_BorderWidth;
			m_rLineWidth=m_rLineWidth>x?m_rLineWidth:x;
			//绘制右边框位图
			WindowDC.StretchBlt(m_RTitleRc.right-m_rLineWidth,m_TitleDrawHeight,
				m_rLineWidth,FactRC.Height()-m_TitleDrawHeight,
				&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//绘制对话框的底边框
		if(Flags&fBottomBand)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(4));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//计算底边框的宽度
			m_bLineHeight=m_BorderHeight+m_FrameHeight;
			m_bLineHeight=m_bLineHeight>y?m_bLineHeight:y;
			//绘制底边框位图
			WindowDC.StretchBlt(m_leftlinewidth,FactRC.Height()-m_bLineHeight,
				m_RTitleRc.right-m_rLineWidth-m_leftlinewidth,
				m_bLineHeight,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}
		
		//绘制左下角和右下角
		if(pSkin->GetDrawRound())
		{
			if(Flags& fLeftBottom)
			{
				DeleteObject(LeftLine);
				LeftLine.Attach(pSkin->GetBitmapRes(12));
				LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
				OldObj=memDC.SelectObject(&LeftLine);
				x=bitInfo.bmiHeader.biWidth;
				y=bitInfo.bmiHeader.biHeight;
				//绘制左下角位图
				WindowDC.StretchBlt(0,FactRC.Height()-m_bLineHeight,
					m_leftlinewidth,m_bLineHeight,
					&memDC,0,0,x,y,SRCCOPY);
				memDC.SelectObject(OldObj);
				LeftLine.Detach();
			}
			if(Flags& fRightBottom)
			{
				DeleteObject(LeftLine);
				LeftLine.Attach(pSkin->GetBitmapRes(13));
				LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
				OldObj=memDC.SelectObject(&LeftLine);
				x=bitInfo.bmiHeader.biWidth;
				y=bitInfo.bmiHeader.biHeight;
				//绘制左下角位图
				WindowDC.StretchBlt(m_RTitleRc.right-x,FactRC.Height()-m_bLineHeight,
					x,m_bLineHeight,
					&memDC,0,0,x,y,SRCCOPY);
				memDC.SelectObject(OldObj);
				LeftLine.Detach();
			}
		}

		//根据标题栏按钮位图的大小计算标题栏按钮的显示区域
		CPoint pos=pSkin->GetButtonPos(6);
		//计算最小化按钮位图的显示区域
		m_MinRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
			(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
			m_ButtonWidth,m_ButtonHeight));

		pos=pSkin->GetButtonPos(7);
		//计算最大化按钮位图显示区域
		m_MaxRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
			(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
			m_ButtonWidth,m_ButtonHeight));

		pos=pSkin->GetButtonPos(8);
		//计算关闭按钮位图显示区域
		m_CloseRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
			(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
			m_ButtonWidth,m_ButtonHeight));

		//根据标题栏按钮的显示区域绘制标题栏按钮
		//绘制最小化按钮
		if(Flags&fMinButton)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(6));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//绘制最小按钮
			WindowDC.StretchBlt(m_MinRect.left,m_MinRect.top,m_MinRect.right,	//注意这里是right不是Width和Height，因为得到的m_MinRect它的左右颠倒了
				m_MinRect.bottom,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//绘制最大化按钮
		if(Flags&fMaxButton)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(7));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//绘制最大化按钮
			WindowDC.StretchBlt(m_MaxRect.left,m_MaxRect.top,m_MinRect.right,
				m_MinRect.bottom,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		//绘制关闭按钮
		if(Flags&fCloseButton)
		{
			DeleteObject(LeftLine);
			LeftLine.Attach(pSkin->GetBitmapRes(8));
			LeftLine.GetObject(sizeof(bitInfo),&bitInfo);
			OldObj=memDC.SelectObject(&LeftLine);
			x=bitInfo.bmiHeader.biWidth;
			y=bitInfo.bmiHeader.biHeight;
			//绘制最大化按钮
			WindowDC.StretchBlt(m_CloseRect.left,m_CloseRect.top,m_MinRect.right,
				m_MinRect.bottom,&memDC,0,0,x,y,SRCCOPY);
			memDC.SelectObject(OldObj);
			LeftLine.Detach();
		}

		m_IsDrawForm=TRUE;
		LeftLine.DeleteObject();	//是否位图对象
		memDC.DeleteDC();			
		DrawDialogText();			//绘制标题文本
	}
}





/*****************************************
* void CChangeSkinDlg::SkinApplication()
* 功能: 对接动态库加载后的参数，与窗口相关联,获取背景位图信息
		，菜单信息，字体信息
* ****************************************/
void CChangeSkinDlg::SkinApplication()
{
	m_bLoadDll=((CChangeSkinApp*)AfxGetApp())->m_bLoadDll;
	pSkin=((CChangeSkinApp*)AfxGetApp())->pSkin;

	m_Bk.DeleteObject();
	m_CaptionFont.DeleteObject();
	if(m_bLoadDll)
	{
		ModifyStyle(WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU,0);		//修改窗口样式，去掉最大化，最小化，关闭按钮和菜单
		m_Bk.Attach(pSkin->GetBitmapRes(14));							//加载背景位图并且保留下来没有释放
		//获取按钮位图大小
		CBitmap bitmap;
		bitmap.Attach(pSkin->GetBitmapRes(6));
		BITMAPINFO bInfo;
		bitmap.GetObject(sizeof(bInfo),&bInfo);
		m_ButtonWidth=bInfo.bmiHeader.biWidth;			//获取标题栏按钮的宽度
		m_ButtonHeight=bInfo.bmiHeader.biHeight;		//获取标题栏按钮的高度
		bitmap.Detach();
		m_WndRgn.DeleteObject();
		SetDlgZone();	
		
		m_Menu.m_BkColor=pSkin->GetMenuBKColor();		//从动态库中获取菜单背景颜色传送到菜单类中
		m_Menu.m_SelTopColor=pSkin->GetMenuSelColor();
		m_CaptionFont.CreateFont(12,10,0,0,600,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_ROMAN,"MS Sans Serif");

	}
	//如果没有加载成功动态库，则使用原始界面
	else
	{
		ModifyStyle(0,WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU|WS_CAPTION);
	}

}






/**********************************************
* void CChangeSkinDlg::SetDlgZone()
* 功能：如果对话框4个角的位图具有白色背景，则扣除该区域，
		将对话框设置诶圆角矩形，调用绘制对话框函数绘制窗口
**********************************************/
void CChangeSkinDlg::SetDlgZone()
{
	SkinDialog();		//绘制对话框
	CRect winrect,factRC;		//保存窗口矩形，并创建矩形副本
	GetWindowRect(winrect);		//获取窗口区域
	factRC.CopyRect(CRect(0,0,winrect.Width(),winrect.Height()));
	m_WndRgn.DeleteObject();
	m_WndRgn.CreateRectRgnIndirect(factRC);	//创建圆角区域
	CBitmap bitmap;			//定义位图对象
	BITMAPINFO bInfo;		//定义位图信息对象

	//去除左上角的空白区域，方法是根据左标题栏位图的白色像素点来确定去除的区域
	bitmap.Attach(pSkin->GetBitmapRes(0));
	bitmap.GetObject(sizeof(bInfo),&bInfo);	//获取位图信息
	int x,y,m,n;
	x=bInfo.bmiHeader.biWidth;
	y=bInfo.bmiHeader.biHeight;
	CDC memDC;
	CDC* pDC=GetDC();
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&bitmap);
	for(m=0;m<x;m++)
	{
		for(n=0;n<y;n++)
		{
			if(memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m,n,m+1,n+1);
				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();

			}
		}
	}
	bitmap.Detach();

	//去除右上角的空白区域
	bitmap.Attach(pSkin->GetBitmapRes(2));
	bitmap.GetObject(sizeof(bInfo),&bInfo);
	x = bInfo.bmiHeader.biWidth;
	y = bInfo.bmiHeader.biHeight;
	memDC.SelectObject(&bitmap);
	for ( m = 0; m<x; m++)
		for (n = 0; n<y; n++)
		{
			if (memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m_RTitleRc.left+m,m_RTitleRc.top+n,m_RTitleRc.left+ m+1,m_RTitleRc.top+n+1);

				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();
			}
		}
	bitmap.Detach();


	//去除左下角的空白区域
	bitmap.Attach(pSkin->GetBitmapRes(12));
	bitmap.GetObject(sizeof(bInfo),&bInfo);
	x = bInfo.bmiHeader.biWidth;
	y = bInfo.bmiHeader.biHeight;
	memDC.SelectObject(&bitmap);
	for ( m = 0; m<x; m++)
		for (n = 0; n<y; n++)
		{
			if (memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m,factRC.Height()-y+n ,m+1,factRC.Height()-y+n+1);
				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();
			}
		}
	bitmap.Detach();
	//去除右下角的空白区域
	bitmap.Attach(pSkin->GetBitmapRes(13));
	bitmap.GetObject(sizeof(bInfo),&bInfo);
	x = bInfo.bmiHeader.biWidth;
	y = bInfo.bmiHeader.biHeight;
	memDC.SelectObject(&bitmap);
	for ( m = 0; m<x; m++)
		for (n = 0; n<y; n++)
		{
			if (memDC.GetPixel(m,n)==RGB(255,255,255))
			{
				m_ClipRgn.CreateRectRgn(m_RTitleRc.right-x+m,factRC.Height()-y+n,m_RTitleRc.right-x+m+1,factRC.Height()-y+n+1);
				m_WndRgn.CombineRgn(&m_WndRgn,&m_ClipRgn,RGN_XOR);
				m_ClipRgn.DeleteObject();
			}
		}
	bitmap.Detach();
	ReleaseDC(&memDC);
	ReleaseDC(pDC);
	SetWindowRgn(m_WndRgn,TRUE);
	DeleteObject(m_WndRgn);

}

void CChangeSkinDlg::OnSize(UINT nType, int cx, int cy) 
{
//	SetWindowRgn(NULL,TRUE);//有这句会使窗口在大小变化时很闪烁

	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bLoadDll)
		return;
	CRect rect;
	GetClientRect(rect);
	CPoint pos=pSkin->GetButtonPos(6);	//获取最小化按钮显示相对位置
	//计算最小化按钮显示位置
	m_MinRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
		(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
		m_ButtonWidth,m_ButtonHeight));

	pos=pSkin->GetButtonPos(7);	//获取最小化按钮显示相对位置
	//计算最大化按钮显示位置
	m_MaxRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
		(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
		m_ButtonWidth,m_ButtonHeight));

	pos=pSkin->GetButtonPos(8);	//获取最小化按钮显示相对位置
	//计算关闭按钮显示位置
	m_CloseRect.CopyRect(CRect(m_RTitleRc.left+pos.x,
		(m_TitleDrawHeight+2*m_BorderHeight-m_ButtonHeight)/2+pos.y,
		m_ButtonWidth,m_ButtonHeight));

	SetDlgZone();		//设置窗口区域
	Invalidate();

}

void CChangeSkinDlg::OnNcPaint() 
{
	// TODO: Add your message handler code here
	CWnd::OnNcPaint();
	OnPaint();
	// Do not call CDialog::OnNcPaint() for painting messages
}

BOOL CChangeSkinDlg::OnNcActivate(BOOL bActive) 
{
	// TODO: Add your message handler code here and/or call default
	OnPaint();
	return TRUE;
}

void CChangeSkinDlg::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLoadDll)
	{
		CRect tempIni,tempMin,tempMax,tempClose,ClientRect;
		CWindowDC WindowDC(this);
		CDC memDC;
		memDC.CreateCompatibleDC(&WindowDC);
		BITMAPINFO bInfo;
		CBitmap LeftLine;
		int x,y;
		GetWindowRect(ClientRect);//获取整个窗口区域
		
		//获取最小化按钮，最大化按钮和关闭按钮的显示区域(相对边界位置）
		tempMin.CopyRect(CRect(m_MinRect.left+ ClientRect.left,
			ClientRect.top+m_MinRect.top,
			m_MinRect.right+m_MinRect.left+ ClientRect.left,
			m_MinRect.bottom+m_MinRect.top+ClientRect.top));

		tempMax.CopyRect(CRect(m_MaxRect.left+ ClientRect.left,
			ClientRect.top+m_MaxRect.top,
			m_MaxRect.right+m_MaxRect.left+ ClientRect.left,
			m_MaxRect.bottom+m_MaxRect.top+ClientRect.top));

		tempClose.CopyRect(CRect(m_CloseRect.left+ ClientRect.left,
			ClientRect.top+m_CloseRect.top,
			m_CloseRect.right+m_CloseRect.left+ ClientRect.left,
			m_CloseRect.bottom+m_CloseRect.top+ClientRect.top));

		if(tempMin.PtInRect(point))
		{
			if(m_ButtonState!=bsMin)
			{
				LeftLine.Attach(pSkin->GetBitmapRes(9));
				LeftLine.GetObject(sizeof(bInfo),&bInfo);
				x=bInfo.bmiHeader.biWidth;
				y=bInfo.bmiHeader.biHeight;
				memDC.SelectObject(&LeftLine);
				//绘制最小化按钮的热点位图
				WindowDC.StretchBlt(m_MinRect.left,m_MinRect.top,
					m_MinRect.right,m_MinRect.bottom,&memDC,
					0,0,x,y,SRCCOPY);
				m_IsDrawForm=FALSE;
				m_ButtonState=bsMin;
				LeftLine.Detach();
			}
		}
		else if(tempMax.PtInRect(point))
		{
			//如果按钮状态不是最大化或还原状态
			if(m_ButtonState!=bsMax&&m_ButtonState!=bsRes)
			{
				LeftLine.Attach(pSkin->GetBitmapRes(10));
				LeftLine.GetObject(sizeof(bInfo),&bInfo);
				x=bInfo.bmiHeader.biWidth;
				y=bInfo.bmiHeader.biHeight;
				memDC.SelectObject(&LeftLine);
				//绘制最大化按钮的热点位图
				WindowDC.StretchBlt(m_MaxRect.left,m_MaxRect.top,
					m_MaxRect.right,m_MaxRect.bottom,&memDC,
					0,0,x,y,SRCCOPY);
				m_IsDrawForm=FALSE;
				if(m_IsMax)		//当前是否最大化状态
				{
					m_ButtonState=bsMax;	//设置最大化状态
				}
				else
				{
					m_ButtonState=bsRes;	//设置还原按钮状态
				}
				LeftLine.Detach();					
			}
		}
		else if(tempClose.PtInRect(point))
		{
			if(m_ButtonState!=bsClose)
			{
				LeftLine.Attach(pSkin->GetBitmapRes(11));
				LeftLine.GetObject(sizeof(bInfo),&bInfo);
				x=bInfo.bmiHeader.biWidth;
				y=bInfo.bmiHeader.biHeight;
				memDC.SelectObject(&LeftLine);
				//绘制最小化按钮的热点位图
				WindowDC.StretchBlt(m_CloseRect.left,m_CloseRect.top,
					m_CloseRect.right,m_CloseRect.bottom,&memDC,
					0,0,x,y,SRCCOPY);
				m_IsDrawForm=FALSE;
				m_ButtonState=bsClose;
				LeftLine.Detach();					
			}
		}
		else
		{
			if(m_IsDrawForm==FALSE)
			{
				if(m_ButtonState==bsMin)	//当前按钮状体为最小化按钮
					SkinDialog(fMinButton);
				else if(m_ButtonState==bsClose)
					SkinDialog(fCloseButton);
				else if(m_ButtonState==bsMax||m_ButtonState==bsRes)
					SkinDialog(fMaxButton);
			}
			m_ButtonState=bsNone;
		}
		LeftLine.DeleteObject();
		ReleaseDC(&memDC);
	}
	CDialog::OnNcMouseMove(nHitTest, point);
}

void CChangeSkinDlg::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLoadDll)
	{
		switch(m_ButtonState)	//判断当前按钮状态
		{
		case bsClose:
			{
				OnCancel();
				break;
			}
		case bsMin:
			{
				ShowWindow(SW_SHOWMINIMIZED);
				break;
			}
		case bsMax:
			{
				m_ButtonState=bsMax;
				ShowWindow(SW_SHOWMAXIMIZED);
				m_IsMax=FALSE;
				break;
			}
		case bsRes:
			{
				ShowWindow(SW_RESTORE);
				m_IsMax=TRUE;
				break;
			}
		}
	}
	CDialog::OnNcLButtonDown(nHitTest, point);
}


/*********************************************
* void CChangeSkinDlg::OnWindowsskin() 
* 功能：点击使用Window界面菜单项时的消息相应响应函数
**********************************************/
void CChangeSkinDlg::OnWindowsskin() 
{
	// TODO: Add your command handler code here
	if(m_bLoadDll)
	{
		((CChangeSkinApp*)AfxGetApp())->pSkin->Release();	//释放CSkin对象
		FreeLibrary(((CChangeSkinApp*)AfxGetApp())->m_hInstance);//释放动态链接库
		((CChangeSkinApp*)AfxGetApp())->m_bLoadDll=FALSE;
		m_bLoadDll=FALSE;
		SkinApplication();
		m_Menu.m_nMenuTop=m_CaptionHeight;	//修改
		m_Menu.m_BkColor=m_Menu.m_OrginBkColor;//设置默认的菜单背景颜色
		m_Menu.m_SelTopColor=m_Menu.m_OrginSelColor;//设置默认的菜单选中时的颜色
		m_Menu.m_nMenuLeft=0;
		SetWindowPos(NULL,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_DRAWFRAME);
		Invalidate();
		OnSize(0,0,0);
	}
}

/********************************************************
* void CChangeSkinDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
* 功能：绘制菜单
********************************************************/
void CChangeSkinDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_Menu.DrawItem(lpDrawItemStruct);
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CChangeSkinDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	m_Menu.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CChangeSkinDlg::OnLoadfile() 
{
	// TODO: Add your command handler code here
	CFileDialog fd(TRUE,_T("*.ski"),NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("皮肤(.ski)|*.ski||"),this);
	if(fd.DoModal()==IDCANCEL)
		return;
	m_Bk.DeleteObject();
	m_CaptionFont.DeleteObject();
	((CChangeSkinApp*)AfxGetApp())->AlterSkin(fd.GetPathName());
	SkinApplication();
	fd.DestroyWindow();
	Invalidate();
	OnSize(0,0,0);


}

void CChangeSkinDlg::OnAboutbox() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}



void CChangeSkinDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CChangeSkinDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}	
//	CDialog::OnSysCommand(nID, lParam);
}

void CChangeSkinDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CChangeSkinDlg::OnOK() 
{
//	CDialog::OnOK();
}

void CChangeSkinDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_bLoadDll)
	{
		m_Bk.Detach();
		m_CaptionFont.DeleteObject();
		m_Bk.DeleteObject();
	}	
	CDialog::OnCancel();
}
