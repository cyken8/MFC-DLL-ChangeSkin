// FornPart.h: interface for the CFornPart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORNPART_H__6D4EDCDF_7E5B_4A40_A3A5_F8EBE6DEEF87__INCLUDED_)
#define AFX_FORNPART_H__6D4EDCDF_7E5B_4A40_A3A5_F8EBE6DEEF87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFornPart  
{
public:
	HBITMAP m_hBitmap;	//位图资源
	CRect m_Rect;		//位图资源位置，该位置相对于右标题部分的相对位置，只对标题栏按钮起作用
	
public:
	CFornPart();
	virtual ~CFornPart();

};

#endif // !defined(AFX_FORNPART_H__6D4EDCDF_7E5B_4A40_A3A5_F8EBE6DEEF87__INCLUDED_)
