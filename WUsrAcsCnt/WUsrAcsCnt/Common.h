#pragma once
#include <vector>
#include <string>
using namespace std;

class CCommon
{
private:
	CCommon(void);
	~CCommon(void);

private:
	static CCommon* pInstance;
	
	WCHAR m_wszExeName[MAX_PATH] = { 0 };

public:
	static CCommon* GetInstance();
	static void FreeInstance();

	void Logging(LPCTSTR pszStr, ...);

	bool Init();

	bool SetAuthCntPth();
	bool SetExeName();

	LPWSTR GetExeName();

public:
	std::vector<std::wstring> m_vecAuthCntPth;
};