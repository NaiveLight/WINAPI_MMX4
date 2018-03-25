#pragma once

typedef struct tagInfo
{
	// position
	float fX;
	float fY;

	// size
	float fCX;
	float fCY;
}INFO;

typedef struct tagFrame
{
	// x축 기준
	// 애니메이션 시작 프레임부터 마지막 프레임까지
	int iStart;
	int iEnd;

	// y축 기중
	// 상태에 따른 애니메이션 변경
	int iScene;

	// 프레임 변환한 시간값
	DWORD dwTime;
	// 애니메이션 재생 속도
	DWORD dwSpeed;
}FRAME;