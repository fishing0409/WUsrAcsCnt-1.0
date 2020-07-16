#pragma once
#include "pch.h"
#include "AuthorityControl.h"
#include "Definition.h"
#include "detoursV2.h"
#include "Common.h"
#include <tchar.h>
#include <string>

fnTreeSetNamedSecurityInfoW CGlobal::g_pTreeSetNamedSecurityInfoW = NULL;
fnTreeSetNamedSecurityInfoA CGlobal::g_pTreeSetNamedSecurityInfoA = NULL;
fnSetNamedSecurityInfoW CGlobal::g_pSetNamedSecurityInfoW = NULL;
fnSetNamedSecurityInfoA CGlobal::g_pSetNamedSecurityInfoA = NULL;

CAuthorityControl* CAuthorityControl::pInstance = nullptr;
CAuthorityControl::CAuthorityControl(void)
{
}
CAuthorityControl::~CAuthorityControl(void)
{
}
CAuthorityControl* CAuthorityControl::GetInstance()
{
    if (pInstance == nullptr)
    {
        pInstance = new CAuthorityControl;
    }
    return pInstance;
}
void CAuthorityControl::FreeInstance()
{
    if (nullptr != pInstance)
    {
        delete pInstance;
        pInstance = nullptr;
    }
}
bool CAuthorityControl::Start()
{
    Hook();
    return true;
}
bool CAuthorityControl::Stop()
{
    UnHook();
    FreeInstance();
    return true;
}
LONG CAuthorityControl::Hook()
{
    LONG lError = 0;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourSetIgnoreTooSmall(TRUE);

    CGlobal::g_pTreeSetNamedSecurityInfoW = (fnTreeSetNamedSecurityInfoW)DetourFindFunction("Advapi32.dll", "TreeSetNamedSecurityInfoW");
    if (CGlobal::g_pTreeSetNamedSecurityInfoW)
    {
        DetourAttach((PVOID*)&CGlobal::g_pTreeSetNamedSecurityInfoW, CGlobal::NewTreeSetNamedSecurityInfoW);
    }
    CGlobal::g_pTreeSetNamedSecurityInfoA = (fnTreeSetNamedSecurityInfoA)DetourFindFunction("Advapi32.dll", "TreeSetNamedSecurityInfoA");
    if (CGlobal::g_pTreeSetNamedSecurityInfoA)
    {
        DetourAttach((PVOID*)&CGlobal::g_pTreeSetNamedSecurityInfoA, CGlobal::NewTreeSetNamedSecurityInfoA);
    }

    CGlobal::g_pSetNamedSecurityInfoW = (fnSetNamedSecurityInfoW)DetourFindFunction("Advapi32.dll", "SetNamedSecurityInfoW");
    if (CGlobal::g_pSetNamedSecurityInfoW)
    {
        DetourAttach((PVOID*)&CGlobal::g_pSetNamedSecurityInfoW, CGlobal::NewSetNamedSecurityInfoW);
    }
    CGlobal::g_pSetNamedSecurityInfoA = (fnSetNamedSecurityInfoA)DetourFindFunction("Advapi32.dll", "SetNamedSecurityInfoA");
    if (CGlobal::g_pSetNamedSecurityInfoA)
    {
        DetourAttach((PVOID*)&CGlobal::g_pSetNamedSecurityInfoA, CGlobal::NewSetNamedSecurityInfoA);
    }

    lError = DetourTransactionCommit();
    return lError;
}
LONG CAuthorityControl::UnHook()
{
    LONG lError = 0;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourSetIgnoreTooSmall(TRUE);

    if (CGlobal::g_pTreeSetNamedSecurityInfoW)
    {
        DetourDetach((PVOID*)&CGlobal::g_pTreeSetNamedSecurityInfoW, CGlobal::NewTreeSetNamedSecurityInfoW);
    }
    if (CGlobal::g_pTreeSetNamedSecurityInfoA)
    {
        DetourDetach((PVOID*)&CGlobal::g_pTreeSetNamedSecurityInfoA, CGlobal::NewTreeSetNamedSecurityInfoA);
    }
    if (CGlobal::g_pSetNamedSecurityInfoW)
    {
        DetourDetach((PVOID*)&CGlobal::g_pSetNamedSecurityInfoW, CGlobal::NewSetNamedSecurityInfoW);
    }
    if (CGlobal::g_pSetNamedSecurityInfoA)
    {
        DetourDetach((PVOID*)&CGlobal::g_pSetNamedSecurityInfoA, CGlobal::NewSetNamedSecurityInfoA);
    }

    lError = DetourTransactionCommit();
    return lError;
}

bool CAuthorityControl::IsControlPath(LPWSTR pwszPath)
{
    bool bRes = false;

    if (wcslen(pwszPath) == 0)
        return bRes;

    for (auto i : CCommon::GetInstance()->m_vecAuthCntPth)
    {
        if (wcslen(i.c_str()) == 0)
            continue;

        if (wcsstr(pwszPath, i.c_str()) != NULL)
        {
            CCommon::GetInstance()->Logging(_T("CAuthorityControl.IsControlPath() [%s] - Controlled Path Detection "), pwszPath);
            bRes |= true;
            break;
        }
    }
    return bRes;
}
bool CAuthorityControl::IsControlPath(LPSTR pszPath)
{
    return IsControlPath(CA2W(pszPath));
}

DWORD WINAPI CGlobal::NewTreeSetNamedSecurityInfoW(
    LPWSTR pObjectName,
    SE_OBJECT_TYPE ObjectType,
    SECURITY_INFORMATION SecurityInfo,
    PSID pOwner,
    PSID pGroup,
    PACL pDacl,
    PACL pSacl,
    DWORD dwAction,
    FN_PROGRESS fnProgress,
    PROG_INVOKE_SETTING ProgressInvokeSetting,
    PVOID Args)
{
    if(CAuthorityControl::GetInstance()->IsControlPath(pObjectName))
    {
        return NULL;
    }
	return CGlobal::g_pTreeSetNamedSecurityInfoW(pObjectName, ObjectType, SecurityInfo, pOwner, pGroup, pDacl, pSacl, dwAction, fnProgress, ProgressInvokeSetting, Args);
}
DWORD WINAPI CGlobal::NewTreeSetNamedSecurityInfoA(
    LPSTR pObjectName,
    SE_OBJECT_TYPE ObjectType,
    SECURITY_INFORMATION SecurityInfo,
    PSID pOwner,
    PSID pGroup,
    PACL pDacl,
    PACL pSacl,
    DWORD dwAction,
    FN_PROGRESS fnProgress,
    PROG_INVOKE_SETTING ProgressInvokeSetting,
    PVOID Args)
{
    if (CAuthorityControl::GetInstance()->IsControlPath(pObjectName))
    {
        return NULL;
    }
    return CGlobal::g_pTreeSetNamedSecurityInfoA(pObjectName, ObjectType, SecurityInfo, pOwner, pGroup, pDacl, pSacl, dwAction, fnProgress, ProgressInvokeSetting, Args);
}

DWORD WINAPI CGlobal::NewSetNamedSecurityInfoW(
    LPWSTR pObjectName,
    SE_OBJECT_TYPE ObjectType,
    SECURITY_INFORMATION SecurityInfo,
    PSID psidOwner,
    PSID psidGroup,
    PACL pDacl,
    PACL pSacl)
{
    if (CAuthorityControl::GetInstance()->IsControlPath(pObjectName))
    {
        return NULL;
    }
    return CGlobal::g_pSetNamedSecurityInfoW(pObjectName, ObjectType, SecurityInfo, psidOwner, psidGroup, pDacl, pSacl);
}

DWORD WINAPI CGlobal::NewSetNamedSecurityInfoA(
    LPSTR pObjectName,
    SE_OBJECT_TYPE ObjectType,
    SECURITY_INFORMATION SecurityInfo,
    PSID psidOwner,
    PSID psidGroup,
    PACL pDacl,
    PACL pSacl)
{
    if (CAuthorityControl::GetInstance()->IsControlPath(pObjectName))
    {
        return NULL;
    }
    return CGlobal::g_pSetNamedSecurityInfoA(pObjectName, ObjectType, SecurityInfo, psidOwner, psidGroup, pDacl, pSacl);
}