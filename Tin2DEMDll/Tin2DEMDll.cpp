// Tin2DEMDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Tin2DEMDll.h"


// 这是导出变量的一个示例
TIN2DEMDLL_API int nTin2DEMDll=0;

// 这是导出函数的一个示例。
TIN2DEMDLL_API int fnTin2DEMDll(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Tin2DEMDll.h
CTin2DEMDll::CTin2DEMDll()
{
    return;
}
