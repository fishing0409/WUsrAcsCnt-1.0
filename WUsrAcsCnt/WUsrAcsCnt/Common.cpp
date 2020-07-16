#pragma once
#include "pch.h"
#include "Common.h"
#include "Reg.h"
#include "WDefine.h"
#include "PCRegConfig.h"

CCommon* CCommon::pInstance = nullptr;
CCommon::CCommon(void)
{
}
CCommon::~CCommon(void)
{
}
CCommon* CCommon::GetInstance()
{
    if (pInstance == nullptr)
    {
        pInstance = new CCommon;
        if (pInstance != nullptr)
            pInstance->Init();
    }
    return pInstance;
}
void CCommon::FreeInstance()
{
    if (nullptr != pInstance)
    {
        delete pInstance;
        pInstance = nullptr;
    }
}
bool CCommon::Init()
{
    SetExeName();
    SetAuthCntPth();
    return true;
}

bool CCommon::SetExeName()
{
    WCHAR wszPath[MAX_PATH] = { 0 };
    GetModuleFileNameW(NULL, wszPath, MAX_PATH);
    wcscpy_s(m_wszExeName, MAX_PATH, PathFindFileNameW(wszPath));
    
    if (wcslen(m_wszExeName))
        return true;
    return false;
}

LPWSTR CCommon::GetExeName()
{
    if (!wcslen(m_wszExeName))
        SetExeName();
    return m_wszExeName;
}

void CCommon::Logging(LPCTSTR pszStr, ...)
{
    TCHAR szMsg[MAX_PATH * 2];
    TCHAR szLogging[MAX_PATH * 2];
    va_list args;
    va_start(args, pszStr);
    _vstprintf_s(szMsg, MAX_PATH * 2, pszStr, args);
    swprintf_s(szLogging, L"[WUsrAcsCnt] [%s] %s", GetExeName(),szMsg);
    OutputDebugString(szLogging);
}

bool CCommon::SetAuthCntPth()
{
    DWORD dwSize = NULL;
    WCHAR wszPCSetupPath[MAX_PATH] = { 0 };
    WCHAR wszDHSetupPath[MAX_PATH] = { 0 };
    WCHAR wszCSSetupPath[MAX_PATH] = { 0 };
    WCHAR wszPFSetupPath[MAX_PATH] = { 0 };
    WCHAR wszSCSetupPath[MAX_PATH] = { 0 };
    WCHAR wszITSSetupPath[MAX_PATH] = { 0 };

    WCHAR wszPCSpcfPath[MAX_PATH] = { 0 };
    WCHAR wszDHSpcfPath[MAX_PATH] = { 0 };
    WCHAR wszCSSpcfPath[MAX_PATH] = { 0 };
    WCHAR wszPFSpcfPath[MAX_PATH] = { 0 };
    WCHAR wszSCSpcfPath[MAX_PATH] = { 0 };
    WCHAR wszITSSpcfPath[MAX_PATH] = { 0 };

    WCHAR wszExtraPth[MAX_PATH * 4] = { 0 };

    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_PC_ROOT, REGVAL_SETUPPATH, NULL, (BYTE*)wszPCSetupPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_DH_ROOT, REGVAL_SETUPPATH, NULL, (BYTE*)wszDHSetupPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_CS_ROOT, REGVAL_SETUPPATH, NULL, (BYTE*)wszCSSetupPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_PF_ROOT, REGVAL_SETUPPATH, NULL, (BYTE*)wszPFSetupPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_SC_ROOT, REGVAL_SETUPPATH, NULL, (BYTE*)wszSCSetupPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_ITS_ROOT, REGVAL_SETUPPATH, NULL, (BYTE*)wszITSSetupPath, &(dwSize = MAX_PATH));

    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_PC_ROOT, REGVAL_SPECIFICFOLDER, NULL, (BYTE*)wszPCSpcfPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_DH_ROOT, REGVAL_SPECIFICFOLDER, NULL, (BYTE*)wszDHSpcfPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_CS_ROOT, REGVAL_SPECIFICFOLDER, NULL, (BYTE*)wszCSSpcfPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_PF_ROOT, REGVAL_SPECIFICFOLDER, NULL, (BYTE*)wszPFSpcfPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_SC_ROOT, REGVAL_SPECIFICFOLDER, NULL, (BYTE*)wszSCSpcfPath, &(dwSize = MAX_PATH));
    CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_ITS_ROOT, REGVAL_SPECIFICFOLDER, NULL, (BYTE*)wszITSSpcfPath, &(dwSize = MAX_PATH));

    wcslen(wszPCSetupPath) > 0 ? m_vecAuthCntPth.push_back(wszPCSetupPath) : NULL;
    wcslen(wszDHSetupPath) > 0 ? m_vecAuthCntPth.push_back(wszDHSetupPath) : NULL;
    wcslen(wszCSSetupPath) > 0 ? m_vecAuthCntPth.push_back(wszCSSetupPath) : NULL;
    wcslen(wszPFSetupPath) > 0 ? m_vecAuthCntPth.push_back(wszPFSetupPath) : NULL;
    wcslen(wszSCSetupPath) > 0 ? m_vecAuthCntPth.push_back(wszSCSetupPath) : NULL;
    wcslen(wszITSSetupPath) > 0 ? m_vecAuthCntPth.push_back(wszITSSetupPath) : NULL;

    wcslen(wszPCSpcfPath) > 0 ? m_vecAuthCntPth.push_back(wszPCSpcfPath) : NULL;
    wcslen(wszDHSpcfPath) > 0 ? m_vecAuthCntPth.push_back(wszDHSpcfPath) : NULL;
    wcslen(wszCSSpcfPath) > 0 ? m_vecAuthCntPth.push_back(wszCSSpcfPath) : NULL;
    wcslen(wszPFSpcfPath) > 0 ? m_vecAuthCntPth.push_back(wszPFSpcfPath) : NULL;
    wcslen(wszSCSpcfPath) > 0 ? m_vecAuthCntPth.push_back(wszSCSpcfPath) : NULL;
    wcslen(wszITSSpcfPath) > 0 ? m_vecAuthCntPth.push_back(wszITSSpcfPath) : NULL;

    if (CReg::GetInstance()->_RegGetValue(HKEY_LOCAL_MACHINE, REGKEY_WOW_ROOT, REGVAL_AUTHCNT_PATH, NULL, (BYTE*)wszExtraPth, &(dwSize = MAX_PATH * 4)))
    {
        if (wcslen(wszExtraPth) > 0)
        {
            WCHAR split_type[] = _T("|");
            WCHAR* p_next_token = NULL;
            WCHAR* p_token = _tcstok_s(wszExtraPth, split_type, &p_next_token);

            while (p_token != NULL)
            {
                std::wstring szTemp = p_token;
                m_vecAuthCntPth.push_back(szTemp);
                p_token = wcstok_s(NULL, split_type, &p_next_token);
            }
        }
    }

    for (auto i : m_vecAuthCntPth)
    {
        CCommon::GetInstance()->Logging(_T("Authority Control Path %s"), i.c_str());
    }

    return true;
}



