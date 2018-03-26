#pragma once

// ��� DEFINE�� ���⿡�� ����

// ������ ������
#define WINCX 1280
#define WINCY 960

#define BUFCX 1280
#define BUFCY 960

// Ÿ�� ������
#define TILECX 64
#define TILECY 64

// Ÿ�� ����
#define TILEX 30
#define TILEY 20

// �Ŵ��� �ν��Ͻ� ��ȯ ��ũ��
#define GameManager CGameManager::GetInstance()
#define KeyManager CKeyManager::GetInstance()
#define SceneManager CSceneManager::GetInstance()
#define BmpManager CBmpManager::GetInstance()
#define SoundManager CSoundManager::GetInstance()