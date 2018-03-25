#pragma once

// 템플릿 함수들 모음

template <typename T>
void SafeDelete(T& obj)
{
	if (obj != nullptr)
	{
		delete obj;
		obj = nullptr;
	}
}