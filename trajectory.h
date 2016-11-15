// trajectory.h : main header file for the PROJECT_NAME application
// Agung Pambudi <agung.pambudi5595@gmail.com>

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CtrajectoryApp:
// See trajectory.cpp for the implementation of this class
//

class CtrajectoryApp : public CWinApp
{
public:
	CtrajectoryApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CtrajectoryApp theApp;