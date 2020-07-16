#pragma once
#include "pch.h"
#include "CommonControl.h"
#include "Definition.h"
#include "detoursV2.h"
#include "Common.h"

CCommonControl* CCommonControl::pInstance = nullptr;
CCommonControl::CCommonControl(void)
{
}
CCommonControl::~CCommonControl(void)
{
}
CCommonControl* CCommonControl::GetInstance()
{
    if (pInstance == nullptr)
    {
        pInstance = new CCommonControl;
    }
    return pInstance;
}
void CCommonControl::FreeInstance()
{
    if (nullptr != pInstance)
    {
        delete pInstance;
        pInstance = nullptr;
    }
}
bool CCommonControl::Start()
{
    Hook();
    return true;
}
bool CCommonControl::Stop()
{
    UnHook();
    FreeInstance();
    return true;
}
LONG CCommonControl::Hook()
{
    LONG lError = 0;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourSetIgnoreTooSmall(TRUE);

    lError = DetourTransactionCommit();
    return lError;
}
LONG CCommonControl::UnHook()
{
    LONG lError = 0;
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourSetIgnoreTooSmall(TRUE);

    lError = DetourTransactionCommit();
    return lError;
}