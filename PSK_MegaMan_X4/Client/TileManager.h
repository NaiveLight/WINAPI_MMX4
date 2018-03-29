#pragma once
#include "Singleton.h"
class CTileManager :
	public CSingleton<CTileManager>
{
public:
	enum TILE {DEFAULT, };
public:
	CTileManager();
	virtual ~CTileManager();
};

