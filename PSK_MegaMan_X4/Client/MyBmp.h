#pragma once

// 비트맵 리소스들을 불러오는 역할

class CMyBmp
{
private:
	HDC m_hDC;
	HDC m_hMemDC;

	HBITMAP m_hBitmap;
	HBITMAP m_hOld;

public:
	CMyBmp();
	~CMyBmp();

public:
	// Getter
	HDC GetMemDC() { return m_hMemDC; }
	
public:
	void LoadBmp(const TCHAR* pFilePath);
	void Release();
};


