#pragma once

#define VIRTUAL_KEY 0xff

class CKeyManager :
	public CSingleton<CKeyManager>
{
private:
	bool m_bKey[VIRTUAL_KEY];

public:
	CKeyManager();
	virtual ~CKeyManager();

public:
	bool KeyPressing(int iVKey);
	bool KeyDown(int iVKey);
	bool KeyUp(int iVKey);
	void Update();
};

