#pragma once

// ���ø� �Լ��� ����

template <typename T>
void SafeDelete(T& obj)
{
	if (obj != nullptr)
	{
		delete obj;
		obj = nullptr;
	}
}