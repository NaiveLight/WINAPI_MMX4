#pragma once

// ��Ʈ�� ���ҽ����� �ҷ����� ����

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


