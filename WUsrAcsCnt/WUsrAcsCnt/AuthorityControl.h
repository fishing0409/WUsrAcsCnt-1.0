#pragma once
using namespace std;

class CAuthorityControl
{
private:
	CAuthorityControl(void);
	~CAuthorityControl(void);

	LONG Hook();
	LONG UnHook();

private:
	static CAuthorityControl* pInstance;

public:
	static CAuthorityControl* GetInstance();
	static void FreeInstance();

	bool Start();
	bool Stop();

	bool IsControlPath(LPWSTR pwszPath);
	bool IsControlPath(LPSTR pszPath);
};