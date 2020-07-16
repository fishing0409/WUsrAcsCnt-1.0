// WUsrAcsCnt.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WUsrAcsCnt.h"
#include "CommonControl.h"
#include "AuthorityControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CWUsrAcsCntApp, CWinApp)
END_MESSAGE_MAP()

CWUsrAcsCntApp::CWUsrAcsCntApp()
{

}
CWUsrAcsCntApp::~CWUsrAcsCntApp()
{
	CCommonControl::GetInstance()->Stop();
	CAuthorityControl::GetInstance()->Stop();
}

CWUsrAcsCntApp theApp;

BOOL CWUsrAcsCntApp::InitInstance()
{// TODO : 해당 모듈 개발 시 기능별로 코드 분기 권장
	CWinApp::InitInstance();
	CCommonControl::GetInstance()->Start();
	CAuthorityControl::GetInstance()->Start();
	return TRUE;
}
