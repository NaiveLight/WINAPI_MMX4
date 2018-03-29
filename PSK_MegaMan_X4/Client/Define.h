#pragma once

// 모든 DEFINE은 여기에서 관리

// 윈도우 사이즈
#define WINCX 1280
#define WINCY 960

#define BUFCX 320
#define BUFCY 240

// 타일 사이즈
#define TILECX 64
#define TILECY 64

// 타일 갯수
#define TILEX 30
#define TILEY 20

// 매니저 인스턴스 반환 매크로
#define GameManager CGameManager::GetInstance()
#define KeyManager CKeyManager::GetInstance()
#define SceneManager CSceneManager::GetInstance()
#define BmpManager CBmpManager::GetInstance()
#define SoundManager CSoundManager::GetInstance()