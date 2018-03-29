#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
	:m_bIsInit(false)
{
}


CScene::~CScene()
{
}

void CScene::LateInit()
{
	if (!m_bIsInit)
		this->LateInit();
	m_bIsInit = true;
}

void CScene::DrawBackground(HDC hDC, const TCHAR* szName)
{
	CMyBmp* pBackGround = BmpManager->FindImage(szName);

	GdiTransparentBlt(hDC, 0, 0, BUFCX, BUFCY, pBackGround->GetMemDC(), 0, 0, pBackGround->GetBmpCX(), pBackGround->GetBmpCY(), RGB(255, 0, 255));
}

void CScene::DrawBackground(HDC hDC, const TCHAR * szName, float fScrollX, float fScrollY)
{
	// �̹��� : ȭ�� = 1 : 4 ����
	// ȭ�鿡�� 400�� ��ũ���� ���� �̹��������� 100�� ��ũ���� ������
	// �׸��� ����� �߸� �����ϰ� �־��� - 

	CMyBmp* pBackGround = BmpManager->FindImage(szName);

	int iSizeX = (int) (fScrollX != 0 ? fScrollX : 0);
	int iSizeY = (int) (fScrollY != 0 ? fScrollY : 0);

	GdiTransparentBlt(hDC, 0, 0, BUFCX, BUFCY, pBackGround->GetMemDC(), (int)fScrollX , (int)fScrollY, BUFCX, BUFCY, RGB(255, 0, 255));
}
