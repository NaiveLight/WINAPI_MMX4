#pragma once

class CSoundManager
	:public CSingleton<CSoundManager>
{
public:
	enum CHANNEL_ID { BGM, PLAYER, MONSTER, EFFECT, UI, END };

public:
	CSoundManager();
	~CSoundManager();

public:
	void Init();
	void Update();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void PauseSound(CHANNEL_ID eID, BOOL bPause = TRUE);
	void PauseAll(CHANNEL_ID eID, BOOL bPause = TRUE);

private:
	void Release();
	void LoadSoundFile();


private:
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;	// ���� ���ҽ� ������ ���� map
	FMOD_SYSTEM*	m_pSystem;			// ���� ��� �� ������ �ֵ��ϴ� �ý���
	FMOD_CHANNEL*	m_pChannel[END];	// ���� ����� ���� ä��
};
