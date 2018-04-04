#include "stdafx.h"
#include "Stage1_1.h"
#include "Player.h"
#include "MapObj.h"
#include "Door.h"
#include "Ground.h"
#include "SpikeMarl.h"
#include "KnotBeretA.h"
#include "Eregion.h"
#include "Effect_Explosion.h"


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

	//배경 이미지
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_1.bmp", L"ST1_OBJ_1");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_2.bmp", L"ST1_OBJ_2");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_3.bmp", L"ST1_OBJ_3");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_4.bmp", L"ST1_OBJ_4");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_5.bmp", L"ST1_OBJ_5");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_6.bmp", L"ST1_OBJ_6");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_7.bmp", L"ST1_OBJ_7");
	BmpManager->AddBitMap(L"../MyResource/ST1/MAP_OBJ_8.bmp", L"ST1_OBJ_8");

	// 인터랙션 
	BmpManager->AddBitMap(L"../MyResource/ST1/ST1_HALF_DOOR.bmp", L"ST1_HALF_DOOR");
	BmpManager->AddBitMap(L"../MyResource/ST1/ST1_FULL_DOOR.bmp", L"ST1_FULL_DOOR");

	// 캐릭터
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_LEFT.bmp", L"X_LEFT");
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_RIGHT.bmp", L"X_RIGHT");
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_RF_LEFT.bmp", L"X_RF_LEFT");
	BmpManager->AddBitMap(L"../MyResource/PLAYER/X_RF_RIGHT.bmp", L"X_RF_RIGHT");

	//UI
	BmpManager->AddBitMap(L"../MyResource/UI/HUD_HPBAR.bmp", L"PLAYER_HP_BAR");
	BmpManager->AddBitMap(L"../MyResource/UI/HUD_CUR_HP.bmp", L"PLAYER_CUR_HP");
	BmpManager->AddBitMap(L"../MyResource/UI/HUD_DAMAGED_HP.bmp", L"PLAYER_DAMAGED_HP");
	BmpManager->AddBitMap(L"../MyResource/UI/HUD_LIFE_COUNT.bmp", L"HUD_LIFE_COUNT");
	BmpManager->AddBitMap(L"../MyResource/UI/HUD_WEAPON.bmp", L"PLAYER_WEAPON_ICON");

	// 총알 이미지
	BmpManager->AddBitMap(L"../MyResource/BULLET/BULLET_BUSTER_LARGE_LEFT.bmp", L"BULLET_BLL");
	BmpManager->AddBitMap(L"../MyResource/BULLET/BULLET_BUSTER_LARGE_RIGHT.bmp", L"BULLET_BLR");
	BmpManager->AddBitMap(L"../MyResource/BULLET/BULLET_BUSTER_SMALL_LEFT.bmp", L"BULLET_BSL");
	BmpManager->AddBitMap(L"../MyResource/BULLET/BULLET_BUSTER_SMALL_RIGHT.bmp", L"BULLET_BSR");
	BmpManager->AddBitMap(L"../MyResource/BULLET/BULLET_NORMAL_LEFT.bmp", L"BULLET_NBL");
	BmpManager->AddBitMap(L"../MyResource/BULLET/BULLET_NORMAL_RIGHT.bmp", L"BULLET_NBR");

	//차지 이펙트
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_CHARGE.bmp", L"E_CHARGE");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_CHARGE_BODY.bmp", L"E_CHARGE_BODY");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_CHARGE_GREEN.bmp", L"E_CHARGE_G");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_CHARGE_BODY_GREEN.bmp", L"E_CHARGE_BODY_G");

	// 총알 히트 이펙트
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BULLET_BLOCKED_LEFT.bmp", L"E_BLOCK_L");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BULLET_BLOCKED_RIGHT.bmp", L"E_BLOCK_R");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_NORMAL_BULLET_COLLISION_LEFT.bmp", L"E_NB_HIT_L");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_NORMAL_BULLET_COLLISION_RIGHT.bmp", L"E_NB_HIT_R");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BUSTER_BULLET_COLLISON_LEFT.bmp", L"E_BL_HIT_L");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BUSTER_BULLET_COLLISON_RIGHT.bmp", L"E_BL_HIT_R");

	// 총알 발사 이펙트
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BULLET_NORMAL_LEFT.bmp", L"E_NB_FIRE_L");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BULLET_NORMAL_RIGHT.bmp", L"E_NB_FIRE_R");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BUSTER_SMALL_LEFT.bmp", L"E_BS_FIRE_L");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BUSTER_SMALL_RIGHT.bmp", L"E_BS_FIRE_R");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BUSTER_LARGE_LEFT.bmp", L"E_BL_FIRE_L");
	BmpManager->AddBitMap(L"../MyResource/BULLET/EFFECT_BUSTER_LARGE_RIGHT.bmp", L"E_BL_FIRE_R");

	// 몬스터
	BmpManager->AddBitMap(L"../MyResource/Monster/Monster_Spike_Left.bmp", L"M_SPIKE_L");
	BmpManager->AddBitMap(L"../MyResource/Monster/Monster_Spike_Right.bmp", L"M_SPIKE_R");
	BmpManager->AddBitMap(L"../MyResource/Monster/KnotBeret_LEFT.bmp", L"M_KNOT_BERET_A_L");
	BmpManager->AddBitMap(L"../MyResource/Monster/KnotBeret_RIGHT.bmp", L"M_KNOT_BERET_A_R");

	//보스
	BmpManager->AddBitMap(L"../MyResource/Monster/BOSS_Erigon_LEFT.bmp", L"B_EREGION_L");
	BmpManager->AddBitMap(L"../MyResource/Monster/BOSS_Erigon_RIGHT.bmp", L"B_EREGION_R");

	//폭발 이펙트
	BmpManager->AddBitMap(L"../MyResource/EFFECT/EFFECT_EXPLOSION.bmp", L"E_EXPLOSION");

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
	SoundManager->PlayBGM(L"06_Opening Stage X.mp3");
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
	pHalfDoor->SetIsLeft(true);
	GameManager->AddObject(pHalfDoor, OBJ_GROUND);

	pHalfDoor = CAbstractFactory<CDoor>::CreateObj(2181, 130, L"ST1_HALF_DOOR", 3, 4, 0, 1);
	pHalfDoor->SetIsLeft(true);
	GameManager->AddObject(pHalfDoor, OBJ_GROUND);

	pHalfDoor = CAbstractFactory<CDoor>::CreateObj(2692, 129, L"ST1_HALF_DOOR", 3, 4, 0, 1);
	pHalfDoor->SetIsLeft(true);
	GameManager->AddObject(pHalfDoor, OBJ_GROUND);

	CGameObject* pFullDoor = CAbstractFactory<CDoor>::CreateObj(3215, 110, L"ST1_FULL_DOOR", 3, 4, 0, 1);
	pFullDoor->SetHitBox(40, 150);
	pFullDoor->SetIsLeft(true);
	GameManager->AddObject(pFullDoor, OBJ_GROUND);

	//GameManager->SetScrollX(3700.f);
	//GameManager->SetScrollX(104.f);

	//GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 0, 190 , 3800, BUFCY}), OBJ_GROUND);
	//GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 200,  50, 250, 120}), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 50,  150, 100, 200 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 4900, 100, 5050, 145 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateRectGround(RECT{ 5042, 145, 5080, 257 }), OBJ_GROUND);

	GameManager->AddObject(CAbstractFactory<CGround>::CreateLineGround(POINT{ 0, 190 }, POINT{ 3800, 190 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateLineGround(POINT{ 3800, 190 }, POINT{ 4320, 320 }), OBJ_GROUND);
	GameManager->AddObject(CAbstractFactory<CGround>::CreateLineGround(POINT{ 4320, 320 }, POINT{ 5384, 320 }), OBJ_GROUND);

	//몬스터
	//스파이크
	CGameObject* pMonster = CAbstractFactory<CSpikeMarl>::CreateObj(150.f, 175.f, L"M_SPIKE_R", 3, 7, 0, 5);
	pMonster->SetTarget(GameManager->GetPlayer());
	GameManager->AddObject(pMonster, OBJ_MONSTER);

	//놋베렛
	//CGameObject* pMonster = CAbstractFactory<CKnotBeretA>::CreateObj(150.f, 165.f, L"M_KNOT_BERET_R", 6, 7, 0, 5);
	//pMonster->SetTarget(GameManager->GetPlayer());
	//GameManager->AddObject(pMonster, OBJ_MONSTER);

	//CGameObject* pEffect = CAbstractFactory<CEffect_Explosion>::CreateObj(200.f, 150.f, L"E_EXPLOSION", 17, 18, 0, 1);
	//GameManager->AddObject(pEffect, OBJ_EFFECT);

	//pEffect = CAbstractFactory<CEffect_Explosion>::CreateObj(220.f, 160.f, L"E_EXPLOSION", 17, 18, 0, 1);
	//GameManager->AddObject(pEffect, OBJ_EFFECT);

	//pEffect = CAbstractFactory<CEffect_Explosion>::CreateObj(180.f, 140.f, L"E_EXPLOSION", 17, 18, 0, 1);
	//GameManager->AddObject(pEffect, OBJ_EFFECT);

	CGameObject* pBoss = CAbstractFactory<CEregion>::CreateObj(300, BUFCY / 4, L"B_EREGION_R", 5, 7, 0, 3);
	pBoss->SetTarget(GameManager->GetPlayer());
	GameManager->AddObject(pBoss, OBJ_BOSS);
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
