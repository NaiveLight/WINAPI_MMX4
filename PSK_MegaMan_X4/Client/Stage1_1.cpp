#include "stdafx.h"
#include "Stage1_1.h"
#include "Player.h"
#include "MapObj.h"
#include "Door.h"
#include "Ground.h"


CStage1_1::CStage1_1()
{
}

CStage1_1::~CStage1_1()
{
	Release();
}

void CStage1_1::Init()
{
	BmpManager->AddBitMap(L"../MyResource/BG/BG_ST1_1.bmp", L"BG_STAGE1_1");

	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_1.bmp", L"ST1_OBJ_1");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_2.bmp", L"ST1_OBJ_2");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_3.bmp", L"ST1_OBJ_3");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_4.bmp", L"ST1_OBJ_4");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_5.bmp", L"ST1_OBJ_5");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_6.bmp", L"ST1_OBJ_6");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_7.bmp", L"ST1_OBJ_7");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_8.bmp", L"ST1_OBJ_8");

	BmpManager->AddBitMap(L"../MyResource/ST1/ST1_HALF_DOOR.bmp", L"ST1_HALF_DOOR");
	BmpManager->AddBitMap(L"../MyResource/ST1/ST1_FULL_DOOR.bmp", L"ST1_FULL_DOOR");

	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_LEFT.bmp", L"X_LEFT");
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_RIGHT.bmp", L"X_RIGHT");
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_RF_LEFT.bmp", L"X_RF_LEFT");
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_RF_RIGHT.bmp", L"X_RF_RIGHT");

	// Max X : 5064 / Y : 104
	// Boss 전 X : 4756
	// Boss 등장 : 1250

	// SavePoint = 1180 / 3250
	

	// 문
	//1530 , 2050, 2560, 3070

	// 3576 쯤 부터 y스크롤 들어가야할듯

	GameManager->SetMaxScrollX(5064.f);
	GameManager->SetMaxScrollY(104.f);
}

void CStage1_1::LateInit()
{
	CGameObject* pPlayer = CAbstractFactory<CPlayer>::CreateObj();
	GameManager->AddObject(pPlayer, OBJ_PLAYER);
	
	CGameObject* m_Obj = CAbstractFactory<CMapObj>::CreateObj(77,  141 , L"ST1_OBJ_1");
	m_Obj->SetSize(150.f, 200.f);
	INFO temp = { 77, 141, 150, 200 };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(694, 111, L"ST1_OBJ_2");
	m_Obj->SetSize(150.f, 200.f);
	temp = { 694, 111, 150, 200 };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(1309, 104, L"ST1_OBJ_3");
	m_Obj->SetSize(400.f, 200.f);
	temp = { 1309, 104, 400.f, 200.f };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(1717, 104, L"ST1_OBJ_4");
	m_Obj->SetSize(200.f, 200.f);
	temp = { 1717, 104, 200.f, 200.f };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(2229, 99, L"ST1_OBJ_5");
	m_Obj->SetSize(200.f, 200.f);
	temp = { 2229, 99, 200.f, 200.f };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(2735, 100, L"ST1_OBJ_6");
	m_Obj->SetSize(200.f, 200.f);
	temp = { 2735, 100, 200.f, 200.f };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(3170, 100, L"ST1_OBJ_7");
	m_Obj->SetSize(400.f, 200.f);
	temp = { 3170, 100, 400.f, 200.f };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	m_Obj = CAbstractFactory<CMapObj>::CreateObj(3573, 120, L"ST1_OBJ_8");
	m_Obj->SetSize(100.f, 240.f);
	temp = { 3573, 120, 100.f, 240.f };
	dynamic_cast<CMapObj*>(m_Obj)->SetOriginInfo(temp);
	GameManager->AddObject(m_Obj, OBJ_MAP);

	// 문
	//1530 , 2050, 2560, 3070
	CGameObject* pHalfDoor = CAbstractFactory<CDoor>::CreateObj(1665, 131, L"ST1_HALF_DOOR",3, 4, 0, 1);
	GameManager->AddObject(pHalfDoor, OBJ_INTERACT);

	pHalfDoor = CAbstractFactory<CDoor>::CreateObj(2181, 130, L"ST1_HALF_DOOR", 3, 4, 0, 1);
	GameManager->AddObject(pHalfDoor, OBJ_INTERACT);

	pHalfDoor = CAbstractFactory<CDoor>::CreateObj(2692, 129, L"ST1_HALF_DOOR", 3, 4, 0, 1);
	GameManager->AddObject(pHalfDoor, OBJ_INTERACT);

	CGameObject* pFullDoor = CAbstractFactory<CDoor>::CreateObj(3215, 110, L"ST1_FULL_DOOR", 3, 4, 0, 1);
	GameManager->AddObject(pFullDoor, OBJ_INTERACT);

	//GameManager->SetScrollX(3700.f);
	//GameManager->SetScrollX(104.f);

	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 200,  50, 250, 100}), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 0, 190, 3790, BUFCY}), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateLineGround(POINT{ 3790, 190 }, POINT{ 3800, 190 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateLineGround(POINT{ 3800, 190 }, POINT{4320, 320}), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 4320, 320, 5384, 400 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 4900, 100, 5050, 145 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 5042, 145, 5060, 255 }), OBJ_GROUND);

}

void CStage1_1::Update()
{
	CScene::LateInit();
	GameManager->Update();
}

void CStage1_1::LateUpdate()
{
	//if (KeyManager->KeyPressing(VK_UP))
	//{
	//	GameManager->SetScrollY(-5.f);
	//}

	//if (KeyManager->KeyPressing(VK_DOWN))
	//{
	//	GameManager->SetScrollY(5.f);
	//}

	//if (KeyManager->KeyPressing(VK_LEFT))
	//{
	//	GameManager->SetScrollX(-10.f);
	//}

	//if (KeyManager->KeyPressing(VK_RIGHT))
	//{
	//	GameManager->SetScrollX(10.f);
	//}

	GameManager->LateUpdate();
}

void CStage1_1::Render(HDC hDC)
{
	float fScrollX = GameManager->GetScrollX();
	float fScrollY = GameManager->GetScrollY();

	DrawBackground(hDC, L"BG_STAGE1_1", fScrollX, fScrollY);
	GameManager->Render(hDC);

}

void CStage1_1::Release()
{
	GameManager->ReleaseObj(OBJ_PLAYER);
	GameManager->ReleaseObj(OBJ_INTERACT);
	GameManager->ReleaseObj(OBJ_GROUND);
	GameManager->ReleaseObj(OBJ_MAP);
	GameManager->ReleaseObj(OBJ_MONSTER);
	GameManager->ReleaseObj(OBJ_UI);
	GameManager->ResetScroll();
}
