#include "stdafx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager()
{
	Init();
}


CSoundManager::~CSoundManager()
{
	Release();
}

void CSoundManager::Update()
{
	//FMOD_System_Update(m_pSystem);
}

void CSoundManager::PlaySound(const TCHAR * pSoundKey, CHANNEL_ID eID)
{
	//auto iter_find = find_if(m_SoundMap.begin(), m_SoundMap.end(),
	//	[&](auto& MyPair)
	//{
	//	return !lstrcmp(pSoundKey, MyPair.first);
	//});

	//if (iter_find == m_SoundMap.end())
	//{
	//	// can't found sound
	//	return;
	//}

	//FMOD_System_PlaySound();
}

void CSoundManager::PlayBgm(const TCHAR * pSoundKey)
{
}

void CSoundManager::StopSound(CHANNEL_ID eID)
{
}

void CSoundManager::StopAll()
{
}

void CSoundManager::Init()
{
	//FMOD_System_Create(&m_pSystem); //시스템 할당
	//FMOD_System_Init(m_pSystem, CHANNEL_ID::END, FMOD_INIT_NORMAL, nullptr); // 시스템 초기화
	//LoadSoundFile();
}

void CSoundManager::LoadSoundFile()
{
	//_finddate_t fd;
	//int iResult = 0;
	//long handle = _findfirst("../Sound/*.*", &fd);

	//if (0 == handle)
	//{
	//	return;
	//}

	//while (iResult != -1)
	//{
	//	char szFullPath[128] = "../Sound/";
	//	strcat_s(szFullPath, fd.name);

	//	FMOD_SOUND* pSound = nullptr;

	//	FMOD_RESULT res =	FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, );

	//	if (res = FMOD_OK)
	//	{
	//		m_SoundMap.insert({ __TEXT( fd.name), pSound });
	//	}

	//	iResult = _findnext(handle, &fd);
	//}

	//FMOD_System_Update(m_pSystem);
}

void CSoundManager::Release()
{
	//for (auto& pSound : m_SoundMap)
	//{
	//	delete[] pSound.first;
	//	FMOD_Sound_Release(pSound.second);
	//}
}
