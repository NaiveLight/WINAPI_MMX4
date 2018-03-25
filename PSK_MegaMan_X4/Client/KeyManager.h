#pragma once

class CKeyManager :
	public CSingleton<CKeyManager>
{
public:
	CKeyManager();
	virtual ~CKeyManager();
};

