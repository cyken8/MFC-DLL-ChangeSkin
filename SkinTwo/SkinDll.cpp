// SkinDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "SkinDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CSkinDllApp

BEGIN_MESSAGE_MAP(CSkinDllApp, CWinApp)
	//{{AFX_MSG_MAP(CSkinDllApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinDllApp construction

CSkinDllApp::CSkinDllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSkinDllApp object

CSkinDllApp theApp;
class  CFormPart
{
public:
	HBITMAP  m_hBitmap;  //位图资源
	CPoint   m_Pos;      //位图资源位置,该位置是相对于右标题部分的相对位置,只对标题栏按钮起作用
	                     //x表示水平位置,y表示相对于标题栏居中位置的偏移量,为正数向下偏移,为负
	                     //数向上偏移
};

#define MINBUTTON   6
#define MAXTBUTTON  7
#define CLOSEBUTTON 8

class CSkin
{
protected:
	UINT m_PartCount;  //窗体由几部分组成
	/*************************************************************
	窗体各部分位图资源:  
	0,1,2:         分别为标题栏的左\中\右3部分
	3,4,5:         分别为左,下,右边框
	6,7,8,9,10,11: 为标题栏普通按钮和热点按钮
	12,13:         表示左下角和右下角位图
	14:            表示背景位图
	*************************************************************/
	CFormPart* m_pParts;
	COLORREF m_MenuBkColor;		//菜单背景颜色
	COLORREF m_MenuSelColor;	//菜单选中时的颜色
	BOOL DrawRound; //是否绘制圆角
	//加载位图资源
	void LoadBitmapRes()
	{
		for (int i = 0; i< m_PartCount; i++)
		{
			//1000表示位图资源的起始ID
			m_pParts[i].m_hBitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(1000+i));
		}
	}
	void SetButtonPos()
	{
		for (int i= MINBUTTON; i<=CLOSEBUTTON; i++)
		{
			m_pParts[i].m_Pos.y = 3;
			switch (i)
			{
			case MINBUTTON:
				{
					m_pParts[i].m_Pos.x = 15;
					break;
				}
			case MAXTBUTTON:
				{
					m_pParts[i].m_Pos.x = 40;
					break;
				}
			case CLOSEBUTTON:
				{
					m_pParts[i].m_Pos.x = 65;
					break;
				}			
			}
		}
	}
public:
	CSkin()
	{
		m_PartCount = 15;
		m_pParts = new CFormPart[m_PartCount];
		LoadBitmapRes();
		SetButtonPos();
		m_MenuBkColor = RGB(3,125,205);
		m_MenuSelColor = RGB(193, 210, 238);
		DrawRound = TRUE;
	}
	CSkin(UINT PartCount)
	{
		m_PartCount = PartCount;
		m_pParts = new CFormPart[m_PartCount];	
	}
	~CSkin()
	{
		for (int i = 0; i< m_PartCount; i++)
		{
			//1000表示位图资源的起始ID
			DeleteObject(m_pParts[i].m_hBitmap) ;
		}
		delete [] m_pParts;
	}

	//获取位图资源
	virtual HBITMAP GetBitmapRes(UINT Index)
	{
		return m_pParts[Index].m_hBitmap;
	}
	//释放对象
	virtual Release()
	{	
		delete this;
	}
	//获取按钮的位置
	virtual CPoint GetButtonPos(UINT Index)
	{
		return  m_pParts[Index].m_Pos;
	}

	virtual BOOL GetDrawRound()
	{
		return DrawRound;
	}
	virtual COLORREF GetMenuBKColor()
	{
		return m_MenuBkColor;
	}
	virtual COLORREF GetMenuSelColor()
	{
		return m_MenuSelColor;
	}
};

CSkin * __stdcall CreateSkinObj()
{
	return new CSkin();
}