#pragma once
#include "Definition2.h"
class CGlobal
{
public:
    static DWORD WINAPI NewTreeSetNamedSecurityInfoW(
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
        PVOID Args);

    static DWORD WINAPI NewTreeSetNamedSecurityInfoA(
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
        PVOID Args);

    static DWORD WINAPI NewSetNamedSecurityInfoW(
        LPWSTR pObjectName,
        SE_OBJECT_TYPE ObjectType,
        SECURITY_INFORMATION SecurityInfo,
        PSID psidOwner,
        PSID psidGroup,
        PACL pDacl,
        PACL pSacl);

    static DWORD WINAPI NewSetNamedSecurityInfoA(
        LPSTR pObjectName,
        SE_OBJECT_TYPE ObjectType,
        SECURITY_INFORMATION SecurityInfo,
        PSID psidOwner,
        PSID psidGroup,
        PACL pDacl,
        PACL pSacl);


    /// [#3716] [20.07.15] [YYKIM] [ ���� �� ���� ���ȱ��� ���� - AuthorityControl.cpp ]
    static fnTreeSetNamedSecurityInfoW	g_pTreeSetNamedSecurityInfoW;
    static fnTreeSetNamedSecurityInfoA	g_pTreeSetNamedSecurityInfoA;
    static fnSetNamedSecurityInfoW g_pSetNamedSecurityInfoW;
    static fnSetNamedSecurityInfoA g_pSetNamedSecurityInfoA;

};
//TODO : static ���� �ʱ�ȭ�� �ش� Cpp���� ����