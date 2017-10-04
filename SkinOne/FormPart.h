// FormPart.h: interface for the CFormPart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMPART_H__23A4D480_D7F4_4B6A_8FD1_DA22FCF34FC1__INCLUDED_)
#define AFX_FORMPART_H__23A4D480_D7F4_4B6A_8FD1_DA22FCF34FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFormPart  
{
public:
	HBITMAP m_hBitmap;		//位图资源
	CPoint m_Pos;			//位图资源位置，相对于右标题部分的相对位置，只对标题栏按钮起作用

public:
	CFormPart();
	virtual ~CFormPart();

};

#endif // !defined(AFX_FORMPART_H__23A4D480_D7F4_4B6A_8FD1_DA22FCF34FC1__INCLUDED_)
