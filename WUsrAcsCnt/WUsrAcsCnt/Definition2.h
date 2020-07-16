#pragma once
#include <aclapi.h>

typedef DWORD(WINAPI* fnTreeSetNamedSecurityInfoW)(
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

typedef DWORD(WINAPI* fnTreeSetNamedSecurityInfoA)(
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

typedef DWORD(WINAPI* fnSetNamedSecurityInfoW)(
    LPWSTR pObjectName,
    SE_OBJECT_TYPE ObjectType,
    SECURITY_INFORMATION SecurityInfo,
    PSID psidOwner,
    PSID psidGroup,
    PACL pDacl,
    PACL pSacl);

typedef DWORD(WINAPI* fnSetNamedSecurityInfoA)(
    LPSTR pObjectName,
    SE_OBJECT_TYPE ObjectType,
    SECURITY_INFORMATION SecurityInfo,
    PSID psidOwner,
    PSID psidGroup,
    PACL pDacl,
    PACL pSacl );
