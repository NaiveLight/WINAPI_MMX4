#include "stdafx.h"
#include "BmpManager.h"


CBmpManager::CBmpManager()
{
}


CBmpManager::~CBmpManager()
{
	Release();
}

void CBmpManager::AddBitMap(const TCHAR * pFilePath, const TCHAR * pKey)
{
	CMyBmp* pBmp = new CMyBmp;
	pBmp->LoadBmp(pFilePath);

	if (m_BmpMap.insert({ pKey, pBmp }).second == false)
		delete pBmp;
}

CMyBmp * CBmpManager::FindImage(const TCHAR * pFindKey)
{
	auto iter_find = find_if(m_BmpMap.begin(), m_BmpMap.end(),
		[&pFindKey](auto& MyPair)
	{
		return !lstrcmp(pFindKey, MyPair.first);
	});

	if (iter_find == m_BmpMap.end())
	{
		return nullptr;
	}

	return iter_find->second;
}

void CBmpManager::Release()
{
	for_each(m_BmpMap.begin(), m_BmpMap.end(),
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_BmpMap.clear();
}
