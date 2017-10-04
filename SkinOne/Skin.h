// Skin.h: interface for the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKIN_H__BBFFEE8F_E185_4C26_B9B1_A0873DC82AA4__INCLUDED_)
#define AFX_SKIN_H__BBFFEE8F_E185_4C26_B9B1_A0873DC82AA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FormPart.h"
class CSkin
{
protected:
	UINT m_PartCount;  //窗体由几部分组成
	/******************窗体各部分位图资源索引: *******************
 
	0,1,2:         分别为标题栏的左\中\右3部分
	3,4,5:         分别为左,下,右边框
	6,7,8,9,10,11: 为标题栏普通按钮和热点按钮
	12,13:         表示左下角和右下角位图
	14:            表示背景位图
	*************************************************************/
	CFormPart* m_pParts;
	COLORREF m_MenuBkColor;		//菜单背景颜色
	COLORREF m_MenuSelColor;	//菜单选中时的颜色
	BOOL DrawRound;				//是否绘制圆角

public:


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

	void LoadBitmapRes();		//加载位图资源
	void SetButtonPos()	;		//设置标题栏按钮的相对位置
public:
	CSkin();
	CSkin(UINT PartCount);
	~CSkin();

};


#endif // !defined(AFX_SKIN_H__BBFFEE8F_E185_4C26_B9B1_A0873DC82AA4__INCLUDED_)
