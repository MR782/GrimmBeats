#pragma once
//#include"GameObject.h"
#include<memory>

class MemoryFunction {
public:
	template<typename T>
	static void CheckMem(T*);//�������m�ۂł�����
};

template<typename T>
void MemoryFunction::CheckMem(T* obj)
{
	if (obj == nullptr)throw("Object is nullptr");
}
