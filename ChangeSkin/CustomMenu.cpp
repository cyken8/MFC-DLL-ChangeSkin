// CustomMenu.cpp : implementation file
//
/************************************************************************************
模块：CustomMenu.h
描述：实现一个自定义菜单
作者：宋坤
日期：2008-04-26
************************************************************************************/

#include "stdafx.h"

#include "CustomMenu.h"

#include "Windows.h"

#include "ChangeSkin.h"
#include "ChangeSkinDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCustomMenu
#define DEFAULTWIDTH 120
#define DEFAULTHEIGHT 26

//这些宏编号可查看MSDN
#define     OBJID_WINDOW        0x00000000
#define     OBJID_SYSMENU       0xFFFFFFFF
#define     OBJID_TITLEBAR      0xFFFFFFFE
#define     OBJID_MENU          0xFFFFFFFD
#define     OBJID_CLIENT        0xFFFFFFFC
#define     OBJID_VSCROLL       0xFFFFFFFB
#define     OBJID_HSCROLL       0xFFFFFFFA
#define     OBJID_SIZEGRIP      0xFFFFFFF9
#define     OBJID_CARET         0xFFFFFFF8
#define     OBJID_CURSOR        0xFFFFFFF7
#define     OBJID_ALERT         0xFFFFFFF6
#define     OBJID_SOUND         0xFFFFFFF5

typedef struct tagMENUBARINFO
{
    DWORD cbSize;
    RECT  rcBar;  
    HMENU hMenu;  
    HWND  hwndMenu; 
    BOOL  fBarFocused:1; 
    BOOL  fFocused:1; 
} MENUBARINFO, *PMENUBARINFO, *LPMENUBARINFO;

typedef BOOL(WINAPI *FunGetMenuInfo) (HWND hwnd, LONG idObject, LONG idItem,PMENUBARINFO pmbi);



BOOL GetMenuBarInfo(HWND hwnd, LONG idObject, LONG idItem,PMENUBARINFO pmbi)   
{   
	HMODULE hModule = ::LoadLibrary("user32.dll");   
	if(hModule)   
	{   
		void* pVoid = (void*)GetProcAddress(hModule,"GetMenuBarInfo");   
		if(pVoid)   
		{   
			((FunGetMenuInfo)pVoid)(hwnd,idObject,idItem,pmbi);   
		}   
		else   
		{   
			::FreeLibrary(hModule);   
			return FALSE;   
		}   
	}   
	::FreeLibrary(hModule);   
	return  TRUE;   
}   



CCustomMenu::CCustomMenu()
{
	m_ItemCount = 0;
	m_Index = 0;
	m_MenuList = NULL;
	//m_BkColor = RGB(204,199,186);
	m_OrginBkColor = m_BkColor = RGB(247,227,199);
	m_OrginSelColor = m_SelTopColor = RGB(193, 210, 238);
	m_RandColor = FALSE;
	m_nMenuLeft = 0;
	m_nMenuTop=0;

}

CCustomMenu::~CCustomMenu()
{
	if (m_ItemCount > 0)
		delete []m_MenuList;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMenu message handlers
BOOL CCustomMenu::AttatchMenu(HMENU hMenu)
{
	Attach(hMenu);
	GetAllItemCount(hMenu,m_ItemCount);
	if (m_ItemCount > 0)
		m_MenuList = new CMenuItem[m_ItemCount];

	return TRUE;
}


/***************************************************************************
* void CCustomMenu::GetAllItemCount(HMENU hMenu,int &ItemCount,BOOL FirstFind )
* 功能：统计包括顶级菜单项和子菜单项的个数总和
* 参数：hMenu,菜单的句柄
		ItemCount,传出参数，个数总和
		FirstFind，是否是第一次调用这个函数
*****************************************************************************/
void CCustomMenu::GetAllItemCount(HMENU hMenu,int &ItemCount,BOOL FirstFind )
{
	CMenu* pMenu = CMenu::FromHandle(hMenu);
	if (pMenu)
	{	
		if (FirstFind)
			ItemCount = 0;
		int count = pMenu->GetMenuItemCount();
		ItemCount += count;
		CMenu* pSubMenu = NULL;
		for(int i=0; i<count; i++)
		{
			pSubMenu = pMenu->GetSubMenu(i);
			if (pSubMenu != NULL)
			{
				 GetAllItemCount(pSubMenu->m_hMenu,ItemCount,FALSE);
			}
		}	
	}
}

/*******************************************************
* BOOL CCustomMenu::SetMenuItemInfo(CMenu *pMenu, BOOL Toped)
* 功能:获取菜单的相关信息，保存进m_MenuList数组中
* 参数：pMenu，菜单的指针，
		Toped,是否是顶级菜单，默认是
* 返回值：是否获取成功
***********************************************************/
BOOL CCustomMenu::SetMenuItemInfo(CMenu *pMenu, BOOL Toped)
{

	if (pMenu != NULL)
	{
		int MenuCount = pMenu->GetMenuItemCount();
		for (int i=0;i<MenuCount;i++)
		{
			pMenu->GetMenuString(i,m_MenuList[m_Index].m_MenuText,MF_BYPOSITION);
			UINT MenuID = pMenu->GetMenuItemID(i);

			if ((MenuID==-1 || MenuID==65535) && Toped==TRUE)	//MenuID = -1 Toped = false 表示弹出式菜单
			{
				MenuID = -2; //顶层菜单
			};	
			m_MenuList[m_Index].m_MenuType = MenuID;
			//设置菜单的风格，使其能够自绘，自绘菜单项必须附带MeasureItem(..)消息相应函数
			pMenu->ModifyMenu(i,MF_OWNERDRAW|MF_BYPOSITION |MF_STRING,m_MenuList[m_Index].m_MenuType,(LPSTR)&(m_MenuList[m_Index]));
			m_Index += 1;
			CMenu* pSubMenu = pMenu->GetSubMenu(i);//递归获取顶层菜单下的子菜单的信息
			if (pSubMenu)
			{
				SetMenuItemInfo(pSubMenu,FALSE);
			}
		}
	}
	return TRUE;
}


/************************************************************
* void CCustomMenu::SetMenuItemText(CDC *pDC, LPSTR strMenuText, CRect Rect)
* 功能：绘制菜单项文字
* 参数：pDC，绘图设备
		strMenuText,菜单项的文字
		Rect,菜单项的矩形
**************************************************************/
void CCustomMenu::SetMenuItemText(CDC *pDC, LPSTR strMenuText, CRect Rect)
{
	Rect.DeflateRect(20,0);
	pDC->DrawText(strMenuText,Rect,DT_SINGLELINE|DT_VCENTER|DT_LEFT);
}



/****************************************************************
* void CCustomMenu::DrawTopMenuBk(CDC *pDC, CRect Rect, BOOL State)
* 功能：绘制顶级菜单栏的背景颜色，值包括顶级菜单项
* 参数：pDC,绘图句柄
		Rect,
		State，菜单项是否被选中
****************************************************************/
void CCustomMenu::DrawTopMenuBk(CDC *pDC, CRect Rect, BOOL State)
{
	if (State)		//选中状态
	{
		CPen pen(PS_SOLID,1,RGB(49,106,197));
		pDC->SelectObject(&pen);
		pDC->Rectangle(&Rect);
		Rect.DeflateRect(1,1);
		pDC->FillSolidRect(Rect,m_SelTopColor);
		pen.DeleteObject();
	}
	else
	{
		HRGN nClientRgn =  GetClientMenuRgn();//获取菜单栏的非菜单项区域
		CBrush brush(m_BkColor);

		FillRgn(pDC->m_hDC,nClientRgn,brush);
		pDC->FillSolidRect(&Rect,m_BkColor);
		DeleteObject(nClientRgn);
		brush.DeleteObject();
	}

}



/******************************************************
* void CCustomMenu::DrawSepMenu(CDC *pDC, CRect Rect)
* 功能：绘制菜单分隔条
* 参数：pDC,绘图设备对象指针
		Rect,分隔条指针
******************************************************/
void CCustomMenu::DrawSepMenu(CDC *pDC, CRect Rect)
{
	pDC->Draw3dRect(Rect,RGB(255,0,0),RGB(0,0,255));
}


/****************************************************
* void CCustomMenu::DrawMenuBk(CDC *pDC, CRect Rect, COLORREF SrcColor, COLORREF DesColor, BOOL State)
* 功能：绘制顶级菜单项下的子菜单项的背景颜色
* 参数：pDC,绘图设备对象指针
		Rect,顶级菜单的子菜单项的矩形区域
		SrcColor:菜单项左边边界的颜色（起始颜色）
		DesColor:菜单项右边边界的颜色（终止颜色）
		State:菜单项是否被选中
*****************************************************/
void CCustomMenu::DrawMenuBk(CDC *pDC, CRect Rect, COLORREF SrcColor, COLORREF DesColor, BOOL State)
{
	if (State)
	{	
		pDC->Rectangle(Rect);	 
		Rect.DeflateRect(1,1);
		int r1,g1,b1; 
		//读取渐变起点的颜色值
		r1 = GetRValue(SrcColor);
		g1 = GetGValue(SrcColor);
		b1 = GetBValue(SrcColor);
		int r2,g2,b2;
		//读取渐变终点的颜色值
		r2 = GetRValue(DesColor);
		g2 = GetGValue(DesColor);
		b2 = GetBValue(DesColor);
		float  r3,g3,b3;		//菜单区域水平方向每个点RGB值应该变化的度(范围)
		r3 = ((float)(r2-r1)) / (float)(Rect.Height());
		g3 = (float)(g2-g1)/(float)(Rect.Height());			
		b3 = (float)(b2-b1)/(float)(Rect.Height());
		COLORREF r,g,b;			//菜单区域水平方向每个点的颜色值
		CPen* pOldPen ;
		for (int i=Rect.top; i<Rect.bottom; i++)
		{
			r = r1+(int)r3*(i-Rect.top);
			g = g1+(int)g3*(i-Rect.top);
			b = b1+ (int)b3*(i-Rect.top);
			CPen pen (PS_SOLID,1,RGB(r,g,b));
			pOldPen = pDC->SelectObject(&pen);
			pDC->MoveTo(Rect.left,i);
			pDC->LineTo(Rect.right,i);
			pDC->SelectObject(pOldPen);
		}
	}
	else
	{
		pDC->FillSolidRect(Rect,RGB(0x000000F9, 0x000000F8, 0x000000F7));
	}
}



/********************************************************
* void CCustomMenu::MeasureItem( LPMEASUREITEMSTRUCT lpStruct )
* 功能：消息响应函数，用于改变菜单项与菜单项之间的高度或者菜单项的宽度
* 参数：请参阅MSDN
**********************************************************/
void CCustomMenu::MeasureItem( LPMEASUREITEMSTRUCT lpStruct )
{
	if (lpStruct->CtlType==ODT_MENU)
	{
		lpStruct->itemHeight = 20;
		lpStruct->itemWidth = DEFAULTWIDTH;
		
		CMenuItem* MenuItem;
		MenuItem = (CMenuItem*)lpStruct->itemData;
		CDC dc;
		dc.Attach(AfxGetMainWnd()->GetDC()->m_hDC);
		CSize size = dc.GetTextExtent(((CMenuItem*)lpStruct->itemData)->m_MenuText);
		if (lpStruct->itemID==-2)
		{
			lpStruct->itemWidth = size.cx+25;//控制顶级菜单项背景绘制的右边界
		}
		else
			lpStruct->itemWidth = size.cx+40;//控制非顶级菜单项背景绘制的右边界
		switch(MenuItem->m_MenuType)
		{
			case 0: //分隔条
				{
					lpStruct->itemHeight = 1;
					break;
				}	
		}
	}
}




/****************************************************
* void CCustomMenu::DrawItem( LPDRAWITEMSTRUCT lpStruct )
* 功能：绘制所有菜单项的背景和文字
* 参数：请参阅MSDN
*****************************************************/
void CCustomMenu::DrawItem( LPDRAWITEMSTRUCT lpStruct )
{
	if (lpStruct->CtlType==ODT_MENU)
	{
		if(lpStruct->itemData == NULL)
			return;
		unsigned int m_state = lpStruct->itemState;
		CDC* pDC = CDC::FromHandle(lpStruct->hDC);
		//获取菜单项里面的文字，再调用SetMenuItemText绘制文字
		CString str =  ((CMenuItem*)(lpStruct->itemData))->m_MenuText;
		int MenuID = ((CMenuItem*)(lpStruct->itemData))->m_MenuType;

		CRect Rect = lpStruct->rcItem;

		/*
		当窗口Style属性为Resizing时，菜单的左边界肯定为4（在不人为改变菜单位置的情况下）；
		当窗口Style属性为Dialog Frame时，菜单的左边界肯定为3（在不人为改变菜单位置的情况下）
		*/
		if (Rect.left==4||Rect.left==3 )//控制第一个顶级菜单项的背景绘制范围
		{
			Rect.DeflateRect(m_nMenuLeft,0,0,0);
		}
	
		pDC->SetBkMode(TRANSPARENT);
		switch(MenuID)
		{
		case -2:	//顶层菜单
			{
				Rect.top=m_nMenuTop;	//修改
				//Rect.top=m_nMenuTop=((CChangeSkinDlg*)AfxGetMainWnd())->m_TitleDrawHeight;
				DrawTopMenuBk(pDC,Rect,(m_state & ODS_SELECTED)||(m_state & 0x0040)); //0x0040 ==ODS_HOTLIGHT
				SetMenuItemText(pDC,str.GetBuffer(0),Rect);
				break;
			}
		case -1:
			{	
				SetMenuItemText(pDC,str.GetBuffer(0),Rect);
				break;
			}
		case 0:
			{
				DrawSepMenu(pDC,Rect);
				break;
			}
		default:
			{	
				if (m_RandColor)
				{
					int srcred = rand() % 255;
					int srcblue = rand() % 255;
					int srcgreen = rand() % 255;
					int desred = rand() % 255;
					int desblue = rand() % 255;
					int desgreen = rand() % 255;
					
					DrawMenuBk(pDC,Rect,RGB(srcred,srcgreen,srcblue),RGB(desred,desgreen,desblue),m_state & ODS_SELECTED);
				}
				else
				{
					DrawMenuBk(pDC,Rect,0xfaa0,0xf00ff,m_state & ODS_SELECTED);
				}
				SetMenuItemText(pDC,str.GetBuffer(0),Rect);
				break;
			}
		}
	}
}




/*******************************************
* int CCustomMenu::GetTopMenuWidth()
* 功能：获取所有顶层菜单项的宽度之和
* 返回值：顶层菜单项的宽度之和
*********************************************/
int CCustomMenu::GetTopMenuWidth()
{
	int Count = GetMenuItemCount();
	int width = 0;
	CRect rc;
	for (int i=0; i<Count; i++)
	{
		::GetMenuItemRect(AfxGetMainWnd()->m_hWnd,m_hMenu,i,rc);
		width += rc.Width();
	}
	return width;
}



/*****************************************
* HRGN CCustomMenu::GetClientMenuRgn()
* 功能：获取菜单栏中非菜单项区域
* 返回值：菜单栏中非菜单项区域
*****************************************/
HRGN CCustomMenu::GetClientMenuRgn()
{
	MENUBARINFO MenuInfo;
	memset(&MenuInfo,0,sizeof(MENUBARINFO));
	MenuInfo.cbSize = sizeof(MENUBARINFO);
	::GetMenuBarInfo(AfxGetMainWnd()->m_hWnd,OBJID_MENU,0,&MenuInfo);
	CRect rc = MenuInfo.rcBar;

	int MenuCount = GetMenuItemCount();
	CRect *pRC = new CRect[MenuCount];
	HRGN *pRgn = new HRGN[MenuCount];

	CRect winRC;
	AfxGetMainWnd()->GetWindowRect(winRC);
	int x  = winRC.left;
	int y  = winRC.top;
	rc.left = rc.left-x;
	rc.right = rc.right -x;
	rc.top = rc.top-y;
	rc.bottom = rc.bottom-y;
	rc.top=m_nMenuTop;		//修改
//	rc.top=m_nMenuTop=((CChangeSkinDlg*)AfxGetMainWnd())->m_TitleDrawHeight;
	//创建菜单项的区域
	for (int i=0; i<MenuCount; i++)//MenuCount是顶级菜单的个数
	{
		GetMenuItemRect(AfxGetMainWnd()->m_hWnd,m_hMenu,i,&pRC[i]);	
		pRC[i].left = pRC[i].left-x;
		pRC[i].right = pRC[i].right-x;
		pRC[i].top = pRC[i].top-y;
		pRC[i].bottom = pRC[i].bottom-y;
		pRgn[i] = CreateRectRgn(pRC[i].left,pRC[i].top,pRC[i].right,pRC[i].bottom);
	}
	HRGN MenuRgn = CreateRectRgn(rc.left,rc.top,rc.right-m_nMenuLeft,rc.bottom);//占据一整行的空间
	HRGN retRgn = CreateRectRgn(0,0,0,0);
	HRGN MenuClientRgn = CreateRectRgn(0,0,0,0);
	//组合菜单项的区域
	for (int j=0; j<MenuCount; j++)
	{
		CombineRgn(MenuClientRgn,MenuClientRgn,pRgn[j],RGN_OR);
	}
	//去除菜单栏中菜单项的区域，以获取非菜单项区域
	CombineRgn(retRgn,MenuRgn,MenuClientRgn,RGN_DIFF);
	for ( j=0; j<MenuCount; j++)
	{
		DeleteObject(pRgn[j]);
	}
	DeleteObject(MenuRgn);
	DeleteObject(MenuClientRgn);

	delete []pRC;
	delete []pRgn;
	return retRgn;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMenu message handlers
