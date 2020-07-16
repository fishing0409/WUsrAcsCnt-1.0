#pragma once
using namespace std;

class CCommonControl
{
private:
	CCommonControl(void);
	~CCommonControl(void);

	LONG Hook();
	LONG UnHook();

private:
	static CCommonControl* pInstance;

public:
	static CCommonControl* GetInstance();
	static void FreeInstance();

	bool Start();
	bool Stop();
};