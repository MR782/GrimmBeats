#pragma once
//#include"GameObject.h"
#include<memory>

class MemoryFunction {
public:
	template<typename T>
	static void CheckMem(T*);//メモリ確保できたか
};

template<typename T>
void MemoryFunction::CheckMem(T* obj)
{
	if (obj == nullptr)throw("Object is nullptr");
}
