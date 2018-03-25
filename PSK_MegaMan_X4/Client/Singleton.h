#pragma once

// 모든 매니저에 싱글톤 패턴을 적용시키기 위한 싱글톤 템플릿 클래스

template <typename T>
class CSingleton
{
private:
	static T* m_pInstance;

protected:
	CSingleton() {}
	virtual ~CSingleton() {}

public:
	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T;

		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

template<typename T>
T* CSingleton<T>::m_pInstance = nullptr;

