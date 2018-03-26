#pragma once
#include "Singleton.h"
#include "MyBmp.h"

class CBmpManager :
	public CSingleton<CBmpManager>
{
private:
	BMPMAP m_BmpMap;

public:
	CBmpManager();
	virtual ~CBmpManager();

public:
	void AddBitMap(const TCHAR* pFilePath, const TCHAR* pKey);
	CMyBmp* FindImage(const TCHAR* pFindKey);
	void Release();
};

