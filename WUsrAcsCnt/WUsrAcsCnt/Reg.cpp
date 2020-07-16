#include "Reg.h"

CReg* CReg::pInstance = nullptr;
CReg::CReg(void)
{
    m_dwSamDesired_Read = KEY_READ;
    m_dwSamDesired_Create = KEY_CREATE_SUB_KEY;
    m_dwSamDesired_Write = KEY_WRITE;
    if (IsWow64())
    {
        m_dwSamDesired_Read |= KEY_WOW64_64KEY;
        m_dwSamDesired_Create |= KEY_WOW64_64KEY;
        m_dwSamDesired_Write |= KEY_WOW64_64KEY;
    }
}
CReg::~CReg(void)
{
    CReg::GetInstance()->FreeInstance();
}
CReg* CReg::GetInstance()
{
    if (pInstance == nullptr)
    {
        pInstance = new CReg;
    }
    return pInstance;
}

void CReg::FreeInstance()
{
    if (nullptr != pInstance)
    {
        delete pInstance;
        pInstance = nullptr;
    }
}

BOOL CReg::IsWow64()
{
    BOOL	bIsWow64 = FALSE;
    if (m_fnIsWow64Process == NULL)
    {
        m_fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
    }
    if (NULL != m_fnIsWow64Process)
    {
        if (!m_fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        {
        }
    }
    return bIsWow64;
}

bool CReg::_RegCreateKey(HKEY hKey, LPCTSTR lpcszSubKey)
{
    HKEY hRKey = nullptr;
    __try
    {
        return (ERROR_SUCCESS == ::RegCreateKeyEx(hKey, lpcszSubKey, 0, nullptr, REG_OPTION_NON_VOLATILE, m_dwSamDesired_Create, nullptr, &hRKey, nullptr));
    }
    __finally
    {
        if (nullptr != hRKey) { ::RegCloseKey(hRKey); }
    }
    return false;
}
bool CReg::_RegDeleteKey(HKEY hKey, LPCTSTR lpcszSubKey)
{
    return (ERROR_SUCCESS == ::RegDeleteKey(hKey, lpcszSubKey));
}
bool CReg::_RegDeleteValue(HKEY hKey, LPCTSTR lpcszSubKey, LPCTSTR lpcszValue)
{
    HKEY hRKey = nullptr;
    __try
    {
        if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpcszSubKey, 0UL, m_dwSamDesired_Write, &hRKey))
        {
            return (ERROR_SUCCESS == ::RegDeleteValue(hRKey, lpcszValue));
        }
    }
    __finally
    {
        if (nullptr != hRKey) { ::RegCloseKey(hRKey); }
    }
    return false;
}
bool CReg::_RegSetValue(HKEY hKey, LPCTSTR lpcszSubKey, LPCTSTR lpcszValue, DWORD dwType, LPBYTE lpData, DWORD cbData)
{
    HKEY hRKey = nullptr;
    __try
    {
        if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpcszSubKey, 0UL, m_dwSamDesired_Write, &hRKey))
        {
            return (ERROR_SUCCESS == ::RegSetValueEx(hRKey, lpcszValue, 0UL, dwType, lpData, cbData));
        }
    }
    __finally
    {
        if (nullptr != hRKey) { ::RegCloseKey(hRKey); }
    }
    return false;
}
bool CReg::_RegGetValue(HKEY hKey, LPCTSTR lpcszSubKey, LPCTSTR lpcszValue, LPDWORD lpdwType, LPBYTE lpData, LPDWORD lpcbData)
{
    HKEY hRKey = nullptr;
    __try
    {
        if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpcszSubKey, 0UL, m_dwSamDesired_Read, &hRKey))
        {
            return (ERROR_SUCCESS == ::RegQueryValueEx(hRKey, lpcszValue, nullptr, lpdwType, (LPBYTE)lpData, lpcbData));
        }
    }
    __finally
    {
        if (nullptr != hRKey) { ::RegCloseKey(hRKey); }
    }
    return false;
}