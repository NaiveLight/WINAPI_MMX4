#pragma once
class CMainGame
{
	// ���� Init�� ����ۿ� ȭ�� ��ȯ�� ������ ��� ��� ��Ʈ�� �Ŵ����� ���
	// Ÿ��Ʋ ������ ��ȯ �� �� �Ŵ����� �Է� �Ŵ��� �׸���  ������ ��������.
	// Alt+F4 ���� �� Ŭ���̾�Ʈ ����
	// �� �� �����Ҷ����� �ε��ʿ�

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