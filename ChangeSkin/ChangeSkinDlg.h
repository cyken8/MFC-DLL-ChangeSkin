// ChangeSkinDlg.h : header file
//

#if !defined(AFX_CHANGESKINDLG_H__D570EB87_FAC0_479C_B43F_5325A15D6B7B__INCLUDED_)
#define AFX_CHANGESKINDLG_H__D570EB87_FAC0_479C_B43F_5325A15D6B7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChangeSkinDlg dialog

#define WM_ICONALT WM_USER + 1		//绘制动画图标

typedef CSkinManage* (__stdcall* fCreateSkinObj)();
#define fLeftBand     1				//绘制窗口各部分标识
#define fLeftTitle    2
#define fRightTitle   4
#define fMidTitle     8
#define fRightBand    16
#define fBottomBand   32
#define fLeftBottom   64
#define fRightBottom  128
#define fMinButton    256
#define fMaxButton    512
#define fCloseButton  1024
#define fAll          2047



//class CSkinManage;
#include "CustomMenu.h"
#include "SkinManage.h"
class CChangeSkinDlg : public CDialog
{
public:
	enum CButtonState{bsNone,bsIni,bsMin,bsMax,bsRes,bsClose};
public:
	enum{ICONNUM=2};
	HICON m_icon[ICONNUM];
public:
	CCustomMenu m_Menu;		//自定义菜单
	CSkinManage* pSkin;		//定义皮肤对象
	HINSTANCE m_hInstance;	//动态链接库实例句柄
	CBitmap m_Bk;			//背景位图
	BOOL m_bLoadDll;		//是否加载DLL
	int m_TitleDrawHeight;	//标题栏实际的绘制高度
	BOOL m_IsMax;			//是否处于最大化状态
	int m_BorderWidth;		//边框宽度
	int m_BorderHeight;		//边框高度
	int m_FrameWidth;		//窗体3D宽度
	int m_FrameHeight;		//窗体3D高度
	int m_CaptionHeight;	//标题栏的高度(非实际)
	CString m_szCaption;	//窗口标题
	COLORREF m_CaptionColor;//标题字体颜色
	CFont m_CaptionFont;	//标题字体
	int m_ButtonWidth;		//按钮位图宽度
	int m_ButtonHeight;		//按钮位图高度
	BOOL m_FirstShow;		//窗口首次被显示
	CRect m_OriginRect;		//原始窗口区域
	//标题栏按钮的显示区域
	CRect m_IniRect,m_MinRect,m_MaxRect,m_CloseRect;
	//左标题，中间标题，右标题显示区域
	CRect m_LTitleRc,m_MTitleRc,m_RTitleRc;
	CButtonState m_ButtonState;
	BOOL m_IsDrawForm;		//是否需要绘制窗体
	CRgn m_WndRgn,m_ClipRgn;	//创建和显示剪辑区域
	int m_leftwidth;		//左标题的宽度
	int m_rightwidth;		//右标题的宽度
	int m_leftlinewidth;		//窗口边框和3D宽度，左边框的宽度
	int m_rLineWidth;			//右边框的宽度
	int m_bLineHeight;			//底边框的宽度


// Construction
public:
	void SetDlgZone();
	void SkinApplication();
	void SkinDialog(UINT Flags=fAll);
	void DrawDialogText();
	CChangeSkinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeSkinDlg)
	enum { IDD = IDD_CHANGESKIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeSkinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChangeSkinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnWindowsskin();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnLoadfile();
	afx_msg void OnAboutbox();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGESKINDLG_H__D570EB87_FAC0_479C_B43F_5325A15D6B7B__INCLUDED_)
