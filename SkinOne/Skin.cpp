// Skin.cpp: implementation of the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinDll.h"
#include "Skin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "resource.h"

#define MINBUTTON   6
#define MAXBUTTON   7
#define CLOSEBUTTON 8


void CSkin::LoadBitmapRes()		//加载位图资源
{
	for (UINT i = 0; i<m_PartCount; i++)
	{
		//1000表示位图资源的起始ID
	//	m_pParts[i].m_hBitmap = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(1000+i));
		m_pParts[i].m_hBitmap = ::LoadBitmap(AfxGetResourceHandle(),MAKEINTRESOURCE(1000+i));
	}
}

void CSkin::SetButtonPos()			//设置标题栏按钮的相对位置
{
	for (UINT i= MINBUTTON; i<=CLOSEBUTTON; i++)
	{
		m_pParts[i].m_Pos.y = 1;
		switch (i)
		{
		case MINBUTTON:
			{
				m_pParts[i].m_Pos.x = 30;
				break;
			}
		case MAXBUTTON:
			{
				m_pParts[i].m_Pos.x = 55;
				break;
			}
		case CLOSEBUTTON:
			{
				m_pParts[i].m_Pos.x = 80;
				break;
			}			
		}
	}
}


CSkin::CSkin()
{
	m_PartCount = 15;
	m_pParts = new CFormPart[m_PartCount];
	DrawRound = FALSE;
	m_MenuBkColor = RGB(85,179,108);
	m_MenuSelColor = RGB(193, 210, 238);
	LoadBitmapRes();
	SetButtonPos();
}

CSkin::CSkin(UINT PartCount)
{
	m_PartCount = PartCount;
	m_pParts = new CFormPart[m_PartCount];	
}

CSkin::~CSkin()
{	
	for (UINT i = 0; i< m_PartCount; i++)
	{
		//1000表示位图资源的起始ID
		DeleteObject(m_pParts[i].m_hBitmap) ;
	}
	delete [] m_pParts;
}




