// CustomMenu.h: interface for the CCustomMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMMENU_H__2BE130BB_E237_4C40_B14D_783A1376A16E__INCLUDED_)
#define AFX_CUSTOMMENU_H__2BE130BB_E237_4C40_B14D_783A1376A16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CCustomMenu : public CMenu
{
public:
//定义一个结构，记录菜单项的详细信息
	struct CMenuItem
	{
		CString m_MenuText;//菜单项的文本
		UINT m_ImageIndex;	//菜单项图像索引
		int m_MenuType;		//菜单的类型，-2顶层菜单，-1弹出式菜单，-0分隔条，其他普通菜单
	};
public:
	int m_ItemCount;		//记录菜单项的数量
	CMenuItem* m_MenuList;	//记录每个菜单项的信息
	int m_Index;			//遍历菜单时使用的索引
	COLORREF m_BkColor;		//菜单背景颜色
	COLORREF m_SelTopColor;	//顶层菜单选中时的颜色
	COLORREF m_OrginBkColor;
	COLORREF m_OrginSelColor;
	BOOL m_RandColor;		//菜单项是否启动随机颜色
	int m_nMenuLeft;
	int m_nMenuTop;			//菜单项的顶部起始位置
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpStruct);
	BOOL AttatchMenu(HMENU hMenu);
	static void GetAllItemCount(HMENU hMenu,int &ItemCount,BOOL FirstFind=TRUE);
	BOOL SetMenuItemInfo(CMenu* pMenu,BOOL Toped=TRUE);
	void SetMenuItemText(CDC* pDC,LPSTR strMenuText,CRect Rect);
	void DrawTopMenuBk(CDC* pDC,CRect Rect,BOOL State);
	void DrawSepMenu(CDC* pDC,CRect Rect);
	void DrawMenuBk(CDC* pDC,CRect Rect,COLORREF SrcColor,COLORREF DesColor,BOOL State=FALSE);
	int GetTopMenuWidth();
	HRGN GetClientMenuRgn();
	CCustomMenu();
	virtual ~CCustomMenu();

};

#endif // !defined(AFX_CUSTOMMENU_H__2BE130BB_E237_4C40_B14D_783A1376A16E__INCLUDED_)
