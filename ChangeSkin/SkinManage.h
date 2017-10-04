// SkinManage.h: interface for the CSkinManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINMANAGE_H__1A0E7B1F_60C1_4A72_A3C6_7B4ADB224B5D__INCLUDED_)
#define AFX_SKINMANAGE_H__1A0E7B1F_60C1_4A72_A3C6_7B4ADB224B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CFormPart;


//这个类里的变量和函数一定要按照动态库里面的顺序编写
class CSkinManage  
{
protected:
	UINT m_PartCount;    //窗体由几部分组成
	/******************窗体各部分位图资源********************
	0,1,2			分别为标题栏的左\中\右3部分
	3,4,5			分别为左,下,右边框
	6,7,8,9,10,11	为标题栏普通按钮和热点按钮
	*********************************************************/
	CFormPart* m_pParts;


public:
	//加载位图资源 
	virtual HBITMAP GetBitmapRes(UINT Index) = 0;
	virtual Release() = 0;
	virtual CPoint GetButtonPos(UINT Index) = 0;
	virtual BOOL GetDrawRound() = 0;
	virtual COLORREF GetMenuBKColor() = 0;
	virtual COLORREF GetMenuSelColor() = 0;

public:
	CSkinManage();
	virtual ~CSkinManage();
};

#endif // !defined(AFX_SKINMANAGE_H__1A0E7B1F_60C1_4A72_A3C6_7B4ADB224B5D__INCLUDED_)
