#pragma once
#include <Windows.h>

typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

class CReg
{
private:
	CReg(void);
	~CReg(void);

	BOOL IsWow64();
private:
	static CReg* pInstance;

	DWORD m_dwSamDesired_Read;
	DWORD m_dwSamDesired_Create;
	DWORD m_dwSamDesired_Write;

public:
	static CReg* GetInstance();
	static void FreeInstance();

	/// 레지스트리 키 생성, 키 삭제, 값 삭제, 값 설정
	bool _RegCreateKey(HKEY hKey, LPCTSTR lpcszSubKey);
	bool _RegDeleteKey(HKEY hKey, LPCTSTR lpcszSubKey);
	bool _RegDeleteValue(HKEY hKey, LPCTSTR lpcszSubKey, LPCTSTR lpcszValue);
	bool _RegSetValue(HKEY hKey, LPCTSTR lpcszSubKey, LPCTSTR lpcszValue, DWORD dwType, LPBYTE lpData, DWORD cbData);
	bool _RegGetValue(HKEY hKey, LPCTSTR lpcszSubKey, LPCTSTR lpcszValue, LPDWORD lpdwType, LPBYTE lpData, LPDWORD lpcbData);

public:
	LPFN_ISWOW64PROCESS			m_fnIsWow64Process;

};
