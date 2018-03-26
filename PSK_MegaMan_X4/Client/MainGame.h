#pragma once
class CMainGame
{
	// 최초 Init시 백버퍼와 화면 전환용 검은색 흰색 배경 비트맵 매니저에 등록
	// 타이틀 씬으로 전환 및 씬 매니저와 입력 매니저 그리고  루프를 돌려야함.
	// Alt+F4 누를 시 클라이언트 종료
	// 각 씬 진입할때마다 로딩필요

public:
	CMainGame();
	~CMainGame();

public:
	void Init();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	void ResetMainDC();

private:
	HDC m_hDC;
}; 