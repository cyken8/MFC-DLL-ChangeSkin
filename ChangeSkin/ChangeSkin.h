// ChangeSkin.h : main header file for the CHANGESKIN application
//

#if !defined(AFX_CHANGESKIN_H__E74C529B_F483_4F10_896A_A9E64AA7E05E__INCLUDED_)
#define AFX_CHANGESKIN_H__E74C529B_F483_4F10_896A_A9E64AA7E05E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SkinManage.h"
/////////////////////////////////////////////////////////////////////////////
// CChangeSkinApp:
// See ChangeSkin.cpp for the implementation of this class
//

class CChangeSkinApp : public CWinApp
{
public:
	CSkinManage* pSkin;				//换肤对象
	HINSTANCE m_hInstance;			//DLL实例句柄
	BOOL m_bLoadDll;					//是否加载DLL
public:
	BOOL AlterSkin(LPCTSTR lpFileName);
	CChangeSkinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeSkinApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChangeSkinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGESKIN_H__E74C529B_F483_4F10_896A_A9E64AA7E05E__INCLUDED_)
