// Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Client.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND g_hWnd;
DWORD g_iFrame;
LONG g_lWINCX;
LONG g_lWINCY;
int g_iBufCX;
int g_iBufCY;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void SetBufSize(int& iBufCX, int& iBufCY);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	g_lWINCX = 1240;
	g_lWINCY = 960;

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	MSG msg;
	msg.message = WM_NULL;

	DWORD dwOldTime = GetTickCount();
	g_iFrame = 0;

	CMainGame mainGame;
	mainGame.Init();
	mainGame.LateInit();

	// FPS 계산해보기!
	int iFPS = 0;
	TCHAR szFPS[32] = L"";

	DWORD dwFpsTime = GetTickCount();

	while (msg.message != WM_QUIT)
	{
		RECT rcWnd = {};
		GetClientRect(g_hWnd, &rcWnd);

		if (rcWnd.right - rcWnd.left != g_lWINCX ||
			rcWnd.bottom - rcWnd.top != g_lWINCY)
		{
			g_lWINCX = rcWnd.right - rcWnd.left;
			g_lWINCY = rcWnd.bottom - rcWnd.top;

			SetWindowPos(g_hWnd, g_hWnd, rcWnd.left, rcWnd.top, g_lWINCX, g_lWINCY, SWP_DRAWFRAME);
		}

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (dwOldTime + 10 < GetTickCount())
			{
				mainGame.Update();
				mainGame.LateUpdate();
				mainGame.Render();

				dwOldTime = GetTickCount();
				++g_iFrame;
				++iFPS;
			}


			// FPS 출력
			if (dwFpsTime + 1000 < GetTickCount())
			{
				swprintf_s(szFPS, L"FPS: %d", iFPS);

				// SetWindowText: 윈도우의 타이틀바에 문자열을 출력하는 함수
				SetWindowText(g_hWnd, szFPS);

				iFPS = 0;
				dwFpsTime = GetTickCount();
			}
		}
	}

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //RECT rc = { 0, 0, WINCX, WINCY };
   RECT rc = { 0, 0, g_lWINCX, g_lWINCY};

   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

   HWND hWnd = CreateWindowW(szWindowClass, L"MMX4", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(g_hWnd);
			break;
		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void SetBufSize(int & iBufCX, int & iBufCY)
{
}
