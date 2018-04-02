#pragma once

class CSoundManager :
	public CSingleton<CSoundManager>
{
public:
	CSoundManager();
	virtual ~CSoundManager();

public:
	enum CHANNEL_ID {BGM, PLAYER, MONSTER, EFFECT, UI, END};

public:
	void Update();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBgm(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();

private:
	void Init();
	void LoadSoundFile();
	void Release();

private:
	//SOUNDMAP m_SoundMap; // 사운드 리소스 관리를 위한 map
	//FMOD_SYSTEM* m_pSystem; //사운드 재생 및 관리를 주도하는 시스템
	//FMOD_CHANNEL* m_pChannel[]; // 사운드 재생을 위한 채널

};

