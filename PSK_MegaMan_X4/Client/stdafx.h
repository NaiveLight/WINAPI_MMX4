// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

//#include <iostream>
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ctime>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

#include <vld.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Define.h"
#include "Extern.h"
#include "Enum.h"
#include "Function.h"
#include "Struct.h"
#include "Typedef.h"

#include "AbstractFactory.h"
#include "Singleton.h"
#include "GameManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "BmpManager.h"
#include "SoundManager.h"
#include "Collision.h"
