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
	//SOUNDMAP m_SoundMap; // ���� ���ҽ� ������ ���� map
	//FMOD_SYSTEM* m_pSystem; //���� ��� �� ������ �ֵ��ϴ� �ý���
	//FMOD_CHANNEL* m_pChannel[]; // ���� ����� ���� ä��

};

