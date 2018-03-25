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
	// x�� ����
	// �ִϸ��̼� ���� �����Ӻ��� ������ �����ӱ���
	int iStart;
	int iEnd;

	// y�� ����
	// ���¿� ���� �ִϸ��̼� ����
	int iScene;

	// ������ ��ȯ�� �ð���
	DWORD dwTime;
	// �ִϸ��̼� ��� �ӵ�
	DWORD dwSpeed;
}FRAME;